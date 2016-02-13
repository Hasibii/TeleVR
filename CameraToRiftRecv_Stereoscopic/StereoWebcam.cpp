#include "Common.h"


#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <glib.h>

using namespace cv;

#define W 1280
#define H 720

#pragma region GstreamerSBS_1_Notworking
//struct CaptureData {
//	ovrPosef pose;
//	cv::Mat imageLeft;
//	cv::Mat imageRight;
//};
//
//class WebcamHandler {
//
//private:
//
//	bool hasFrame{ false };
//	bool stopped{ false };
//	std::thread captureThread;
//	std::mutex mutex;
//	CaptureData frame;
//	ovrHmd hmd;
//	GstAppSink *appsink1;
//public:
//
//	WebcamHandler(){
//	}
//
//
//	float startCaptureGstreamer(ovrHmd & hmdRef){
//		hmd = hmdRef;
//		GstElement *pipeline, *videosrc, *conv, *dec, *pay, *udp, *appsink;
//
//		// init GStreamer
//		gst_init(NULL, NULL);
//
//		// setup pipeline
//		pipeline = gst_pipeline_new("pipeline");
//
//		videosrc = gst_element_factory_make("udpsrc", "source");
//		g_object_set(G_OBJECT(videosrc), "port", 5000, NULL);
//		g_object_set(G_OBJECT(videosrc), "caps", gst_caps_from_string("application/x-rtp, payload=96"), NULL);
//
//
//		pay = gst_element_factory_make("rtph264depay", "pay");
//
//		dec = gst_element_factory_make("avdec_h264", "dec");
//
//		conv = gst_element_factory_make("videoconvert", "conv");
//
//		appsink = gst_element_factory_make("appsink", "sink");
//		g_object_set(G_OBJECT(appsink), "sync", true, NULL);
//		g_object_set(G_OBJECT(appsink), "name", "sink", NULL);
//
//		gst_bin_add_many(GST_BIN(pipeline), videosrc, pay, dec, conv, appsink, NULL);
//
//		if (gst_element_link_many(videosrc, pay, dec, conv, appsink, NULL) != TRUE)
//		{
//			g_printerr("Elements could not be linked.\n");
//			return -1;
//		}
//		g_print("Pipeline erstellt\n");
//		//if (!pipeline || !videosrc || !pay || !dec || !conv || !sink) {
//		//	g_printerr("Not all elements could be created.\n");
//		//	return -1;
//		//}
//
//		/* get sink */
//		GstElement *sink = gst_bin_get_by_name(GST_BIN(pipeline), "sink");
//
//		gst_app_sink_set_emit_signals((GstAppSink*)sink, true);
//		gst_app_sink_set_drop((GstAppSink*)sink, true);
//		gst_app_sink_set_max_buffers((GstAppSink*)sink, 1);
//
//		GstBus *bus;
//		guint bus_watch_id;
//		bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
//		gst_object_unref(bus);
//
//
//		appsink1 = (GstAppSink *)sink;
//		gst_app_sink_set_max_buffers(appsink1, 2); // limit number of buffers queued
//		gst_app_sink_set_drop(appsink1, true);	// drop old buffers in queue when full
//
//
//		// play
//		gst_element_set_state(pipeline, GST_STATE_PLAYING);
//
//
//		float aspect;
//		bool gotFrame = false;
//		while (!gotFrame)
//			if (!gst_app_sink_is_eos(appsink1)){
//				GstSample *sample = gst_app_sink_pull_sample(appsink1);
//				GstCaps *caps = gst_sample_get_caps(sample);
//				GstBuffer *buffer = gst_sample_get_buffer(sample);
//				const GstStructure *info = gst_sample_get_info(sample);
//
//				// ---- Read frame and convert to opencv format ---------------
//
//				GstMapInfo map;
//				gst_buffer_map(buffer, &map, GST_MAP_READ);
//
//				Mat yuv(Size(W, H + H / 2), CV_8U, map.data); //640,480+240
//				//printf(" got buffer: size = %d, data=0x%p\n", size, data );
//
//				Mat frame1;
//				cvtColor(yuv, frame1, CV_YUV2BGR_IYUV);
//				Mat Left, Right;
//				Rect RLeft(0, 0, W / 2, H);
//				Rect RRight(W / 2, 0, W / 2, H);
//				Left = frame1(RLeft);
//				Right = frame1(RRight);
//
//				aspect = (float)Left.cols / (float)Left.rows;
//				gotFrame = true;
//			}
//
//
//		captureThread = std::thread(&WebcamHandler::captureLoopGstreamer, this);
//		Platform::sleepMillis(200);
//		return aspect;
//	}
//
//
//
//	void stopCapture() {
//		stopped = true;
//		captureThread.join();
//	}
//
//	void set(const CaptureData & newFrame) {
//		std::lock_guard<std::mutex> guard(mutex);
//		frame = newFrame;
//		hasFrame = true;
//	}
//
//	bool get(CaptureData & out) {
//		if (!hasFrame) {
//			return false;
//		}
//		std::lock_guard<std::mutex> guard(mutex);
//		out = frame;
//		hasFrame = false;
//		return true;
//	}
//
//	void captureLoopGstreamer() {
//		CaptureData captured;
//		while (!stopped) {
//			if (!gst_app_sink_is_eos(appsink1)){
//				float captureTime = ovr_GetTimeInSeconds();
//				ovrTrackingState tracking = ovrHmd_GetTrackingState(hmd, captureTime);
//				captured.pose = tracking.HeadPose.ThePose;
//				GstSample *sample = gst_app_sink_pull_sample(appsink1);
//				GstCaps *caps = gst_sample_get_caps(sample);
//				GstBuffer *buffer = gst_sample_get_buffer(sample);
//				const GstStructure *info = gst_sample_get_info(sample);
//
//				// ---- Read frame and convert to opencv format ---------------
//
//				GstMapInfo map;
//				gst_buffer_map(buffer, &map, GST_MAP_READ);
//
//				Mat yuv(Size(W, H + H / 2), CV_8U, map.data); //640,480+240
//				//printf(" got buffer: size = %d, data=0x%p\n", size, data );
//
//				Mat frame1;
//				cvtColor(yuv, frame1, CV_YUV2BGR_IYUV);
//
//
//				Mat Left, Right;
//				Rect RLeft(0, 0, W / 2, H);
//				Rect RRight(W / 2, 0, W / 2, H);
//				Left = frame1(RLeft);
//				Right = frame1(RRight);
//				//imshow("left", Left);
//				//imshow("right", Right);
//				//cv::waitKey(10);
//				gst_buffer_unref(buffer);
//
//				captured.imageLeft = Left;
//				captured.imageRight = Right;
//				cv::flip(captured.imageLeft.clone(), captured.imageLeft, 0);
//				cv::flip(captured.imageRight.clone(), captured.imageRight, 0);
//				set(captured);
//			}
//		}
//	}
//};
//
//class WebcamApp : public RiftApp {
//
//protected:
//
//  ProgramPtr program;
//  TexturePtr texture[2];
//  ShapeWrapperPtr videoGeometry[2];
//  WebcamHandler captureHandler;
//  CaptureData captureData;
//
//public:
//
//	WebcamApp() {
//	}
//
//
//  virtual ~WebcamApp() {
//
//      captureHandler.stopCapture();
//    
//  }
//
//  void initGl() {
//    RiftApp::initGl();
//    using namespace oglplus;
//
//    program = oria::loadProgram(Resource::SHADERS_TEXTURED_VS, Resource::SHADERS_TEXTURED_FS);
//
//	float aspect = captureHandler.startCaptureGstreamer(hmd);
//	aspect = 16 / 9;
//    for (int i = 0; i < 2; i++) {
//      texture[i] = TexturePtr(new Texture());
//      Context::Bound(TextureTarget::_2D, *texture[i])
//        .MagFilter(TextureMagFilter::Linear)
//        .MinFilter(TextureMinFilter::Linear);
//      program = oria::loadProgram(Resource::SHADERS_TEXTURED_VS, Resource::SHADERS_TEXTURED_FS);
//     // float aspect = captureHandler[i].startCapture(hmd, CAMERA_FOR_EYE[i]);
//      videoGeometry[i] = oria::loadPlane(program, aspect);
//    }
//  }
//
//  virtual void update() {
//	if (captureHandler.get(captureData)) {
//		
//        using namespace oglplus;
//        Context::Bound(TextureTarget::_2D, *texture[0])
//          .Image2D(0, PixelDataInternalFormat::RGBA8,
//		  captureData.imageLeft.cols, captureData.imageLeft.rows, 0,
//          PixelDataFormat::BGR, PixelDataType::UnsignedByte,
//		  captureData.imageLeft.data);
//
//		Context::Bound(TextureTarget::_2D, *texture[1])
//			.Image2D(0, PixelDataInternalFormat::RGBA8,
//			captureData.imageRight.cols, captureData.imageRight.rows, 0,
//			PixelDataFormat::BGR, PixelDataType::UnsignedByte,
//			captureData.imageRight.data);
//      
//    }
//  }
//
//  virtual void renderScene() {
//    using namespace oglplus;
//    glClear(GL_DEPTH_BUFFER_BIT);
//    oria::renderSkybox(Resource::IMAGES_SKY_CITY_XNEG_PNG);
//    MatrixStack & mv = Stacks::modelview();
//
//    mv.withPush([&] {
//      glm::quat eyePose = ovr::toGlm(getEyePose().Orientation);
//      glm::quat webcamPose = ovr::toGlm(captureData.pose.Orientation);
//      glm::mat4 webcamDelta = glm::mat4_cast(glm::inverse(eyePose) * webcamPose);
//
//      mv.identity();
//      mv.preMultiply(webcamDelta);
//	  
//      mv.translate(glm::vec3(0, 0, -2.75));
//      texture[getCurrentEye()]->Bind(TextureTarget::_2D); 
//      oria::renderGeometry(videoGeometry[getCurrentEye()], program);
//    });
//    oglplus::DefaultTexture().Bind(TextureTarget::_2D);
//  }
//};
//
//RUN_OVR_APP(WebcamApp);

#pragma endregion


#pragma region GStreamer_2_Working
////2x Gstreamer Working!
//int CAMERA_FOR_EYE[2] = { 2, 1 };
//
//struct CaptureData {
//	ovrPosef pose;
//	cv::Mat image;
//};
//
//class WebcamHandler {
//
//private:
//
//	bool hasFrame{ false };
//	bool stopped{ false };
//	cv::VideoCapture videoCapture;
//	std::thread captureThread;
//	std::mutex mutex;
//	CaptureData frame;
//	ovrHmd hmd;
//	GstAppSink *appsink1;
//
//public:
//
//	WebcamHandler() {
//	}
//
//	// Spawn capture thread and return webcam aspect ratio (width over height)
//	float startCapture(ovrHmd & hmdRef, int which) {
//		hmd = hmdRef;
//		GstElement *pipeline, *videosrc, *conv, *dec, *pay, *udp, *appsink;
//		
//		// init GStreamer
//		gst_init(NULL, NULL);
//		
//		// setup pipeline
//		pipeline = gst_pipeline_new("pipeline");
//		
//		videosrc = gst_element_factory_make("udpsrc", "source");
//		g_object_set(G_OBJECT(videosrc), "port", 5000+which-1, NULL);
//		g_object_set(G_OBJECT(videosrc), "caps", gst_caps_from_string("application/x-rtp, payload=96"), NULL);
//		
//		
//		pay = gst_element_factory_make("rtph264depay", "pay");
//		
//		dec = gst_element_factory_make("avdec_h264", "dec");
//		
//		conv = gst_element_factory_make("videoconvert", "conv");
//		
//		appsink = gst_element_factory_make("appsink", "sink");
//		g_object_set(G_OBJECT(appsink), "sync", true, NULL);
//		g_object_set(G_OBJECT(appsink), "name", "sink", NULL);
//		
//		gst_bin_add_many(GST_BIN(pipeline), videosrc, pay, dec, conv, appsink, NULL);
//		
//		if (gst_element_link_many(videosrc, pay, dec, conv, appsink, NULL) != TRUE)
//		{
//			g_printerr("Elements could not be linked.\n");
//			return -1;
//		}
//		g_print("Pipeline erstellt\n");
//		//if (!pipeline || !videosrc || !pay || !dec || !conv || !sink) {
//		//	g_printerr("Not all elements could be created.\n");
//		//	return -1;
//		//}
//		
//		/* get sink */
//		GstElement *sink = gst_bin_get_by_name(GST_BIN(pipeline), "sink");
//		
//		gst_app_sink_set_emit_signals((GstAppSink*)sink, true);
//		gst_app_sink_set_drop((GstAppSink*)sink, true);
//		gst_app_sink_set_max_buffers((GstAppSink*)sink, 1);
//		
//		GstBus *bus;
//		guint bus_watch_id;
//		bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
//		gst_object_unref(bus);
//		
//		
//		appsink1 = (GstAppSink *)sink;
//		gst_app_sink_set_max_buffers(appsink1, 2); // limit number of buffers queued
//		gst_app_sink_set_drop(appsink1, true);	// drop old buffers in queue when full
//		
//		
//		// play
//		gst_element_set_state(pipeline, GST_STATE_PLAYING);
//		
//		
//		float aspect;
//		bool gotFrame = false;
//		while (!gotFrame)
//			if (!gst_app_sink_is_eos(appsink1)){
//				GstSample *sample = gst_app_sink_pull_sample(appsink1);
//				GstCaps *caps = gst_sample_get_caps(sample);
//				GstBuffer *buffer = gst_sample_get_buffer(sample);
//				const GstStructure *info = gst_sample_get_info(sample);
//		
//				// ---- Read frame and convert to opencv format ---------------
//		
//				GstMapInfo map;
//				gst_buffer_map(buffer, &map, GST_MAP_READ);
//		
//				Mat yuv(Size(W, H + H / 2), CV_8U, map.data); //640,480+240
//				//printf(" got buffer: size = %d, data=0x%p\n", size, data );
//		
//				Mat frame1;
//				cvtColor(yuv, frame1, CV_YUV2BGR_IYUV);
//
//				aspect = (float)frame1.cols / (float)frame1.rows;
//				gotFrame = true;
//			}
//		
//		
//		captureThread = std::thread(&WebcamHandler::captureLoop, this);
//		Platform::sleepMillis(200);
//		return aspect;
//	}
//
//	void stopCapture() {
//		stopped = true;
//		captureThread.join();
//		videoCapture.release();
//	}
//
//	void set(const CaptureData & newFrame) {
//		std::lock_guard<std::mutex> guard(mutex);
//		frame = newFrame;
//		hasFrame = true;
//	}
//
//	bool get(CaptureData & out) {
//		if (!hasFrame) {
//			return false;
//		}
//		std::lock_guard<std::mutex> guard(mutex);
//		out = frame;
//		hasFrame = false;
//		return true;
//	}
//
//	void captureLoop() {
//		CaptureData captured;
//		while (!stopped) {
//			if (!gst_app_sink_is_eos(appsink1)){
//				float captureTime = ovr_GetTimeInSeconds();
//				ovrTrackingState tracking = ovrHmd_GetTrackingState(hmd, captureTime);
//				captured.pose = tracking.HeadPose.ThePose;
//				GstSample *sample = gst_app_sink_pull_sample(appsink1);
//				GstCaps *caps = gst_sample_get_caps(sample);
//				GstBuffer *buffer = gst_sample_get_buffer(sample);
//				const GstStructure *info = gst_sample_get_info(sample);
//		
//				// ---- Read frame and convert to opencv format ---------------
//		
//				GstMapInfo map;
//				gst_buffer_map(buffer, &map, GST_MAP_READ);
//		
//				Mat yuv(Size(W, H + H / 2), CV_8U, map.data); //640,480+240
//				//printf(" got buffer: size = %d, data=0x%p\n", size, data );
//		
//				Mat frame1;
//				cvtColor(yuv, frame1, CV_YUV2BGR_IYUV);
//		
//	
//				gst_buffer_unref(buffer);
//		
//
//				captured.image = frame1;
//				cv::flip(captured.image.clone(), captured.image, 0);
//				set(captured);
//				//delete sample;
//				//delete caps;
//				//delete buffer;
//				//delete info;
//			}
//		}
//	}
//};
//
//class WebcamApp : public RiftApp {
//
//protected:
//
//	ProgramPtr program;
//	TexturePtr texture[2];
//	ShapeWrapperPtr videoGeometry[2];
//	WebcamHandler captureHandler[2];
//	CaptureData captureData[2];
//
//public:
//
//	WebcamApp() {
//	}
//
//	virtual ~WebcamApp() {
//		for (int i = 0; i < 2; i++) {
//			captureHandler[i].stopCapture();
//		}
//	}
//
//	void initGl() {
//		RiftApp::initGl();
//		using namespace oglplus;
//
//		program = oria::loadProgram(Resource::SHADERS_TEXTURED_VS, Resource::SHADERS_TEXTURED_FS);
//
//		for (int i = 0; i < 2; i++) {
//			texture[i] = TexturePtr(new Texture());
//			Context::Bound(TextureTarget::_2D, *texture[i])
//				.MagFilter(TextureMagFilter::Linear)
//				.MinFilter(TextureMinFilter::Linear);
//			program = oria::loadProgram(Resource::SHADERS_TEXTURED_VS, Resource::SHADERS_TEXTURED_FS);
//			float aspect = captureHandler[i].startCapture(hmd, CAMERA_FOR_EYE[i]);
//			videoGeometry[i] = oria::loadPlane(program, aspect);
//		}
//	}
//
//	virtual void update() {
//		for (int i = 0; i < 2; i++) {
//			if (captureHandler[i].get(captureData[i])) {
//				using namespace oglplus;
//				Context::Bound(TextureTarget::_2D, *texture[i])
//					.Image2D(0, PixelDataInternalFormat::RGBA8,
//					captureData[i].image.cols, captureData[i].image.rows, 0,
//					PixelDataFormat::BGR, PixelDataType::UnsignedByte,
//					captureData[i].image.data);
//			}
//		}
//	}
//
//	virtual void renderScene() {
//		using namespace oglplus;
//		glClear(GL_DEPTH_BUFFER_BIT);
//		oria::renderSkybox(Resource::IMAGES_SKY_CITY_XNEG_PNG);
//		MatrixStack & mv = Stacks::modelview();
//
//		mv.withPush([&] {
//			glm::quat eyePose = ovr::toGlm(getEyePose().Orientation);
//			glm::quat webcamPose = ovr::toGlm(captureData[getCurrentEye()].pose.Orientation);
//			glm::mat4 webcamDelta = glm::mat4_cast(glm::inverse(eyePose) * webcamPose);
//
//			mv.identity();
//			mv.preMultiply(webcamDelta);
//
//			mv.translate(glm::vec3(0, 0, -2.75));
//			texture[getCurrentEye()]->Bind(TextureTarget::_2D);
//			oria::renderGeometry(videoGeometry[getCurrentEye()], program);
//		});
//		oglplus::DefaultTexture().Bind(TextureTarget::_2D);
//	}
//};
//
//RUN_OVR_APP(WebcamApp);

#pragma endregion


#pragma region Gstreamer_1_2Threads

//2x Gstreamer Working!
int CAMERA_FOR_EYE[2] = { 2, 1 };

struct CaptureData {
	ovrPosef pose;
	cv::Mat image;
};

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
	bool isSubThread;

public:

	WebcamHandler() {
		
	}

	// Spawn capture thread and return webcam aspect ratio (width over height)
	float startCapture(ovrHmd & hmdRef, int which, bool _isSubThread) {
		isSubThread = _isSubThread;
		hmd = hmdRef;

		if (!isSubThread){

			GstElement *pipeline, *videosrc, *conv, *dec, *pay, *udp, *appsink;

			// init GStreamer
			gst_init(NULL, NULL);

			// setup pipeline
			pipeline = gst_pipeline_new("pipeline");

			videosrc = gst_element_factory_make("udpsrc", "source");
			g_object_set(G_OBJECT(videosrc), "port", 5000, NULL);
			g_object_set(G_OBJECT(videosrc), "caps", gst_caps_from_string("application/x-rtp, payload=96"), NULL);


			pay = gst_element_factory_make("rtph264depay", "pay");

			dec = gst_element_factory_make("avdec_h264", "dec");

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
			//if (!pipeline || !videosrc || !pay || !dec || !conv || !sink) {
			//	g_printerr("Not all elements could be created.\n");
			//	return -1;
			//}

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
			while (!gotFrame)
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

					Mat frame1;
					cvtColor(yuv, frame1, CV_YUV2BGR_IYUV);

					aspect = (float)frame1.cols / (float)frame1.rows;
					gotFrame = true;
				}


			captureThread = std::thread(&WebcamHandler::captureLoop, this);
			Platform::sleepMillis(200);
			return aspect;
		}
		else
		{
			return W/H/2;
		}
		
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
			if (!gst_app_sink_is_eos(appsink1)){
				float captureTime = ovr_GetTimeInSeconds();
				ovrTrackingState tracking = ovrHmd_GetTrackingState(hmd, captureTime);
				captured.pose = tracking.HeadPose.ThePose;
				GstSample *sample = gst_app_sink_pull_sample(appsink1);
				GstCaps *caps = gst_sample_get_caps(sample);
				GstBuffer *buffer = gst_sample_get_buffer(sample);
				const GstStructure *info = gst_sample_get_info(sample);

				// ---- Read frame and convert to opencv format ---------------

				GstMapInfo map;
				gst_buffer_map(buffer, &map, GST_MAP_READ);

				Mat yuv(Size(W, H + H / 2), CV_8U, map.data); //640,480+240
				//printf(" got buffer: size = %d, data=0x%p\n", size, data );

				Mat frame1;
				cvtColor(yuv, frame1, CV_YUV2BGR_IYUV);


				gst_buffer_unref(buffer);


				captured.image = frame1;
				cv::flip(captured.image.clone(), captured.image, 0);
				set(captured);
				//delete sample;
				//delete caps;
				//delete buffer;
				//delete info;
			}
		}
	}
};

class WebcamApp : public RiftApp {

protected:

	ProgramPtr program;
	TexturePtr texture[2];
	ShapeWrapperPtr videoGeometry[2];
	WebcamHandler CamHandler;
	CaptureData CamHandlerCaptureData;
	WebcamHandler captureHandler[2];
	CaptureData captureData[2];

public:

	WebcamApp() {
	}

	virtual ~WebcamApp() {
		for (int i = 0; i < 2; i++) {
			captureHandler[i].stopCapture();
		}
	}

	void initGl() {
		RiftApp::initGl();
		using namespace oglplus;
		CamHandler.startCapture(hmd, 0, false);
		program = oria::loadProgram(Resource::SHADERS_TEXTURED_VS, Resource::SHADERS_TEXTURED_FS);

		for (int i = 0; i < 2; i++) {
			texture[i] = TexturePtr(new Texture());
			Context::Bound(TextureTarget::_2D, *texture[i])
				.MagFilter(TextureMagFilter::Linear)
				.MinFilter(TextureMinFilter::Linear);
			program = oria::loadProgram(Resource::SHADERS_TEXTURED_VS, Resource::SHADERS_TEXTURED_FS);
			float aspect = captureHandler[i].startCapture(hmd, CAMERA_FOR_EYE[i], true);
			videoGeometry[i] = oria::loadPlane(program, aspect);
		}
	}

	virtual void update() {
		if (CamHandler.get(CamHandlerCaptureData)){
			CaptureData captured1;
			CaptureData captured2;
			Mat Left, Right;
			Rect RLeft(0, 0, W / 2, H);
			Rect RRight(W / 2, 0, W / 2, H);
			Left = CamHandlerCaptureData.image(RLeft);
			Right = CamHandlerCaptureData.image(RRight);
			captured1.pose = CamHandlerCaptureData.pose;
			captured2.pose = CamHandlerCaptureData.pose;
			captured1.image = Left;
			captured2.image = Right;
			captureHandler[0].set(captured1);
			captureHandler[1].set(captured2);

			for (int i = 0; i < 2; i++) {
				if (captureHandler[i].get(captureData[i])) {
					using namespace oglplus;
					Context::Bound(TextureTarget::_2D, *texture[i])
						.Image2D(0, PixelDataInternalFormat::RGBA8,
						captureData[i].image.cols, captureData[i].image.rows, 0,
						PixelDataFormat::BGR, PixelDataType::UnsignedByte,
						captureData[i].image.data);
				}
			}
		}
	}

	virtual void renderScene() {
		using namespace oglplus;
		glClear(GL_DEPTH_BUFFER_BIT);
		oria::renderSkybox(Resource::IMAGES_SKY_CITY_XNEG_PNG);
		MatrixStack & mv = Stacks::modelview();

		mv.withPush([&] {
			glm::quat eyePose = ovr::toGlm(getEyePose().Orientation);
			glm::quat webcamPose = ovr::toGlm(captureData[getCurrentEye()].pose.Orientation);
			glm::mat4 webcamDelta = glm::mat4_cast(glm::inverse(eyePose) * webcamPose);

			mv.identity();
			mv.preMultiply(webcamDelta);

			mv.translate(glm::vec3(0, 0, -2.75));
			texture[getCurrentEye()]->Bind(TextureTarget::_2D);
			oria::renderGeometry(videoGeometry[getCurrentEye()], program);
		});
		oglplus::DefaultTexture().Bind(TextureTarget::_2D);
	}
};

RUN_OVR_APP(WebcamApp);


#pragma endregion