#include "HGC.h"
#include "CmdLine.h"

int main( int argc, char ** argv){

  CmdLine cmd( argc, argv ) ;

  HGC hgc( &cmd );
  
  //Response
  // hgc.plot_profile_L1jet_response_pt_PU0_STC();
  // hgc.plot_profile_L1jet_response_eta_PU0_STC();
  //  hgc.plot_profile_L1jet_response_pt_VBFHInv_PU0_STC();
  //  hgc.plot_profile_L1jet_response_pt_VBFHInv_PU0_HistoMax();

  //Resolution
  //  hgc.plot_effRMS_pT_C3D_histo_PU0_STC();
  //  hgc.plot_effRMS_pT();//test for pileup studies
  //  hgc.plot_effRMS_pT_STC();
  //    hgc.plot_effRMS_pT_VBFHinv_PU0_HistoMax();

  //Event Display

  TString file2 = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU0_threshold_polarHisto_Max/jet_ntuples_merged/ntuple_jet_merged_1.root" ;
  //  TFile * file = new TFile ( file2 , "OPEN");

  hgc.display3D_tc( file2, 1);
  hgc.display3D_cl( file2, 1);
  hgc.display2D_c3d( file2, 1);
  hgc.display2D_gen( file2, 1);

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
