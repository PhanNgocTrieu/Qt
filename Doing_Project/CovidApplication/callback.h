#ifndef CALLBACK_H
#define CALLBACK_H
#include <iostream>
#include <iomanip>
extern int callbackValues(void* NotUsed, int argc, char** argv, char** azColName);
extern int callbackColName(void* NotUsed, int argc, char** argv, char** azColName);


#endif // CALLBACK_H
