#include "HGC.h"

int main(){


  HGC hgc;
  
  //Response
  // hgc.plot_profile_L1jet_response_pt_PU0_STC();
  // hgc.plot_profile_L1jet_response_eta_PU0_STC();
  

  //Resolution
  //  hgc.plot_effRMS_pT_C3D_histo_PU0_STC();
  //  hgc.plot_effRMS_pT();//test for pileup studies

  hgc.plot_effRMS_pT_STC();

  return 0;
}
