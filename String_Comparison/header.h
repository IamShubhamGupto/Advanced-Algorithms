#ifndef HEADER_H
#define HEADER_H
//#include "header.h"
void readTextAndPattern(char* text, char* pattern);
void initialize_string(char* string, int m);
int NaiveString(char* text, char* pattern);
int ModNaiveString(char* text, char* pattern);
int RabinKarp(char* text, char* pattern, int q);
#endif