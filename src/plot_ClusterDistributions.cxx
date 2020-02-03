//Previously plot_C2D_dR.C
#include "HGC.h"
#include "Plotter.h"

void HGC::plot_GenRecoET(){

  TString stats = "*";
  // TString stats = "1*";

  TString file_QG_Pos_200 = "QuarkGun/QuarkGun-Pos-PU200-Decentralised";
  TString file_QG_Pos_140 = "QuarkGun/QuarkGun-Pos-PU140-Decentralised";
  TString file_QG_Pos_0 = "QuarkGun/QuarkGun-Pos-PU0-Decentralised";
  TString file2_QG_Pos_200 = "QuarkGun/QuarkGun-Pos-PU200-Decentralised-DR0p2";
  TString file2_QG_Pos_140 = "QuarkGun/QuarkGun-Pos-PU140-Decentralised-DR0p2";
  TString file2_QG_Pos_0 = "QuarkGun/QuarkGun-Pos-PU0-Decentralised-DR0p2";

  TString file_VBF_Decentralised = "VBF_HGG/VBF-HGG-PU200-Decentralised";
  TString file_VBF_Decentralised_signaldriven = "VBF_HGG/VBF-HGG-PU200-Decentralised-SignalDriven";
  TString file_VBF_Decentralised_signaldriven_DR0p4 = "VBF_HGG/VBF-HGG-PU200-Decentralised-SignalDriven-DR0p4";
  TString file_VBF_Default = "VBF_HGG/VBF-HGG-PU200-Default";
  TString file_Nu_Decentralised = "DoubleNu/DoubleNu-PU200-Decentralised";
  TString file_VBF_withTCs = "VBF_HGG/VBF-HGG-PU200-Default-withTCs";
  TString file_VBF_withTCs_DR0p2 = "VBF_HGG/VBF-HGG-PU200-Default-withTCs-DR0p2";
  TString file_VBF_withTCs_DR0p4 = "VBF_HGG/VBF-HGG-PU200-Default-withTCs-DR0p4";
  TString file_VBF_MixedFE = "VBF_HGG/VBF-HGG-PU200-MixedFE-EM-DR0p2";
  TString file_VBF_BCCoarse = "VBF_HGG/VBF-HGG-PU200-BestChoice-Coarser-DR0p2";
  TString file_VBF_BCCoarseH = "VBF_HGG/VBF-HGG-PU0-BestChoice-CoarserInH-Fix-DR0p2";
  TString file_VBF_Validation = "VBF_HGG/VBF-HGG-PU200-SuperTC-Validation-DR0p2";
  TString file_VBF_Old = "VBF_HGG/VBF-HGG-PU200-SuperTC-Old-DR0p2";
  TString file_VBF_Decentralised_signaldriven_DR0p2 = "VBF_HGG/VBF-HGG-PU200-Decentralised-SignalDriven-DR0p2";
  TString file_VBF_Decentralised_signaldriven_DR0p2_Normal = "VBF_HGG/VBF-HGG-PU200-Decentralised-SignalDriven-DR0p2-Normal";
  TString VBF_HGG_PU200_SuperTC_SignalDriven_DR0p2 = "VBF_HGG/VBF-HGG-PU200-SuperTC-SignalDriven-DR0p2";
  TString VBF_HGG_PU200_SuperTC_ScintillatorStudies_DR0p2 = "VBF_HGG/VBF-HGG-PU200-SuperTC-ScintillatorStudies-DR0p2";
  TString file_VBF_Standard = "VBF_HGG/VBF-HGG-PU200-Standard-DR0p2";
  TString file_Nu_BCCoarseH = "DoubleNu/DoubleNu-PU200-BestChoice-CoarserInH-DR0p2";
  TString file_VBF_Dec = "VBF_HGG/VBF-HGG-PU200-BestChoice-Coarse-DR0p2";
  TString file_VBF_OOP = "VBF_HGG/VBF-HGG-PU200-OOP-DR0p2";
  TString file_VBF_OOP_LargerDR = "VBF_HGG/VBF-HGG-PU200-OOP-LargerDR-DR0p2";


  TString tree_thresh  =  "Fp8ThresholdDummyHistomaxNtup";
  TString tree_stc_validation  =    "Fp8Stc4444FixedDummyHistomaxNtup";
  TString tree_stc  =    "Fp8Stc4161616DummyHistomaxNtup";
  TString tree_stcScin4  =    "Fp8Stc416164DummyHistomaxNtup";
  TString tree_stcScin4C  =    "Fp8Stc416164CoarseDummyHistomaxNtup";
  TString tree_stc_sig1  =    "Fp8StcSigDriv1DummyHistomaxNtup";
  TString tree_stc_sig2  =    "Fp8StcSigDriv2DummyHistomaxNtup";
  TString tree_stc_sig3  =    "Fp8StcSigDriv3DummyHistomaxNtup";
  TString tree_bc  =    "Fp8BestchoiceDummyHistomaxNtup";
  TString tree_mixed  =    "Fp8MixedDummyHistomaxNtup";
  TString tree_tcs  =  "hgcalTriggerNtuplizer";
  TString tree_bc_c1  =    "Fp8BestchoiceCoarse1DummyHistomaxNtup";
  TString tree_bc_c2  =    "Fp8BestchoiceCoarse2DummyHistomaxNtup";
  TString tree_bc_c4  =    "Fp8BestchoiceCoarse4DummyHistomaxNtup";
  TString tree_bc_c8  =    "Fp8BestchoiceCoarse8DummyHistomaxNtup";
  TString tree_bc_c16  =   "Fp8BestchoiceCoarse16DummyHistomaxNtup";

  TString tree_no_oop_thresh  =  "NoOOTThresholdDummyHistomaxxydr015Genclustersntuple";
  TString tree_no_oop_mixed  =     "NoOOTMixedbcstcDummyHistomaxxydr015Genclustersntuple";
  TString tree_oop1_thresh  =     "OOT1ThresholdDummyHistomaxxydr015Genclustersntuple";
  TString tree_oop1_mixed  =     "OOT1MixedbcstcDummyHistomaxxydr015Genclustersntuple";
  TString tree_oop2_thresh  =     "OOT2ThresholdDummyHistomaxxydr015Genclustersntuple";
  TString tree_oop2_mixed  =     "OOT2MixedbcstcDummyHistomaxxydr015Genclustersntuple";
  // 
  //Cuts

  TString cut_v9 = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8 ";
  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8";
  TString cut_pion = "Pion_genjet>=0 && Pion_jets>=0 && abs(genjet_eta[Pion_genjet])>1.7 && abs(genjet_eta[Pion_genjet])<2.8 ";
  TString cuteta1 = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.0 ";
  TString cuteta2 = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.0 && abs(genjet_eta[VBF_parton_genjet])<2.8 ";

  TString cuteta51 = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.5 && abs(genjet_eta[VBF_parton_genjet])<1.8 ";
  TString cuteta52 = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.8 && abs(genjet_eta[VBF_parton_genjet])<2.1 ";
  TString cuteta53 = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.1 && abs(genjet_eta[VBF_parton_genjet])<2.4 ";
  TString cuteta54 = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.4 && abs(genjet_eta[VBF_parton_genjet])<2.7 ";
  TString cuteta55 = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.7 && abs(genjet_eta[VBF_parton_genjet])<3 ";

  std::vector<HistObject> histobjects, histobjects2;
  std::vector<TGraphErrors*> graphs;
  Plotter * plotter = new Plotter( _cmd );
  double x[16]={0,10,20,40,60,80,100,120,140,160,180,200,220,250,300,400};
  
  TString file = file_VBF_OOP_LargerDR;

  // std::vector<TString> trees = { tree_stc_validation, tree_stc};
  // std::vector<TString> description = { "STC4_CTC4", "STC4_16"};
  // std::vector<TString> legend = { "STC4+CTC4", "STC4+16"};
  // std::string algo = "Fp8BestchoiceDummyHistomaxNtup";
  
  // std::vector<TString> trees = { tree_stc, tree_bc_c4, tree_thresh};
  // std::vector<TString> description = { "STC4_16", "BC_4", "Thresh"};
  // std::vector<TString> legend = { "STC4+16", "BC-4", "Threshold"};
  // std::string algo = "Fp8BestchoiceDummyHistomaxNtup";

  // std::vector<TString> trees = { tree_bc, tree_bc,tree_bc};
  // std::vector<TString> description = { "200", "140", "0"};
  // std::vector<TString> legend = { "PU 200", "PU 140", "PU 0"};
  // std::string algo = "Fp8BestchoiceDummyHistomaxNtup";
  
  // std::vector<TString> trees = { tree_thresh, tree_stc, tree_bc, tree_mixed, tree_bc_c4};
  // std::vector<TString> description = { "th","stc","bc","mixed", "bccoarse"};
  // std::vector<TString> legend = { "Threshold 1.35 mip_{T}","SuperTriggerCell","BestChoice", "Mixed BC + SuperTriggerCell", "Coarse-4 BC in CE-H"};

 // std::vector<TString> trees = { tree_no_oop_thresh,tree_no_oop_mixed,tree_oop1_thresh, tree_oop1_mixed, tree_oop2_thresh, tree_oop2_mixed};
 // std::vector<TString> description = {  "nooop_thresh", "nooop_mixed", "oop1_thresh", "oop1_mixed", "oop2_thresh", "oop2_mixed"};
 // std::vector<TString> legend = {  "nooop_thresh", "nooop_mixed", "oop1_thresh", "oop1_mixed", "oop2_thresh", "oop2_mixed"};

 // std::vector<TString> trees = { tree_no_oop_thresh};
 // std::vector<TString> description = {  "nooop_thresh"};
 // std::vector<TString> legend = {   "No OOT Correction"};

 std::vector<TString> trees = { tree_no_oop_thresh,tree_oop1_thresh,tree_oop2_thresh};
 std::vector<TString> description = {  "nooop_thresh", "oop1_thresh", "oop2_thresh"};
 std::vector<TString> legend = {   "No OOT Correction",  "OOT Option 1",  "OOT Option 2"};

 // std::vector<TString> trees = {tree_no_oop_mixed, tree_oop1_mixed, tree_oop2_mixed};
 // std::vector<TString> description = {  "nooop_mixed", "oop1_mixed", "oop2_mixed"};
 // std::vector<TString> legend = {   "No OOT Correction",  "OOT Option 1",  "OOT Option 2"};


  // std::vector<TString> trees = { tree_thresh, tree_stc};
  // std::vector<TString> description = {  "thresh", "STC"};
  // std::vector<TString> legend = { "Threshold", "Super TC"};

  // std::vector<TString> trees = { tree_bc_c1,tree_bc_c2, tree_bc_c4, tree_bc_c8, tree_bc_c16,tree_mixed, tree_bc, tree_thresh, tree_stc};
  // std::vector<TString> description = { "bccoarse1", "bccoarse2", "bccoarse4", "bccoarse8","bccoarse16","mixed", "bc", "thresh", "STC"};
  // std::vector<TString> legend = { "Coarse-1 BC in CE-H", "Coarse-2 BC in CE-H","Coarse-4 BC in CE-H", "Coarse-8 BC in CE-H", "Coarse-16 BC in CE-H","Mixed", "BC","Threshold", "Super TC"};
  //  std::vector<std::string algo> = std::string(tree_bc_c1);

  // std::vector<TString> trees = { tree_bc_c2};
  // std::vector<TString> description = { "bccoarse"};
  // std::vector<TString> legend = { "Coarse-2 BC in CE-H"};
  // std::string algo = std::string(tree_bc_c2);

  // std::vector<TString> trees = { tree_bc_c4};
  // std::vector<TString> description = { "bccoarse"};
  // std::vector<TString> legend = { "Coarse-4 BC in CE-H"};
  // std::string algo = std::string(tree_bc_c4);

  // std::vector<TString> trees = { tree_bc_c8};
  // std::vector<TString> description = { "bccoarse"};
  // std::vector<TString> legend = { "Coarse-8 BC in CE-H"};
  // std::string algo = std::string(tree_bc_c8);

  // std::vector<TString> trees = { tree_bc_c16};
  // std::vector<TString> description = { "bccoarse"};
  // std::vector<TString> legend = { "Coarse-16 BC in CE-H"};
  // std::string algo = std::string(tree_bc_c16);


  // std::vector<TString> trees = { tree_bc};
  // std::vector<TString> description = { "bc"};
  // std::vector<TString> legend = { "Best Choice"};
  // std::string algo = "Fp8BestchoiceDummyHistomaxNtup";
  
  // std::vector<TString> trees = { tree_thresh};
  // std::vector<TString> description = { "th"};
  // std::vector<TString> legend = { "th" };
  // std::string algo = "Fp8ThresholdDummyHistomaxNtup";
  
  // std::vector<TString> trees = { tree_stc};
  // std::vector<TString> description = { "stc"};
  // std::vector<TString> legend = { "stc"};
  // std::string algo = "Fp8Stc4161616DummyHistomaxNtup";


  // std::vector<TString> trees = { tree_mixed};
  // std::vector<TString> description = { "mixed"};
  // std::vector<TString> legend = { "Mixed BC + SuperTriggerCell"};
  // std::string algo = std::string(tree_mixed);
    
  // std::vector<TString> trees = { tree_tcs};
  // std::vector<TString> description = { "tcs"};
  // std::vector<TString> legend = { "tcs" };
  // std::string algo = "hgcalTriggerNtuplizer";

  // std::vector<TString> trees = { tree_thresh, tree_stc, tree_stcScin4, tree_stcScin4C};
  // std::vector<TString> description = { "th","stc4161616","stc416164","stc416164Coarse"};
  // std::vector<TString> legend = { "Threshold","STC 4,16,16,16","STC 4,16,16,4","STC 4,16,16,4(Coarse)"};

  for(unsigned int i=0;i<trees.size();i++){


    //       if (i==4) file = file_VBF_BCCoarseH;
    //    if (i==2 ) file = file_VBF_MixedFE;
    //5 eta bins

    // histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + files.at(i) + "/jet_ntuples_merged/ntuple_jet_merged_"+stats+".root"), "", "jets_pt[VBF_parton_jets]:genjet_pt[VBF_parton_genjet]", cuteta51, true  ) );
    // histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + files.at(i) + "/jet_ntuples_merged/ntuple_jet_merged_"+stats+".root"), "", "jets_pt[VBF_parton_jets]:genjet_pt[VBF_parton_genjet]" ,cuteta52, true  ) );
    // histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + files.at(i) + "/jet_ntuples_merged/ntuple_jet_merged_"+stats+".root"), "", "jets_pt[VBF_parton_jets]:genjet_pt[VBF_parton_genjet]" ,cuteta53, true  ) );
    // histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + files.at(i) + "/jet_ntuples_merged/ntuple_jet_merged_"+stats+".root"), "", "jets_pt[VBF_parton_jets]:genjet_pt[VBF_parton_genjet]" ,cuteta54, true  ) );
    // histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + files.at(i) + "/jet_ntuples_merged/ntuple_jet_merged_"+stats+".root"), "", "jets_pt[VBF_parton_jets]:genjet_pt[VBF_parton_genjet]" ,cuteta55, true  ) );


    //Pion
    //    histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + files.at(i) + "/jet_ntuples_merged/ntuple_jet_merged_"+stats+".root"), "", "jets_pt[Pion_jets]:genjet_pt[Pion_genjet]", cut_pion, true  ) );
    //Not separated (default)
    //                histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + files.at(i) + "/jet_ntuples_merged/ntuple_jet_merged_"+stats+".root"), "", "jets_pt[VBF_parton_jets]:genjet_pt[VBF_parton_genjet]" ,cut, true  ) );


     histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + file + "/jet_ntuples_merged/ntuple_jet_merged_"+ trees.at(i) +"_"+stats+".root"), trees.at(i)+"_Jet", "", "jets_pt[VBF_parton_jets]:genjet_pt[VBF_parton_genjet]" ,cut_v9, true  ) );

    //3D attempt
    //         histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + file + "/jet_ntuples_merged/ntuple_jet_merged_"+ trees.at(i) +"_"+stats+".root"), trees.at(i)+"_Jet", "", "jets_pt[VBF_parton_jets]*2.3/abs(jets_eta[VBF_parton_jets]):genjet_pt[VBF_parton_genjet]" ,cut_v9, true  ) );
     //histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + file + "/jet_ntuples_merged/ntuple_jet_merged_"+ trees.at(i) +"_"+stats+".root"), trees.at(i)+"_Jet", "", "jets_pt[VBF_parton_jets]:genjet_pt[VBF_parton_genjet]" ,cut_v9, true  ) );


    // histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + file + "/jet_ntuples_merged/ntuple_jet_merged_"+ trees.at(i) +"_"+stats+".root"), trees.at(i)+"_Jet", "", "jets_pt[VBF_parton_jets]*2.3/abs(jets_eta[VBF_parton_jets]):genjet_pt[VBF_parton_genjet]" ,cuteta52, true  ) );
    // histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + file + "/jet_ntuples_merged/ntuple_jet_merged_"+ trees.at(i) +"_"+stats+".root"), trees.at(i)+"_Jet", "", "jets_pt[VBF_parton_jets]*2.3/abs(jets_eta[VBF_parton_jets]):genjet_pt[VBF_parton_genjet]" ,cuteta53, true  ) );
    // histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + file + "/jet_ntuples_merged/ntuple_jet_merged_"+ trees.at(i) +"_"+stats+".root"), trees.at(i)+"_Jet", "", "jets_pt[VBF_parton_jets]*2.3/abs(jets_eta[VBF_parton_jets]):genjet_pt[VBF_parton_genjet]" ,cuteta54, true  ) );
    //    histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + file + "/jet_ntuples_merged/ntuple_jet_merged_"+ trees.at(i) +"_"+stats+".root"), trees.at(i)+"_Jet", "", "jets_pt[VBF_parton_jets]:genjet_pt[VBF_parton_genjet]" ,cuteta55, true  ) );

  }


  std::vector<TProfile*> profiles;

  for(unsigned int i=0;i<histobjects.size();i++){
    TH2F * hist = plotter->Draw2D(histobjects.at(i), 15, x, 4000,0,400  ,description.at(i) );//VBF
    //    TH2F * hist = plotter.Draw2D(histobjects.at(i), 10, y, 4000,0,400  ,description.at(i) );//Pion

    graphs.emplace_back( plotter->DrawProfile(hist  ,(description.at(i)+"_profile"), "s" ) );
    profiles.push_back( hist->ProfileX( ( "profile_mean_eff" + description.at(i) )) );

    // hist = plotter.Draw2D(histobjects2.at(i), 15, x, 4000,0,400  ,description.at(i) + "_high_eta");
    // graphs.emplace_back( plotter.DrawProfile(hist  ,(description.at(i)+"_profile_high_eta"), "s" ) );
 
 }


  plotter->DrawGraphs(graphs, legend);
  //  plotter.DrawEtaGraphs(graphs );
  plotter->SaveFile( graphs );

  delete plotter;

  for(unsigned int i=0;i<trees.size();i++){

    TF1 * pol_choice = new TF1 ( "pol", "[0] + [1]*x + [2]*x*x" , 20 , 350);
    TProfile * profile = profiles.at(i);
    
    profile->Fit( pol_choice, "R","",20,300);

    TGraph * mapping = CalculateEfficiency( profile->GetFunction("pol")->GetParameter( 0 ), profile->GetFunction("pol")->GetParameter( 1 ), profile->GetFunction("pol")->GetParameter( 2 ), std::string(trees.at(i))  );
    CalculateRates ( profile->GetFunction("pol")->GetParameter( 0 ), profile->GetFunction("pol")->GetParameter( 1 ), profile->GetFunction("pol")->GetParameter( 2 ) , std::string(trees.at(i)), mapping);

    //    profile->SaveAs("prof.root");
    
    // profile->GetFunction("pol")->GetParameter( 1 ) ;
    // profile->GetFunction("pol")->GetParameter( 2 ) ;
  }
  

  // TGraph * mapping = CalculateEfficiency( profile->GetFunction("pol")->GetParameter( 0 ), profile->GetFunction("pol")->GetParameter( 1 ), profile->GetFunction("pol")->GetParameter( 2 ), algo  );
  // CalculateRates ( profile->GetFunction("pol")->GetParameter( 0 ), profile->GetFunction("pol")->GetParameter( 1 ), profile->GetFunction("pol")->GetParameter( 2 ) , algo, mapping);
  //  JetStudies(  profile->GetFunction("pol")->GetParameter( 0 ), profile->GetFunction("pol")->GetParameter( 1 ), profile->GetFunction("pol")->GetParameter( 2 ), algo  );
  
}


void HGC::plot_nC3D(){

  std::vector<TH1F*> hist;
  std::vector<TString> files;
  std::vector<TString> legend;
  Plotter plotter( _cmd );

  //Gamma stc threshold study
  files.push_back( "DoubleNu/DoubleNu-PU200-Default-withTCs-DR0p2");
  // legend.push_back( "stc w/thresh");
  legend.push_back( "");

  for(unsigned int i=0;i<files.size();i++){

    TString cutval = "1.0";
    //    TString cutval = "0.5";
    // if ( i == 1 ) cutval = "1";
    // if ( i == 2 ) cutval = "2";
    // if ( i == 3 ) cutval = "5";
    // if ( i == 4 ) cutval = "10";
    //    TH1F * ncl3D = helper.single_plot( tstreble + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_2.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 250,0,750);
    TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_hgcalTriggerNtuplizer_*.root" , "hgcalTriggerNtuplizer_Jet", "Sum$(cl3d_pt>"+cutval+")", "", 450,300,750);
    //    ncl3D->Scale(0.5);//per endcap
    ncl3D->SetTitle(";3D clusters per endcap;arbitrary units");
    ncl3D->Scale(1/(ncl3D->Integral()));
    hist.push_back( ncl3D );
  }
  plotter.Draw( hist , legend, "ncl3d" , true);
  
}

void HGC::plot_nTCs(){

  std::vector<TH1F*> hist;
  std::vector<TString> files;
  std::vector<TString> legend;
  Plotter plotter( _cmd );

  files.push_back( "DoubleNu/DoubleNu-PU200-Default-withTCs-DR0p2");

  for(unsigned int i=0;i<files.size();i++){

    TString cutval = "0.0";
    TH1F * nTCs = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_1.root" , "hgcalTriggerNtuplizer_Jet", "Sum$(tc_pt>"+cutval+")", "", 10000,0,10000);

    //    ncl3D->Scale(0.5);//per endcap
    nTCs->SetTitle(";TCs per endcap;arbitrary units");
    nTCs->Scale(1/(nTCs->Integral()));
    hist.push_back( nTCs );
 
  }
  
  plotter.Draw( hist , legend, "nTCs" , true);
  
}


void HGC::JetStudies(double par0, double par1, double par2, std::string algo){

        std::string stats = "*";
  //      std::string stats = "1*";


  std::string file2 = "DoubleNu/DoubleNu-PU200-Decentralised-SignalDriven";
  std::string file1 = "VBF_HGG/VBF-HGG-PU200-Decentralised-SignalDriven";

  // std::string file2 = "DoubleNu/DoubleNu-PU200-Decentralised-SignalDriven-DR0p4";
  // std::string file1 = "VBF_HGG/VBF-HGG-PU200-Decentralised-SignalDriven-DR0p4";

   // std::string file1 = "VBF_HGG/VBF-HGG-PU200-Default-withTCs-DR0p2";
   // std::string file2 = "DoubleNu/DoubleNu-PU200-Default-withTCs-DR0p2";
      
  // std::string file1 = "VBF_HGG/VBF-HGG-PU200-Default-withTCs-DR0p4";
  // std::string file2 = "DoubleNu/DoubleNu-PU200-Default-withTCs-DR0p4";

  //   std::string file1 = "VBF_HGG/VBF-HGG-PU200-Decentralised-SignalDriven-DR0p4";

  std::string tree = algo;
  std::string tree1 = algo;

  //allpt
  std::string jetpt_low = "0";
  std::string jetpt_high = "600";
  // std::string jetpt_low = "30";
  // std::string jetpt_high = "60";

  TString calibpt_VBF = "( -"+TString(std::to_string(par1))+ "+ sqrt( " +  TString(std::to_string(par1*par1)) + "- 4*"+TString(std::to_string(par2))+"*("+TString(std::to_string(par0))+"-jets_pt[VBF_parton_jets]) ) ) / (2 * "+TString(std::to_string(par2))+")";
  TString calibpt_PU = "( -"+TString(std::to_string(par1))+ "+ sqrt( " +  TString(std::to_string(par1*par1)) + "- 4*"+TString(std::to_string(par2))+"*("+TString(std::to_string(par0))+"-jets_pt) ) ) / (2 * "+TString(std::to_string(par2))+")";

  //Uncalibrated
  //   TString cut_basic = "abs(jets_eta)>1.7 && abs(jets_eta)<2.8 && jets_pt>" +jetpt_low +  " && jets_pt<"+jetpt_high;
  //   TString cut_vbf = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8 && genjet_pt[VBF_parton_genjet]>"+jetpt_low +"&& genjet_pt[VBF_parton_genjet]<"+jetpt_high;

  TString cut_basic = "abs(jets_eta)>1.7 && abs(jets_eta)<2.8 && "+calibpt_PU+">" +jetpt_low +  " && "+calibpt_PU+"<"+jetpt_high;
  TString cut_vbf = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8 && "+calibpt_VBF+">"+jetpt_low +"&& "+calibpt_VBF+"<"+jetpt_high;


   TString cut_vbf_etalow = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.1 && genjet_pt[VBF_parton_genjet]>"+jetpt_low +"&& genjet_pt[VBF_parton_genjet]<"+jetpt_high;
   TString cut_vbf_etahigh = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.4 && abs(genjet_eta[VBF_parton_genjet])<2.8 && genjet_pt[VBF_parton_genjet]>"+jetpt_low +"&& genjet_pt[VBF_parton_genjet]<"+jetpt_high;
   TString cut_vbf_etamid = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.1 && abs(genjet_eta[VBF_parton_genjet])<2.4 && genjet_pt[VBF_parton_genjet]>"+jetpt_low +"&& genjet_pt[VBF_parton_genjet]<"+jetpt_high;


   std::vector<HistObject> histobjects, histobjects_n_cl, histobjects_firstfrac, histobjects_srrsum, histobjects_srrjet, histobjects_sppsum, histobjects_sppjet, histobjects_spp_best, histobjects_srr_best, histobjects_spp_paul,histobjects_srr_paul, histobjects_sppsrr, histobjects_coreenergyratio, histobjects_hoe, histobjects_riso, histobjects_n_tcs;

  HistObject histobjects_hoe_pt( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "1/(1+jets_hoe[VBF_parton_jets]):jets_pt[VBF_parton_jets]" ,cut_vbf, true  );


  HistObject histobjects_2d( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_cl[VBF_parton_jets]:" + calibpt_VBF ,cut_vbf, true  );

  HistObject histobjects_2d_etalow( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_cl[VBF_parton_jets]:jets_pt[VBF_parton_jets]" ,cut_vbf_etalow, true  );
  HistObject histobjects_2d_etamid( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_cl[VBF_parton_jets]:jets_pt[VBF_parton_jets]" ,cut_vbf_etamid, true  );
  HistObject histobjects_2d_etahigh( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_cl[VBF_parton_jets]:jets_pt[VBF_parton_jets]" ,cut_vbf_etahigh, true  );

  HistObject histobjects_2d_pu( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "vbf", "jets_n_cl:" + calibpt_PU ,cut_basic, true  );

  histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_pt[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_pt" ,cut_basic, true  ) );

  histobjects_n_cl.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_cl[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_n_cl.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_n_cl" ,cut_basic, true  ) );


  histobjects_firstfrac.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_firstfrac[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_firstfrac.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_firstfrac" ,cut_basic, true  ) );


  histobjects_srrsum.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_srrsum[VBF_parton_jets]/jets_n_cl[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_srrsum.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_srrsum/jets_n_cl" ,cut_basic, true  ) );

  histobjects_sppsum.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_sppsum[VBF_parton_jets]/jets_n_cl[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_sppsum.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_sppsum/jets_n_cl" ,cut_basic, true  ) );


  histobjects_srrjet.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_srrjet[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_srrjet.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_srrjet" ,cut_basic, true  ) );

  histobjects_sppjet.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_sppjet[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_sppjet.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_sppjet" ,cut_basic, true  ) );



  histobjects_srr_best.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_srr_best[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_srr_best.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_srr_best" ,cut_basic, true  ) );


  histobjects_spp_best.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_spp_best[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_spp_best.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_spp_best" ,cut_basic, true  ) );

  histobjects_srr_paul.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_srr_paul[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_srr_paul.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_srr_paul" ,cut_basic, true  ) );


  histobjects_spp_paul.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_spp_paul[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_spp_paul.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_spp_paul" ,cut_basic, true  ) );

  // histobjects_sppsrr.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_spp_best[VBF_parton_jets]/jets_srr_best[VBF_parton_jets]" ,cut_vbf, true  ) );
  // histobjects_sppsrr.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_spp_best/jets_srr_best" ,cut_basic, true  ) );

  histobjects_coreenergyratio.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_coreenergyratio[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_coreenergyratio.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "pu", "jets_coreenergyratio" ,cut_basic, true  ) );


  histobjects_riso.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_riso[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_riso.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "pu", "jets_riso" ,cut_basic, true  ) );

  //  histobjects_n_tcs.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_tcs[VBF_parton_jets]" ,cut_vbf, true  ) );

  histobjects_n_tcs.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_tcs[VBF_parton_jets]" ,cut_vbf, true  ) );
  histobjects_n_tcs.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "pu", "jets_n_tcs" ,cut_basic, true  ) );


  histobjects_hoe.emplace_back( HistObject( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "1/(jets_hoe[VBF_parton_jets]+1)" ,cut_vbf, true  ) );
  histobjects_hoe.emplace_back( HistObject( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "pu", "1/(jets_hoe+1)" ,cut_basic, true  ) );

  Plotter plotter( _cmd );




  //  plotter.Draw(histobjects, 100, 0, 200  ,"pt" );

  plotter.Draw(histobjects_n_cl, 20, -0.5, 19.5  ,"ncl_small" );
  plotter.Draw(histobjects_n_cl, 20, -0.5, 9.5  ,"ncl_vsmall" );

  // plotter.Draw(histobjects_n_cl, 150, -0.5, 1499.5  ,"ncl" );
  // plotter.Draw(histobjects_n_cl, 150, -0.5, 999.5  ,"ncl_med" );
  //plotter.Draw(histobjects_n_cl, 100, -0.5, 99.5  ,"ncl" );
  // plotter.Draw(histobjects_firstfrac, 51, 0,1.01  ,"ff" );
  //  plotter.Draw(histobjects_srrsum, 100, 0,0.05  ,"srrsum" );
  //  plotter.Draw(histobjects_srrjet, 100, 0,0.05  ,"srrjet" );
  //  plotter.Draw(histobjects_sppsum, 100, 0,0.2  ,"sppsum" );
  //  plotter.Draw(histobjects_sppjet, 100, 0,0.3  ,"sppjet" );
  // plotter.Draw2D(histobjects_2d, 100, 0,200,10,-0.5,9.5  ,"nclpt_vbf" );
  // plotter.Draw2D(histobjects_2d_pu, 100, 0,200,10,-0.5,9.5  ,"nclpt_pu" );  
  // // plotter.Draw2D(histobjects_2d_etalow, 100, 0,200,10,-0.5,9.5  ,"nclpt_vbf_etalow" );
  // // plotter.Draw2D(histobjects_2d_etamid, 100, 0,200,10,-0.5,9.5  ,"nclpt_vbf_etamid" );
  // // plotter.Draw2D(histobjects_2d_etahigh, 100, 0,200,10,-0.5,9.5  ,"nclpt_vbf_etahigh" );

  // plotter.Draw(histobjects_srr_best, 100, -0.05,0.1  ,"srr_best" );
  // plotter.Draw(histobjects_spp_best, 100, -0.1,0.5  ,"spp_best" );
  // plotter.Draw(histobjects_srr_paul, 100, -0.05,0.1  ,"srr_paul" );
  // plotter.Draw(histobjects_spp_paul, 100, -0.1,0.5  ,"spp_paul" );
  //  //  plotter.Draw(histobjects_sppsrr, 100, -10,20  ,"s_div" );
  //  plotter.Draw(histobjects_coreenergyratio, 100, -0.1,1.1  ,"coreenergyratio" );
  //  plotter.Draw(histobjects_riso, 50, 0,10  ,"riso" );
  //  plotter.Draw2D(histobjects_hoe_pt, 47, 20, 300,100, 0,1 ,"emfrac_pt" );

  plotter.Draw(histobjects_n_tcs, 100, -0.5, 499.5  ,"n_tcs_500" );
  plotter.Draw(histobjects_n_tcs, 100, -0.5, 999.5  ,"n_tcs_1000" );
  
  //  plotter.Draw(histobjects_hoe, 100, 0, 1  ,"emfrac" );

}

TGraph * HGC::CalculateEfficiency(double par0, double par1, double par2, std::string algo){
  
  std::string stats = "*";
  //  std::string stats = "1*";
  //  std::string file1 = "VBF_HGG/VBF-HGG-PU200-OOP-DR0p2";  
  std::string file1 = "VBF_HGG/VBF-HGG-PU200-OOP-LargerDR-DR0p2";
  std::string tree1  =    algo;
  
  
  //  std::string jetpt_low = "40";
  TString cut_gen = "VBF_parton_genjet>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8";
  
  std::vector<TH1F*> turnons;
  //   std::vector<TEfficiency*> turnons_eff;
  std::vector<TString> legend;
  
   TH1F* genhist = 0;
   TH1F* recohist = 0;

   std::vector<TString> cuts = {"10","20","30","40","50", "100", "150", "175"};

   //   std::vector<TString> cuts = {"250","225", "200","175","150","100","50","40","30", "20", "10"};
   //   std::vector<double> cutsdouble = {250, 225, 200, 175, 150, 100, 50, 40, 30, 20, 10};
   //   std::vector<double> cutsdouble = {250, 225, 200, 175, 150, 100, 50, 40, 30, 20, 10};
   std::vector<double> cutsdouble = {10,20,30,40,50, 100, 150, 175};
   std::vector<double> values95;
   
   TF1 * fit = new TF1 ( "f1","0.5*[2]*TMath::TanH( ( (x-[0])/[1] ) )+0.5*[3]",0,300);
   //   TF1 * fit = new TF1 ( "f1","0.5*[2]*TMath::TanH( ( (x-[0])/[1] ) )+0.5*[3]",0,400);

   fit->SetParameter(1,20);
   fit->SetParameter(2,1);
   fit->SetParameter(3,1);

   //   double max = 400;
   double max = 300;
   genhist = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", "genjet_pt[VBF_parton_genjet]", cut_gen, 100, 0, max );

   for ( unsigned i = 0; i < cuts.size(); i++){
     fit->SetParameter(0,cutsdouble.at(i));
     fit->SetParameter(1,20);
     fit->SetParameter(2,1);
     fit->SetParameter(3,1);

     fit->SetRange( cutsdouble.at(i)-10,(1.3)*cutsdouble.at(i)+50);
     //     TString cut_reco = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8 && jets_pt[VBF_parton_jets]>"+cuts.at(i);
     
     TString calibpt = "( -"+TString(std::to_string(par1))+ "+ sqrt( " +  TString(std::to_string(par1*par1)) + "- 4*"+TString(std::to_string(par2))+"*("+TString(std::to_string(par0))+"-jets_pt[VBF_parton_jets]) ) ) / (2 * "+TString(std::to_string(par2))+")";

     //Original cut
     TString cut_reco = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8 && "+ calibpt + ">"+cuts.at(i);

     //With VBF requirement
     //        cut_reco = cut_reco + " &&  jets_n_cl[VBF_parton_jets] < 3";
     //            cut_reco = cut_reco + " &&  jets_n_cl[VBF_parton_jets] < 4";

     recohist = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", "genjet_pt[VBF_parton_genjet]", cut_reco, 100, 0, max );
     recohist->SetTitle(";Gen Jet p_{T}; Efficiency");

     TH1D * recoclone = (TH1D*)recohist->Clone("reco");
     //     TEfficiency * pEff = new TEfficiency(recohist,genhist);
     recohist->Divide(genhist);

     //SetErrors
     for (int j = 1; j < recohist->GetNbinsX()+1;j++){
       double A = recoclone->GetBinContent(j);
       double sA = recoclone->GetBinError(j);
       double C = genhist->GetBinContent(j);
       double sC = genhist->GetBinError(j);
       double B = C-A;

       double err =std::sqrt( ((B*B)/(C*C*C*C))*(sA*sA)  +  ((A*A)/(C*C*C*C))*( sC*sC-sA*sA  )  ) ;
       if (err==0) err = 0.001;
       recohist->SetBinError(j, err );

     }

     recoclone->Delete();

     recohist->Fit(fit, "R");
     recohist->GetFunction("f1")->SetLineColor(i+1);     
     if(i>3){
       recohist->GetFunction("f1")->SetLineColor(i+2);
     }
     if(i>7){
       recohist->GetFunction("f1")->SetLineColor(i+3);
     }
     
     turnons.push_back(recohist);
     //     turnons_eff.push_back(pEff);
     legend.push_back(cuts.at(i) + " pT");
     values95.push_back( fit->GetX( 0.95 ) );


   }

   TVectorD t_cutsdouble(cutsdouble.size(), &cutsdouble[0]);
   TVectorD t_values95(values95.size(), &values95[0]);

   TGraph * graph = new TGraph(t_cutsdouble,t_values95);
   //Fit graph with curveto obtain mapping.  
   TF1 * mapfit = new TF1("fit","[2]*x*x+[1]*x+[0]");
   graph->Fit(mapfit);

   
   Plotter plotter2( _cmd );
   //   plotter.Draw(recohist, "40", "turnon", false);
   
   
   plotter2.Draw(turnons, legend, "turnon_" + algo, false);
   

   plotter2.DrawGraph(graph , "95eff_" + algo);

   //   plotter.DrawEff(turnons_eff, legend, "turnon_eff", false);
   
   return graph;   

}

void HGC::CalculateRates(double par0, double par1, double par2, std::string algo, TGraph * mapping){

  //      std::string stats = "1*";
  std::string stats = "*";

  //  std::string file1 = "DoubleNu/DoubleNu-PU200-OOP-DR0p2";
  std::string file1 = "DoubleNu/DoubleNu-PU200-OOP-LargerDR-DR0p2";
  std::string tree1  =  algo;
  
  TF1 * mapfit = new TF1("pol2","[2]*x*x+[1]*x+[0]");
  mapping->Fit(mapfit);
  
  std::vector<TH1F*> ratevec;
  std::vector<TGraphErrors*> rategraphvec;
  //  std::vector<TString> legend = {"Inclusive", "VBF-like", "di-jet", "di-jet+VBF-like", "di-jet+masscut"};
  //  std::vector<TString> legend = {"Inclusive", "di-jet", "di-jet+masscut"};
      std::vector<TString> legend = {"Inclusive", "VBF-like", "di-jet+VBF-like"};
  //  std::vector<TString> cuts = {"10","20","30","40","50","60","70","80","90","100","110","120","130","140","150","160","170","180","190","200"};

  TH1F * recohist = 0;  
  TH1F * recohist_vbf = 0;  
  TH1F * recohist_dijet = 0;  
  TH1F * recohist_dijetvbf = 0;  
  TH1F * recohist_dijetmass = 0;  

  //  TString cut_basic = "abs(jets_eta[0])>1.7 && abs(jets_eta[0])<2.8";
  TString cut_basic = "(1==1)";
  //  TString cut_vbf = cut_basic + "&& jets_n_cl[0] < 3";
  TString cut_vbf = cut_basic + "&& jets_n_cl[0] < 4";
  //  TString cut_dijet = cut_basic + "&& abs(jets_eta[1])>1.7 && abs(jets_eta[1])<2.8";
  TString cut_dijet = cut_basic;
    //  TString cut_dijetvbf = cut_basic + "&& abs(jets_eta[1])>1.7 && abs(jets_eta[1])<2.8 && jets_n_cl[0] < 3";
  //  TString cut_dijetvbf = cut_basic + " && jets_n_cl[0] < 3";
  TString cut_dijetvbf = cut_basic + " && jets_n_cl[0] < 4";
  TString cut_etaprod = "jets_eta[0] * jets_eta[1] < 0";


  TString calibpt = "( -"+TString(std::to_string(par1))+ "+ sqrt( " +  TString(std::to_string(par1*par1)) + "- 4*"+TString(std::to_string(par2))+"*("+TString(std::to_string(par0))+"-jets_pt[0]) ) ) / (2 * "+TString(std::to_string(par2))+")";
  TString calibpt1 = "( -"+TString(std::to_string(par1))+ "+ sqrt( " +  TString(std::to_string(par1*par1)) + "- 4*"+TString(std::to_string(par2))+"*("+TString(std::to_string(par0))+"-jets_pt[1]) ) ) / (2 * "+TString(std::to_string(par2))+")";

  TString calibenergy0 = "( -"+TString(std::to_string(par1))+ "+ sqrt( " +  TString(std::to_string(par1*par1)) + "- 4*"+TString(std::to_string(par2))+"*("+TString(std::to_string(par0))+"-jets_energy[0]) ) ) / (2 * "+TString(std::to_string(par2))+")";
  TString calibenergy1 = "( -"+TString(std::to_string(par1))+ "+ sqrt( " +  TString(std::to_string(par1*par1)) + "- 4*"+TString(std::to_string(par2))+"*("+TString(std::to_string(par0))+"-jets_energy[1]) ) ) / (2 * "+TString(std::to_string(par2))+")";

  TString cut_dijetmass = cut_basic + "&&" + cut_etaprod + "&& abs(jets_eta[1])>1.7 && abs(jets_eta[1])<2.8 &&  ( sqrt(2*sqrt(  pow("+calibpt+",2)*pow(cosh(jets_eta[0]),2)) * sqrt(  pow("+calibpt1+",2)*pow(cosh(jets_eta[1]),2)) - 2 *" +calibpt+ "*" + calibpt1 + "*( cos(jets_phi[0]-jets_phi[1]) + sinh(jets_eta[0])*sinh(jets_eta[1])    )    ))  > 200" ;

  recohist = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", calibpt, cut_basic, 1000, 0, 1000 );


  recohist->SaveAs(("recohist"+ tree1+ ".root").c_str());

  recohist_vbf = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", calibpt, cut_vbf, 200, 0, 1000 );


  int nbins = 80;
  TH1F * rate = new TH1F("rate","",nbins,2.5,202.5);
  TGraphErrors * rate_graph = new TGraphErrors(nbins);
  TH1F * ratevbf = new TH1F("rate_vbf","",nbins,2.5,202.5);  
  // TH1F * ratedijet = new TH1F("rate_dijet","",nbins,2.5,202.5);  
  // TH1F * ratedijetmass = new TH1F("rate_dijetmass","",nbins,2.5,202.5);  
  // TH1F * ratedijetvbf = new TH1F("rate_dijetvbf","",nbins,2.5,202.5);  

  for ( int i = 1; i < nbins + 1; i++){

    //   find the bin which corresponds to the offline pT value
    double l1pt = rate->GetBinCenter(i);
    double offlinept = mapping->Eval( l1pt );
    int newi = rate->GetXaxis()->FindBin(offlinept);

    int recohisti = recohist->GetXaxis()->FindBin(offlinept);

    //Inclusive

    rate_graph->SetPoint(i-1, offlinept, 31200 * recohist->Integral(recohisti,recohist->GetNbinsX()+1) / recohist->Integral() );

    double sA = 0;
    double sC = 0;
    double A = recohist->IntegralAndError(recohisti,recohist->GetNbinsX()+1,sA);
    double C = recohist->IntegralAndError(0,recohist->GetNbinsX()+1,sC);
    double B = C-A;
    double err =std::sqrt( ((B*B)/(C*C*C*C))*(sA*sA)  +  ((A*A)/(C*C*C*C))*( sC*sC-sA*sA  )  ) ;
    rate_graph->SetPointError(i-1, 0, 31200 * err );

    if ( newi > nbins ) continue;

    rate->SetBinContent(newi, 31200 * recohist->Integral(recohisti,recohist->GetNbinsX()+1) / recohist->Integral());
    rate->SetBinError(newi, 31200 * err );

    // //VBF like
    // ratevbf->SetBinContent(newi, 31200 * recohist_vbf->Integral(recohisti,recohist_vbf->GetNbinsX()+1) / recohist->Integral());
    // sA = 0;
    // sC = 0;
    // A = recohist_vbf->IntegralAndError(recohisti,recohist_vbf->GetNbinsX()+1,sA);
    // C = recohist->IntegralAndError(0,recohist->GetNbinsX()+1,sC);
    // B = C-A;
    // err =std::sqrt( ((B*B)/(C*C*C*C))*(sA*sA)  +  ((A*A)/(C*C*C*C))*( sC*sC-sA*sA  )  ) ;
    // ratevbf->SetBinError(newi, 31200 * err );


    //    std::cout <<  cut_dijet + "&&"+ calibpt1 + ">" + TString(std::to_string( rate->GetBinLowEdge(i) ) );


    // //Di jet
    // recohist_dijet = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", calibpt, cut_dijet + "&&"+calibpt1 + ">" + TString(std::to_string( rate->GetBinLowEdge(i) ) ) , 200, 0, 1000 );
    // ratedijet->SetBinContent(newi, 31200 * recohist_dijet->Integral(recohisti,recohist_dijet->GetNbinsX()+1) / recohist->Integral());
    // sA = 0;
    // sC = 0;
    // A = recohist_dijet->IntegralAndError(recohisti,recohist_dijet->GetNbinsX()+1,sA);
    // C = recohist->IntegralAndError(0,recohist->GetNbinsX()+1,sC);
    // B = C-A;
    // err =std::sqrt( ((B*B)/(C*C*C*C))*(sA*sA)  +  ((A*A)/(C*C*C*C))*( sC*sC-sA*sA  )  ) ;
    // ratedijet->SetBinError(newi, 31200 * err );



    // //Di jet + vbf
    // recohist_dijetvbf = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", calibpt, cut_dijetvbf + "&&"+calibpt1 + ">" + TString(std::to_string( rate->GetBinLowEdge(i) ) ) , 200, 0, 1000 );
    // ratedijetvbf->SetBinContent(newi, 31200 * recohist_dijetvbf->Integral(recohisti,recohist_dijetvbf->GetNbinsX()+1) / recohist->Integral());
    // sA = 0;
    // sC = 0;
    // A = recohist_dijetvbf->IntegralAndError(recohisti,recohist_dijetvbf->GetNbinsX()+1,sA);
    // C = recohist->IntegralAndError(0,recohist->GetNbinsX()+1,sC);
    // B = C-A;
    // err =std::sqrt( ((B*B)/(C*C*C*C))*(sA*sA)  +  ((A*A)/(C*C*C*C))*( sC*sC-sA*sA  )  ) ;
    // ratedijetvbf->SetBinError(newi, 31200 * err );
    


    // // //Di jet + mass
    // recohist_dijetmass = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", calibpt, cut_dijetmass + "&&"+calibpt1 + ">" + TString(std::to_string( rate->GetBinLowEdge(i) ) ) , 200, 0, 1000 );
    // ratedijetmass->SetBinContent(newi, 31200 * recohist_dijetmass->Integral(recohisti,recohist_dijetmass->GetNbinsX()+1) / recohist->Integral());
    // sA = 0;
    // sC = 0;
    // A = recohist_dijetmass->IntegralAndError(recohisti,recohist_dijetmass->GetNbinsX()+1,sA);
    // C = recohist->IntegralAndError(0,recohist->GetNbinsX()+1,sC);
    // B = C-A;
    // err =std::sqrt( ((B*B)/(C*C*C*C))*(sA*sA)  +  ((A*A)/(C*C*C*C))*( sC*sC-sA*sA  )  ) ;
    // ratedijetmass->SetBinError(newi, 31200 * err );
    



  }
  _outdir = _cmd->string_val( "--outdir" );
  rate_graph->SaveAs(("plots/" + _outdir + "/rateg_Inclusive_"+algo+".root").c_str());

  ratevec.push_back(rate);


  // ratevec.push_back(ratedijet);  
  // ratevec.push_back(ratedijetmass);  
  ratevec.push_back(ratevbf);  
  //  ratevec.push_back(ratedijetvbf);  




  rategraphvec.push_back(rate_graph);

  Plotter plotter( _cmd );
  //  plotter.Draw(rate, "rate", "rate", true);
  plotter.Draw(ratevec, legend, "rate_" + algo, true);


  
  
}


