#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TH1F.h>
#include <TH2F.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <TProfile.h>
#include <TLatex.h>
#include <TLine.h>

using namespace std;

double TrgLayer_weights[53] = {0.0,
                               0.0183664,
                               0.,
                               0.0305622,
                               0.,
                               0.0162589,
                               0.,
                               0.0143918,
                               0.,
                               0.0134475,
                               0.,
                               0.0185754,
                               0.,
                               0.0204934,
                               0.,
                               0.016901,
                               0.,
                               0.0207958,
                               0.,
                               0.0167985,
                               0.,
                               0.0238385,
                               0.,
                               0.0301146,
                               0.,
                               0.0274622,
                               0.,
                               0.0468671,
                               0.,
                               0.078819,
                               0.0555831,
                               0.0609312,
                               0.0610768,
                               0.0657626,
                               0.0465653,
                               0.0629383,
                               0.0610061,
                               0.0517326,
                               0.0492882,
                               0.0699336,
                               0.0673457,
                               0.119896,
                               0.125327,
                               0.143235,
                               0.153295,
                               0.104777,
                               0.109345,
                               0.161386,
                               0.174656,
                               0.108053,
                               0.121674,
                               0.1171,
                               0.328053
                               };



double TrgLayer_weights_jets_PU0[53] = {0.0,
                                        0.050437247343955285417,
                                        0.,
                                        0.05457104726732550648,
                                        0.,
                                        0.050946734520740999397,
                                        0.,
                                        0.020300337240900467872,
                                        0.,
                                        0.0066465422755270439636,
                                        0.,
                                        0.0097071787228232772615,
                                        0.,
                                        0.011510143615408911788,
                                        0.,
                                        0.017495198841730397188,
                                        0.,
                                        0.023261278602742661153,
                                        0.,
                                        0.02943855093502065895,
                                        0.,
                                        0.040160256382594627933,
                                        0.,
                                        0.035003016560392438694,
                                        0.,
                                        0.045362367665355590729,
                                        0.,
                                        0.051144064501032329706,
                                        0.,
                                        0.091648664914695532335,
                                        0.090535428962797454,
                                        0.060983296591353097771,
                                        0.066208724655714742968,
                                        0.085346415429417454845,
                                        0.055817666450215019935,
                                        0.094626726519364462442,
                                        0.064634116878070524415,
                                        0.079559173112939654549,
                                        0.072462729040954437787,
                                        0.0994274573535449957,
                                        0.090602890013672027214,
                                        0.33183168989510469782,
                                        0.46123802512535583276,
                                        0.36883792527761072311,
                                        0.45715040076681345838,
                                        0.45634492649377478291,
                                        0.4571472715587554525,
                                        0.37051204960283623535,
                                        0.85084062404998761497,
                                        0.24648447956431335237,
                                        0.40636694126765560142,
                                        0.900640041236248301,
                                        1.256395470648857593
                                        };


double TrgLayer_weights_jets_PU200[53] = {0.0,
                                          -0.019299944290572162986,
                                          0.,
                                          -0.015811449422398371478,
                                          0.,
                                          0.0092758765893339867326,
                                          0.,
                                          0.02755649829651304894,
                                          0.,
                                          0.021827218609566871599,
                                          0.,
                                          0.019581048781363540046,
                                          0.,
                                          0.01179940237448611276,
                                          0.,
                                          0.012880741097844233822,
                                          0.,
                                          0.019743266145052770777,
                                          0.,
                                          0.033017659221241481282,
                                          0.,
                                          0.031805021957081291983,
                                          0.,
                                          0.035605231384541621842,
                                          0.,
                                          0.044755470434655830747,
                                          0.,
                                          0.053463996611978495399,
                                          0.,
                                          0.091222875387911461775,
                                          0.070374720741017138259,
                                          0.065358219139360407279,
                                          0.069278733194507308157,
                                          0.083949033104980516629,
                                          0.054799309554729197513,
                                          0.094100214299173590149,
                                          0.067459329178554697237,
                                          0.072788532105084971513,
                                          0.078968256304505046739,
                                          0.07978952984745113497,
                                          0.090182377874189589839,
                                          0.34231579920248567106,
                                          0.45291929961330312793,
                                          0.36276089633355901309,
                                          0.50275741274191321217,
                                          0.48363202098957214226,
                                          0.40655813186937117543,
                                          0.43116763611465458439,
                                          0.80182370043112705105,
                                          0.59936052730006661449,
                                          0.45604930323612924425,
                                          0.80959120281708263356,
                                          0.31549584391048446363
                                          };





void plot_coeff(){

   double layers[53];
   for(int i=0; i<53;i++)
      layers[i] = i;

   TGraphErrors* gr_Luca = new TGraphErrors(53,layers,TrgLayer_weights);
   TGraphErrors* gr_Paul_PU0 = new TGraphErrors(53,layers,TrgLayer_weights_jets_PU0);

   vector<TString> leg_entry;
   leg_entry.push_back("Trg layer current");
   leg_entry.push_back("Trg layer new PU0");

  TLegend* leg=new TLegend(0.25,0.6,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);

   vector<TGraphErrors*> graph;
   graph.push_back(gr_Luca);
   graph.push_back(gr_Paul_PU0);

   for(unsigned int i=0;i<graph.size();i++){
      graph[i]->SetLineWidth(2);
      graph[i]->SetLineColor(i+1);
      graph[i]->SetMarkerColor(i+1);     
      graph[i]->SetMarkerStyle(21);
      graph[i]->SetMarkerSize(0.7);
      graph[i]->SetFillColor(0);
      leg->AddEntry(graph[i],leg_entry[i]);
   }

   graph[0]->GetXaxis()->SetTitle("Layer");
   graph[0]->GetYaxis()->SetTitle("Coefficient");
   graph[0]->GetYaxis()->SetTitleSize(20);
   graph[0]->GetYaxis()->SetTitleOffset(1.5);
   graph[0]->GetYaxis()->SetTitleFont(43);
   graph[0]->GetYaxis()->SetRangeUser(0,1.5);
   graph[0]->SetTitle("");

   TCanvas* c=new TCanvas("c","c",650,600);
   c->SetLeftMargin(0.15);
   c->SetTicks();
   c->SetGrid();

   graph[0]->Draw("AP");
   for(unsigned int i=1; i<graph.size(); i++)
     graph[i]->Draw("sameP");
   leg->Draw("same");

   c->SaveAs("plots/coeff.pdf");
   return;

}



void plot_chi2(){

  TH1F* h_Luca = new TH1F("","",100,0,10000);
  TH1F* h_Paul_PU0 = new TH1F("","",100,0,10000);

  TString log_file = "jets_GEO_PU0.txt";
  std::ifstream infile(log_file);

  string line;
  while(getline(infile,line)){
    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<40;j++)
      var.push_back(-1); 

    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8] >> var[9] >> var[10] >> var[11] >> var[12] >> var[13] >> var[14] >> var[15] >> var[16] >> var[17] >> var[18] >> var[19] >> var[20] >> var[21] >> var[22] >> var[23] >> var[24] >> var[25] >> var[26] >> var[27] >> var[28] >> var[29] >> var[30] >> var[31] >> var[32] >> var[33] >> var[34] >> var[35] >> var[36] >> var[37] >> var[38] >> var[39];

    float gen_pt = var[0];
    vector<float> layer(53);
    for(unsigned int i=2; i<40;i++){
      if(i<16)
        layer[2*(i-2)+1] = var[i];
      else
        layer[i+13]=var[i];
    }

    float pT_Luca = 0;
    float pT_Paul_PU0 = 0;

    for(unsigned int i=0; i<53; i++){
      pT_Luca += layer[i]*TrgLayer_weights[i];
      pT_Paul_PU0 += layer[i]*TrgLayer_weights_jets_PU0[i];
    }

    h_Luca->Fill(pow(pT_Luca-gen_pt,2));
    h_Paul_PU0->Fill(pow(pT_Paul_PU0-gen_pt,2));
  
  }

  h_Luca->SetLineColor(1);
  h_Paul_PU0->SetLineColor(2);
  h_Luca->SetLineWidth(2);
  h_Paul_PU0->SetLineWidth(2);
  h_Paul_PU0->SetStats(0);

  h_Paul_PU0->Draw();
  h_Luca->Draw("same");

}





void plot_res(){

  TH1F* h_Luca = new TH1F("","",100,-2,1);
  TH1F* h_Paul_PU0 = new TH1F("","",100,-2,1);

  TString log_file = "jets_GEO_PU0.txt";
  std::ifstream infile(log_file);

  string line;
  while(getline(infile,line)){
    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<40;j++)
      var.push_back(-1);

    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8] >> var[9] >> var[10] >> var[11] >> var[12] >> var[13] >> var[14] >> var[15] >> var[16] >> var[17] >> var[18] >> var[19] >> var[20] >> var[21] >> var[22] >> var[23] >> var[24] >> var[25] >> var[26] >> var[27] >> var[28] >> var[29] >> var[30] >> var[31] >> var[32] >> var[33] >> var[34] >> var[35] >> var[36] >> var[37] >> var[38] >> var[39];


    float gen_pt = var[0];
    vector<float> layer(53);
    for(unsigned int i=2; i<40;i++){
      if(i<16)
        layer[2*(i-2)+1] = var[i];
      else
        layer[i+13]=var[i];
    }

    float pT_Luca = 0;
    float pT_Paul_PU0 = 0;

    for(unsigned int i=0; i<53; i++){
      pT_Luca += layer[i]*TrgLayer_weights[i];
      pT_Paul_PU0 += layer[i]*TrgLayer_weights_jets_PU0[i];
    }


    h_Luca->Fill((pT_Luca-gen_pt)/gen_pt);
    h_Paul_PU0->Fill((pT_Paul_PU0-gen_pt)/gen_pt);

  }

  h_Luca->SetLineColor(1);
  h_Paul_PU0->SetLineColor(2);
  h_Luca->SetLineWidth(2);
  h_Paul_PU0->SetLineWidth(2);
  h_Luca->SetStats(0);

  h_Luca->Draw();
  h_Paul_PU0->Draw("same");

}




void plot_response_PU0(){

  TH2F* h_Luca = new TH2F("","",25,0,500,97,0.06,2);
  TH2F* h_Paul_PU0 = new TH2F("","",25,0,500,97,0.06,2);

  TString log_file = "jets_GEO_PU0.txt";
  std::ifstream infile(log_file);

  string line;
  while(getline(infile,line)){
    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<40;j++)
      var.push_back(-1);

    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8] >> var[9] >> var[10] >> var[11] >> var[12] >> var[13] >> var[14] >> var[15] >> var[16] >> var[17] >> var[18] >> var[19] >> var[20] >> var[21] >> var[22] >> var[23] >> var[24] >> var[25] >> var[26] >> var[27] >> var[28] >> var[29] >> var[30] >> var[31] >> var[32] >> var[33] >> var[34] >> var[35] >> var[36] >> var[37] >> var[38] >> var[39];


    float gen_pt = var[0];
    float gen_eta = var [1];
    vector<float> layer(53);
    for(unsigned int i=2; i<40;i++){
      if(i<16)
        layer[2*(i-2)+1] = var[i];
      else
        layer[i+13]=var[i];
    }

    float pT_Luca = 0;
    float pT_Paul_PU0 = 0;

    for(unsigned int i=0; i<53; i++){
      pT_Luca += layer[i]*TrgLayer_weights[i];
      pT_Paul_PU0 += layer[i]*TrgLayer_weights_jets_PU0[i];
    }

    if(gen_pt>20 && abs(gen_eta)>1.6 && abs(gen_eta)<2.9){

      h_Luca->Fill(gen_pt,pT_Luca/gen_pt);
      h_Paul_PU0->Fill(gen_pt,pT_Paul_PU0/gen_pt);
    }

  }


  vector<TH2F*> histo;
  histo.push_back(h_Luca);
  histo.push_back(h_Paul_PU0);

  vector<TString> leg_entry;
  leg_entry.push_back("Current cal.");
  leg_entry.push_back("New cal. PU=0");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

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
  prof[0]->GetYaxis()->SetRangeUser(-0.1,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* tline = new TLine(0,1,500,1);
  tline->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/coeff_calibr_response_pt_PU0.pdf");
 
  

}




void plot_resolution_PU0(){

  TH2F* h_Luca = new TH2F("","",25,0,500,97,0.06,2);
  TH2F* h_Paul_PU0 = new TH2F("","",25,0,500,97,0.06,2);

  TString log_file = "jets_GEO_PU0.txt";
  std::ifstream infile(log_file);

  string line;
  while(getline(infile,line)){
    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<40;j++)
      var.push_back(-1);

    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8] >> var[9] >> var[10] >> var[11] >> var[12] >> var[13] >> var[14] >> var[15] >> var[16] >> var[17] >> var[18] >> var[19] >> var[20] >> var[21] >> var[22] >> var[23] >> var[24] >> var[25] >> var[26] >> var[27] >> var[28] >> var[29] >> var[30] >> var[31] >> var[32] >> var[33] >> var[34] >> var[35] >> var[36] >> var[37] >> var[38] >> var[39];


    float gen_pt = var[0];
    float gen_eta = var [1];
    vector<float> layer(53);
    for(unsigned int i=2; i<40;i++){
      if(i<16)
        layer[2*(i-2)+1] = var[i];
      else
        layer[i+13]=var[i];
    }

    float pT_Luca = 0;
    float pT_Paul_PU0 = 0;

    for(unsigned int i=0; i<53; i++){
      pT_Luca += layer[i]*TrgLayer_weights[i];
      pT_Paul_PU0 += layer[i]*TrgLayer_weights_jets_PU0[i];
    }

    if(gen_pt>20 && abs(gen_eta)>1.6 && abs(gen_eta)<2.9){

      h_Luca->Fill(gen_pt,pT_Luca/gen_pt);
      h_Paul_PU0->Fill(gen_pt,pT_Paul_PU0/gen_pt);
    }

  }


  vector<TH2F*> histo;
  histo.push_back(h_Luca);
  histo.push_back(h_Paul_PU0);

  vector<TString> leg_entry;
  leg_entry.push_back("Current cal.");
  leg_entry.push_back("New cal. PU=0");

  TLegend* leg=new TLegend(0.4,0.5,0.7,0.85);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);

  vector<TGraphErrors*> graph;


  for(unsigned int i=0;i<histo.size();i++){

    TGraphErrors* gr = new TGraphErrors();


    for(unsigned int j=1;j<=histo[i]->GetNbinsX();j++){
      TH1D* proj = histo[i]->ProjectionY("proj",j,j);
      cout<<"bin "<<j<<endl;
      Double_t xq[4] = {0.25,0.5,0.75,1};
      Double_t yq[4];
      proj->GetQuantiles(4,yq,xq);
      gr->SetPoint(j-1,histo[i]->GetXaxis()->GetBinCenter(j),(yq[2]-yq[0])/yq[1]);
    }

   for(unsigned int j=0;j<gr->GetN();j++){
      double x,y;
      gr->GetPoint(j,x,y);
      if(y==0) gr->RemovePoint(j);
    }

    graph.push_back(gr);
    graph[i]->SetLineColor(i+1);    
    if(i>3)
      graph[i]->SetLineColor(i+2);
    graph[i]->SetLineWidth(2);
    graph[i]->SetFillColor(0);
    leg->AddEntry(graph[i],leg_entry[i]);

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  graph[0]->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  graph[0]->GetYaxis()->SetTitle("IQR / Median");
  graph[0]->GetYaxis()->SetTitleOffset(1.7);
  graph[0]->GetYaxis()->SetRangeUser(0,1.);
  graph[0]->SetTitle("");
  graph[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    graph[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.01,"CMS Simulation VBF H#rightarrowinv. #sqrt{s}=14 TeV PU=0");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/coeff_calibr_resolution_pt_PU0.pdf");
 
  

}






void plot_response_PU200(){

  TH2F* h_Luca = new TH2F("","",25,0,500,97,0.06,2);
  TH2F* h_Paul_PU0 = new TH2F("","",25,0,500,97,0.06,2);
  TH2F* h_Paul_PU200 = new TH2F("","",25,0,500,97,0.06,2);

  TString log_file = "jets_GEO_PU200.txt";
  std::ifstream infile(log_file);

  string line;
  while(getline(infile,line)){
    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<40;j++)
      var.push_back(-1);

    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8] >> var[9] >> var[10] >> var[11] >> var[12] >> var[13] >> var[14] >> var[15] >> var[16] >> var[17] >> var[18] >> var[19] >> var[20] >> var[21] >> var[22] >> var[23] >> var[24] >> var[25] >> var[26] >> var[27] >> var[28] >> var[29] >> var[30] >> var[31] >> var[32] >> var[33] >> var[34] >> var[35] >> var[36] >> var[37] >> var[38] >> var[39];


    float gen_pt = var[0];
    float gen_eta = var [1];
    vector<float> layer(53);
    for(unsigned int i=2; i<40;i++){
      if(i<16)
        layer[2*(i-2)+1] = var[i];
      else
        layer[i+13]=var[i];
    }

    float pT_Luca = 0;
    float pT_Paul_PU0 = 0;
    float pT_Paul_PU200 = 0;

    for(unsigned int i=0; i<53; i++){
      pT_Luca += layer[i]*TrgLayer_weights[i];
      pT_Paul_PU0 += layer[i]*TrgLayer_weights_jets_PU0[i];
      pT_Paul_PU200 += layer[i]*TrgLayer_weights_jets_PU200[i];
    }

    if(gen_pt>20 && abs(gen_eta)>1.6 && abs(gen_eta)<2.9){
      h_Luca->Fill(gen_pt,pT_Luca/gen_pt);
      h_Paul_PU0->Fill(gen_pt,pT_Paul_PU0/gen_pt);
      h_Paul_PU200->Fill(gen_pt,pT_Paul_PU200/gen_pt);
    }

  }


  vector<TH2F*> histo;
  histo.push_back(h_Luca);
  histo.push_back(h_Paul_PU0);
  histo.push_back(h_Paul_PU200);

  vector<TString> leg_entry;
  leg_entry.push_back("Current cal.");
  leg_entry.push_back("New cal. PU=0");
  leg_entry.push_back("New cal. PU=200");

  TLegend* leg=new TLegend(0.4,0.15,0.7,0.5);
  leg->SetHeader("#splitline{p_T(gen. jet)>20 GeV}{1.6<|#eta(gen.jet)|<2.9}");
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  
  vector<TProfile*> prof;

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
  prof[0]->GetYaxis()->SetRangeUser(-0.1,1.2);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");
  leg->Draw("same");

  TLatex *texl = new TLatex(2.,1.21,"CMS Simulation Preliminary, VBF H#rightarrowinv. #sqrt{s}=14 TeV  PU=200");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TLine* tline = new TLine(0,1,500,1);
  tline->Draw("same");

  gPad->SetTicks();


  c->SaveAs("plots/coeff_calibr_response_pt_PU200.pdf");
 
  

}






void plot_layer_pt_ZB(){

  TH2F* h_ZB_old = new TH2F("","",40,0,40,1000,0.,500.);
  TH2F* h_ZB = new TH2F("","",40,0,40,100000,0.,50000.);

  TString log_file = "jets_ZB_GEO_PU200_ptcut50.txt";
  std::ifstream infile(log_file);

  int njets=0;
  int n13=0;
  float m13=0;
  int n14=0;
  float m14=0;

  string line;
  while(getline(infile,line)){
    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<40;j++)
      var.push_back(-1);

    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8] >> var[9] >> var[10] >> var[11] >> var[12] >> var[13] >> var[14] >> var[15] >> var[16] >> var[17] >> var[18] >> var[19] >> var[20] >> var[21] >> var[22] >> var[23] >> var[24] >> var[25] >> var[26] >> var[27] >> var[28] >> var[29] >> var[30] >> var[31] >> var[32] >> var[33] >> var[34] >> var[35] >> var[36] >> var[37] >> var[38] >> var[39];


    float pt_jet = var[0];
    float eta_jet = var [1];

    if(pt_jet>50 && pt_jet<80 && abs(eta_jet)>1.7 && abs(eta_jet)<2.8){
      njets++;
      for(unsigned int j=2;j<40;j++){
	h_ZB->Fill(j-2,var[j]);
	h_ZB_old->Fill(j-2,var[j]);
	if(var[j]>500 && j==16)
	  cout<<var[j]<<endl;
	if(j==15){
	  n13++;
	  m13+=var[j];
	}
	if(j==16){
	  n14++;
	  m14+=var[j];
	}
      }
    }
    
  }

  cout<<n14<<endl;
  cout<<m13/n13<<endl;
  cout<<m14/n14<<endl;

  TH2F* h_VBF = new TH2F("","",40,0,40,100000,0.,50000.);

  TString log_file2 = "jets_GEO_PU200.txt";
  std::ifstream infile2(log_file2);

  int njets2=0;

  //string line;
  while(getline(infile2,line)){
    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<40;j++)
      var.push_back(-1);

    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8] >> var[9] >> var[10] >> var[11] >> var[12] >> var[13] >> var[14] >> var[15] >> var[16] >> var[17] >> var[18] >> var[19] >> var[20] >> var[21] >> var[22] >> var[23] >> var[24] >> var[25] >> var[26] >> var[27] >> var[28] >> var[29] >> var[30] >> var[31] >> var[32] >> var[33] >> var[34] >> var[35] >> var[36] >> var[37] >> var[38] >> var[39];


    float pt_jet = var[0];
    float eta_jet = var [1];

    if(pt_jet>50 && pt_jet<80 && abs(eta_jet)>1.7 && abs(eta_jet)<2.8){
      njets2++;
      for(unsigned int j=2;j<40;j++){
	h_VBF->Fill(j-2,var[j]);
	if(var[j]>500 && j==16)
	  cout<<var[j]<<endl;
      }
    }
    
  }



  cout<<njets<<endl;
  cout<<njets2<<endl;

  vector<TH2F*> histo;
  histo.push_back(h_ZB_old);
  histo.push_back(h_ZB);
  histo.push_back(h_VBF);

  
  vector<TProfile*> prof;

  for(unsigned int i=0;i<histo.size();i++){
    TProfile* p = (TProfile*)histo[i]->ProfileX()->Clone();
    prof.push_back(p);
    prof[i]->SetLineColor(i+1);
    if(i>3)
      prof[i]->SetLineColor(i+2);
    prof[i]->SetLineWidth(2);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  prof[0]->GetXaxis()->SetTitle("Trigger Layer");
  prof[0]->GetYaxis()->SetTitle("<MIP_{T}>");
  prof[0]->GetYaxis()->SetTitleOffset(1.7);
  prof[0]->GetYaxis()->SetRangeUser(0.,350.);
  prof[0]->SetStats(0);
  prof[0]->SetTitle("");
  prof[0]->Draw();
  for(unsigned int i=1;i<histo.size();i++)
    prof[i]->Draw("same");


  gPad->SetTicks();


  c->SaveAs("plots/layer_MIPpT_ZB.pdf");
 
  

}
