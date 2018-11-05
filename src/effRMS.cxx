#include "HGC.h"


void HGC::plot_effRMS_pT_C3D_histo_PU0_STC(){
  
  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  vector<TString> filename;
  filename.push_back((snwebb + "/VBF_Hinv_PU0_C3D_polarHisto_refinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root"));
  filename.push_back((snwebb + "/VBF_Hinv_PU0_C3D_polarHisto_crossRefinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root"));
  filename.push_back((snwebb + "/VBF_Hinv_PU0_C3D_polarHisto_refinedMax_TC/jet_ntuples_merged/ntuple_jet_merged_*.root"));
  filename.push_back((snwebb + "/VBF_Hinv_PU0_C3D_polarHisto_crossRefinedMax_TC/jet_ntuples_merged/ntuple_jet_merged_*.root"));

  vector<TString> leg_entry;
  leg_entry.push_back("C2D + Histo dr=0.01 Max. finding refined");
  leg_entry.push_back("C2D + Histo dr=0.01 Max. finding cross refined");
  leg_entry.push_back("TC + Histo dr=0.01 Max. finding refined");
  leg_entry.push_back("TC + Histo dr=0.01 Max. finding cross refined");

  vector<TString> var;
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");
  var.push_back("0.84*(5.09004e+00 -1.22767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]");

  std::vector<double> x={20,40,60,80,100,120,140,160,180,200,220,250,300};


  PlotterResolution plotter;
  plotter.Draw(filename, leg_entry, var, x, cut);


}



