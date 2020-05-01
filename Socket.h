#pragma once
#include "Data.h"

void socketCreate();
void socketConnect();
void socketSend(const char* data);
void socketSendBoard();
string socketRecv();