#ifndef _C3D_HISTO_JET_h_
#define _C3D_HISTO_JET_h_

#include "Helpers.h"

using namespace std;

class C3D_histo_jet{

 private:

  Helpers helper;

 public:

  void plot_profile_L1jet_response_pt_master(std::vector<TH2F*> &histo, std::vector<TString> &leg_entry, std::string plotname );
  void plot_profile_L1jet_response_pt_PU0_C3D_histo_refined();
  void plot_profile_L1jet_response_pt_PU0_STC();

};

#endif
