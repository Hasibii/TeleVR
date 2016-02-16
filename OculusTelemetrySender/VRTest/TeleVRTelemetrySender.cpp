
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <OVR_CAPI.h>
#include <Extras\OVR_Math.h>
#include <WS2tcpip.h>

using namespace std;
using namespace OVR;


//Prototypen
int startWinsock(void);
std::wstring s2ws(const std::string& s);

int main(int argc, char* argv[])
{
	
	// Check the number of parameters
		if (argc < 2) {
			// Tell the user how to run the program
			std::cerr << "Usage: " << argv[0] << " NAME" << std::endl;
			/* "Usage messages" are a conventional way of telling the user
			* how to run a program if they enter the command incorrectly.
			*/
			return 1;
		}

	//Parameter auslesen
	string IP = argv[1];
	int Port = atoi(argv[2]);

	//Console
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(h, &bufferInfo);
	

	SOCKET s;
	long rc;
	SOCKADDR_IN addr;
	//Socket initialisieren
	rc = startWinsock();
	if (rc != 0)
	{
		printf("Fehler: startWinsock, fehler code: %d\n", rc);
		return 1;
	}
	else
	{
		printf("Winsock gestartet!\n");

		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s == INVALID_SOCKET)
		{
			printf("Fehler: Der Socket konnte nicht erstellt werden, fehler code: %d\n", WSAGetLastError());
			return 1;
		}
		else
		{
			printf("Socket erstellt!\n");
			memset(&addr, 0, sizeof(SOCKADDR_IN)); // zuerst alles auf 0 setzten 
			addr.sin_family = AF_INET;
			addr.sin_port = htons(Port); 
			std::wstring stemp = s2ws(IP); // String zu wstring konvertieren
			LPCWSTR result = stemp.c_str();
			InetPton(AF_INET, result, &addr.sin_addr);
			rc = connect(s, (SOCKADDR*)&addr, sizeof(SOCKADDR)); //Verbinden
			if (rc == SOCKET_ERROR)
			{
				printf("Fehler: connect gescheitert, fehler code: %d\n", WSAGetLastError());
				return 1;
			}
			else
			{
				printf("Verbunden mit 127.0.0.1..\n");
			}
		}
	}
	
	//Ovr Initialisierung
	ovrResult result = ovr_Initialize(nullptr);
	if (OVR_FAILURE(result))
		return -1;
	
	
	ovrHmd session;
	result = ovrHmd_Create(0, &session);
	if (OVR_FAILURE(result))
	{
		ovr_Shutdown();
		return -2;
	}

	//Oculus Ausrichtung resetten auf aktuelle Orientierung
	ovrHmd_RecenterPose(session);
	char buf[256];
	while (true) //Überträgt kontinuierlich die Pose des HMD alle 25ms
	{
		system("cls");
		ovrTrackingState ts = ovrHmd_GetTrackingState(session,ovr_GetTimeInSeconds());

		if (ts.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)) {
			// The cpp compatibility layer is used to convert ovrPosef to Posef (see OVR_Math.h)
			Posef pose = ts.HeadPose.ThePose;
			float yaw, pitch, roll;
			pose.Rotation.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);

			// Optional: move cursor back to starting position and print values
			SetConsoleCursorPosition(h, bufferInfo.dwCursorPosition);
			cout << "yaw: " << (int)RadToDegree(yaw) << endl;
			cout << "pitch: " << (int)RadToDegree(pitch) << endl;
			cout << "roll: " << (int)RadToDegree(roll) << endl;
			

			buf[0] = 8;//Length
			buf[1] = 0x01; //Rift Sensor Orientation CMD? TODO: Commandliste
			buf[2] = (int)RadToDegree(roll);
			buf[3] = (int)RadToDegree(roll) >> 8;
			buf[4] = (int)RadToDegree(pitch);
			buf[5] = (int)RadToDegree(pitch) >> 8;
			buf[6] = (int)RadToDegree(yaw);
			buf[7] = (int)RadToDegree(yaw) >> 8;
			send(s, buf, buf[0], 0);
			Sleep(25);

		}
	}
	
	closesocket(s);
	ovrHmd_Destroy(session);
	ovr_Shutdown();
	system("Pause");
	char x;
	cin >> x;
	return 1;
}

int startWinsock(void)
{
	WSADATA wsa;
	return WSAStartup(MAKEWORD(2, 0), &wsa);
}

//Konvertiert string zu wstring
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}