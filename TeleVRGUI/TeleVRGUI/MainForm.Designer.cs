namespace TeleVRGUI
{
    partial class MainForm
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnStart = new System.Windows.Forms.Button();
            this.tbxIPAddress = new System.Windows.Forms.TextBox();
            this.tbxPort = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.btnConnect = new System.Windows.Forms.Button();
            this.btnRestart = new System.Windows.Forms.Button();
            this.btnStartTelemetry = new System.Windows.Forms.Button();
            this.btnStartCamera = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.tbxBitrate = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.lblServoControl = new System.Windows.Forms.Label();
            this.lblVideostream = new System.Windows.Forms.Label();
            this.lblTelemetrySender = new System.Windows.Forms.Label();
            this.lblCameraToRiftRecv = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnKillAll = new System.Windows.Forms.Button();
            this.btnTeleSender = new System.Windows.Forms.Button();
            this.btnCameraRecv = new System.Windows.Forms.Button();
            this.lblSSHStatus = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(54, 124);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 23);
            this.btnStart.TabIndex = 0;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // tbxIPAddress
            // 
            this.tbxIPAddress.Location = new System.Drawing.Point(126, 24);
            this.tbxIPAddress.Name = "tbxIPAddress";
            this.tbxIPAddress.Size = new System.Drawing.Size(100, 20);
            this.tbxIPAddress.TabIndex = 1;
            this.tbxIPAddress.Text = "192.168.1.107";
            // 
            // tbxPort
            // 
            this.tbxPort.Location = new System.Drawing.Point(126, 50);
            this.tbxPort.Name = "tbxPort";
            this.tbxPort.Size = new System.Drawing.Size(100, 20);
            this.tbxPort.TabIndex = 2;
            this.tbxPort.Text = "5555";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 31);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(101, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Remote IP-Address:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(91, 57);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Port:";
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(6, 18);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(99, 23);
            this.btnConnect.TabIndex = 5;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // btnRestart
            // 
            this.btnRestart.Location = new System.Drawing.Point(111, 19);
            this.btnRestart.Name = "btnRestart";
            this.btnRestart.Size = new System.Drawing.Size(99, 23);
            this.btnRestart.TabIndex = 6;
            this.btnRestart.Text = "Restart";
            this.btnRestart.UseVisualStyleBackColor = true;
            this.btnRestart.Click += new System.EventHandler(this.btnRestart_Click);
            // 
            // btnStartTelemetry
            // 
            this.btnStartTelemetry.Location = new System.Drawing.Point(6, 47);
            this.btnStartTelemetry.Name = "btnStartTelemetry";
            this.btnStartTelemetry.Size = new System.Drawing.Size(99, 23);
            this.btnStartTelemetry.TabIndex = 7;
            this.btnStartTelemetry.Text = "Start Telemetry";
            this.btnStartTelemetry.UseVisualStyleBackColor = true;
            this.btnStartTelemetry.Click += new System.EventHandler(this.btnStartTelemetry_Click);
            // 
            // btnStartCamera
            // 
            this.btnStartCamera.Location = new System.Drawing.Point(111, 47);
            this.btnStartCamera.Name = "btnStartCamera";
            this.btnStartCamera.Size = new System.Drawing.Size(99, 23);
            this.btnStartCamera.TabIndex = 8;
            this.btnStartCamera.Text = "Start Camera";
            this.btnStartCamera.UseVisualStyleBackColor = true;
            this.btnStartCamera.Click += new System.EventHandler(this.btnStartCamera_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(80, 74);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(40, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Bitrate:";
            // 
            // tbxBitrate
            // 
            this.tbxBitrate.Location = new System.Drawing.Point(126, 74);
            this.tbxBitrate.Name = "tbxBitrate";
            this.tbxBitrate.Size = new System.Drawing.Size(100, 20);
            this.tbxBitrate.TabIndex = 9;
            this.tbxBitrate.Text = "4000000";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 26);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(119, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "RaspberryServoControl:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(61, 50);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(68, 13);
            this.label5.TabIndex = 12;
            this.label5.Text = "Videostream:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(39, 71);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(90, 13);
            this.label6.TabIndex = 13;
            this.label6.Text = "TelemetrySender:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(28, 94);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(101, 13);
            this.label7.TabIndex = 14;
            this.label7.Text = "CameraToRiftRecv:";
            // 
            // lblServoControl
            // 
            this.lblServoControl.AutoSize = true;
            this.lblServoControl.Location = new System.Drawing.Point(135, 26);
            this.lblServoControl.Name = "lblServoControl";
            this.lblServoControl.Size = new System.Drawing.Size(10, 13);
            this.lblServoControl.TabIndex = 15;
            this.lblServoControl.Text = "-";
            // 
            // lblVideostream
            // 
            this.lblVideostream.AutoSize = true;
            this.lblVideostream.Location = new System.Drawing.Point(135, 50);
            this.lblVideostream.Name = "lblVideostream";
            this.lblVideostream.Size = new System.Drawing.Size(10, 13);
            this.lblVideostream.TabIndex = 16;
            this.lblVideostream.Text = "-";
            // 
            // lblTelemetrySender
            // 
            this.lblTelemetrySender.AutoSize = true;
            this.lblTelemetrySender.Location = new System.Drawing.Point(135, 71);
            this.lblTelemetrySender.Name = "lblTelemetrySender";
            this.lblTelemetrySender.Size = new System.Drawing.Size(10, 13);
            this.lblTelemetrySender.TabIndex = 17;
            this.lblTelemetrySender.Text = "-";
            // 
            // lblCameraToRiftRecv
            // 
            this.lblCameraToRiftRecv.AutoSize = true;
            this.lblCameraToRiftRecv.Location = new System.Drawing.Point(135, 94);
            this.lblCameraToRiftRecv.Name = "lblCameraToRiftRecv";
            this.lblCameraToRiftRecv.Size = new System.Drawing.Size(10, 13);
            this.lblCameraToRiftRecv.TabIndex = 18;
            this.lblCameraToRiftRecv.Text = "-";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.lblSSHStatus);
            this.groupBox1.Controls.Add(this.tbxIPAddress);
            this.groupBox1.Controls.Add(this.tbxPort);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.tbxBitrate);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(247, 145);
            this.groupBox1.TabIndex = 19;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Settings";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnCameraRecv);
            this.groupBox2.Controls.Add(this.btnTeleSender);
            this.groupBox2.Controls.Add(this.btnKillAll);
            this.groupBox2.Controls.Add(this.btnStartCamera);
            this.groupBox2.Controls.Add(this.btnConnect);
            this.groupBox2.Controls.Add(this.btnRestart);
            this.groupBox2.Controls.Add(this.btnStartTelemetry);
            this.groupBox2.Location = new System.Drawing.Point(265, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(221, 145);
            this.groupBox2.TabIndex = 20;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Advanced";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btnStart);
            this.groupBox3.Controls.Add(this.lblServoControl);
            this.groupBox3.Controls.Add(this.lblCameraToRiftRecv);
            this.groupBox3.Controls.Add(this.label7);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.lblVideostream);
            this.groupBox3.Controls.Add(this.lblTelemetrySender);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Location = new System.Drawing.Point(12, 163);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(474, 179);
            this.groupBox3.TabIndex = 21;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Main";
            // 
            // btnKillAll
            // 
            this.btnKillAll.Location = new System.Drawing.Point(111, 105);
            this.btnKillAll.Name = "btnKillAll";
            this.btnKillAll.Size = new System.Drawing.Size(99, 23);
            this.btnKillAll.TabIndex = 9;
            this.btnKillAll.Text = "Kill All";
            this.btnKillAll.UseVisualStyleBackColor = true;
            this.btnKillAll.Click += new System.EventHandler(this.btnKillAll_Click);
            // 
            // btnTeleSender
            // 
            this.btnTeleSender.Location = new System.Drawing.Point(6, 76);
            this.btnTeleSender.Name = "btnTeleSender";
            this.btnTeleSender.Size = new System.Drawing.Size(99, 23);
            this.btnTeleSender.TabIndex = 10;
            this.btnTeleSender.Text = "Start TeleSender";
            this.btnTeleSender.UseVisualStyleBackColor = true;
            this.btnTeleSender.Click += new System.EventHandler(this.btnTeleSender_Click);
            // 
            // btnCameraRecv
            // 
            this.btnCameraRecv.Location = new System.Drawing.Point(111, 76);
            this.btnCameraRecv.Name = "btnCameraRecv";
            this.btnCameraRecv.Size = new System.Drawing.Size(99, 23);
            this.btnCameraRecv.TabIndex = 11;
            this.btnCameraRecv.Text = "Start OpenGL";
            this.btnCameraRecv.UseVisualStyleBackColor = true;
            this.btnCameraRecv.Click += new System.EventHandler(this.btnCameraRecv_Click);
            // 
            // lblSSHStatus
            // 
            this.lblSSHStatus.AutoSize = true;
            this.lblSSHStatus.Location = new System.Drawing.Point(126, 110);
            this.lblSSHStatus.Name = "lblSSHStatus";
            this.lblSSHStatus.Size = new System.Drawing.Size(73, 13);
            this.lblSSHStatus.TabIndex = 19;
            this.lblSSHStatus.Text = "Disconnected";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(55, 110);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(65, 13);
            this.label8.TabIndex = 20;
            this.label8.Text = "SSH Status:";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(498, 365);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "MainForm";
            this.Text = "TeleVR";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.TextBox tbxIPAddress;
        private System.Windows.Forms.TextBox tbxPort;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.Button btnRestart;
        private System.Windows.Forms.Button btnStartTelemetry;
        private System.Windows.Forms.Button btnStartCamera;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox tbxBitrate;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label lblServoControl;
        private System.Windows.Forms.Label lblVideostream;
        private System.Windows.Forms.Label lblTelemetrySender;
        private System.Windows.Forms.Label lblCameraToRiftRecv;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnKillAll;
        private System.Windows.Forms.Button btnCameraRecv;
        private System.Windows.Forms.Button btnTeleSender;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label lblSSHStatus;
    }
}

