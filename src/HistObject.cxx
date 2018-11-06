#include "HistObject.h"

HistObject::HistObject( std::string process, TString filename, TString leg_entry, TString var, TString cut, bool PUS ){


  _process = process;
  _filename = filename;
  _leg_entry = leg_entry;
  _var = var;
  _cut = cut;
  _PUS = PUS;

}
