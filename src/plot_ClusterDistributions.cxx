//Previously plot_C2D_dR.C
#include "HGC.h"
#include "Plotter.h"

void HGC::plot_GenRecoET(){

  //        TString stats = "full";
  //    TString stats = "2";
  //            TString stats = "10*";
  //  TString stats = "*";
                     TString stats = "1*";

  TString file_OneBit4444Fixed       = "VBF_Hinv/VBF-PU200-OneBit-4-4-4-4-Fixed";	  
  TString file_EqualShare4444Fixed   = "VBF_Hinv/VBF-PU200-EqualShare-4-4-4-4-Fixed";
  TString file_Threshold3p0	     = "VBF_Hinv/VBF-PU200-Threshold-3p0";		  
  TString file_Threshold2p0	     = "VBF_Hinv/VBF-PU200-Threshold-2p0";		  
  TString file_Threshold1p5	     = "VBF_Hinv/VBF-PU200-Threshold-1p5";		  
  TString file_Threshold1p0	     = "VBF_Hinv/VBF-PU200-Threshold-1p0";		  
  TString file_Threshold0p5	     = "VBF_Hinv/VBF-PU200-Threshold-0p5";		  
  TString file_Threshold0p0	     = "VBF_Hinv/VBF-PU200-Threshold-0p0";             


  TString file_hgg_Threshold	     = "VBF_HGG/VBF-HGG-PU200-MultiAlgo-Threshold";		  
  //V9 For Workshop
  TString file_v9_Threshold	     = "VBF_HTT/VBF-HTT-PU200-MultiAlgo-Threshold";		  
  TString file_v9_SuperTCs	     = "VBF_HTT/VBF-HTT-PU200-MultiAlgo-SuperTCs";		  
  TString file_v9_SeedThreshold	     = "VBF_HTT/VBF-HTT-PU200-MultiAlgo-SeedThreshold";		  
  TString file_v9_ClusterRadius	     = "VBF_HTT/VBF-HTT-PU200-MultiAlgo-ClusterRadius";		  
  //V8 For Workshop
  TString file_v8_Threshold	     = "VBF_Hinv/VBF-PU200-MultiAlgo-Threshold";		  
  TString file_v8_SuperTCs	     = "VBF_Hinv/VBF-PU200-MultiAlgo-SuperTCs";		  
  TString file_v8_SeedThreshold	     = "VBF_Hinv/VBF-PU200-MultiAlgo-SeedThreshold";		  
  TString file_v8_ClusterRadius	     = "VBF_Hinv/VBF-PU200-MultiAlgo-ClusterRadius";		  

  TString file_v8_Threshold_dr175	     = "VBF_Hinv/VBF-PU200-MultiAlgo-Threshold-DR1p75";		  
  TString file_v8_SuperTCs_dr175	     = "VBF_Hinv/VBF-PU200-MultiAlgo-SuperTCs-DR1p75";		  
  TString file_v8_SeedThreshold_dr175	     = "VBF_Hinv/VBF-PU200-MultiAlgo-SeedThreshold-DR1p75";		  

  TString file_v9_Default_WithTriggerCells = "VBF_HTT/VBF-HTT-PU200-Default-WithTriggerCells-WS";
  TString file_v8_Default_WithTriggerCells = "VBF_Hinv/VBF-PU200-Default-WithTriggerCells";

  TString file_httws_Threshold	     = "VBF_HTT/VBF-HTT-PU200-MultiAlgo-Threshold-WS";		  
  TString file_httws_SuperTCs	     = "VBF_HTT/VBF-HTT-PU200-MultiAlgo-SuperTCs-WS";		  
  TString file_httws_SeedThreshold	     = "VBF_HTT/VBF-HTT-PU200-MultiAlgo-SeedThreshold-WS";		  
  TString file_httws_ClusterRadius	     = "VBF_HTT/VBF-HTT-PU200-MultiAlgo-ClusterRadius-WS";		  


  TString file_hggws_Threshold	     = "VBF_HGG/VBF-HGG-PU200-MultiAlgo-Threshold-WS";		  
  TString file_hggws_SuperTCs	     = "VBF_HGG/VBF-HGG-PU200-MultiAlgo-SuperTCs-WS";		  
  TString file_hggws_SeedThreshold	     = "VBF_HGG/VBF-HGG-PU200-MultiAlgo-SeedThreshold-WS";		  
  TString file_hggws_ClusterRadius	     = "VBF_HGG/VBF-HGG-PU200-MultiAlgo-ClusterRadius-WS";		  

  //  TString file_VBF_Decentralised = "VBF_HGG/VBF-HGG-PU200-MultiAlgo-Decentralised";
  TString file_VBF_Decentralised = "VBF_HGG/VBF-HGG-PU200-Decentralised";
  TString file_VBF_Default = "VBF_HGG/VBF-HGG-PU200-Default";
  TString file_Nu_Decentralised = "DoubleNu/DoubleNu-PU200-Decentralised";

  // TString file_VBF_Decentralised = "VBF_HGG/VBF-HGG-PU200-MultiAlgo-Decentralised-BugFix";
  // TString file_Nu_Decentralised = "DoubleNu/DoubleNu-PU200-MultiAlgo-Decentralised-BugFix";

  TString file_QG_Pos_200 = "QuarkGun/QuarkGun-Pos-PU200-Decentralised";
  TString file_QG_Pos_140 = "QuarkGun/QuarkGun-Pos-PU140-Decentralised";
  TString file_QG_Pos_0 = "QuarkGun/QuarkGun-Pos-PU0-Decentralised";

  TString tree_dr175_Threshold0p0  = "Fp8Threshold0p0DummyHistomaxvardrdrho1p75Ntup";
  TString tree_dr175_Threshold0p5  = "Fp8Threshold0p5DummyHistomaxvardrdrho1p75Ntup";
  TString tree_dr175_Threshold1p0  = "Fp8Threshold1p0DummyHistomaxvardrdrho1p75Ntup";
  TString tree_dr175_Threshold1p5  = "Fp8Threshold1p5DummyHistomaxvardrdrho1p75Ntup";
  TString tree_dr175_Threshold2p0  = "Fp8Threshold2p0DummyHistomaxvardrdrho1p75Ntup";
  TString tree_dr175_Threshold3p0  = "Fp8Threshold3p0DummyHistomaxvardrdrho1p75Ntup";  

  TString tree_v9_Threshold0p0  = "Fp8Threshold0p0DummyHistomaxvardrdrho1p0Ntup";
  TString tree_v9_Threshold0p5  = "Fp8Threshold0p5DummyHistomaxvardrdrho1p0Ntup";
  TString tree_v9_Threshold1p0  = "Fp8Threshold1p0DummyHistomaxvardrdrho1p0Ntup";
  TString tree_v9_Threshold1p5  = "Fp8Threshold1p5DummyHistomaxvardrdrho1p0Ntup";
  TString tree_v9_Threshold2p0  = "Fp8Threshold2p0DummyHistomaxvardrdrho1p0Ntup";
  TString tree_v9_Threshold3p0  = "Fp8Threshold3p0DummyHistomaxvardrdrho1p0Ntup";

  TString tree_v8_Threshold0p0  = "Fp8Threshold0p0DummyHistomaxvardrth10Ntup"; 
  TString tree_v8_Threshold0p5  = "Fp8Threshold0p5DummyHistomaxvardrth10Ntup";
  TString tree_v8_Threshold1p0  = "Fp8Threshold1p0DummyHistomaxvardrth10Ntup";
  TString tree_v8_Threshold1p5  = "Fp8Threshold1p5DummyHistomaxvardrth10Ntup";
  TString tree_v8_Threshold2p0  = "Fp8Threshold2p0DummyHistomaxvardrth10Ntup";
  TString tree_v8_Threshold3p0  = "Fp8Threshold3p0DummyHistomaxvardrth10Ntup";


  TString tree_v8_Stc16  = "Fp8Stc4161616DummyHistomaxvardrth10Ntup";
  TString tree_v8_Stc4  = "Fp8Stc4444FixedDummyHistomaxvardrth10Ntup";
  TString tree_v8_ES  = "Fp8EqualShare4444FixedDummyHistomaxvardrth10Ntup";
  TString tree_v8_OB  = "Fp8Onebit4444FixedDummyHistomaxvardrth10Ntup";
  TString tree_v8_best  = "Fp8BestchoiceDummyHistomaxvardrth10Ntup";
 
  TString tree_dr175_Stc16  = "Fp8Stc4161616DummyHistomaxvardrdrho1p75Ntup";
  TString tree_dr175_Stc4  = "Fp8Stc4444FixedDummyHistomaxvardrdrho1p75Ntup";
  TString tree_dr175_ES  = "Fp8EqualShare4444FixedDummyHistomaxvardrdrho1p75Ntup";
  TString tree_dr175_OB  = "Fp8Onebit4444FixedDummyHistomaxvardrdrho1p75Ntup";
  TString tree_dr175_best  = "Fp8BestchoiceDummyHistomaxvardrdrho1p75Ntup";

  TString tree_v9_Stc16  = "Fp8Stc4161616DummyHistomaxvardrdrho1p0Ntup";
  TString tree_v9_Stc4  = "Fp8Stc4444FixedDummyHistomaxvardrdrho1p0Ntup";
  TString tree_v9_ES  = "Fp8EqualShare4444FixedDummyHistomaxvardrdrho1p0Ntup";
  TString tree_v9_OB  = "Fp8Onebit4444FixedDummyHistomaxvardrdrho1p0Ntup";
  TString tree_v9_best  = "Fp8BestchoiceDummyHistomaxvardrdrho1p0Ntup";

  TString tree_v9_default  = "hgcalTriggerNtuplizer";

  TString tree_v9_Seed0  = "Fp8ThresholdDummyHistomaxvardrth0Ntup";
  TString tree_v9_Seed10  = "Fp8ThresholdDummyHistomaxvardrth10Ntup";
  TString tree_v9_Seed20  = "Fp8ThresholdDummyHistomaxvardrth20Ntup";
  TString tree_v9_Seed30  = "Fp8ThresholdDummyHistomaxvardrth30Ntup";
  TString tree_v9_Seed40  = "Fp8ThresholdDummyHistomaxvardrth40Ntup";
  TString tree_v9_Seed50  = "Fp8ThresholdDummyHistomaxvardrth50Ntup";
  TString tree_v9_Seed100  = "Fp8ThresholdDummyHistomaxvardrth100Ntup";
  
  TString tree_v9_dr1p0  ="Fp8ThresholdDummyHistomaxvardrdrho1p0Ntup";
  TString tree_v9_dr1p25  ="Fp8ThresholdDummyHistomaxvardrdrho1p25Ntup";
  TString tree_v9_dr1p5  ="Fp8ThresholdDummyHistomaxvardrdrho1p5Ntup";
  TString tree_v9_dr1p75  ="Fp8ThresholdDummyHistomaxvardrdrho1p75Ntup";
  TString tree_v9_dr2p0  ="Fp8ThresholdDummyHistomaxvardrdrho2p0Ntup";
  TString tree_v9_dr3p0  ="Fp8ThresholdDummyHistomaxvardrdrho3p0Ntup";
  TString tree_v9_dr5p0  ="Fp8ThresholdDummyHistomaxvardrdrho5p0Ntup";




  TString tree_thresh  =  "Fp8ThresholdDummyHistomaxNtup";
  //  TString tree_stc  =    "Fp8Stc4444FixedDummyHistomaxNtup";
  //  TString tree_stc  =    "Fp8Stc4161616DummyHistomaxbin4Ntup";
   TString tree_stc  =    "Fp8Stc4161616DummyHistomaxNtup";

  TString tree_bc  =    "Fp8BestchoiceDummyHistomaxNtup";

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


  //  double y[7]={0,10,20,40,60,80,100};
  double y[11]={0,10,20,30,40,50,60,70,80,90,100};
  

    TString file = file_VBF_Decentralised;
  //  TString file = file_VBF_Default;
    //    file = file_Nu_Decentralised;
  //      TString file = file_QG_Pos_200;

  // std::vector<TString> trees = { tree_thresh, tree_stc, tree_bc};
  // std::vector<TString> description = { "th","stc","bc", "th","stc","bc",};
  // std::vector<TString> legend = { "ThresholdLow","STCLow","Best ChoiceLow", "thresholdHigh","STCHigh","Best ChoiceHigh",};
  // std::vector<TString> trees = { tree_bc};
  // std::vector<TString> description = { "bc1", "bc2", "bc3"};
  // std::vector<TString> legend = { "1.8-2.1", "2.1-2.4", "2.4-2.7" };
  

  // std::vector<TString> trees = { tree_bc, tree_bc,tree_bc};
  // std::vector<TString> description = { "200", "140", "0"};
  // std::vector<TString> legend = { "200", "140", "0"};

  // std::vector<TString> trees = { tree_stc, tree_stc,tree_stc};
  // std::vector<TString> description = { "200", "140", "0"};
  // std::vector<TString> legend = { "200", "140", "0"};

  // std::vector<TString> trees = { tree_thresh, tree_thresh,tree_thresh,};
  // std::vector<TString> description = { "200", "140", "0"};
  // std::vector<TString> legend = { "200", "140", "0"};

  // std::vector<TString> trees = { tree_thresh, tree_stc, tree_bc};
  // std::vector<TString> description = { "th","stc","bc"};
  // std::vector<TString> legend = { "Threshold","STC","Best Choice"};

  // std::vector<TString> trees = { tree_bc};
  // std::vector<TString> description = { "bc"};
  // std::vector<TString> legend = { "Best Choice"};

  std::vector<TString> trees = { tree_thresh};
  std::vector<TString> description = { "th"};
  std::vector<TString> legend = { "th" };
 
 
  //   for(unsigned int i=0;i<files.size();i++){
  for(unsigned int i=0;i<trees.size();i++){

     // if (i==1) file = file_QG_Pos_140;
     // if (i==2) file = file_QG_Pos_0;

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


  TProfile* profile = 0;

  for(unsigned int i=0;i<histobjects.size();i++){
    TH2F * hist = plotter->Draw2D(histobjects.at(i), 15, x, 4000,0,400  ,description.at(i) );//VBF
    //    TH2F * hist = plotter.Draw2D(histobjects.at(i), 10, y, 4000,0,400  ,description.at(i) );//Pion

    graphs.emplace_back( plotter->DrawProfile(hist  ,(description.at(i)+"_profile"), "s" ) );

    profile = hist->ProfileX( "profile_mean_eff");

    // hist = plotter.Draw2D(histobjects2.at(i), 15, x, 4000,0,400  ,description.at(i) + "_high_eta");
    // graphs.emplace_back( plotter.DrawProfile(hist  ,(description.at(i)+"_profile_high_eta"), "s" ) );
 

 }


  plotter->DrawGraphs(graphs, legend);
  //  plotter.DrawEtaGraphs(graphs );
  plotter->SaveFile( graphs );


  TF1 * pol_choice = new TF1 ( "pol", "[0] + [1]*x + [2]*x*x" , 20 , 350);

  profile->Fit( pol_choice, "R","",20,300);
  
  profile->GetFunction("pol")->GetParameter( 0 ); 
  profile->GetFunction("pol")->GetParameter( 1 ) ;
  profile->GetFunction("pol")->GetParameter( 2 ) ;
  
  delete plotter;

  
  //   CalculateEfficiency( profile->GetFunction("pol")->GetParameter( 0 ), profile->GetFunction("pol")->GetParameter( 1 ), profile->GetFunction("pol")->GetParameter( 2 )  );

  CalculateRates ( profile->GetFunction("pol")->GetParameter( 0 ), profile->GetFunction("pol")->GetParameter( 1 ), profile->GetFunction("pol")->GetParameter( 2 ) );

  

  /*
  std::vector<TH1F*> hist;

  for(unsigned int i=0;i<files.size();i++){

    TString cutval = "0.5";
    // if ( i == 1 ) cutval = "1";
    // if ( i == 2 ) cutval = "2";
    // if ( i == 3 ) cutval = "5";
    // if ( i == 4 ) cutval = "10";
    //    TH1F * ncl3D = helper.single_plot( tstreble + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_2.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 250,0,750);


    //        TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_5.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 300,300.5,900.5);
        TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_11.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 300,0.5,600.5);
    //    TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_5.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 500,300,1800);
    //    TH1F * ncl3D = helper.single_plot( snwebb + "/" +files.at(i) +"/jet_ntuples_merged/ntuple_jet_merged_2.root" , "HGCalTriggerNtupleJet", "Sum$(cl3d_pt>"+cutval+")/2", "", 14,-0.5,6.5);

    ncl3D->SetTitle(";3D clusters per endcap;arbitrary units");
    ncl3D->Scale(1/(ncl3D->Integral()));
    hist.push_back( ncl3D );
 
  }
 
  plotter.Draw( hist , legend, "ncl3d" , true);
  */ 

  



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


void HGC::JetStudies(){

  std::string stats = "*";

  // std::string file1 = "VBF_HGG/VBF-HGG-PU200-MultiAlgo-Decentralised-BugFix";
  // std::string file2 = "DoubleNu/DoubleNu-PU200-MultiAlgo-Decentralised-BugFix";

  //  std::string file1 = "VBF_HGG/VBF-HGG-PU200-MultiAlgo-Decentralised";
  //  std::string file1 = "VBF_HGG/VBF-HGG-PU200-Default";
  std::string file1 = "VBF_HGG/VBF-HGG-PU200-Decentralised";
  //  std::string file2 = "DoubleNu/DoubleNu-PU200-MultiAlgo-Decentralised";
  //  TString file_VBF_Default = "VBF_HGG/VBF-HGG-PU200-Default";

  std::string file2 = "DoubleNu/DoubleNu-PU200-Decentralised";

  //  std::string tree = "Fp8Stc4444FixedDummyHistomaxNtup";


  //std::string tree1 = "Fp8Stc4161616DummyHistomaxNtup";
std::string tree1 = "Fp8ThresholdDummyHistomaxNtup";

std::string tree = "Fp8ThresholdDummyHistomaxNtup";
  //  std::string tree ="Fp8Stc4161616DummyHistomaxbin4Ntup";
  std::string jetpt_low = "0";
  std::string jetpt_high = "10000";

  //NCL == 1
   // TString cut_basic = "abs(jets_eta)>1.7 && abs(jets_eta)<2.8 && jets_pt>" +jetpt_low +  " && jets_pt<"+jetpt_high + "&&jets_n_cl==1";
   // TString cut_vbf = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8 && genjet_pt[VBF_parton_genjet]>"+jetpt_low +"&& genjet_pt[VBF_parton_genjet]<"+jetpt_high + "&&jets_n_cl[VBF_parton_jets]==1";

   TString cut_basic = "abs(jets_eta)>1.7 && abs(jets_eta)<2.8 && jets_pt>" +jetpt_low +  " && jets_pt<"+jetpt_high;
   TString cut_vbf = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8 && genjet_pt[VBF_parton_genjet]>"+jetpt_low +"&& genjet_pt[VBF_parton_genjet]<"+jetpt_high;


   TString cut_vbf_etalow = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.1 && genjet_pt[VBF_parton_genjet]>"+jetpt_low +"&& genjet_pt[VBF_parton_genjet]<"+jetpt_high;
   TString cut_vbf_etahigh = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.4 && abs(genjet_eta[VBF_parton_genjet])<2.8 && genjet_pt[VBF_parton_genjet]>"+jetpt_low +"&& genjet_pt[VBF_parton_genjet]<"+jetpt_high;
   TString cut_vbf_etamid = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>2.1 && abs(genjet_eta[VBF_parton_genjet])<2.4 && genjet_pt[VBF_parton_genjet]>"+jetpt_low +"&& genjet_pt[VBF_parton_genjet]<"+jetpt_high;

   //TString cut_basic = "abs(jets_eta)>1.7 && abs(jets_eta)<2.8";
  //  TString cut_basic = """";
   //  TString cut_vbf = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8";

   std::vector<HistObject> histobjects, histobjects_n_cl, histobjects_firstfrac, histobjects_srrsum, histobjects_srrjet, histobjects_sppsum, histobjects_sppjet, histobjects_spp_best, histobjects_srr_best, histobjects_spp_paul,histobjects_srr_paul, histobjects_sppsrr;

  HistObject histobjects_2d( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_cl[VBF_parton_jets]:jets_pt[VBF_parton_jets]" ,cut_vbf, true  );

  HistObject histobjects_2d_etalow( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_cl[VBF_parton_jets]:jets_pt[VBF_parton_jets]" ,cut_vbf_etalow, true  );
  HistObject histobjects_2d_etamid( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_cl[VBF_parton_jets]:jets_pt[VBF_parton_jets]" ,cut_vbf_etamid, true  );
  HistObject histobjects_2d_etahigh( "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root"), tree1+"_Jet", "vbf", "jets_n_cl[VBF_parton_jets]:jets_pt[VBF_parton_jets]" ,cut_vbf_etahigh, true  );

  HistObject histobjects_2d_pu( "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree +"_"+stats+".root"), tree+"_Jet", "vbf", "jets_n_cl:jets_pt" ,cut_basic, true  );

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



  Plotter plotter( _cmd );





  //  plotter.Draw(histobjects, 100, 0, 200  ,"pt" );

  // plotter.Draw(histobjects_n_cl, 10, -0.5, 9.5  ,"ncl" );

  // plotter.Draw(histobjects_firstfrac, 51, 0,1.01  ,"ff" );

  // plotter.Draw(histobjects_srrsum, 100, 0,0.05  ,"srrsum" );
  // plotter.Draw(histobjects_srrjet, 100, 0,0.05  ,"srrjet" );

  // plotter.Draw(histobjects_sppsum, 100, 0,0.2  ,"sppsum" );
  // plotter.Draw(histobjects_sppjet, 100, 0,0.05  ,"sppjet" );

  plotter.Draw2D(histobjects_2d, 100, 0,200,10,-0.5,9.5  ,"nclpt_vbf" );
  plotter.Draw2D(histobjects_2d_pu, 100, 0,200,10,-0.5,9.5  ,"nclpt_pu" );
  

  plotter.Draw2D(histobjects_2d_etalow, 100, 0,200,10,-0.5,9.5  ,"nclpt_vbf_etalow" );
  plotter.Draw2D(histobjects_2d_etamid, 100, 0,200,10,-0.5,9.5  ,"nclpt_vbf_etamid" );
  plotter.Draw2D(histobjects_2d_etahigh, 100, 0,200,10,-0.5,9.5  ,"nclpt_vbf_etahigh" );

  // plotter.Draw(histobjects_srr_best, 100, -0.05,0.1  ,"srr_best" );
  // plotter.Draw(histobjects_spp_best, 100, -0.1,0.5  ,"spp_best" );

  // plotter.Draw(histobjects_srr_paul, 100, -0.05,0.1  ,"srr_paul" );
  // plotter.Draw(histobjects_spp_paul, 100, -0.1,0.5  ,"spp_paul" );

  //  plotter.Draw(histobjects_sppsrr, 100, -10,20  ,"s_div" );


}

void HGC::CalculateEfficiency(double par0, double par1, double par2){
  
  std::string stats = "*";
  std::string file1 = "VBF_HGG/VBF-HGG-PU200-Decentralised";

  std::string tree1 = "Fp8ThresholdDummyHistomaxNtup";


  //  std::string jetpt_low = "40";
  TString cut_gen = "VBF_parton_genjet>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8";
  
  std::vector<TH1F*> turnons;
  //   std::vector<TEfficiency*> turnons_eff;
  std::vector<TString> legend;
  
   TH1F* genhist = 0;
   TH1F* recohist = 0;

   //   std::vector<TString> cuts = {"10","20","30","40","50", "100", "150"};

   std::vector<TString> cuts = {"150","100","50","40","30", "20", "10"};
   std::vector<double> cutsdouble = {150,100,50,40,30, 20, 10};
   std::vector<double> values95;

   //      std::vector<TString> cuts = {"40"};
   //   TF1 * fit = new TF1 ( "f1","-exp([0]/(x-[1]))+2",11,200);
   //   TF1 * fit = new TF1 ( "f1","0.5*TMath::Erf( ( (x-[0])/[1] ) )+0.5",0,200);
   //      TF1 * fit = new TF1 ( "f1","0.5*[2]*TMath::TanH( ( (x-[0])/[1] ) )+0.5*[3]",0,300);


   TF1 * fit = new TF1 ( "f1","0.5*[2]*TMath::TanH( ( (x-[0])/[1] ) )+0.5*[3]",0,300);



   //   TF1 * fit = new TF1 ( "f1"," -[3] /  ( 1 + pow( ((x-[0])/[1]),[2] )  )  ",0,300);

   // fit->SetParameter(1,15);
   // fit->SetParameter(2,7);
   // fit->SetParameter(3,1.5);


   //   TF1 * fit = new TF1 ( "f1","0.25*TMath::TanH( ( (x-[0])/[1] ) ) + 0.25*TMath::TanH( ( (x-[0])/[2] ) )  +0.5",0,200);

   fit->SetParameter(1,20);
   fit->SetParameter(2,1);
   fit->SetParameter(3,1);

   genhist = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", "genjet_pt[VBF_parton_genjet]", cut_gen, 100, 0, 300 );

   for ( int i = 0; i < cuts.size(); i++){
     fit->SetParameter(0,cutsdouble.at(i));
     fit->SetRange( cutsdouble.at(i)-10,(1.3)*cutsdouble.at(i)+50);
     //     TString cut_reco = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8 && jets_pt[VBF_parton_jets]>"+cuts.at(i);
     
     TString calibpt = "( -"+TString(std::to_string(par1))+ "+ sqrt( " +  TString(std::to_string(par1*par1)) + "- 4*"+TString(std::to_string(par2))+"*("+TString(std::to_string(par0))+"-jets_pt[VBF_parton_jets]) ) ) / (2 * "+TString(std::to_string(par2))+")";

     std::cout << calibpt << std::endl;


     TString cut_reco = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.7 && abs(genjet_eta[VBF_parton_genjet])<2.8 && "+ calibpt + ">"+cuts.at(i);

     //     std::cout << cut_reco << std::endl;

     recohist = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", "genjet_pt[VBF_parton_genjet]", cut_reco, 100, 0, 300 );
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

     turnons.push_back(recohist);
     //     turnons_eff.push_back(pEff);
     legend.push_back(cuts.at(i) + " pT");
     values95.push_back( fit->GetX( 0.95 ) );


   }

   TVectorD t_cutsdouble(cutsdouble.size(), &cutsdouble[0]);
   TVectorD t_values95(values95.size(), &values95[0]);

   TGraph * graph = new TGraph(t_cutsdouble,t_values95);

   //   std::cout << "efficiency = " << recohist->Integral() / genhist->Integral() << std::endl;
   
   Plotter plotter2( _cmd );
   //   plotter.Draw(recohist, "40", "turnon", false);


   plotter2.Draw(turnons, legend, "turnon", false);


   plotter2.DrawGraph(graph , "95eff");

   //   plotter.DrawEff(turnons_eff, legend, "turnon_eff", false);
   //   std::cout << "end of here " << std::endl;
   
   

}

void HGC::CalculateRates(double par0, double par1, double par2){

  
  std::string stats = "1*";
  std::string file1 = "DoubleNu/DoubleNu-PU200-Decentralised";
  std::string tree1 = "Fp8ThresholdDummyHistomaxNtup";

  std::vector<TH1F*> ratevec;
  std::vector<TString> legend = {"Inclusive", "VBF-like", "di-jet"};
  //  std::vector<TString> cuts = {"10","20","30","40","50","60","70","80","90","100","110","120","130","140","150","160","170","180","190","200"};

  TH1F * recohist = 0;  
  TH1F * recohist_vbf = 0;  
  TH1F * recohist_dijet = 0;  

  TString cut_basic = "abs(jets_eta[0])>1.7 && abs(jets_eta[0])<2.8";
  TString cut_vbf = cut_basic + "&& jets_n_cl[0] < 3";
  TString cut_dijet = cut_basic + "&& abs(jets_eta[1])>1.7 && abs(jets_eta[1])<2.8";


  TString calibpt = "( -"+TString(std::to_string(par1))+ "+ sqrt( " +  TString(std::to_string(par1*par1)) + "- 4*"+TString(std::to_string(par2))+"*("+TString(std::to_string(par0))+"-jets_pt[0]) ) ) / (2 * "+TString(std::to_string(par2))+")";
  TString calibpt1 = "( -"+TString(std::to_string(par1))+ "+ sqrt( " +  TString(std::to_string(par1*par1)) + "- 4*"+TString(std::to_string(par2))+"*("+TString(std::to_string(par0))+"-jets_pt[1]) ) ) / (2 * "+TString(std::to_string(par2))+")";


  recohist = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", calibpt, cut_basic, 200, 0, 1000 );
  recohist_vbf = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", calibpt, cut_vbf, 200, 0, 1000 );
  

  int nbins = 40;
  TH1F * rate = new TH1F("rate","",nbins,2.5,202.5);
  TH1F * ratevbf = new TH1F("rate_vbf","",nbins,2.5,202.5);  
  TH1F * ratedijet = new TH1F("rate_dijet","",nbins,2.5,202.5);  
  //  for ( int i = 0; i < cuts.size(); i++){
  for ( int i = 1; i < nbins + 1; i++){

    //Inclusive
    rate->SetBinContent(i, 31200 * recohist->Integral(i,recohist->GetNbinsX()+1) / recohist->Integral());
    double sA = 0;
    double sC = 0;
    double A = recohist->IntegralAndError(i,recohist->GetNbinsX()+1,sA);
    double C = recohist->IntegralAndError(0,recohist->GetNbinsX()+1,sC);
    double B = C-A;
    double err =std::sqrt( ((B*B)/(C*C*C*C))*(sA*sA)  +  ((A*A)/(C*C*C*C))*( sC*sC-sA*sA  )  ) ;
    rate->SetBinError(i, 31200 * err );


    //VBF like
    ratevbf->SetBinContent(i, 31200 * recohist_vbf->Integral(i,recohist_vbf->GetNbinsX()+1) / recohist->Integral());
    sA = 0;
    sC = 0;
    A = recohist_vbf->IntegralAndError(i,recohist_vbf->GetNbinsX()+1,sA);
    C = recohist->IntegralAndError(0,recohist->GetNbinsX()+1,sC);
    B = C-A;
    err =std::sqrt( ((B*B)/(C*C*C*C))*(sA*sA)  +  ((A*A)/(C*C*C*C))*( sC*sC-sA*sA  )  ) ;
    ratevbf->SetBinError(i, 31200 * err );


    std::cout <<  cut_dijet + "&&"+ calibpt1 + ">" + TString(std::to_string( rate->GetBinLowEdge(i) ) );
    //Di jet
    recohist_dijet = helper.single_plot( snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_"+ tree1 +"_"+stats+".root", tree1+"_Jet", calibpt, cut_dijet + "&&"+calibpt1 + ">" + TString(std::to_string( rate->GetBinLowEdge(i) ) ) , 200, 0, 1000 );
    ratedijet->SetBinContent(i, 31200 * recohist_dijet->Integral(i,recohist_dijet->GetNbinsX()+1) / recohist->Integral());
    sA = 0;
    sC = 0;
    A = recohist_dijet->IntegralAndError(i,recohist_dijet->GetNbinsX()+1,sA);
    C = recohist->IntegralAndError(0,recohist->GetNbinsX()+1,sC);
    B = C-A;
    err =std::sqrt( ((B*B)/(C*C*C*C))*(sA*sA)  +  ((A*A)/(C*C*C*C))*( sC*sC-sA*sA  )  ) ;
    ratedijet->SetBinError(i, 31200 * err );
    



  }

  ratevec.push_back(rate);
  ratevec.push_back(ratevbf);  
  ratevec.push_back(ratedijet);  
  Plotter plotter( _cmd );
  //  plotter.Draw(rate, "rate", "rate", true);
  plotter.Draw(ratevec, legend, "rate", true);
  
}


