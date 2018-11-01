#ifndef MYUTIL_H
#define MYUTIL_H

#include <iostream>
#include <cstring>

using namespace std;
const int MAX_CHAR = 100;

void pause();
float getFloat();
void getString(char str[], int capacity);
extern volatile int flag;

#endif