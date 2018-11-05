#ifndef _C3D_HISTO_JET_h_
#define _C3D_HISTO_JET_h_

#include "Helpers.h"
#include "PlotterResponse.h"

using namespace std;

class C3D_histo_jet{

 private:

  Helpers helper;
  TString snwebb = "/vols/cms/snwebb/HGC_ntuples/";

 public:

  /* void plot_profile_L1jet_response_master(std::vector<TH2F*> &histo, std::vector<TString> &leg_entry, std::string plotname, std::string xvar ); */
  /* void plot_profile_L1jet_response_pt(std::vector<TH2F*> &histo, std::vector<TString> &leg_entry, std::string plotname ); */
  /* void plot_profile_L1jet_response_eta(std::vector<TH2F*> &histo, std::vector<TString> &leg_entry, std::string plotname ); */

  //  void plot_profile_L1jet_response_pt_PU0_C3D_histo_refined();
  void plot_profile_L1jet_response_pt_PU0_STC();
  void plot_profile_L1jet_response_eta_PU0_STC();
};

#endif
