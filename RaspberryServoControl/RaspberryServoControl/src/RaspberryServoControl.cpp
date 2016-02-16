//============================================================================
// Name        : HelloPi.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>   // fprintf()
#include <stdlib.h>  // system
#include <unistd.h>  // fork(), exec()
#include <string.h>  // strerror()
#include <errno.h>   // errno
#include <stdlib.h>  // exit()
#include <iostream>  // cout

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "teleVRServoControl.h"

using namespace std;



void error(char* msg);
int main() {

	teleVR_ServoControl ServoCTRL;
			if(!ServoCTRL.init_PWM())
				return 1;

	while(1){

		// Socket initialisieren
		int sockfd, newsockfd, portno;
		portno = 5555; // Port = 5555
		socklen_t clilen;
		char buffer[256];
		struct sockaddr_in serv_addr, cli_addr;
		int n;
		error("GO");
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
		error("ERROR opening socket");
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);



		if (bind(sockfd, (struct sockaddr *) &serv_addr,
			  sizeof(serv_addr)) < 0)
			  error("ERROR on binding");
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd,
				 (struct sockaddr *) &cli_addr,
				 &clilen);
		if (newsockfd < 0)
		  error("ERROR on accept");
		bzero(buffer,256);


		do{
			n = read(newsockfd,buffer,255);
			if (n < 0) error("ERROR reading from socket");
			printf("Here is the message: yaw %i  pitch %d  roll %d\n",(signed short)(buffer[2]|(buffer[3]<<8)),(signed short)(buffer[4]|(buffer[5]<<8)),(signed short)(buffer[6]|(buffer[7]<<8)));

			ServoCTRL.setOrientation((signed short)(buffer[2]|(buffer[3]<<8)),(signed short)(buffer[4]|(buffer[5]<<8)),(signed short)(buffer[6]|(buffer[7]<<8)));
			//ServoCTRL.setOrientation(0,0,0); //Einkommentieren um 0 Orientierung zu prüfen
		}while(n >0); // Solange keine Fehler auftreten

		ServoCTRL.resetPWM(); // PWM reset um die Servos auszuschalten, ansonsten halten die Servos dauerhaft die letzte position
		close(newsockfd);
		close(sockfd);
	}

	return 0;
}

void error(char* msg){
	cout << msg << endl;
}

