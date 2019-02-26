//Previously plot_C2D_dR.C
#include "HGC.h"
#include "Plotter.h"

void HGC::plot_GenRecoET(){

    TString stats = "1*";
  //    TString stats = "1*";
  //    TString stats = "1*";

  TString file1 = "VBF_Hinv/VBF-PU200-stc-TCs-TCs";


  TString file1a = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA015-DRB02-NS";
  TString file2a = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA020-DRB02-NS";
  TString file3a = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA030-DRB02-NS";
  TString file4a = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS-pu21";
  TString file5a = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA050-DRB02-NS";

  TString file7a = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS";

  TString file6 = "VBF_Hinv/VBF-PU0-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS-2";
  TString file6a = "VBF_Hinv/VBF-PU0-stc-TCs-TCs";

  
  TString file1b = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA040-DRB00-NS";
  TString file2b = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA040-DRB01-NS";
  TString file3b = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS-pu21";
  TString file4b = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA040-DRB03-NS";
  TString file5b = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA040-DRB04-NS";

  TString file6b = "VBF_Hinv/VBF-PU200-stcV2-TCs-histoMax-DRA04-DRB00-NS";
  TString file7b = "VBF_Hinv/VBF-PU200-stcV3-TCs-histoMax-DRA04-DRB00-NS";
  TString file8b = "VBF_Hinv/VBF-PU200-stc-4416r-TCs-histoMax-DRA04-DRB00-NS";


  TString file1c = "VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Max";
  TString file2c = "VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Max";
  TString file3c = "VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Interpolated1stOrder";
  TString file4c = "VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated1stOrder";
  TString file5c = "VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Interpolated2ndOrder";
  TString file6c = "VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated2ndOrder";
  TString file7c = "VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_ModMax";
  TString file8c = "VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_ModMax";

  TString file1d = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS";
  TString file2d = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet1p0";
  TString file3d = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet2p0";
  TString file4d = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet5p0";
  TString file5d = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet10p0";
  TString file_nomin = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA04-DRB00-NS-cl3dpt0";



  //For presentation  
  TString file_thresh_histomax_0400 = "VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-DRA04-DRB00-NS";
  TString file_thresh_inter_0400    = "VBF_Hinv/VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRA04-DRB00-NS";

  TString file_thresh_histomax_0402 = "VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-DRA04-DRB02-NS";
  TString file_thresh_inter_0402    = "VBF_Hinv/VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRA04-DRB02-NS";

  TString file_thresh_histomax_0302 = "VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-DRA03-DRB02-NS";
  TString file_thresh_inter_0302    = "VBF_Hinv/VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRA03-DRB02-NS";

  TString file_thresh_histomax_inf02 = "VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-DRAInf-DRB02-NS";
  TString file_thresh_inter_inf02    = "VBF_Hinv/VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRAInf-DRB02-NS";

  TString file_bestchoice    = "VBF_Hinv/VBF-PU200-bestChoice-TCs-histoMax-DRA04-DRB00-NS";
  TString file_thresh_TCs = "VBF_Hinv/VBF-PU200-threshold-TCs-TCs";
  TString file_stc_TCs = "VBF_Hinv/VBF-PU200-stc-TCs-TCs";


  TString file_stc_histomax_0400 = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA040-DRB00-NS";
  TString file_stc_inter_0400    = "VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA04-DRB00-NS";

  TString file_stc_histomax_0402 = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS-pu21";
  //  TString file_stc_inter_0402    = "VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA04-DRB02-NS";
  TString file_stc_inter_0402    = "VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated1stOrder";
  TString file_stc_histomax_0302 = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA030-DRB02-NS";
  TString file_stc_inter_0302    = "VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA030-DRB02-NS";

  TString file_stc_histomax_inf02 = "VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS";
  TString file_stc_inter_inf02    = "VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRAInf-DRB02-NS";


  TString file_stc_histomax_0402_PU0 = "VBF_Hinv/VBF-PU0-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS-2";

  TString file_threshold_histomax_0402_PU0 = "doesn't exist";
  TString file_stc_inter_0402_PU0 = "doesn't exist";
  TString file_threshold_inter_0402_PU0 = "doesn't exist";



  TString file_photon_wThresh = "SingleGammaPt25/SingleGamma-PU2000-stc-wThresh-TCs-histoMax-DRA040-DRB00-NS";
  TString file_photon_nThresh = "SingleGammaPt25/SingleGamma-PU200-stc-TCs-histoMax-DRA040-DRB00-NS";

  TString file_photon_wThresh_pu0 = "SingleGammaPt25/SingleGamma-PU0-stc-wThresh-TCs-histoMax-DRA040-DRB00-NS";
  TString file_photon_nThresh_pu0 = "SingleGammaPt25/SingleGammaPt25_PU0_stc_HistoMax";

  TString file_threshold_histomax_LayerDep01 = "VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA01-NS";
  TString file_threshold_histomax_LayerDep02 = "VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA02-NS";
  TString file_threshold_histomax_LayerDep03 = "VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA03-NS";
  TString file_threshold_histomax_LayerDep04 = "VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA04-NS";
  TString file_CurrentDefault = "VBF_Hinv/VBF-PU200-CurrentDefault";
  
  
  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8 ";
  
  std::vector<HistObject> histobjects;
  std::vector<TGraph*> graphs;
  Plotter plotter( _cmd );
  double x[16]={0,10,20,40,60,80,100,120,140,160,180,200,220,250,300,400};
  
  
  //Varying 3D cl pt
  // std::vector<TString> files = {file1d, file2d, file3d, file4d, file5d};
  // std::vector<TString> description = {"0p5","1p0","2p0","5p0","10p0"};
  // std::vector<TString> legend = {"0p5","1p0","2p0","5p0","10p0"}; 

  //Comparing TCs directly with 3D cluster jets
  // std::vector<TString> files = {file1, file_nomin};
  // std::vector<TString> description = {"TC-TCs","no_min"};
  // std::vector<TString> legend = {"TC-TCs","no_min"}; 

  //  Threshold algorithm - comparing seeding algorithms
  // std::vector<TString> files = {file_thresh_histomax_0402, file_thresh_inter_0402};
  // std::vector<TString> description = {"maximum","interpolated"};
  // std::vector<TString> legend = {"maximum","interpolated"};

  //Threshold algorithm - comparing clustering radius maximum
  // std::vector<TString> files = {file_thresh_histomax_0400, file_thresh_histomax_0402, file_thresh_histomax_0302, file_thresh_histomax_inf02};
  // std::vector<TString> description = {"0400","0402", "0302","Inf02"};
  // std::vector<TString> legend = {"A=0.04,B=0.00","A=0.04,B=0.02","A=0.03,B=0.02","A=Infinity,B=0.02"};

  //Threshold algorithm - comparing clustering radius interpolated
  // std::vector<TString> files = {file_thresh_inter_0400, file_thresh_inter_0402, file_thresh_inter_0302, file_thresh_inter_inf02};
  // std::vector<TString> description = {"0400","0402", "0302","Inf02"};
  // std::vector<TString> legend = {"A=0.04,B=0.00","A=0.04,B=0.02","A=0.03,B=0.02","A=Infinity,B=0.02"};


  // //STC algorithm - comparing seeding algorithms
  // std::vector<TString> files = {file_stc_histomax_0400, file_stc_inter_0402};
  // std::vector<TString> description = {"maximum","interpolated"};
  // std::vector<TString> legend = {"maximum","interpolated"};

  //STC algorithm - comparing clustering radius maximum
  // std::vector<TString> files = {file_stc_histomax_0400, file_stc_histomax_0402, file_stc_histomax_0302, file_stc_histomax_inf02};
  // std::vector<TString> description = {"0400","0402", "0302","Inf02"};
  // std::vector<TString> legend = {"A=0.04,B=0.00","A=0.04,B=0.02","A=0.03,B=0.02","A=Infinity,B=0.02"};

  //STC algorithm - comparing clustering radius interpolated
  // std::vector<TString> files = {file_stc_inter_0402, file_stc_inter_0302, file_stc_inter_inf02};
  // std::vector<TString> description = {"0402", "0302","Inf02"};
  // std::vector<TString> legend = {"A=0.04,B=0.02","A=0.03,B=0.02","A=Infinity,B=0.02"};

  //Comparing Thresh and STC with TCs directly (done)
  // std::vector<TString> files = {file_stc_TCs,file_thresh_TCs};
  // std::vector<TString> description = {"stc","thresh"};
  // std::vector<TString> legend = {"stc","thresh"}; 


  //Comparing Thresh, STC and best choice
  // std::vector<TString> files = {file_thresh_histomax_0400,file_stc_histomax_0400,file_bestchoice, file_CurrentDefault};
  // std::vector<TString> description = {"thresh","stc","bestchoice", "currentdefault"};
  // std::vector<TString> legend = {"thresh","stc","bestchoice", "currentdefault"};

  //STC algorithm - comparing seeding algorithms PU 0 
  // std::vector<TString> files = {file_stc_histomax_0400, file_stc_inter_0400, file_threshold_histomax_0400, file_threshold_inter_0400,};
  // std::vector<TString> description = {"maximum","interpolated"};
  // std::vector<TString> legend = {"maximum","interpolated"};


  //Single Photon PU200 - STC, with and without threshold
  // std::vector<TString> files = {file_photon_wThresh, file_photon_nThresh};
  // std::vector<TString> description = {"Threshold","NoThreshold"};
  // std::vector<TString> legend = {"Threshold","No threshold"};

  // //Single Photon PU0 - STC, with and without threshold
  // std::vector<TString> files = {file_photon_wThresh_pu0, file_photon_nThresh_pu0};
  // std::vector<TString> description = {"Threshold","NoThreshold"};
  // std::vector<TString> legend = {"With Threshold","No Threshold"};

  //  Comparing STC with TCs directly and inter
  // std::vector<TString> files = {file_stc_TCs,file_stc_inter_0402};
  // std::vector<TString> description = {"TCs","inter"};
  // std::vector<TString> legend = {"TCs","inter"}; 


  //Comparing Thresh, STC and best choice for inter
  // std::vector<TString> files = {file_thresh_inter_0402,file_stc_inter_0402};
  // std::vector<TString> description = {"thresh","stc"};
  // std::vector<TString> legend = {"thresh","stc"};



  //Layer dependent studies
   std::vector<TString> files = {file_threshold_histomax_LayerDep01,file_threshold_histomax_LayerDep02,file_threshold_histomax_LayerDep03,file_threshold_histomax_LayerDep04};
   //  std::vector<TString> files = {file_threshold_histomax_LayerDep02,file_threshold_histomax_LayerDep03,file_threshold_histomax_LayerDep04};
   std::vector<TString> description = {"0p01","0p02","0p03","0p04"};
   std::vector<TString> legend = {"A=0.01","A=0.02","A=0.03","A=0.04"};



  //Producing N seed plots
  //  std::vector<TString> files = {file_thresh_histomax_0400,file_stc_histomax_0400,file_bestchoice};
  //  std::vector<TString> files = {file_thresh_histomax_0400,file_thresh_histomax_0400,file_thresh_histomax_0400,file_thresh_histomax_0400,file_thresh_histomax_0400};
  //  std::vector<TString> files = {file_stc_histomax_0400,file_stc_histomax_0400,file_stc_histomax_0400,file_stc_histomax_0400,file_stc_histomax_0400};
  // std::vector<TString> files = {file_bestchoice,file_bestchoice,file_bestchoice,file_bestchoice,file_bestchoice};
  // std::vector<TString> description = {"0.5","1.0","2.0","5.0","10.0"};
  // std::vector<TString> legend = {"0.5","1.0","2.0","5.0","10.0"};






  for(unsigned int i=0;i<files.size();i++){
    histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + files.at(i) + "/jet_ntuples_merged/ntuple_jet_merged_"+stats+".root"), "", "jets_pt[VBF_parton_jets]:genjet_pt[VBF_parton_genjet]", cut, true  ) );
  }

  for(unsigned int i=0;i<histobjects.size();i++){
    TH2F * hist = plotter.Draw2D(histobjects.at(i), 15, x, 4000,0,400  ,description.at(i));
    graphs.emplace_back( plotter.DrawProfile(hist  ,(description.at(i)+"_profile"), "s" ) );
  }

  
  plotter.DrawGraphs(graphs, legend);








  std::vector<TH1F*> hist;

  for(unsigned int i=0;i<files.size();i++){

    TString cutval = "0.5";
    // if ( i == 1 ) cutval = "1";
    // if ( i == 2 ) cutval = "2";
    // if ( i == 3 ) cutval = "5";
    // if ( i == 4 ) cutval = "10";
    //    TH1F * ncl3D = helper.single_plot( tstreble + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_2.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 250,0,750);


    //        TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_5.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 300,300.5,900.5);
        TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_5.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 300,0.5,600.5);
    //    TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_5.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 500,300,1800);
    //    TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_2.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 14,-0.5,6.5);

    ncl3D->SetTitle(";3D clusters per endcap;arbitrary units");
    ncl3D->Scale(1/(ncl3D->Integral()));
    hist.push_back( ncl3D );
 
  }
  
  plotter.Draw( hist , legend, "ncl3d" , true);




}


void HGC::plot_nC3D(){

  std::vector<TH1F*> hist;
  std::vector<TString> files;
  std::vector<TString> legend;
  Plotter plotter( _cmd );




  // files.push_back("VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS");
  // files.push_back("VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS");
  // files.push_back("VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS");
  // files.push_back("VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS");
  // files.push_back("VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS");

  // files.push_back("VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Max");
  // files.push_back("VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Max");
  // files.push_back("VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Max");
  // files.push_back("VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Max");
  // files.push_back("VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Max");
  // files.push_back("VBF_Hinv_PU200_dRNNC2D");
  // files.push_back("VBF_Hinv_PU200_dRNNC2D");
  // files.push_back("VBF_Hinv_PU200_dRNNC2D");
  // files.push_back("VBF_Hinv_PU200_dRNNC2D");
  // files.push_back("VBF_Hinv_PU200_dRNNC2D");

  // files.push_back("VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet1p0");
  // files.push_back("VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet2p0");
  // files.push_back("VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet5p0");
  // files.push_back("VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet10p0");
  // legend.push_back( "0.5");
  // legend.push_back( "1.0");
  // legend.push_back( "2.0");
  // legend.push_back( "5.0");
  // legend.push_back( "10.0");






  // files.push_back( "VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Max");
  // files.push_back("VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Max");
  // legend.push_back( "Threshold Histo");
  // legend.push_back( "Threshold Stc");


  //Gamma stc threshold study
  files.push_back( "SingleGammaPt25/SingleGamma-PU2000-stc-wThresh-TCs-histoMax-DRA040-DRB00-NS");
  files.push_back("SingleGammaPt25/SingleGammaPt25_PU200_stc_HistoMax");
  // files.push_back( "SingleGammaPt25/SingleGamma-PU0-stc-wThresh-TCs-histoMax-DRA040-DRB00-NS");
  // files.push_back("SingleGammaPt25/SingleGammaPt25_PU0_stc_HistoMax");
  legend.push_back( "stc w/thresh");
  legend.push_back( "stc");








  for(unsigned int i=0;i<files.size();i++){

    TString cutval = "0.5";
    // if ( i == 1 ) cutval = "1";
    // if ( i == 2 ) cutval = "2";
    // if ( i == 3 ) cutval = "5";
    // if ( i == 4 ) cutval = "10";
    //    TH1F * ncl3D = helper.single_plot( tstreble + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_2.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 250,0,750);
    TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_*1.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 450,300,750);
    //    TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_2.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 250,0,10);

    //    ncl3D->Scale(0.5);//per endcap
    ncl3D->SetTitle(";3D clusters per endcap;arbitrary units");
    ncl3D->Scale(1/(ncl3D->Integral()));
    hist.push_back( ncl3D );
 
  }

  
  plotter.Draw( hist , legend, "ncl3d" , true);
  
}

/*

void HGC::plot_nC2D(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1*.root","HGCalTriggerNtuple","cl_n","1",130,0,13000);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1*.root","HGCalTriggerNtuple","cl_n","1",130,0,13000);

  TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl_n","1",130,0,13000);
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl_n","1",130,0,13000);

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl_n","1",130,0,13000);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtuple","cl_n","1",130,0,13000);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");

  TLegend* leg=new TLegend(0.2,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#C2D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,0.15);
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(10.,0.151,"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/nC2D.pdf");  


}






void HGC::plot_nC2D_VBF_PU0(){


  TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl_n","1",100,0,500);
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl_n","1",100,0,500);


  vector<TH1F*> histo;
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);

  vector<TString> leg_entry;
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");

  TLegend* leg=new TLegend(0.5,0.5,0.8,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#C2D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.3*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(3010.,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/nC2D.pdf");  


}






void HGC::plot_eta_C2D_ext(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.4,5);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.4,5);

 TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.4,5);
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.4,5);

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.4,5);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.4,5);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");

  TLegend* leg=new TLegend(0.5,0.5,0.8,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
   if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogy();

  histo[0]->GetXaxis()->SetTitle("|#eta(C2D)|");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(1e-7,1e-1);
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.5,0.15,"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_C2D_ext.pdf");  


}





void HGC::plot_eta_TC(){

  TH1F* h_TC_seed = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(tc_eta)","tc_MIPpt>5",50,1.5,3.);
  TH1F* h_TC_clust = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(tc_eta)","tc_MIPpt>2",50,1.5,3.);

  vector<TH1F*> histo;
  histo.push_back(h_TC_seed);
  histo.push_back(h_TC_clust);

  vector<TString> leg_entry;
  leg_entry.push_back("MIP_{T}>5");
  leg_entry.push_back("MIP_{T}>2");

  TLegend* leg=new TLegend(0.5,0.2,0.8,0.5);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    h->SetFillColor(i+1);
    
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  histo[0]->GetXaxis()->SetTitle("|#eta(TC)|");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.3*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_TC.pdf");  


}





void HGC::plot_eta_C2D(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.5,3.);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.5,3.);

 TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.5,3);
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.5,3);

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.5,3);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","abs(cl_eta)","1",100,1.5,3);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");


  TLegend* leg=new TLegend(0.2,0.2,0.5,0.5);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  histo = sort_histo(histo);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  histo[0]->GetXaxis()->SetTitle("|#eta(C2D)|");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.3*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_C2D.pdf");  


}







void HGC::plot_ncells_C2D(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","cl_ncells","1",100,0,100);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","cl_ncells","1",100,0,100);

 TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","cl_ncells","1",100,0,100);
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","cl_ncells","1",100,0,100);

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","cl_ncells","1",100,0,100);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","cl_ncells","1",100,0,100);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");


  TLegend* leg=new TLegend(0.5,0.5,0.8,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("#TC per C2D");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(1e-4,1.2);
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.,1.3,"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/ncells_C2D.pdf");  


}








void HGC::plot_eta_pt_C2D(){

  TH2F* h_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_pt","",25,1.5,3.,1000,0,10);
  TH2F* h_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_pt","",25,1.5,3.,1000,0,10);




  vector<TH2F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
 

  vector<TProfile*> prof;

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");
 

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    
    TProfile* p = (TProfile*)(histo[i]->ProfileX())->Clone();;
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(C2D)|");
  prof[0]->GetYaxis()->SetTitle("<p_{T}(C2D)> [GeV]");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw("");
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,2.01,"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_pT_C2D.pdf");  


}







void HGC::plot_eta_ncells_C2D(){

  TH2F* h_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_ncells","",25,1.5,3.,1000,0,1000);
  TH2F* h_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl_eta)","cl_ncells","",25,1.5,3.,1000,0,1000);


  vector<TH2F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);

  vector<TProfile*> prof;

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TProfile* p = (TProfile*)(histo[i]->ProfileX())->Clone();;
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(C2D)|");
  prof[0]->GetYaxis()->SetTitle("<#TC per C2D> [GeV]");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,20);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,20.2,"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_ncells_C2D.pdf");  


}





*/






/*

void HGC::plot_eta_C3D(){


  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","1",100,1.5,3.);
  h_NN->Scale(1/1500.);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","1",100,1.5,3.);
  h_GEO->Scale(1/1500.);


 TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","abs(cl3d_eta)","1",100,1.5,3);
 h_NN_VBF_PU0->Scale(h_NN->Integral()/h_NN_VBF_PU0->Integral());
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","abs(cl3d_eta)","1",100,1.5,3);
  h_GEO_VBF_PU0->Scale(h_GEO->Integral()/h_GEO_VBF_PU0->Integral());

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","1",100,1.5,3);
  h_NN_VBF_PU200->Scale(1/300.);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","1",100,1.5,3);
  h_GEO_VBF_PU200->Scale(1/300.);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");


  TLegend* leg=new TLegend(0.3,0.2,0.6,0.4);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);      
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  histo[0]->GetXaxis()->SetTitle("|#eta(C3D)|");
  histo[0]->GetYaxis()->SetTitle("#C3D");
  histo[0]->GetYaxis()->SetTitleOffset(1.9);
  histo[0]->GetYaxis()->SetRangeUser(0,1.5*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");
  
  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/eta_C3D.pdf");  


}







void HGC::plot_nclu_C3D(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","cl3d_nclu","1",50,0,50);
  h_NN->Scale(1/1500.);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","cl3d_nclu","1",50,0,50);
  h_GEO->Scale(1/1500.);

  TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","cl3d_nclu","1",50,0,50);
  h_NN_VBF_PU0->Scale(h_NN->Integral()/h_NN_VBF_PU0->Integral());
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","cl3d_nclu","1",50,0,50);
  h_GEO_VBF_PU0->Scale(h_GEO->Integral()/h_GEO_VBF_PU0->Integral());

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","cl3d_nclu","1",50,0,50);
  h_NN_VBF_PU200->Scale(1/300.);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","cl3d_nclu","1",50,0,50);
  h_GEO_VBF_PU200->Scale(1/300.);


  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  ////histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");


  TLegend* leg=new TLegend(0.4,0.5,0.8,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    //h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("#C2D per C3D");
  histo[0]->GetYaxis()->SetTitle("#C3D");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(1,4*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/nclu_C3D.pdf");  


}







void HGC::plot_eta_pt_C3D(){

  TH2F* h_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_pt","",25,1.5,3.,1000,0,100);
  TH2F* h_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_pt","",25,1.5,3.,1000,0,100);


  vector<TH2F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);

  vector<TProfile*> prof;

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TProfile* p = (TProfile*)(histo[i]->ProfileX())->Clone();;
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(C3D)|");
  prof[0]->GetYaxis()->SetTitle("<p_{T}(C3D)> [GeV]");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,6);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,6.1,"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_pT_C3D.pdf");  


}







void HGC::plot_eta_nclu_C3D(){

  TH2F* h_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_nclu","",25,1.5,3.,1000,0,1000);
  TH2F* h_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_nclu","",25,1.5,3.,1000,0,1000);


  vector<TH2F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);

  vector<TProfile*> prof;

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TProfile* p = (TProfile*)(histo[i]->ProfileX())->Clone();;
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(C3D)|");
  prof[0]->GetYaxis()->SetTitle("<#C2D per C3D> [GeV]");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,20);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,20.2,"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_nclu_C3D.pdf");  


}









void HGC::plot_showerlength_C3D(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","cl3d_showerlength","1",58,2,60);
  h_NN->Scale(1/1500.);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","cl3d_showerlength","1",58,2,60);
  h_GEO->Scale(1/1500.);


  TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","cl3d_showerlength","1",58,2,60);
  h_NN_VBF_PU0->Scale(h_NN->Integral()/h_NN_VBF_PU0->Integral());
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","cl3d_showerlength","1",58,2,60);
  h_GEO_VBF_PU0->Scale(h_GEO->Integral()/h_GEO_VBF_PU0->Integral());

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","cl3d_showerlength","1",58,2,60);
  h_NN_VBF_PU200->Scale(1/300.);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","cl3d_showerlength","1",58,2,60);
  h_GEO_VBF_PU200->Scale(1/300.);


  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);
 

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");


  TLegend* leg=new TLegend(0.5,0.5,0.7,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    //h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Shower length");
  histo[0]->GetYaxis()->SetTitle("#C3D");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.3*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(3.,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/showerlength_C3D.pdf");  


}




void HGC::plot_showerlength_C3D_pt20(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1*.root","HGCalTriggerNtuple","cl3d_showerlength","cl3d_pt>20",58,2,60);
  h_NN->Scale(1/1500.);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1*.root","HGCalTriggerNtuple","cl3d_showerlength","cl3d_pt>20",58,2,60);
  h_GEO->Scale(1/1500.);


  TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl3d_showerlength","cl3d_pt>20",58,2,60);
  h_NN_VBF_PU0->Scale(h_NN->Integral()/h_NN_VBF_PU0->Integral());
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl3d_showerlength","cl3d_pt>20",58,2,60);
  h_GEO_VBF_PU0->Scale(h_GEO->Integral()/h_GEO_VBF_PU0->Integral());

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl3d_showerlength","cl3d_pt>20",58,2,60);
  h_NN_VBF_PU200->Scale(1/300.);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtuple","cl3d_showerlength","cl3d_pt>20",58,2,60);
  h_GEO_VBF_PU200->Scale(1/300.);


  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);
 

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");


  TLegend* leg=new TLegend(0.5,0.5,0.7,0.8);
  leg->SetHeader("p_{T}(C3D)>20 GeV");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("Shower length");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.3*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(3.,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/showerlength_C3D_pt20.pdf");  


}








void HGC::plot_firstlayer_C3D(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","cl3d_firstlayer","1",60,0,60);
  h_NN->Scale(1/1500.);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","cl3d_firstlayer","1",60,0,60);
  h_GEO->Scale(1/1500.);

  TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","cl3d_firstlayer","1",60,0,60);
  h_NN_VBF_PU0->Scale(h_NN->Integral()/h_NN_VBF_PU0->Integral());
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_13.root","HGCalTriggerNtuple","cl3d_firstlayer","1",60,0,60);
  h_GEO_VBF_PU0->Scale(h_GEO->Integral()/h_GEO_VBF_PU0->Integral());

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1.root","HGCalTriggerNtuple","cl3d_firstlayer","1",60,0,60);
  h_NN_VBF_PU200->Scale(1/300.);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1.root","HGCalTriggerNtuple","cl3d_firstlayer","1",60,0,60);
  h_GEO_VBF_PU200->Scale(1/300.);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");


  TLegend* leg=new TLegend(0.6,0.6,0.8,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    //h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("First layer");
  histo[0]->GetYaxis()->SetTitle("#C3D");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(1e-1,5*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/firstlayer_C3D.pdf");  


}







void HGC::plot_firstlayer_C3D_pt20(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1*.root","HGCalTriggerNtuple","cl3d_firstlayer","cl3d_pt>20",60,0,60);
  h_NN->Scale(1/1500.);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1*.root","HGCalTriggerNtuple","cl3d_firstlayer","cl3d_pt>20",60,0,60);
  h_GEO->Scale(1/1500.);


  TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl3d_firstlayer","cl3d_pt>20",60,0,60);
  h_NN_VBF_PU0->Scale(h_NN->Integral()/h_NN_VBF_PU0->Integral());
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl3d_firstlayer","cl3d_pt>20",60,0,60);
  h_GEO_VBF_PU0->Scale(h_GEO->Integral()/h_GEO_VBF_PU0->Integral());

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","HGCalTriggerNtuple","cl3d_firstlayer","cl3d_pt>20",60,0,60);
  h_NN_VBF_PU200->Scale(1/300.);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","HGCalTriggerNtuple","cl3d_firstlayer","cl3d_pt>20",60,0,60);
  h_GEO_VBF_PU200->Scale(1/300.);


  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);
 

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");


  TLegend* leg=new TLegend(0.5,0.5,0.7,0.8);
  leg->SetHeader("p_{T}(C3D)>20 GeV");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogy();

  histo = sort_histo(histo);

  histo[0]->GetXaxis()->SetTitle("First layer");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(1e-6,5*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(3.,1.02*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/firstlayer_C3D_pt20.pdf");  


}








void HGC::plot_eta_showerlength_C3D(){

  TH2F* h_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_showerlength","",25,1.5,3.,60,0,60);
  TH2F* h_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_showerlength","",25,1.5,3.,60,0,60);


  vector<TH2F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);

  vector<TProfile*> prof;

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TProfile* p = (TProfile*)(histo[i]->ProfileX())->Clone();;
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(C3D)|");
  prof[0]->GetYaxis()->SetTitle("<Shower length>");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,60);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,61,"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_showerlength_C3D.pdf");  


}









void HGC::plot_eta_firstlayer_C3D(){

  TH2F* h_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_firstlayer","",25,1.5,3.,60,0,60);
  TH2F* h_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_1.root","HGCalTriggerNtuple","abs(cl3d_eta)","cl3d_firstlayer","",25,1.5,3.,60,0,60);


  vector<TH2F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);

  vector<TProfile*> prof;

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TProfile* p = (TProfile*)(histo[i]->ProfileX())->Clone();;
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(C3D)|");
  prof[0]->GetYaxis()->SetTitle("<First layer>");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,60);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,61,"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_firstlayer_C3D.pdf");  


}







void HGC::plot_njets(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1*.root","jets","jets_n","1",300,0,300);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","jets","jets_n","1",300,0,300);

  TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","jets","jets_n","1",300,0,300);
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_1*.root","jets","jets_n","1",300,0,300);

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","jets","jets_n","1",300,0,300);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","jets","jets_n","1",300,0,300);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);
 

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");



  TLegend* leg=new TLegend(0.3,0.6,0.6,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#L1 Jets");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,0.08);
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(10.,0.082,"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/njets.pdf");  


}




void HGC::plot_njets_pt20(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1*.root","jets","Sum$(jets_pt>20)","1",15,0,15);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","jets","Sum$(jets_pt>20)","1",15,0,15);

  TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","jets","Sum$(jets_pt>20)","1",15,0,15);
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_1*.root","jets","Sum$(jets_pt>20)","1",15,0,15);

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","jets","Sum$(jets_pt>20)","1",15,0,15);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","jets","Sum$(jets_pt>20)","1",15,0,15);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);
 

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");



  TLegend* leg=new TLegend(0.3,0.6,0.6,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  histo = sort_histo(histo);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#L1 Jets(p_{T}>20 GeV)");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.3*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.,1.01*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/njets_pt20.pdf");  


}






void HGC::plot_ncl3d_jets(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_10.root","jets","jets_ncl3d","1",25,0,25);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_10.root","jets","jets_ncl3d","1",25,0,25);

  TH1F* h_NN_pt10 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_10.root","jets","jets_ncl3d","jets_pt>10",25,0,25);
  TH1F* h_GEO_pt10 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_10.root","jets","jets_ncl3d","jets_pt>10",25,0,25);

  TH1F* h_NN_pt20 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_10.root","jets","jets_ncl3d","jets_pt>20",25,0,25);
  TH1F* h_GEO_pt20 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_10.root","jets","jets_ncl3d","jets_pt>20",25,0,25);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_pt10);
  histo.push_back(h_GEO_pt10);
  histo.push_back(h_NN_pt20);
  histo.push_back(h_GEO_pt20);

  vector<TString> leg_entry;
  leg_entry.push_back("NN p_{T}>0 GeV");
  leg_entry.push_back("GEO p_{T}>0 GeV");
  leg_entry.push_back("NN p_{T}>10 GeV");
  leg_entry.push_back("GEO p_{T}>10 GeV");
  leg_entry.push_back("NN p_{T}>20 GeV");
  leg_entry.push_back("GEO p_{T}>20 GeV");

  TLegend* leg=new TLegend(0.5,0.5,0.8,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }


  histo = sort_histo(histo);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("#C3D per L1 jet");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(0,1.3*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.,1.01*histo[0]->GetMaximum(),"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(0,1,500,1);
  line->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/nC3D_jets.pdf");  


}









void HGC::plot_pT_jets(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_10.root","jets","jets_pt","1",100,0,100);
  //TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_10.root","jets","max(jets_raw_Luca_pt-jets_PU_subtr_cone_C3D,0)","1",100,0,100);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_10.root","jets","jets_pt","1",100,0,100);

  TH1F* h_NN_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","jets","jets_pt","1",100,0,100);
  TH1F* h_GEO_VBF_PU0 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_1*.root","jets","jets_pt","1",100,0,100);

  TH1F* h_NN_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","jets","jets_pt","1",100,0,100);
  TH1F* h_GEO_VBF_PU200 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","jets","jets_pt","1",100,0,100);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_VBF_PU0);
  histo.push_back(h_GEO_VBF_PU0);
  //histo.push_back(h_NN_VBF_PU200);
  //histo.push_back(h_GEO_VBF_PU200);
 

  vector<TString> leg_entry;
  leg_entry.push_back("NN ZB PU200");
  leg_entry.push_back("GEO ZB PU200");
  leg_entry.push_back("NN VBF PU0");
  leg_entry.push_back("GEO VBF PU0");
  leg_entry.push_back("NN VBF PU200");
  leg_entry.push_back("GEO VBF PU200");

 
  TLegend* leg=new TLegend(0.5,0.6,0.7,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogy();
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("p_{T}(L1 jet) [GeV]");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  histo[0]->GetYaxis()->SetRangeUser(1e-5,5*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.,1.2*histo[0]->GetMaximum(),"CMS Simulation #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/pt_jets.pdf");  


}








void HGC::plot_eta_jets(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_10.root","jets","abs(jets_eta)","1",100,1.5,3.);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_10.root","jets","abs(jets_eta)","1",100,1.5,3.);
  TH1F* h_NN_pt10 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_10.root","jets","abs(jets_eta)","jets_pt>10",100,1.5,3.);
  TH1F* h_GEO_pt10 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_10.root","jets","abs(jets_eta)","jets_pt>10",100,1.5,3.);

  TH1F* h_NN_pt20 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_1*.root","jets","abs(jets_eta)","jets_pt>20",100,1.5,3.);
  TH1F* h_GEO_pt20 = single_plot("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_1*.root","jets","abs(jets_eta)","jets_pt>20",100,1.5,3.);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_pt10);
  histo.push_back(h_GEO_pt10);
  histo.push_back(h_NN_pt20);
  histo.push_back(h_GEO_pt20);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");
  leg_entry.push_back("NN p_{T}>10 GeV");
  leg_entry.push_back("GEO p_{T}>10 GeV");
  leg_entry.push_back("NN p_{T}>20 GeV");
  leg_entry.push_back("GEO p_{T}>20 GeV");
 
  TLegend* leg=new TLegend(0.2,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral()); 
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  histo = sort_histo(histo);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("|#eta(L1 jet)|");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  //histo[0]->GetYaxis()->SetRangeUser(10,5*histo[0]->GetMaximum());
  histo[0]->GetYaxis()->SetRangeUser(0,1.3*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/eta_jets.pdf");  


}










void HGC::plot_eta_jets_VBF_PU0(){

  TH1F* h_NN = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_1*.root","jets","abs(jets_eta)","1",50,1.5,3.);
  TH1F* h_GEO = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_1*.root","jets","abs(jets_eta)","1",50,1.5,3.);
  TH1F* h_NN_pt10 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_*.root","jets","abs(jets_eta)","jets_pt>10",50,1.5,3.);
  TH1F* h_GEO_pt10 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","jets","abs(jets_eta)","jets_pt>10",50,1.5,3.);

  TH1F* h_NN_pt20 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF_old/ntuple_calibr_jet_VBF_*.root","jets","abs(jets_eta)","jets_pt>20",50,1.5,3.);
  TH1F* h_GEO_pt20 = single_plot("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","jets","abs(jets_eta)","jets_pt>20",50,1.5,3.);

  vector<TH1F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);
  histo.push_back(h_NN_pt10);
  histo.push_back(h_GEO_pt10);
  histo.push_back(h_NN_pt20);
  histo.push_back(h_GEO_pt20);

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");
  leg_entry.push_back("NN p_{T}>10 GeV");
  leg_entry.push_back("GEO p_{T}>10 GeV");
  leg_entry.push_back("NN p_{T}>20 GeV");
  leg_entry.push_back("GEO p_{T}>20 GeV");
 
  TLegend* leg=new TLegend(0.3,0.15,0.5,0.5);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){
    TH1F* h = histo[i];
    h->Scale(1/h->Integral());
    h->SetLineWidth(2);
    h->SetLineColor(i+1);
    if(i>3)
      h->SetLineColor(i+2);
    leg->AddEntry(h,leg_entry[i]);
  }

  histo = sort_histo(histo);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  //c->SetLogy();
  TGaxis::SetMaxDigits(4);

  histo[0]->GetXaxis()->SetTitle("|#eta(L1 jet)|");
  histo[0]->GetYaxis()->SetTitle("a. u.");
  histo[0]->GetYaxis()->SetTitleOffset(1.7);
  //histo[0]->GetYaxis()->SetRangeUser(10,5*histo[0]->GetMaximum());
  histo[0]->GetYaxis()->SetRangeUser(0,1.3*histo[0]->GetMaximum());
  histo[0]->SetStats(0);
  histo[0]->SetTitle("");
  histo[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    histo[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,1.01*histo[0]->GetMaximum(),"CMS Simulation VBF H#rightarrowinv. PU=0 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/eta_jets_VBF_PU0.pdf");  


}









void HGC::plot_profile_L1jet_resolution_C2D_PU0(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";



  TH2F* h_PU0_raw = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0/calibr_jet_ntuples_VBF/ntuple_calibr_jet_VBF_*.root","jets","genjet_pt[VBF_parton_genjet]","(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);


  TH2F* h_PU0_raw_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
  TH2F* h_PU0_cal_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_C2D_dR/calibr_jet_ntuples_VBF_new/ntuple_calibr_jet_VBF_*.root","HGCalTriggerNtuple","genjet_pt[VBF_parton_genjet]","1.06*(4.4374 -0.948102 * log(max(jets_raw_Luca_pt[VBF_parton_jets],20)) + .0686934* pow(log(max(jets_raw_Luca_pt[VBF_parton_jets],20)),2) ) * jets_raw_Luca_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_raw_Luca_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);




  vector<TH2F*> histo;
  histo.push_back(h_PU0_raw);
  histo.push_back(h_PU0_raw_GEO);
  histo.push_back(h_PU0_cal);
  histo.push_back(h_PU0_cal_GEO);
  

  
  vector<TString> leg_entry;
  leg_entry.push_back("PU=0 NN");
  leg_entry.push_back("PU=0 GEO");
  leg_entry.push_back("PU=0 + jet calibr. NN");
  leg_entry.push_back("PU=0 + jet calibr. GEO");
 

  TLegend* leg=new TLegend(0.4,0.5,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TGraphErrors*> graph;

  for(unsigned int i=0;i<histo.size();i++){

    TGraphErrors* gr = new TGraphErrors();
*/
    /*TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    p->BuildOptions(0,0,"s");
    for(unsigned int j=1;j<=p->GetNbinsX();j++){
      float x = p->GetBinCenter(j);
      float y = p->GetBinError(j)/p->GetBinContent(j);
      if(y>1 || p->GetBinContent(j)==0) continue;
      gr->SetPoint(j-1,x,y);
      }*/
/*
    for(unsigned int j=1;j<=histo[i]->GetNbinsX();j++){
      TH1D* proj = histo[i]->ProjectionY("",j,j);
      cout<<"bin "<<j<<endl;
      Double_t xq[4] = {0.25,0.5,0.75,1};
      Double_t yq[4];
      proj->GetQuantiles(4,yq,xq);
      gr->SetPoint(j-1,histo[i]->GetXaxis()->GetBinCenter(j),(yq[2]-yq[0])/yq[1]);
    }

   for(unsigned int j=0;j<gr->GetN();j++){
      double x,y;
      gr->GetPoint(j,x,y);
      if(y==0) gr->RemovePoint(j);
    }

    graph.push_back(gr);
    graph[i]->SetLineColor(i+1);    
    if(i>3)
      graph[i]->SetLineColor(i+2);
    graph[i]->SetLineWidth(2);
    graph[i]->SetFillColor(0);
    leg->AddEntry(graph[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  graph[0]->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  graph[0]->GetYaxis()->SetTitle("IQR / Median");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,1.5);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.51,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/profile_L1jet_resolution_C2D_PU0.pdf");  


}











void HGC::plot_eta_pt_jets(){

  TH2F* h_NN = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_jet_ntuples/ntuple_calibr_jet_core_10.root","jets","abs(jets_eta)","jets_pt","",16,1.45,3.05,1000,0,1000);
  TH2F* h_GEO = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/jet_ntuples_merged/ntuple_jet_merged_10.root","jets","abs(jets_eta)","jets_pt","",16,1.45,3.05,1000,0,1000);


  vector<TH2F*> histo;
  histo.push_back(h_NN);
  histo.push_back(h_GEO);

  vector<TProfile*> prof;

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TProfile* p = (TProfile*)(histo[i]->ProfileX())->Clone();;
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta(C3D)|");
  prof[0]->GetYaxis()->SetTitle("<p_{T}(C3D)> [GeV]");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,20);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,20.1,"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/eta_pT_C3D.pdf");  


}









void HGC::plot_eta_pt_cones(){

  TH2F* h_NN_C3D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_10.root","HGCalTriggerNtuple","abs(cone_eta)","cone_calib_Luca_pt","",16,1.45,3.05,100,0,100);
  TH2F* h_GEO_C3D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_10.root","HGCalTriggerNtuple","abs(cone_eta)","cone_calib_Luca_pt","",16,1.45,3.05,100,0,100);


  vector<TH2F*> histo;
  histo.push_back(h_NN_C3D);
  histo.push_back(h_GEO_C3D);

  vector<TProfile*> prof;

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TProfile* p = (TProfile*)(histo[i]->ProfileX())->Clone();;
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta|");
  prof[0]->GetYaxis()->SetTitle("Cone p_{T} [GeV]");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,20);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,20.1,"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_cone_pt_eta_C2D_dR.pdf");  


}







void HGC::plot_eta_pt_cones_tc(){

  TH2F* h_NN_C3D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200/calibr_cone_ntuples/calibr_cone_ntuples_10.root","HGCalTriggerNtuple","abs(cone_eta)","cone_tc_calib_Luca_pt","",16,1.45,3.05,100,0,100);
  TH2F* h_GEO_C3D = single_plot2D("/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_10.root","HGCalTriggerNtuple","abs(cone_eta)","cone_tc_calib_Luca_pt","",16,1.45,3.05,100,0,100);


  vector<TH2F*> histo;
  histo.push_back(h_NN_C3D);
  histo.push_back(h_GEO_C3D);

  vector<TProfile*> prof;

  vector<TString> leg_entry;
  leg_entry.push_back("NN");
  leg_entry.push_back("GEO");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  for(unsigned int i=0;i<histo.size();i++){

    TProfile* p = (TProfile*)(histo[i]->ProfileX())->Clone();;
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("|#eta|");
  prof[0]->GetYaxis()->SetTitle("Cone p_{T} [GeV]");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0,50);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  
  TLatex *texl = new TLatex(1.51,50.1,"CMS Simulation NeutrinoGun PU=200 #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/profile_cone_tc_pt_eta_C2D_dR.pdf");  


}








void HGC::plot_profile_only_eta_C2D_dR(){

 TString filename = "/vols/cms/tstreble/HGC_ntuples/SingleNu_PU200_C2D_dR/calibr_cone_ntuples/calibr_cone_ntuples_10.root";

  TH2F* h_tc = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_tc_calib_Luca_pt","",16,1.45,3.05,100,0,100);
  TH2F* h_tc0 = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_tc_calib_Luca_pt","cone_tc_calib_Luca_pt>0",16,1.45,3.05,100,0,100);
  TH2F* h_C3D = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_calib_Luca_pt","",16,1.45,3.05,100,0,100);
  TH2F* h_C3D0 = single_plot2D(filename,"HGCalTriggerNtuple","abs(cone_eta)","cone_calib_Luca_pt","cone_calib_Luca_pt>0",16,1.45,3.05,100,0,100);

  vector<TH2F*> histo;
  histo.push_back(h_tc);
  histo.push_back(h_tc0);
  histo.push_back(h_C3D);
  histo.push_back(h_C3D0);

  vector<TProfile*> prof;
  
  vector<TString> leg_entry;
  leg_entry.push_back("TC cone");
  leg_entry.push_back("TC cone p_{T}>0");
  leg_entry.push_back("C3D cone");
  leg_entry.push_back("C3D cone p_{T}>0");

  vector<TString> name;
  name.push_back("prof_cone_tc");
  name.push_back("prof_cone_tc_pTgt0");
  name.push_back("prof_cone_C3D");
  name.push_back("prof_cone_C3D_pTgt0");

  TLegend* leg=new TLegend(0.3,0.5,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);


  TFile* f_new = TFile::Open("PU_cone_vs_eta_C2D_dR.root");
  if(f_new!=0){
    cout<<"PU_cone_vs_eta.root already exists, please delete it before converting again"<<endl;
    return;
  }
  f_new = TFile::Open("PU_cone_vs_eta_C2D_dR.root","RECREATE");
  gStyle->SetOptTitle(0);
  
  for(unsigned int i=0; i<histo.size(); i++){

    TProfile* p = histo[i]->ProfileX();
    p->SetLineColor(i+1);
    p->SetLineWidth(2);
    p->BuildOptions(0,0,"s");
    p->SetStats(0);
    p->SetNameTitle(name[i],name[i]);    
    prof.push_back(p);
    leg->AddEntry(p,leg_entry[i]);
    p->Write();

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  c->SetLogz();

  prof[0]->GetXaxis()->SetTitle("|#eta|");
  prof[0]->GetYaxis()->SetTitle("Cone p_{T} [GeV]");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);  
  prof[0]->GetYaxis()->SetRangeUser(0,30);
  prof[0]->Draw();
  for(unsigned int i=1;i<prof.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(1.47,1.02*30,"CMS Simulation Neutrino gun, #sqrt{s}=14 TeV PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");
  

  c->SaveAs("plots/profile_cone_pt_eta_comb_C2D_dR.pdf");  
  f_new->Close();
  return;

}





*/
