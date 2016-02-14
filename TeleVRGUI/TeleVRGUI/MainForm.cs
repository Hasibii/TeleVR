using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using Tamir.SharpSsh;


namespace TeleVRGUI
{
    public partial class MainForm : Form
    {
        private Process TelemetryProcess;
        private Process OculusAppProcess;
        private SshStream SSHConnection;
        private bool HasStarted;

        public MainForm()
        {
            InitializeComponent();
            HasStarted = false;
            TelemetryProcess = new Process();
            OculusAppProcess = new Process();
            
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            if (!HasStarted)
            {
                TelemetryProcess.StartInfo.FileName = "..\\..\\programms\\TeleVRTelemetrySender.exe";
                TelemetryProcess.StartInfo.Arguments = tbxIPAddress.Text + " " + tbxPort.Text;
                TelemetryProcess.Start();


                OculusAppProcess.StartInfo.FileName = "..\\..\\programms\\CameraToRiftRecv.exe";
                OculusAppProcess.Start();
                btnStart.Text = "Stop";
                HasStarted = true;
            }
            else
            {
                if(!TelemetryProcess.HasExited)
                    TelemetryProcess.Kill();
                if (!OculusAppProcess.HasExited)
                    OculusAppProcess.Kill();
                btnStart.Text = "Start";
                HasStarted = false;
            }


        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            try
            {
                SSHConnection = new SshStream(tbxIPAddress.Text, "pi", "raspberry");
                //Set the end of response matcher character
                SSHConnection.Prompt = "#";
                //Remove terminal emulation characters
                SSHConnection.RemoveTerminalEmulationCharacters = true;
                MessageBox.Show(SSHConnection.ReadResponse());
            }
            catch(Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }

        private void btnRestart_Click(object sender, EventArgs e)
        {

            try
            {
                SSHConnection.Write("sudo shutdown -r now");  // Write ssh to RPI
                // works it in putty
                if (SSHConnection.CanRead == true)
                {
                    MessageBox.Show(SSHConnection.ReadResponse()); // return string from terminal from RPI
                }
                else
                {
                    MessageBox.Show("No response");
                }
            }
            catch
            {
                MessageBox.Show("Catch NO response");
            }
        }

        private void btnStartTelemetry_Click(object sender, EventArgs e)
        {
            try
            {
                SSHConnection.Write("sudo ./HelloPi&");  // Write ssh to RPI
                // works it in putty
                if (SSHConnection.CanRead == true)
                {
                     MessageBox.Show( SSHConnection.ReadResponse()); // return string from terminal from RPI
                }
                else
                {
                    MessageBox.Show("No response");
                }
            }
            catch
            {
                MessageBox.Show("Catch NO response");
            }
        }

        private void btnStartCamera_Click(object sender, EventArgs e)
        {
            try
            {
                SSHConnection.Write("sudo raspivid -t 0 -w 1280 -h 720 -fps 48 -b 2000000 -o - | gst-launch-1.0 -e -v fdsrc ! h264parse ! rtph264pay pt=96 config-interval=5 ! udpsink host=192.168.1.106 port=5000&");  // Write ssh to RPI
                // works it in putty
                if (SSHConnection.CanRead == true)
                {
                    string response = SSHConnection.ReadResponse();
                     MessageBox.Show(response); // return string from terminal from RPI
                }
                else
                {
                    MessageBox.Show("No response");
                }
            }
            catch
            {
                MessageBox.Show("Catch NO response");
            }
        }
    }
}
