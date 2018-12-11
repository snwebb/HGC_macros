#include "HGC.h"

//Calibrate Jet code not fully working yet

void HGC::calibrate_jet(TString filein,
		   TString fileout){
  
  TFile* f_new = TFile::Open(fileout);
  // if(f_new!=0){
  //   std::cout<<fileout<<" already exists, please delete it before converting again"<<std::endl;;
  //   return;
  // }  
  f_new = TFile::Open(fileout,"RECREATE");
  
  TChain * tree = new TChain("HGCalTriggerNtupleJet");
  tree->Add(filein);
  Long64_t nentries = tree->GetEntries();
  std::cout<<"nentries="<<nentries<<std::endl;;
  
  
  TTree* tree_new2 = new TChain("HGCalTriggerNtupleJet");
  TChain * tree_jet = new TChain("HGCalTriggerNtupleJet");
  tree_jet->Add(filein);
  Long64_t nentries2 = tree_jet->GetEntries();
  if(nentries!=nentries2){
    std::cout<<"Inconsistent number of entries in two input files"<<std::endl;;
    return;
  }
  
  

  std::vector<float>* _jets_raw_eta;
  std::vector<float>* _jets_raw_phi;
  std::vector<float>* _jets_raw_Luca_pt;
  std::vector<float>* _jets_raw_Luca_energy;
  std::vector<float>* _jets_PU_subtr_cone_C3D;

  tree_jet->SetBranchAddress("jets_raw_eta",           &_jets_raw_eta);
  tree_jet->SetBranchAddress("jets_raw_phi",           &_jets_raw_phi);
  tree_jet->SetBranchAddress("jets_raw_Luca_pt",       &_jets_raw_Luca_pt);
  tree_jet->SetBranchAddress("jets_raw_Luca_energy",   &_jets_raw_Luca_energy);
  tree_jet->SetBranchAddress("jets_PU_subtr_cone_C3D", &_jets_PU_subtr_cone_C3D);
  
  //New branches
  std::vector<float> _jets_raw_PUS_pt;
  std::vector<float> _jets_raw_PUS_energy;
  std::vector<float> _jets_calib_pt;
  std::vector<float> _jets_calib_energy;

  tree_new2->Branch("jets_raw_PUS_pt",     &_jets_raw_PUS_pt);
  tree_new2->Branch("jets_raw_PUS_energy", &_jets_raw_PUS_energy);
  tree_new2->Branch("jets_calib_pt",       &_jets_calib_pt);
  tree_new2->Branch("jets_calib_energy",   &_jets_calib_energy);
  
  
  for(int i=0;i<nentries;i++){
    std::cout<<"i="<<i<<std::endl;;
    
    _jets_raw_eta = 0;
    _jets_raw_phi = 0;
    _jets_raw_Luca_pt = 0;
    _jets_raw_Luca_energy = 0;
    _jets_PU_subtr_cone_C3D = 0;
    
    _jets_raw_PUS_pt.clear();
    _jets_raw_PUS_energy.clear();
    _jets_calib_pt.clear();
    _jets_calib_energy.clear();
    
    tree->GetEntry(i);
    tree_jet->GetEntry(i);
    
    for(unsigned int i_jet=0;i_jet<(*_jets_raw_eta).size();i_jet++){
      
      TLorentzVector jet_PUS;
      double pt_PUS = std::max(double((*_jets_raw_Luca_pt)[i_jet]-(*_jets_PU_subtr_cone_C3D)[i_jet]),0.);
      jet_PUS.SetPtEtaPhiM(pt_PUS,(*_jets_raw_eta)[i_jet],(*_jets_raw_phi)[i_jet],0.);
      
      double SF = 4.4374 -0.948102 *TMath::Log(std::max(pt_PUS,20.)) + 0.0686934* TMath::Log(std::max(pt_PUS,20.)) * TMath::Log(std::max(pt_PUS,20.));
      TLorentzVector jet_calib = SF*jet_PUS;
      
      _jets_raw_PUS_pt.emplace_back(jet_PUS.Pt());
      _jets_raw_PUS_energy.emplace_back(jet_PUS.E());
      _jets_calib_pt.emplace_back(jet_calib.Pt());
      _jets_calib_energy.emplace_back(jet_calib.E());
      
    }
        
  }
  

}

