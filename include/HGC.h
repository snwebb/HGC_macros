#ifndef _HGC_h_
#define _HGC_h_

#include "Helpers.h"
#include "PlotterResponse.h"
#include "PlotterResolution.h"

class HGC{

 private:

  Helpers helper;
  TString snwebb = "/vols/cms/snwebb/HGC_ntuples/";
  CmdLine *  _cmd;
  std::string _outdir;

 public:

  HGC( CmdLine * cmd );
  void MakeTar();

  //Response
  void plot_profile_L1jet_response_pt_PU0_STC();
  void plot_profile_L1jet_response_eta_PU0_STC();
  void plot_profile_L1jet_response_pt_VBFHInv_PU0_STC();

  //Resolution
  void plot_effRMS_pT_C3D_histo_PU0_STC();
  void plot_effRMS_pT();
  void plot_effRMS_pT_STC();

};

#endif
