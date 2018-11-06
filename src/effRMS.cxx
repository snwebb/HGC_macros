#include "HGC.h"


void HGC::plot_effRMS_pT_C3D_histo_PU0_STC(){
  
  //  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";
  TString cut =  "abs(genjet_eta)>1.6 && abs(genjet_eta)<2.9 && genjet_pt>20";
  TString var = "jets_pt/genjet_pt";
  std::vector<HistObject> histobjects;
  bool PUS = false;

  histobjects.push_back( HistObject(  "Gamma", (snwebb + "/SingleGammaPt25_PU0_threshold_1031/jet_ntuples_merged/ntuple_jet_merged_*.root"), "Threshold", var, cut, PUS  ) );
  histobjects.push_back( HistObject(  "Gamma", (snwebb + "/SingleGammaPt25_PU0_stc_1031/jet_ntuples_merged/ntuple_jet_merged_*.root"), "STC", var, cut, PUS  ) );


  // std::vector<TString> filename;
  // filename.push_back((snwebb + "/SingleGammaPt25_PU0_threshold_1031/jet_ntuples_merged/ntuple_jet_merged_*.root"));
  // filename.push_back((snwebb + "/SingleGammaPt25_PU0_stc_1031/jet_ntuples_merged/ntuple_jet_merged_*.root"));

  // std::vector<TString> leg_entry;
  // //  leg_entry.push_back("Threshold");
  // leg_entry.push_back("STC");

  // std::vector<TString> var;
  // var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt,0)) + 1.02929e-01* pow(log(max(jets_pt,0)),2) ) * jets_pt/genjet_pt");
  // var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt,0)) + 1.02929e-01* pow(log(max(jets_pt,0)),2) ) * jets_pt/genjet_pt");


  // var.push_back("jets_pt/genjet_pt");
  // var.push_back("jets_pt/genjet_pt");

  //  std::vector<double> x={20,40,60,80,100,120,140,160,180,200,220,250,300};

  std::vector<double> x={24.990,24.995,25.000,25.005,25.010};

  PlotterResolution plotter;
  //  plotter.Draw("Gamma", filename, leg_entry, var, x, cut);

  plotter.Draw(histobjects, x, TString("L1Jet_resolution_pT_C3D_histo_STC_TEST2"));
  
}




void HGC::plot_effRMS_pT(){

  TString var1 = "(genjet_pt[VBF_parton_genjet] - (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]) ) / genjet_pt[VBF_parton_genjet]";
  TString var2 = "(genjet_pt[VBF_parton_genjet] - (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) ) / genjet_pt[VBF_parton_genjet]";
  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  std::vector<HistObject> histobjects;  

  histobjects.push_back( HistObject(  "Jets", ("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root"), "PU=0", var1, cut, false  ) );
  histobjects.push_back( HistObject(  "Jets", ("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root"), "PU=200", var2, cut, true  ) );

  std::vector<double> x={20,40,60,80,100,120,140,160,180,200,220,250,300};

  //  std::vector<TGraphErrors*> graph;

 
  PlotterResolution plotter;
  plotter.Draw(histobjects, x, "L1Jet_resolution_pT");

  return;


}


