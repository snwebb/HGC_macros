#ifndef _HGC_h_
#define _HGC_h_

#include "Helpers.h"
#include "PlotterResponse.h"
#include "PlotterResolution.h"
#include "PlotterEventDisplay.h"

class HGC{

 private:

  Helpers helper;
  TString snwebb = "/vols/cms/snwebb/HGC_ntuples/";
  TString tstreble = "/vols/cms/tstreble/HGC_ntuples/";

  CmdLine *  _cmd;
  std::string _outdir;

 public:

  HGC( CmdLine * cmd );
  void MakeTar();

  //Response
  void plot_profile_L1jet_response_pt_PU0_STC();
  void plot_profile_L1jet_response_eta_PU0_STC();
  void plot_profile_L1jet_response_pt_VBFHInv_PU0_STC();
  void plot_profile_L1jet_response_pt_VBFHInv_PU0_HistoMax();
  void plot_profile_L1jet_response_pt_VBFHInv_PU200_CompareThreshold();
  //Resolution
  void plot_effRMS_pT_C3D_histo_PU0_STC();
  void plot_effRMS_pT();
  void plot_effRMS_pT_STC();
  void plot_effRMS_pT_VBFHinv_PU0_HistoMax();
  void plot_effRMS_pT_VBFHinv_PU200_CompareAlgos();
  void plot_effRMS_pT_VBFHinv_PU200_CompareThreshold();
  void plot_effRMS_pT_VBFHinv_PU200_CompareDR();

  //Single plots
  void plot_nC3D();
  void plot_GenRecoET();
  void JetStudies();
  void CalculateEfficiency();
  void CalculateEfficiency(double par0, double par1, double par2);
  void CalculateRates(double par0, double par1, double par2);


  //Event Display
  void display3D_tc(TString file,int n_event=0,const std::vector<int>& tc= std::vector<int>(), const std::vector<int>& cl= std::vector<int>(), const std::vector<int>& c3d= std::vector<int>(), float eta_min=-3, float eta_max=3, float phi_min=-3.2, float phi_max=3.2, float layer_min=0, float layer_max=60);

  void display3D_cl(TString file,int n_event=0, const std::vector<int>& cl= std::vector<int>(), const std::vector<int>& c3d= std::vector<int>(), float eta_min=-3, float eta_max=3, float phi_min=3.2, float phi_max=3.2, float layer_min=0, float layer_max=60);

  void display2D_c3d(TString file,int n_event=0,const std::vector<int>& c3d= std::vector<int>(), const std::vector<int>& jets= std::vector<int>(), float eta_min=-3, float eta_max=3, float phi_min=-3.2, float phi_max=3.2);

  void display2D_jets(TString file,int n_event=0,const std::vector<int>& jet= std::vector<int>(), float eta_min=-3, float eta_max=3, float phi_min=-3.2, float phi_max=3.2);

  void display2D_gen(TString file,int n_event=0, float eta_min=-3, float eta_max=3, float phi_min=-3.2, float phi_max=3.2);

  void display2D_jetscl3dtc( TString file, int n_event=0, float eta_min=-3, float eta_max=3,float phi_min=-3.2, float phi_max=3.2);

  //Jet Calibration

  void calibrate_jet(TString filein,TString fileout);



};

#endif
