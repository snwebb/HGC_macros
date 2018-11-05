#include "PlotterResponse.h"

void PlotterResponse::Draw(std::vector<TH2F*> &histo, std::vector<TString> &leg_entry, std::string plotname, std::string xvar){

  std::vector<TProfile*> prof;
  
  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    _legend->AddEntry(prof[i],leg_entry[i]);

  }

  TCanvas * c = _canvas;

  if ( xvar == "pt" ){
    prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
    prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  }
  if ( xvar == "eta" ){
    prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
    prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  }

  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();

  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  _legend->Draw("same");
  _latex->Draw("same");

  TLine* line = new TLine(prof[0]->GetXaxis()->GetBinLowEdge(prof[0]->GetXaxis()->GetFirst()),1,prof[0]->GetXaxis()->GetBinLowEdge(prof[0]->GetXaxis()->GetLast()+1),1);
  line->Draw("same");

  gPad->SetTicks();

  c->SaveAs( ("plots/profile_L1jet_response_" + xvar + "_" +  plotname+ ".pdf" ).c_str() );  

  for(auto &it1 : histo) {
    it1->Delete();
  }

}
