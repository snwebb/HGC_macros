#ifndef _HistObject_h_
#define _HistObject_h_
#include "Helpers.h"

class HistObject{


 private:

  std::string _var;
  std::string _leg_entry;
  std::string _filename;
  std::string _process;
  std::string _cut;
  std::string _treename;
  bool _PUS;

 public:

  HistObject();
  HistObject(std::string process, TString filename, TString treename, TString leg_entry, TString var, TString cut, bool PUS = false);
  
  TString var(){ return _var;};
  TString leg_entry(){return _leg_entry;};
  TString filename(){return _filename;};
  TString treename(){return _treename;};
  TString cut(){return _cut;};
  std::string process(){ return _process;};
  bool PUS(){ return _PUS;};


};


#endif
