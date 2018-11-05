#include "HGC.h"


void HGC::plot_profile_L1jet_response_pt_PU0_STC(){
  
  TString cut = " abs(genjet_eta)>1.6 && abs(genjet_eta)<2.9 && genjet_pt>20";

  std::vector<TH2F*> histo;
  histo.push_back( helper.single_plot2D(snwebb + "/SingleGammaPt25_PU0_threshold_1031/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt","jets_pt/genjet_pt",cut+"&& jets_pt>0",25,24.95,25.05,97,0.06,2));
  histo.push_back( helper.single_plot2D(snwebb + "/SingleGammaPt25_PU0_stc_1031/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt","jets_pt/genjet_pt",cut+"&& jets_pt>0",25,24.95,25.05,97,0.06,2));

  std::vector<TString> leg_entry;
  leg_entry.push_back("Thresh PU=0 ");
  leg_entry.push_back("STC PU=0 ");

  PlotterResponse plotter;
  plotter.Draw(  histo, leg_entry, "PU0_STC_TEST", "pt");

}


void HGC::plot_profile_L1jet_response_eta_PU0_STC(){
  
  TString cut = " abs(genjet_eta)>1.6 && abs(genjet_eta)<2.9 && genjet_pt>20";

  std::vector<TH2F*> histo;
  histo.push_back( helper.single_plot2D(snwebb + "/SingleGammaPt25_PU0_threshold_1031/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta)","jets_pt/genjet_pt",cut+"&& jets_pt>0",13,1.6,2.9,97,0.06,2));
  histo.push_back( helper.single_plot2D(snwebb + "/SingleGammaPt25_PU0_stc_1031/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","abs(genjet_eta)","jets_pt/genjet_pt",cut+"&& jets_pt>0",13,1.6,2.9,97,0.06,2));

  std::vector<TString> leg_entry;
  leg_entry.push_back("Thresh PU=0 ");
  leg_entry.push_back("STC PU=0 ");

  PlotterResponse plotter;
  plotter.Draw(  histo, leg_entry, "PU0_STC_TEST", "eta");

}
