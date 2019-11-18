#include "PlotterResponse.h"

//void PlotterResponse::Draw(std::vector<TH2F*> &histo, std::vector<TString> &leg_entry, std::string plotname, std::string xvar){

void PlotterResponse::Draw(std::vector<HistObject>& hists, std::string savename, std::string xvar){

  std::system( ("mkdir -p plots/" + _outdir )   .c_str() );

  int i = 0;  
  std::vector<TProfile*> prof;  
  for (auto &hist: hists ){    

    TH2F * histo = 0;
    if ( hist.process() == "Gamma" )
      histo =_helper.single_plot2D( hist.filename(),"HGCalTriggerNtupleJet",hist.var(),hist.cut()+"&& jets_pt>0",25,24.95,25.05,97,0.06,2);
    else if ( hist.process() == "Jets" )
      histo = _helper.single_plot2D( hist.filename(),"HGCalTriggerNtupleJet",hist.var(),hist.cut()+"&& jets_pt[VBF_parton_jets]>0",25,0,500,97,0.06,2);
    else{
      std::cout << "Process: " << hist.process() << " is not supported, exiting" << std::endl;
      continue;
    }

    TProfile* p = (TProfile*)histo->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
    _legend->AddEntry( prof[i] , hist.leg_entry() );
    histo->Delete();
    
    i++;
  }

  TCanvas * c = _canvas;

  if ( xvar == "pt" ){
    prof[0]->GetXaxis()->SetTitle("p_{T}(gen. jet) [GeV]");
    prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  }
  if ( xvar == "eta" ){
    prof[0]->GetXaxis()->SetTitle("|#eta(gen. jet)|");
    prof[0]->GetYaxis()->SetTitle("p_{T}(L1)/p_{T}(gen. jet)");
  }

  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  //  prof[0]->GetYaxis()->SetRangeUser(-0.5,1.2);
  prof[0]->GetYaxis()->SetRangeUser(-0.5,2.0);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();

  for(unsigned int i=1;i<hists.size();i++)
    prof[i]->Draw("same");
  _legend->Draw("same");
  _latex->Draw("same");

  TLine* line = new TLine(prof[0]->GetXaxis()->GetBinLowEdge(prof[0]->GetXaxis()->GetFirst()),1,prof[0]->GetXaxis()->GetBinLowEdge(prof[0]->GetXaxis()->GetLast()+1),1);
  line->Draw("same");

  gPad->SetTicks();

  c->SaveAs( ("plots/" + _outdir + "/profile_L1jet_response_" + xvar + "_" +  savename+ ".pdf" ).c_str() );  

  // for(auto &it1 : histo) {
  //   it1->Delete();
  // }

}
