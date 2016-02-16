#include "Common.h"


#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <glib.h>

using namespace cv;



// Resolution
#define W 1280
#define H 720


struct CaptureData {
  ovrPosef pose;
  cv::Mat image;
};


//Übernimmt das Empfangen des Kamerastreams und stellt die Bilder zur Verfügung
class WebcamHandler {

private:

  bool hasFrame{ false };
  bool stopped{ false }; 
  cv::VideoCapture videoCapture;
  std::thread captureThread;
  std::mutex mutex;
  CaptureData frame;
  ovrHmd hmd;
  GstAppSink *appsink1;
public:

  WebcamHandler(ovrHmd & hmd) : hmd(hmd) {
  }


  float startCaptureGstreamer(){
	  GstElement *pipeline, *videosrc, *conv, *dec, *pay, *udp, *appsink;

	  // init GStreamer
	  gst_init(NULL, NULL);

	  // setup pipeline
	  pipeline = gst_pipeline_new("pipeline");

	  videosrc = gst_element_factory_make("udpsrc", "source"); //UDPsrc als Source
	  g_object_set(G_OBJECT(videosrc), "port", 5000, NULL); // Setzt Port auf 5000
	  g_object_set(G_OBJECT(videosrc), "caps", gst_caps_from_string("application/x-rtp, payload=96"), NULL);
	  //videosrc = gst_element_factory_make("videotestsrc", "source");

	  pay = gst_element_factory_make("rtph264depay", "pay"); // Fügt die RTP Pakete wirder zusammen

	  dec = gst_element_factory_make("avdec_h264", "dec"); //h264 Decoder

	  conv = gst_element_factory_make("videoconvert", "conv");

	  appsink = gst_element_factory_make("appsink", "sink");
	  g_object_set(G_OBJECT(appsink), "sync", true, NULL);
	  g_object_set(G_OBJECT(appsink), "name", "sink", NULL);

	  gst_bin_add_many(GST_BIN(pipeline), videosrc, pay, dec, conv, appsink, NULL);

	  if (gst_element_link_many(videosrc, pay, dec, conv, appsink, NULL) != TRUE)
	  {
		  g_printerr("Elements could not be linked.\n");
		  return -1;
	  }
	  g_print("Pipeline erstellt\n");

	  /* get sink */
	  GstElement *sink = gst_bin_get_by_name(GST_BIN(pipeline), "sink");

	  gst_app_sink_set_emit_signals((GstAppSink*)sink, true);
	  gst_app_sink_set_drop((GstAppSink*)sink, true);
	  gst_app_sink_set_max_buffers((GstAppSink*)sink, 1);

	  GstBus *bus;
	  guint bus_watch_id;
	  bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
	  gst_object_unref(bus);


	  appsink1 = (GstAppSink *)sink;
	  gst_app_sink_set_max_buffers(appsink1, 2); // limit number of buffers queued
	  gst_app_sink_set_drop(appsink1, true);	// drop old buffers in queue when full


	  // play
	  gst_element_set_state(pipeline, GST_STATE_PLAYING);
	  float aspect;
	  bool gotFrame = false;
	  while (!gotFrame) //Empfang 1 Bild um Informationen zu erhalten
		  if (!gst_app_sink_is_eos(appsink1)){
			  GstSample *sample = gst_app_sink_pull_sample(appsink1);
			  GstCaps *caps = gst_sample_get_caps(sample);
			  GstBuffer *buffer = gst_sample_get_buffer(sample);
			  const GstStructure *info = gst_sample_get_info(sample);

			  // ---- Read frame and convert to opencv format ---------------

			  GstMapInfo map;
			  gst_buffer_map(buffer, &map, GST_MAP_READ);

			  Mat yuv(Size(W, H + H / 2), CV_8U, map.data); //640,480+240
			  //printf(" got buffer: size = %d, data=0x%p\n", size, data );

			  Mat frame;
			  cvtColor(yuv, frame, CV_YUV2BGR_IYUV);

			  aspect = (float)frame.cols / (float)frame.rows;
			  gotFrame = true;
		  }

	  captureThread = std::thread(&WebcamHandler::captureLoopGstreamer, this); //Startet einen Thread der kontinuierlich Bilder empfängt und bereitstellt
	  return aspect;
  }

  // Spawn capture thread and return webcam aspect ratio (width over height)
  float startCapture() {
    videoCapture.open(1);
    if (!videoCapture.isOpened()
      || !videoCapture.read(frame.image)) {
      FAIL("Could not open video source to capture first frame");
    }
    float aspectRatio = (float)frame.image.cols / (float)frame.image.rows;
    captureThread = std::thread(&WebcamHandler::captureLoop, this);
    return aspectRatio;
  }

  void stopCapture() {
    stopped = true;
    captureThread.join();
    videoCapture.release();
  }

  void set(const CaptureData & newFrame) {
    std::lock_guard<std::mutex> guard(mutex);
    frame = newFrame;
    hasFrame = true;
  }

  bool get(CaptureData & out) {
    if (!hasFrame) {
      return false;
    }
    std::lock_guard<std::mutex> guard(mutex);
    out = frame;
    hasFrame = false;
    return true;
  }

  void captureLoop() {
	  CaptureData captured;
	  while (!stopped) {
		  float captureTime = ovr_GetTimeInSeconds();
		  ovrTrackingState tracking = ovrHmd_GetTrackingState(hmd, captureTime);
		  captured.pose = tracking.HeadPose.ThePose;

		  videoCapture.read(captured.image);
		  cv::flip(captured.image.clone(), captured.image, 0);
		  set(captured);
	  }
  }
	void captureLoopGstreamer() { //Empfängt kontinuierlich Bilder und stellt sie bereit
		CaptureData captured;
		while (!stopped) {
			float captureTime = ovr_GetTimeInSeconds();

			//Orientierung der Oculus Rift lesen und zu dem Frame speichern
			ovrTrackingState tracking = ovrHmd_GetTrackingState(hmd, captureTime); 
			captured.pose = tracking.HeadPose.ThePose;

			if (!gst_app_sink_is_eos(appsink1)){
				GstSample *sample = gst_app_sink_pull_sample(appsink1);
				
				GstCaps *caps = gst_sample_get_caps(sample);
				GstBuffer *buffer = gst_sample_get_buffer(sample);
				//const GstStructure *info = gst_sample_get_info(sample);
				
				// ---- Read frame and convert to opencv format ---------------

				GstMapInfo map;
				gst_buffer_map(buffer, &map, GST_MAP_READ);
				
				//Gstreamer Format zu OpenCV Format konvertieren
				Mat yuv(Size(W, H + H / 2), CV_8U, map.data); 
				Mat frame;
				cvtColor(yuv, frame, CV_YUV2BGR_IYUV);

				printf(gst_caps_to_string(caps));

				//Frame anzeigen um außerhalb des HMDs sichtbar zu sein
				imshow("Test", frame);
				waitKey(1);

				captured.image = frame;
				cv::flip(frame.clone(), captured.image, 0);
				set(captured);
				gst_sample_unref(sample);
				gst_buffer_unmap(buffer,&map);
				gst_object_unref(caps);
			}
		}
  }
};

class WebcamApp : public RiftApp {

protected:

  TexturePtr texture;
  ProgramPtr program;
  ShapeWrapperPtr videoGeometry;
  WebcamHandler captureHandler;
  CaptureData captureData;

public:

  WebcamApp() : captureHandler(hmd) {
  }

  virtual ~WebcamApp() {
    captureHandler.stopCapture();
  }

  //OpenGL Anwendung initialisieren
  void initGl() {
    RiftApp::initGl();
    using namespace oglplus;
    texture = TexturePtr(new Texture());
    Context::Bound(TextureTarget::_2D, *texture)
      .MagFilter(TextureMagFilter::Linear)
      .MinFilter(TextureMinFilter::Linear);
    program = oria::loadProgram(Resource::SHADERS_TEXTURED_VS, Resource::SHADERS_TEXTURED_FS);
    float aspectRatio = captureHandler.startCaptureGstreamer();
    videoGeometry = oria::loadPlane(program, aspectRatio);
  }

  virtual void update() {
	  //Wenn neues Bild der Kamera bereit ist dann änder die Textur zu dem neuen Bild
    if (captureHandler.get(captureData)) {
      using namespace oglplus;
      Context::Bound(TextureTarget::_2D, *texture)
        .Image2D(0, PixelDataInternalFormat::RGBA8,
        captureData.image.cols, captureData.image.rows, 0,
        PixelDataFormat::BGR, PixelDataType::UnsignedByte,
        captureData.image.data);
    }
  }

  virtual void renderScene() {
    glClear(GL_DEPTH_BUFFER_BIT);
    oria::renderSkybox(Resource::IMAGES_SKY_CITY_XNEG_PNG);
    MatrixStack & mv = Stacks::modelview();

    mv.withPush([&] {
      glm::quat eyePose = ovr::toGlm(getEyePose().Orientation);
      glm::quat webcamPose = ovr::toGlm(captureData.pose.Orientation);
      glm::mat4 webcamDelta = glm::mat4_cast(glm::inverse(eyePose) * webcamPose);

      mv.identity();
      mv.preMultiply(webcamDelta);

      mv.translate(glm::vec3(0, 0, -2));
      using namespace oglplus;
      texture->Bind(TextureTarget::_2D);
      oria::renderGeometry(videoGeometry, program);
      oglplus::DefaultTexture().Bind(TextureTarget::_2D);
    });
  }
};

RUN_OVR_APP(WebcamApp);
