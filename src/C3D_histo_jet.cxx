#include "C3D_histo_jet.h"

using namespace std;

void C3D_histo_jet::plot_profile_L1jet_response_pt_PU0_STC(){
  
  TString snwebb = "/vols/cms/snwebb/HGC_ntuples/";
  TString cut = " abs(genjet_eta)>1.6 && abs(genjet_eta)<2.9 && genjet_pt>20";

  std::vector<TH2F*> histo;
  histo.push_back( helper.single_plot2D(snwebb + "/SingleGammaPt25_PU0_threshold_1031/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt","jets_pt/genjet_pt",cut+"&& jets_pt>0",25,24.95,25.05,97,0.06,2));
  //  histo.push_back( helper.single_plot2D(snwebb + "/SingleGammaPt25_PU0_threshold_1031/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt,0)) + 1.02929e-01* pow(log(max(jets_pt,0)),2) ) * jets_pt/genjet_pt",cut+"&& jets_pt>0",25,24.95,25.05,97,0.06,2));
  histo.push_back( helper.single_plot2D(snwebb + "/SingleGammaPt25_PU0_stc_1031/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt","jets_pt/genjet_pt",cut+"&& jets_pt>0",25,24.95,25.05,97,0.06,2));
  //  histo.push_back( helper.single_plot2D(snwebb + "/SingleGammaPt25_PU0_stc_1031/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt,0)) + 1.02929e-01* pow(log(max(jets_pt,0)),2) ) * jets_pt/genjet_pt",cut+"&& jets_pt>0",25,24.95,25.05,97,0.06,2));

  std::vector<TString> leg_entry;
  leg_entry.push_back("Thresh PU=0 ");
  //  leg_entry.push_back("Thresh PU=0 + JEC");
  leg_entry.push_back("STC PU=0 ");
  //  leg_entry.push_back("STC PU=0 + JEC");

  plot_profile_L1jet_response_pt_master ( histo, leg_entry, "PU0_STC" );


}


//used for testing purposes (works)
void C3D_histo_jet::plot_profile_L1jet_response_pt_PU0_C3D_histo_refined(){

  TString cut = "VBF_parton_genjet>=0 && VBF_parton_jets>=0 && abs(genjet_eta[VBF_parton_genjet])>1.6 && abs(genjet_eta[VBF_parton_genjet])<2.9 && genjet_pt[VBF_parton_genjet]>20";

  std::vector<TH2F*> histo;
  histo.push_back( helper.single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2));
  histo.push_back( helper.single_plot2D("/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_PU0_C3D_polarHisto_refinedMax/jet_ntuples_merged/ntuple_jet_merged_*.root","HGCalTriggerNtupleJet","genjet_pt[VBF_parton_genjet]","1.06*(4.98004e+00 -1.23767e+00 * log(max(jets_pt[VBF_parton_jets],0)) + 1.02929e-01* pow(log(max(jets_pt[VBF_parton_jets],0)),2) ) * jets_pt[VBF_parton_jets]/genjet_pt[VBF_parton_genjet]",cut+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2));

  std::vector<TString> leg_entry;
  leg_entry.push_back("PU=0 cone");
  leg_entry.push_back("PU=0 cone + JEC");

  plot_profile_L1jet_response_pt_master ( histo, leg_entry, "PU0_test" );


}




void C3D_histo_jet::plot_profile_L1jet_response_pt_master(std::vector<TH2F*> &histo, std::vector<TString> &leg_entry, std::string plotname ){

  
  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  std::vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    leg->AddEntry(prof[i],leg_entry[i]);

  }

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
  prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* line = new TLine(prof[0]->GetXaxis()->GetBinLowEdge(prof[0]->GetXaxis()->GetFirst()),1,prof[0]->GetXaxis()->GetBinLowEdge(prof[0]->GetXaxis()->GetLast()+1),1);
  line->Draw("same");

  gPad->SetTicks();

  c->SaveAs( ("plots/profile_L1jet_response_pt_" + plotname+ ".pdf" ).c_str() );  

  for(auto &it1 : histo) {
    it1->Delete();
  }


}



