#ifndef interrupts_CC
#define interrupts_CC

#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <signal.h>

extern std::vector<std::string> sSignal; 
extern bool continueJob;

void signalHandler(int signal);
void defineSignals();
bool catchSignal(std::string sig);
void catchSignals();

#endif
