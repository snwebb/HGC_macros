#include "interrupts.h"
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <signal.h>

std::vector<std::string> sSignal; 
bool continueJob = true;



void signalHandler(int signal) {
  std::string theSignal("Unknown");
  if(signal<(int)sSignal.size()) theSignal=sSignal[signal];

  std::cout << "Process " << getpid() << " received signal "
            << signal << " = " << theSignal << std::endl;
  std::cerr << "Process " << getpid() << " received signal "
            << signal << " = " << theSignal << std::endl;

  continueJob=false;
}

void defineSignals() {
  if(sSignal.size()==0) {
    sSignal.push_back("Unknown");
    sSignal.push_back("SIGHUP");
    sSignal.push_back("SIGINT");
    sSignal.push_back("SIGQUIT");
    sSignal.push_back("SIGILL");
    sSignal.push_back("SIGTRAP");
    sSignal.push_back("SIGABRT");
    sSignal.push_back("SIGBUS");
    sSignal.push_back("SIGFPE");
    sSignal.push_back("SIGKILL");
    sSignal.push_back("SIGUSR1");
    sSignal.push_back("SIGSEGV");
    sSignal.push_back("SIGUSR2");
    sSignal.push_back("SIGPIPE");
    sSignal.push_back("SIGALRM");
    sSignal.push_back("SIGTERM");
    sSignal.push_back("SIGSTKFLT");
    sSignal.push_back("SIGCHLD");
    sSignal.push_back("SIGCONT");
    sSignal.push_back("SIGSTOP");
    sSignal.push_back("SIGTSTP");
    sSignal.push_back("SIGTTIN");
    sSignal.push_back("SIGTTOU");
    sSignal.push_back("SIGURG");
    sSignal.push_back("SIGXCPU");
    sSignal.push_back("SIGXFSZ");
    sSignal.push_back("SIGVTALRM");
    sSignal.push_back("SIGPROF");
    sSignal.push_back("SIGWINCH");
    sSignal.push_back("SIGPOLL");
    sSignal.push_back("SIGPWR");
    sSignal.push_back("SIGSYS");
    sSignal.push_back("SIGRTMIN");
  }
}

bool catchSignal(std::string sig) {

  defineSignals();

  for(unsigned s(0);s<sSignal.size();s++) {
    if(sSignal[s]==sig) {
      std::cout << "Setting catch for signal = " << s << " = " << sig << std::endl;
      signal(s,signalHandler);
      return true;
    }
  }

    return false;
}

void catchSignals() {
  //  _continueJob = true;
  defineSignals();

  //  BACKTRACE_AND_ASSERT(catchSignal("SIGINT"));
  
  // Catch signals, mainly for batch
  for(unsigned s(0);s<sSignal.size();s++) {
    if(sSignal[s]=="SIGINT")  signal(s,signalHandler);
    if(sSignal[s]=="SIGUSR1") signal(s,signalHandler);
    if(sSignal[s]=="SIGUSR2") signal(s,signalHandler);
    if(sSignal[s]=="SIGTERM") signal(s,signalHandler);
    if(sSignal[s]=="SIGXCPU") signal(s,signalHandler);
  }
}

