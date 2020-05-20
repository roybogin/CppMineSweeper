#pragma once
#include "Data.h"

void socketCreate();	//create server socket using winsock
void socketConnect();	//connect to a client socket with bind listen accept
void socketSend(const char* data);	//send data through the socket
string socketRecv();	//recieve data from the socket