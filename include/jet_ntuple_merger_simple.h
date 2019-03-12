#ifndef _jet_ntuple_merger_simple_h_
#define _jet_ntuple_merger_simple_h_

#include "Helpers.h"

class jet_ntuple_merger_simple{

 private:

  Helpers helper;
  TString snwebb = "/vols/cms/snwebb/HGC_ntuples/";
  int nBinsPhiHisto_ = 16;
  int nBinsRHisto_ = 10;
  double kROverZMin_ = 0;
  double kROverZMax_ = 1;


  std::vector<float> weights_Fisher = {-2.04613,-3.43434,-3.52741,-0.641428,1.63015,1.72426,2.55182,3.7712,3.05594,4.19388,3.04662,1.95578,2.92687,0.337107,-1.36569,0.662399,0.490461,0.886983,0.566291,3.62657,0.697395,1.08258,2.39743,3.30359,0.667652,0.344089,7.99027,4.89368,2.82031,5.01364,3.67732,3.15481,5.40121,0.162698,11.0507,6.4112,2.57398,-2.11481};

  std::vector<float> weights_Fisher_c3d = { -2.19465f, -1.87364f, -1.66775f, -1.30156f, -1.02639f, -0.876539f, -0.768602f, -0.523715f, -0.648102f, -0.517912f, -0.670387f, -0.696750f, -0.565943f, -0.711266f, -0.757421f, -0.553625f, -0.510087f, -0.438490f, -0.450306f, -0.256428f, -0.385574f, -0.312418f, -0.232202f, -0.203622f, -0.272561f, -0.296243f };

  // there is no layer zero // in GeV
  std::vector<float> dEdX_weights_nominal = { 0.0, 8.603e-3, 8.0675e-3, 8.0675e-3, 8.0675e-3, 8.0675e-3, 8.0675e-3, 8.0675e-3, 8.0675e-3, 8.0675e-3, 8.9515e-3, 10.135e-3, 10.135e-3, 10.135e-3, 10.135e-3, 10.135e-3, 10.135e-3, 10.135e-3, 10.135e-3, 10.135e-3, 11.682e-3, 13.654e-3, 13.654e-3, 13.654e-3, 13.654e-3, 13.654e-3, 13.654e-3, 13.654e-3, 38.2005e-3, 55.0265e-3, 49.871e-3, 49.871e-3, 49.871e-3, 49.871e-3, 49.871e-3, 49.871e-3, 49.871e-3, 49.871e-3, 49.871e-3, 49.871e-3, 62.005e-3, 83.1675e-3, 92.196e-3, 92.196e-3, 92.196e-3, 92.196e-3, 92.196e-3, 92.196e-3, 92.196e-3, 92.196e-3, 92.196e-3, 92.196e-3, 46.098e-3};
  
  std::vector<float> dEdX_weights_Luca_TrgLayer = {0.0, 0.0183664, 0., 0.0305622, 0., 0.0162589, 0., 0.0143918, 0., 0.0134475, 0., 0.0185754, 0., 0.0204934, 0., 0.016901, 0., 0.0207958, 0., 0.0167985, 0., 0.0238385, 0., 0.0301146, 0., 0.0274622, 0., 0.0468671, 0., 0.078819, 0.0555831, 0.0609312, 0.0610768, 0.0657626, 0.0465653, 0.0629383, 0.0610061, 0.0517326, 0.0492882, 0.0699336, 0.0673457, 0.119896, 0.125327, 0.143235, 0.153295, 0.104777, 0.109345, 0.161386, 0.174656, 0.108053, 0.121674, 0.1171, 0.328053};
  
  float triggerCellLsbBeforeCompression = 100./1024.;
  int triggerCellTruncationBits = 0;
  float adcSaturationBH_MIP = 1024.;
  int adcNbitsBH = 12;
  float fCperMIP = 2.57;
  float thickCorr = 1.092;
 

  float calibrateInMipT(int hwPt, float eta, int subdet);
  float calibrateMipTinGeV(float MIPpt, int HGClayer, TString calib_version);

  int HGC_layer(const uint32_t subdet, const uint32_t layer);
  float meanX(const std::vector<std::pair<float,float> >& energy_X_tc);
  float sigmaXX(const std::vector<std::pair<float,float> >& energy_X_tc, const float X_cluster);
  float sigmaPhiPhi(const std::vector<std::pair<float,float> >& energy_phi_tc, const float phi_cluster);


 public:

  jet_ntuple_merger_simple();
  void add_jet(TString filein,  TString treename, TString filein_jet, TString treename_jet, TString fileout);
  void create_cones(TString filein,  TString treename, TString fileout);
  void calibrate_layer(TString filein,  TString treename, TString fileout, bool JB_version=false, bool add_jet=false, bool add_cone=false);
  void test();


};

#endif
