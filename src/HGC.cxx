#include "HGC.h"
#include "CmdLine.h"

int main( int argc, char ** argv){

  CmdLine cmd( argc, argv ) ;

  HGC hgc( &cmd );
  
  //Response
  // hgc.plot_profile_L1jet_response_pt_PU0_STC();
  // hgc.plot_profile_L1jet_response_eta_PU0_STC();
  //  hgc.plot_profile_L1jet_response_pt_VBFHInv_PU0_STC();
  hgc.plot_profile_L1jet_response_pt_VBFHInv_PU0_HistoMax();

  //Resolution
  //  hgc.plot_effRMS_pT_C3D_histo_PU0_STC();
  //  hgc.plot_effRMS_pT();//test for pileup studies
  //  hgc.plot_effRMS_pT_STC();
  //  hgc.plot_effRMS_pT_VBFHinv_PU0_HistoMax();


  hgc.MakeTar();

  return 0;
}


HGC::HGC( CmdLine* cmd ){

  _cmd = cmd;

}

void HGC::MakeTar(  ){

  std::string  out_directory = _cmd->string_val( "--outdir" );
  std::system( ("cd plots; tar -zcf " + out_directory + ".tar.gz " + out_directory + ";  cd ../plots").c_str() );


}
