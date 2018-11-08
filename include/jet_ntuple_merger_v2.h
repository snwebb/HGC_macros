#ifndef _jet_ntuple_merger_v2_h_
#define _jet_ntuple_merger_v2_h_

#include "Helpers.h"

class jet_ntuple_merger_v2{

 private:

  Helpers helper;
  TString snwebb = "/vols/cms/snwebb/HGC_ntuples/";
  int nBinsPhiHisto_ = 16;
  int nBinsRHisto_ = 10;
  double kROverZMin_ = 0;
  double kROverZMax_ = 1;


  std::vector<float> weights_Fisher = {-2.04613,-3.43434,-3.52741,-0.641428,1.63015,1.72426,2.55182,3.7712,3.05594,4.19388,3.04662,1.95578,2.92687,0.337107,-1.36569,0.662399,0.490461,0.886983,0.566291,3.62657,0.697395,1.08258,2.39743,3.30359,0.667652,0.344089,7.99027,4.89368,2.82031,5.01364,3.67732,3.15481,5.40121,0.162698,11.0507,6.4112,2.57398,-2.11481};

  std::vector<float> weights_Fisher_c3d = { -2.19465f, -1.87364f, -1.66775f, -1.30156f, -1.02639f, -0.876539f, -0.768602f, -0.523715f, -0.648102f, -0.517912f, -0.670387f, -0.696750f, -0.565943f, -0.711266f, -0.757421f, -0.553625f, -0.510087f, -0.438490f, -0.450306f, -0.256428f, -0.385574f, -0.312418f, -0.232202f, -0.203622f, -0.272561f, -0.296243f };


  int HGC_layer(const uint32_t subdet, const uint32_t layer);
  float meanX(const std::vector<std::pair<float,float> >& energy_X_tc);
  float sigmaXX(const std::vector<std::pair<float,float> >& energy_X_tc, const float X_cluster);
  float sigmaPhiPhi(const std::vector<std::pair<float,float> >& energy_phi_tc, const float phi_cluster);


 public:

  jet_ntuple_merger_v2();
  void add_jet(TString filein,  TString treename, TString filein_jet, TString treename_jet, TString fileout);
  void test();


};

#endif
