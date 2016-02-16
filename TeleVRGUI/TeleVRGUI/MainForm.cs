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
        private bool _isSSHConnected;
        private bool isSSHConnected
        {
            get { return _isSSHConnected; }
            set
            {
                if (value)
                    lblSSHStatus.Text = "Connected";
                else
                    lblSSHStatus.Text = "Disconnected";
                _isSSHConnected = value;
            }
        }

        public MainForm()
        {
            InitializeComponent();
            HasStarted = false;
            TelemetryProcess = new Process();
            OculusAppProcess = new Process();
            isSSHConnected = false;
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            

            if (!HasStarted)
            {
                if (!ConnectSSH())
                    return;
                if(!StartVideoStream())
                    return;
                if(!StartTelemetry())
                    return;
                
                TelemetryProcess.StartInfo.FileName = "..\\..\\programms\\TeleVRTelemetrySender.exe";
                TelemetryProcess.StartInfo.Arguments = tbxIPAddress.Text + " " + tbxPort.Text;
                TelemetryProcess.Start();

                lblTelemetrySender.Text = "ON";

                OculusAppProcess.StartInfo.FileName = "..\\..\\programms\\CameraToRiftRecv.exe";
                OculusAppProcess.Start();

                lblCameraToRiftRecv.Text = "ON";

                btnStart.Text = "Stop";
                HasStarted = true;
            }
            else
            {
                if(!TelemetryProcess.HasExited)
                    TelemetryProcess.Kill();
                if (!OculusAppProcess.HasExited)
                    OculusAppProcess.Kill();

                SSHConnection.Write("sudo pkill raspivid");
                SSHConnection.Write("sudo pkill RaspberryServoControl");

                lblCameraToRiftRecv.Text = "OFF";
                lblTelemetrySender.Text = "OFF";
                lblVideostream.Text = "OFF";
                lblServoControl.Text = "OFF";

                btnStart.Text = "Start";
                HasStarted = false;
            }


        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            ConnectSSH();
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

            if (SSHConnection != null)
                SSHConnection.Close();
        }

        private void btnStartTelemetry_Click(object sender, EventArgs e)
        {
            StartTelemetry();
        }

        private void btnStartCamera_Click(object sender, EventArgs e)
        {
            StartVideoStream();
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (isSSHConnected)
            {
                SSHConnection.Write("sudo pkill raspivid");
                SSHConnection.Write("sudo pkill RaspberryServoControl");
            }

            if(SSHConnection != null)
                SSHConnection.Close();
            try
            {
                if (!TelemetryProcess.HasExited)
                    TelemetryProcess.Kill();
            }
            catch { }
            try
            {
                if (!OculusAppProcess.HasExited)
                    OculusAppProcess.Kill();
            }
            catch { }

            
        }

        private bool writeSSHMessage(string msg)
        {
            try
            {
                SSHConnection.Write(msg);

                // works it in putty
                if (SSHConnection.CanRead == true)
                {
                    string response = SSHConnection.ReadResponse();
                    return true;
                }
                else
                {
                    MessageBox.Show("No response to: " + msg);
                }
            }
            catch
            {
                MessageBox.Show("Catch NO response: " + msg);
            }
            isSSHConnected = false;
            return false;   
        }

        private bool StartVideoStream()
        {
            if(writeSSHMessage("sudo pkill raspivid"))
                lblVideostream.Text = "OFF";

            if (writeSSHMessage("sudo ./1_Thread_1Camera_Gstreamer.sh 192.168.1.88 5000 " + tbxBitrate.Text + "&"))
            {
                lblVideostream.Text = "ON";
                return true;
            }
            return false;
        }

        private bool StartTelemetry()
        {
            if (writeSSHMessage("sudo pkill RaspberryServoControl"))
                lblServoControl.Text = "OFF";

            if (writeSSHMessage("sudo ./RaspberryServoControl&"))
            {
                lblServoControl.Text = "ON";
                return true;
            }

            return false;
        }

        private bool ConnectSSH()
        {
            try
            {
                SSHConnection = new SshStream(tbxIPAddress.Text, "pi", "raspberry");
                isSSHConnected = true;
                return true;

            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
            isSSHConnected = false;
            return false;
        }

        private void btnKillAll_Click(object sender, EventArgs e)
        {
            if (isSSHConnected)
            {
                writeSSHMessage("sudo pkill RaspberryServoControl");
                writeSSHMessage("sudo pkill raspivid");
            }

            try
            {
                if (!TelemetryProcess.HasExited)
                    TelemetryProcess.Kill();
            }
            catch { }
            try
            {
                if (!OculusAppProcess.HasExited)
                    OculusAppProcess.Kill();
            }
            catch { }


        }

        private void btnTeleSender_Click(object sender, EventArgs e)
        {
            TelemetryProcess.StartInfo.FileName = "..\\..\\programms\\TeleVRTelemetrySender.exe";
            TelemetryProcess.StartInfo.Arguments = tbxIPAddress.Text + " " + tbxPort.Text;
            TelemetryProcess.Start();
        }

        private void btnCameraRecv_Click(object sender, EventArgs e)
        {
            OculusAppProcess.StartInfo.FileName = "..\\..\\programms\\CameraToRiftRecv.exe";
            OculusAppProcess.Start();
        }
    }
}
