#include "HGC.h"

void HGC::plot_profile_L1jet_response_pt_VBFHInv_PU0_STC(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";  
  //  TString cut = " abs(genjet_eta)>1.6 && abs(genjet_eta)<2.9 && genjet_pt>20";  
  //  std::vector<TH2F*> histo;

  std::vector<HistObject> histobjects;
  histobjects.push_back( HistObject( "Jets", (snwebb + "/VBF_Hinv_threshold/jet_ntuples_merged/ntuple_jet_merged_1.root"), "Thresh PU=0", "jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]:genjet_pt[VBF_parton_genjet]", cut+"&&jets_pt[VBF_parton_jets]>0", false ) );
  histobjects.push_back( HistObject( "Jets", (snwebb + "/VBF_Hinv_stc/jet_ntuples_merged/ntuple_jet_merged_1.root"), "STC PU=0", "jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]:genjet_pt[VBF_parton_genjet]", cut+"&&jets_pt[VBF_parton_jets]>0", false ) );

  // std::vector<TString> leg_entry;
  // leg_entry.push_back("Thresh PU=0 ");
  // leg_entry.push_back("STC PU=0 ");

  PlotterResponse plotter( _cmd );
  plotter.Draw(  histobjects, "PU0_STC_TEST2", "pt");

}


void HGC::plot_profile_L1jet_response_pt_PU0_STC(){

  TString cut = " abs(genjet_eta)>1.6 && abs(genjet_eta)<2.9 && genjet_pt>20";  

  std::vector<HistObject> histobjects;
  histobjects.push_back( HistObject( "Gamma", (snwebb + "/SingleGammaPt25_PU0_threshold_1031/jet_ntuples_merged/ntuple_jet_merged_*.root"), "Thresh PU=0", "jets_pt/genjet_pt:genjet_pt", cut+"&&jets_pt>0", false ) );
  histobjects.push_back( HistObject( "Gamma", (snwebb + "/SingleGammaPt25_PU0_stc_1031/jet_ntuples_merged/ntuple_jet_merged_*.root"), "STC PU=0", "jets_pt/genjet_pt:genjet_pt", cut+"&&jets_pt>0", false ) );

  PlotterResponse plotter( _cmd );
  plotter.Draw(  histobjects, "PU0_STC_TEST", "pt");

}


void HGC::plot_profile_L1jet_response_eta_PU0_STC(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";  

  //  std::vector<TH2F*> histo;

  std::vector<HistObject> histobjects;
  histobjects.push_back( HistObject( "Gamma", (snwebb + "/SingleGammaPt25_PU0_threshold_1031/jet_ntuples_merged/ntuple_jet_merged_*.root"), "Thresh PU=0", "jets_pt/genjet_pt:genjet_pt", cut+"&&jets_pt>0", false ) );
  histobjects.push_back( HistObject( "Gamma", (snwebb + "/SingleGammaPt25_PU0_stc_1031/jet_ntuples_merged/ntuple_jet_merged_*.root"), "STC PU=0", "jets_pt/genjet_pt:genjet_pt", cut+"&&jets_pt>0", false ) );

  // std::vector<TString> leg_entry;
  // leg_entry.push_back("Thresh PU=0 ");
  // leg_entry.push_back("STC PU=0 ");

  PlotterResponse plotter( _cmd );
  plotter.Draw(  histobjects, "PU0_STC_TEST", "eta");

}
