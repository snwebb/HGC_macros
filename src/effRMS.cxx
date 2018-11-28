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

  PlotterResolution plotter( _cmd );
  //  plotter.Draw("Gamma", filename, leg_entry, var, x, cut);

  plotter.Draw(histobjects, x, TString("L1Jet_resolution_pT_C3D_histo_STC_TEST2"));
  
}





void HGC::plot_effRMS_pT_STC(){

  TString var1 = "(genjet_pt[VBF_parton_genjet] - (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]) ) / genjet_pt[VBF_parton_genjet]";
  TString var2 = "(genjet_pt[VBF_parton_genjet] - (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) ) / genjet_pt[VBF_parton_genjet]";
  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  std::vector<HistObject> histobjects;  

  histobjects.push_back( HistObject(  "Jets", (snwebb + "/VBF_Hinv_threshold/jet_ntuples_merged/ntuple_jet_merged_*.root"), "thresh", var1, cut, false  ) );
  histobjects.push_back( HistObject(  "Jets", (snwebb + "/VBF_Hinv_stc/jet_ntuples_merged/ntuple_jet_merged_*.root"), "stc", var1, cut, false  ) );

  std::vector<double> x={20,40,60,80,100,120,140,160,180,200,220,250,300};

  PlotterResolution plotter( _cmd );
  plotter.Draw(histobjects, x, "L1Jet_resolution_pT_STCcomparison");

  return;


}



void HGC::plot_effRMS_pT(){

  TString var1 = "(genjet_pt[VBF_parton_genjet] - (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]) ) / genjet_pt[VBF_parton_genjet]";
  TString var2 = "(genjet_pt[VBF_parton_genjet] - (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) ) / genjet_pt[VBF_parton_genjet]";
  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  std::vector<HistObject> histobjects;  

  histobjects.push_back( HistObject(  "Jets", ("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU0_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root"), "PU=0", var1, cut, false  ) );
  histobjects.push_back( HistObject(  "Jets", ("/vols/cms/tstreble/HGC_ntuples/VBF_Hinv_PU200_dRNNC2D/jet_ntuples_merged/ntuple_jet_merged_*.root"), "PU=200", var2, cut, true  ) );

  std::vector<double> x={20,40,60,80,100,120,140,160,180,200,220,250,300};

  PlotterResolution plotter( _cmd );
  plotter.Draw(histobjects, x, "L1Jet_resolution_pT");

  return;


}





void HGC::plot_effRMS_pT_VBFHinv_PU0_HistoMax(){

  TString var1 = "(genjet_pt[VBF_parton_genjet] - (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]) ) / genjet_pt[VBF_parton_genjet]";
  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  std::vector<HistObject> histobjects;  

  TString file1 = "VBF_Hinv/VBF_Hinv_PU0_threshold_polarHisto_Max";
  TString file2 = "VBF_Hinv/VBF_Hinv_PU0_stc_polarHisto_Max";

  histobjects.push_back( HistObject(  "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_*.root"), "thresh", var1, cut, false  ) );
  histobjects.push_back( HistObject(  "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_*.root"), "stc", var1, cut, false  ) );

  std::vector<double> x={20,40,60,80,100,120,140,160,180,200,220,250,300};

  PlotterResolution plotter( _cmd );
  plotter.Draw(histobjects, x, "L1Jet_resolution_pT_STCComparison_Histomax");

  return;


}




void HGC::plot_effRMS_pT_VBFHinv_PU200_CompareAlgos(){

  TString varhisto = "(genjet_pt[VBF_parton_genjet] - (1.17*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.07929e-01* pow(log(max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-1.1*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) ) / genjet_pt[VBF_parton_genjet]";
  TString varcone = "(genjet_pt[VBF_parton_genjet] - (1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)),2) ) * max(jets_pt[VBF_parton_jets]-2*jets_PU_subtr_cone_GEO_C3D[VBF_parton_jets],0)) ) / genjet_pt[VBF_parton_genjet]";

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  std::vector<HistObject> histobjects;  

  TString file1 = "VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Max";
  TString file2 = "VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Max";
  TString file3 = "VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Interpolated1stOrder";
  TString file4 = "VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated1stOrder";
  TString file5 = "VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Interpolated2ndOrder";
  TString file6 = "VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated2ndOrder";
  TString file7 = "VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_ModMax";
  TString file8 = "VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_ModMax";

  //  histobjects.push_back( HistObject(  "Jets", (snwebb + "/" + file1 + "/jet_ntuples_merged/ntuple_jet_merged_*.root"), "thresh - max", varhisto, cut, false  ) );
  //  histobjects.push_back( HistObject(  "Jets", (snwebb + "/" + file2 + "/jet_ntuples_merged/ntuple_jet_merged_*.root"), "stc - max", varhisto, cut, false  ) );
  //histobjects.push_back( HistObject(  "Jets", (snwebb + "/" + file3 + "/jet_ntuples_merged/ntuple_jet_merged_*.root"), "thresh - inter1", varhisto, cut, false  ) );
  // histobjects.push_back( HistObject(  "Jets", (snwebb + "/" + file4 + "/jet_ntuples_merged/ntuple_jet_merged_*.root"), "stc - inter1", varhisto, cut, false  ) );
    histobjects.push_back( HistObject(  "Jets", (snwebb + "/" + file5 + "/jet_ntuples_merged/ntuple_jet_merged_*.root"), "thresh - inter2", varhisto, cut, false  ) );
    histobjects.push_back( HistObject(  "Jets", (snwebb + "/" + file6 + "/jet_ntuples_merged/ntuple_jet_merged_*.root"), "stc - inter2", varhisto, cut, false  ) );
  //  histobjects.push_back( HistObject(  "Jets", (snwebb + "/" + file7 + "/jet_ntuples_merged/ntuple_jet_merged_*.root"), "thresh - modmax", varhisto, cut, false  ) );
  //  histobjects.push_back( HistObject(  "Jets", (snwebb + "/" + file8 + "/jet_ntuples_merged/ntuple_jet_merged_*.root"), "stc - modmax", varhisto, cut, false  ) );
  std::vector<double> x={20,40,60,80,100,120,140,160,180,200,220,250,300};

  PlotterResolution plotter( _cmd );
  plotter.Draw(histobjects, x, "L1Jet_resolution_pT_PU200");

  return;


}

