#include "HGC.h"
#include "PlotterEventDisplay.h"

void HGC::display3D_tc(TString file, int n_event, 
		       const std::vector<int>& tc,
		       const std::vector<int>& cl,
		       const std::vector<int>& c3d,
		  float eta_min, float eta_max, 
		  float phi_min, float phi_max, 
		  float layer_min, float layer_max){

  TH3F* h=new TH3F("h","h",50,eta_min,eta_max,50,phi_min,phi_max,layer_max-layer_min,layer_min,layer_max);
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(file);
  
  std::vector<float> *_tc_eta;
  std::vector<float> *_tc_phi;
  std::vector<float> *_tc_energy;
  std::vector<float> *_tc_pt;
  std::vector<int> *_tc_HGClayer;
  std::vector<unsigned int> *_tc_multicluster_id;

  std::vector<float> *_cl_eta;
  std::vector<float> *_cl_phi;
  std::vector<float> *_cl_energy;
  std::vector<float> *_cl_pt;
  std::vector<int> *_cl_HGClayer;

  std::vector<float> *_cl3d_eta;
  std::vector<float> *_cl3d_phi;
  std::vector<float> *_cl3d_energy;
  std::vector<float> *_cl3d_pt;
  std::vector<unsigned int> *_cl3d_id;

  //  std::vector<unsigned int> *_cl_id;
  std::vector<std::vector<int> > *_cl_cells;
  // std::vector<std::vector<int> > *_cl3d_clusters;

  tree->SetBranchAddress("tc_eta",    &_tc_eta);
  tree->SetBranchAddress("tc_phi",    &_tc_phi);
  tree->SetBranchAddress("tc_energy", &_tc_energy);
  tree->SetBranchAddress("tc_pt",    &_tc_pt);
  tree->SetBranchAddress("tc_layer", &_tc_HGClayer);
  tree->SetBranchAddress("tc_multicluster_id", &_tc_multicluster_id);

  tree->SetBranchAddress("cl_eta",    &_cl_eta);
  tree->SetBranchAddress("cl_phi",    &_cl_phi);
  tree->SetBranchAddress("cl_energy", &_cl_energy);
  tree->SetBranchAddress("cl_pt",     &_cl_pt);
  tree->SetBranchAddress("cl_layer",    &_cl_HGClayer);

  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);
  tree->SetBranchAddress("cl3d_pt",     &_cl3d_pt);
  tree->SetBranchAddress("cl3d_id",     &_cl3d_id);

  //tree->SetBranchAddress("cl_cells", &_cl_cells);
  //tree->SetBranchAddress("cl3d_clusters", &_cl3d_clusters);

  _tc_eta = 0;
  _tc_phi = 0;
  _tc_energy = 0;
  _tc_pt = 0;
  _tc_HGClayer = 0;
  _tc_multicluster_id = 0;
  
  _cl_eta = 0;
  _cl_phi = 0;
  _cl_energy = 0;
  _cl_pt = 0;
  _cl_HGClayer = 0;

  _cl3d_eta = 0;
  _cl3d_phi = 0;
  _cl3d_energy = 0;
  _cl3d_pt = 0;
  _cl3d_id = 0;

  _cl_cells = 0;
  //  _cl_id = 0;
  //  _cl3d_clusters = 0;
  
  tree->GetEntry(n_event);
  
  if(tc.size()==0){
    for(unsigned int i_tc = 0; i_tc<(*_tc_eta).size(); i_tc++){
      h->Fill((*_tc_eta)[i_tc],(*_tc_phi)[i_tc],(*_tc_HGClayer)[i_tc],(*_tc_pt)[i_tc]);
    }
  }
  else{
    for(auto & i_tc : tc){
      h->Fill((*_tc_eta)[i_tc],(*_tc_phi)[i_tc],(*_tc_HGClayer)[i_tc],(*_tc_pt)[i_tc]);
      std::cout<<"Tower "<<i_tc<<std::endl;;
      std::cout<<"(pt,eta,phi,layer)=("<<(*_tc_pt)[i_tc]<<","<<(*_tc_eta)[i_tc]<<","<<(*_tc_phi)[i_tc]<<","<<(*_tc_HGClayer)[i_tc]<<")"<<std::endl;;
    }
  }  

  // else if(cl.size()>0){
  //   for(auto & i_cl : cl){    
  //     std::cout<<"C2D "<<i_cl<<" (pt,eta,phi,layer)=("<<(*_cl_pt)[i_cl]<<","<<(*_cl_eta)[i_cl]<<","<<(*_cl_phi)[i_cl]<<","<<(*_cl_HGClayer)[i_cl]<<")"<<std::endl;;      
  //     for(auto & i_tc : (*_cl_cells)[i_cl]){
  // 	h->Fill((*_tc_eta)[i_tc],(*_tc_phi)[i_tc],(*_tc_HGClayer)[i_tc],(*_tc_pt)[i_tc]);
  // 	std::cout<<"(pt,eta,phi,layer)=("<<(*_tc_pt)[i_tc]<<","<<(*_tc_eta)[i_tc]<<","<<(*_tc_phi)[i_tc]<<","<<(*_tc_HGClayer)[i_tc]<<")"<<std::endl;;
  //     }
  //   }
  // }

  // else if(c3d.size()>0){
  //   for(auto & i_c3d : c3d){
  //     std::cout<<"C3D "<<i_c3d<<" (pt,eta,phi)=("<<(*_cl3d_pt)[i_c3d]<<","<<(*_cl3d_eta)[i_c3d]<<","<<(*_cl3d_phi)[i_c3d]<<")"<<std::endl;;
  //     for(unsigned i_tc=0;i_tc<(*_tc_multicluster_id).size();i_tc++){
  // 	if((*_cl3d_id)[i_c3d]==(*_tc_multicluster_id)[i_tc]){   
  // 	  h->Fill((*_tc_eta)[i_tc],(*_tc_phi)[i_tc],(*_tc_HGClayer)[i_tc],(*_tc_pt)[i_tc]);
  // 	  std::cout<<"(pt,eta,phi,layer)=("<<(*_tc_pt)[i_tc]<<","<<(*_tc_eta)[i_tc]<<","<<(*_tc_phi)[i_tc]<<","<<(*_tc_HGClayer)[i_tc]<<")"<<std::endl;;
  // 	}
  //     }
  //   }
  // }
  
  PlotterEventDisplay plotter( _cmd );
  plotter.Draw(h,"3dtc","display3D_tc");

  h->Delete();

}






void HGC::display3D_cl(TString file,
		  int n_event, 
		  const std::vector<int>& cl,
		  const std::vector<int>& c3d,
		  float eta_min, float eta_max, 
		  float phi_min, float phi_max, 
		  float layer_min, float layer_max){

 
  
  TH3F* h=new TH3F("h","h",50,eta_min,eta_max,50,phi_min,phi_max,layer_max-layer_min,layer_min,layer_max);
  
  //TChain * tree = new TChain("hgcalTriggerNtuplizer/HGCalTriggerNtuple");
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(file);
  
  std::vector<float> *_cl_eta;
  std::vector<float> *_cl_phi;
  std::vector<float> *_cl_energy;
  std::vector<float> *_cl_pt;
  std::vector<int> *_cl_HGClayer;
  //  std::vector<unsigned int> *_cl_id;
  std::vector<unsigned int> *_cl_multicluster_id;
  
  std::vector<float> *_cl3d_eta;
  std::vector<float> *_cl3d_phi;
  std::vector<float> *_cl3d_energy;
  std::vector<float> *_cl3d_pt;
  std::vector<unsigned int> *_cl3d_id;

  tree->SetBranchAddress("cl_eta",    &_cl_eta);
  tree->SetBranchAddress("cl_phi",    &_cl_phi);
  tree->SetBranchAddress("cl_energy", &_cl_energy);
  tree->SetBranchAddress("cl_layer", &_cl_HGClayer);
  tree->SetBranchAddress("cl_pt", &_cl_pt);
  tree->SetBranchAddress("cl_multicluster_id", &_cl_multicluster_id);

  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);
  tree->SetBranchAddress("cl3d_pt",     &_cl3d_pt);
  tree->SetBranchAddress("cl3d_id",     &_cl3d_id);


  _cl_eta = 0;
  _cl_phi = 0;
  _cl_energy = 0;
  _cl_pt = 0;
  _cl_HGClayer = 0;
  //  _cl_id = 0;
  _cl_multicluster_id = 0;
  
  _cl3d_eta = 0;
  _cl3d_phi = 0;
  _cl3d_energy = 0;
  _cl3d_pt = 0;
  _cl3d_id = 0;

  
  tree->GetEntry(n_event);

  
  if(cl.size()==0){
    
    
    //  if(cl[0]==0){
    for(unsigned int i_cl = 0; i_cl<(*_cl_eta).size(); i_cl++){
      h->Fill((*_cl_eta)[i_cl],(*_cl_phi)[i_cl],(*_cl_HGClayer)[i_cl],(*_cl_pt)[i_cl]);
      if((*_cl_eta)[i_cl]>=eta_min && (*_cl_eta)[i_cl]<=eta_max && (*_cl_phi)[i_cl]>=phi_min && (*_cl_phi)[i_cl]<=phi_max && (*_cl_HGClayer)[i_cl]>=layer_min && (*_cl_HGClayer)[i_cl]<=layer_max)
	std::cout<<"(pt,eta,phi,layer)=("<<(*_cl_pt)[i_cl]<<","<<(*_cl_eta)[i_cl]<<","<<(*_cl_phi)[i_cl]<<","<<(*_cl_HGClayer)[i_cl]<<")"<<std::endl;;
    }
  }
  
  else{
    for(auto & i_cl : cl){
      h->Fill((*_cl_eta)[i_cl],(*_cl_phi)[i_cl],(*_cl_HGClayer)[i_cl],(*_cl_pt)[i_cl]);
      std::cout<<"C2D "<<i_cl<<std::endl;;
      std::cout<<"(pt,eta,phi,layer)=("<<(*_cl_pt)[i_cl]<<","<<(*_cl_eta)[i_cl]<<","<<(*_cl_phi)[i_cl]<<","<<(*_cl_HGClayer)[i_cl]<<")"<<std::endl;;
    }
  }
  

  // else if(c3d.size()>0){
  //   for(auto & i_c3d : c3d){
  //     std::cout<<"C3D "<<i_c3d<<" (pt,eta,phi)=("<<(*_cl3d_pt)[i_c3d]<<","<<(*_cl3d_eta)[i_c3d]<<","<<(*_cl3d_phi)[i_c3d]<<")"<<std::endl;;
  //     for(unsigned int i_cl = 0; i_cl<(*_cl_multicluster_id).size(); i_cl++){
  // 	if((*_cl3d_id)[i_c3d]==(*_cl_multicluster_id)[i_cl]){
  // 	  h->Fill((*_cl_eta)[i_cl],(*_cl_phi)[i_cl],(*_cl_HGClayer)[i_cl],(*_cl_pt)[i_cl]);
  // 	  std::cout<<"(pt,eta,phi,layer)=("<<(*_cl_pt)[i_cl]<<","<<(*_cl_eta)[i_cl]<<","<<(*_cl_phi)[i_cl]<<","<<(*_cl_HGClayer)[i_cl]<<")"<<std::endl;;
  // 	}
  //     }
  //   }
  // }
  

  PlotterEventDisplay plotter( _cmd );
  plotter.Draw(h,"3dcl","display3D_cl");


  h->Delete();


}






void HGC::display2D_c3d(TString file, int n_event, 
		   const std::vector<int>& c3d,
		   const std::vector<int>& jets,
		   float eta_min, float eta_max, 
		   float phi_min, float phi_max){

  TH2F* h=new TH2F("h","h",50,eta_min,eta_max,50,phi_min,phi_max);

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(file);
  
  std::vector<float> *_cl3d_eta;
  std::vector<float> *_cl3d_phi;
  std::vector<float> *_cl3d_energy;
  std::vector<float> *_cl3d_pt;

  std::vector<std::vector<int> > *_jets_cl3d;

  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);
  tree->SetBranchAddress("cl3d_pt", &_cl3d_pt);

  tree->SetBranchAddress("jets_cl3d", &_jets_cl3d);

  _cl3d_eta = 0;
  _cl3d_phi = 0;
  _cl3d_energy = 0;
  _cl3d_pt = 0;

  _jets_cl3d = 0;

  
  tree->GetEntry(n_event);
  
  if(c3d.size()==0){

    std::cout<<"ok"<<std::endl;;
    for(unsigned int i_c3d = 0; i_c3d<(*_cl3d_eta).size(); i_c3d++){
      h->Fill((*_cl3d_eta)[i_c3d],(*_cl3d_phi)[i_c3d],(*_cl3d_pt)[i_c3d]);
      std::cout<<"(pt,eta,phi)=("<<(*_cl3d_pt)[i_c3d]<<","<<(*_cl3d_eta)[i_c3d]<<","<<(*_cl3d_phi)[i_c3d]<<")"<<std::endl;;
    }
    std::cout<<"ok2"<<std::endl;;
  }
  
  else{
    for(auto & i_c3d : c3d){     
      std::cout<<"C3D "<<i_c3d<<" (pt,eta,phi)="<<(*_cl3d_pt)[i_c3d]<<","<<(*_cl3d_eta)[i_c3d]<<","<<(*_cl3d_phi)[i_c3d]<<")"<<std::endl;;
      h->Fill((*_cl3d_eta)[i_c3d],(*_cl3d_phi)[i_c3d],(*_cl3d_pt)[i_c3d]);      
    }
  }

  

  // else if(jets.size()>0){
  //   for(auto & i_jet : jets){
  //     for(auto & i_c3d : (*_jets_cl3d)[i_jet]){
  // 	h->Fill((*_cl3d_eta)[i_c3d],(*_cl3d_phi)[i_c3d],(*_cl3d_pt)[i_c3d]);
  // 	std::cout<<"(pt,eta,phi)=("<<(*_cl3d_pt)[i_c3d]<<","<<(*_cl3d_eta)[i_c3d]<<","<<(*_cl3d_phi)[i_c3d]<<")"<<std::endl;;	
  //     }
  //   }

  // }


  PlotterEventDisplay plotter( _cmd );
  plotter.Draw(h,"2dc3d","display2D_c3d");

  h->Delete();

}








void HGC::display2D_jets(TString file, int n_event, 
		    const std::vector<int>& jet,
		    float eta_min, float eta_max, 
		    float phi_min, float phi_max){

  TH2F* h=new TH2F("h","h",50,eta_min,eta_max,50,phi_min,phi_max);

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(file);
  
  std::vector<float> *_jets_eta;
  std::vector<float> *_jets_phi;
  std::vector<float> *_jets_energy;
  std::vector<float> *_jets_pt;

  tree->SetBranchAddress("jets_eta",    &_jets_eta);
  tree->SetBranchAddress("jets_phi",    &_jets_phi);
  tree->SetBranchAddress("jets_energy", &_jets_energy);
  tree->SetBranchAddress("jets_pt", &_jets_pt);     

  _jets_eta = 0;
  _jets_phi = 0;
  _jets_energy = 0;
  _jets_pt = 0;
  
  
  tree->GetEntry(n_event);
  
  if(jet.size()>0){

    if(jet[0]<0){
      for(unsigned int i_jet = 0; i_jet<(*_jets_eta).size(); i_jet++){
	h->Fill((*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_pt)[i_jet]);
	std::cout<<"(pt,eta,phi)=("<<(*_jets_pt)[i_jet]<<","<<(*_jets_eta)[i_jet]<<","<<(*_jets_phi)[i_jet]<<")"<<std::endl;;
      }
    }

    else{
      for(auto & i_jet : jet){   
	std::cout<<"Jet "<<i_jet<<"(pt,eta,phi)=("<<(*_jets_pt)[i_jet]<<","<<(*_jets_eta)[i_jet]<<","<<(*_jets_phi)[i_jet]<<")"<<std::endl;;  
	h->Fill((*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_pt)[i_jet]);
      }
    }
  }

  h->GetXaxis()->SetTitle("#eta(jet)");
  h->GetXaxis()->SetTitleOffset(1.5);
  h->GetYaxis()->SetTitle("#phi(jet)");
  h->GetZaxis()->SetTitle("p_{T}(jet) [GeV]");
  h->SetTitle("");
  h->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  gStyle->SetPaintTextFormat("4.1f");
  h->Draw("colz");

}









void HGC::display2D_gen(TString file, int n_event, 
		   float eta_min, float eta_max, 
		   float phi_min, float phi_max){

  TH2F* h=new TH2F("h","h",100,eta_min,eta_max,100,phi_min,phi_max);

  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(file);
  
  std::vector<float> *_gen_eta;
  std::vector<float> *_gen_phi;
  std::vector<float> *_gen_energy;
  std::vector<float> *_gen_pt;
  std::vector<int> *_gen_pdg;
  std::vector<int> *_gen_status;

  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_phi",    &_gen_phi);
  tree->SetBranchAddress("gen_energy", &_gen_energy);
  tree->SetBranchAddress("gen_pt", &_gen_pt);
  tree->SetBranchAddress("gen_pdgid", &_gen_pdg);
  tree->SetBranchAddress("gen_status", &_gen_status);


  _gen_eta = 0;
  _gen_phi = 0;
  _gen_energy = 0;
  _gen_pt = 0;
  _gen_pdg = 0;
  _gen_status = 0;

  
  tree->GetEntry(n_event);

  for(unsigned int i_gen = 0; i_gen<(*_gen_eta).size(); i_gen++){
    if((*_gen_status)[i_gen]==1){
      h->Fill((*_gen_eta)[i_gen],(*_gen_phi)[i_gen],(*_gen_pt)[i_gen]);
      std::cout<<"(pdg,pt,eta,phi)=("<<(*_gen_pdg)[i_gen]<<","<<(*_gen_pt)[i_gen]<<","<<(*_gen_eta)[i_gen]<<","<<(*_gen_phi)[i_gen]<<")"<<std::endl;;
    }
  }


  PlotterEventDisplay plotter( _cmd );
  plotter.Draw(h,"gen","display2D_gen");

  h->Delete();

}




