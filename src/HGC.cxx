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
  //  hgc.plot_profile_L1jet_response_pt_VBFHInv_PU200_CompareThreshold();

  //Resolution
  //  hgc.plot_effRMS_pT_C3D_histo_PU0_STC();
  //  hgc.plot_effRMS_pT();//test for pileup studies
  //  hgc.plot_effRMS_pT_STC();

  //  hgc.plot_effRMS_pT_VBFHinv_PU200_CompareAlgos();
  //   hgc.plot_effRMS_pT_VBFHinv_PU200_CompareThreshold();

  //        hgc.plot_effRMS_pT_VBFHinv_PU0_HistoMax();

	//            hgc.plot_effRMS_pT_VBFHinv_PU200_CompareDR();

      hgc.plot_GenRecoET();
  //Single plots

  //      hgc.plot_nC3D();

  

  //Event Display

  //    TString file2 = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU0_threshold_polarHisto_Max/jet_ntuples_merged/ntuple_jet_merged_1.root" ;
  //    TString file2 = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-0mipt-DR03-NS/jet_ntuples_merged/ntuple_jet_merged_1.root" ;
  //  TString file3 = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU0_stc_polarHisto_Max/jet_ntuples_merged/ntuple_jet_merged_1.root" ;
    TString file4 = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS/jet_ntuples_merged/ntuple_jet_merged_1.root" ;
    //   hgc.display3D_tc( file2 );
   //hgc.display3D_cl( file2 );
    //        hgc.display2D_c3d( file4 );
  // hgc.display2D_gen( file2 );
    //    hgc.display2D_jetscl3dtc( file4, 3 );

    // //Calibrate Jet
    // TString fileout = "test.root" ;
    // hgc.calibrate_jet( file2, fileout) ;


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
