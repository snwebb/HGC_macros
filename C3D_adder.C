
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include "Helpers.C"
#include <unordered_map>




void add_C3D(TString filein, TString treename, TString fileout){


  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");

  TChain * tree = new TChain(treename);
  tree->Add(filein);
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<nentries<<endl;


  int _tc_n;
  int _cl_n;
  int _cl3d_n;

  vector<float> *_tc_eta;
  vector<float> *_tc_phi;
  vector<float> *_tc_energy;
  vector<float> *_tc_z;
  vector<int> *_tc_layer;
  vector<unsigned int> *_tc_id;
  vector<unsigned int> *_tc_multicluster_id;

  vector<float> *_cl_pt;
  vector<float> *_cl_eta;
  vector<float> *_cl_phi;
  vector<float> *_cl_energy;
  vector<int> *_cl_layer;
  vector<unsigned int> *_cl_id;
  vector<unsigned int> *_cl_multicluster_id;
  vector<vector<unsigned int> > *_cl_cells_id;
  
  vector<float> *_cl3d_pt;
  vector<float> *_cl3d_eta;
  vector<float> *_cl3d_phi;
  vector<float> *_cl3d_energy;
  vector<int> *_cl3d_firstlayer;
  vector<int> *_cl3d_showerlength;
  vector<int> *_cl3d_id;
  vector<vector<int> > *_cl3d_clusters_id;

  tree->SetBranchAddress("tc_n",     &_tc_n);
  tree->SetBranchAddress("cl_n",     &_cl_n);
  tree->SetBranchAddress("cl3d_n",   &_cl3d_n);
  
  tree->SetBranchAddress("tc_eta",    &_tc_eta);
  tree->SetBranchAddress("tc_phi",    &_tc_phi);
  tree->SetBranchAddress("tc_energy", &_tc_energy);
  tree->SetBranchAddress("tc_z", &_tc_z);
  tree->SetBranchAddress("tc_layer", &_tc_layer);
  tree->SetBranchAddress("tc_id", &_tc_id);
  tree->SetBranchAddress("tc_multicluster_id", &_tc_multicluster_id);

  tree->SetBranchAddress("cl_pt",     &_cl_pt);
  tree->SetBranchAddress("cl_eta",    &_cl_eta);
  tree->SetBranchAddress("cl_phi",    &_cl_phi);
  tree->SetBranchAddress("cl_energy", &_cl_energy);
  tree->SetBranchAddress("cl_layer", &_cl_layer);
  tree->SetBranchAddress("cl_id", &_cl_id);
  tree->SetBranchAddress("cl_multicluster_id", &_cl_multicluster_id);
  tree->SetBranchAddress("cl_cells_id", &_cl_cells_id);

  tree->SetBranchAddress("cl3d_pt",     &_cl3d_pt);
  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);
  tree->SetBranchAddress("cl3d_firstlayer", &_cl3d_firstlayer);
  tree->SetBranchAddress("cl3d_showerlength", &_cl3d_showerlength);
  tree->SetBranchAddress("cl3d_id", &_cl3d_id);
  tree->SetBranchAddress("cl3d_clusters_id", &_cl3d_clusters_id);

  vector<int> _cl3d_closest_index;
  vector<float> _cl3d_closest_dR;
  
  vector<int> _cl3d_clusters_n_firstlayer;
  vector<float> _cl3d_xOverZ_firstlayer;
  vector<float> _cl3d_yOverZ_firstlayer;
  vector<float> _cl3d_z_firstlayer;

  vector<int> _cl3d_clusters_n_lastlayer;
  vector<float> _cl3d_xOverZ_lastlayer;
  vector<float> _cl3d_yOverZ_lastlayer;
  vector<float> _cl3d_z_lastlayer;

  TTree* tree_new=tree->GetTree()->CloneTree(0);  

  tree_new->Branch("cl3d_closest_index",&_cl3d_closest_index);
  tree_new->Branch("cl3d_closest_dR",   &_cl3d_closest_dR);

  tree_new->Branch("cl3d_clusters_n_firstlayer",   &_cl3d_clusters_n_firstlayer);
  tree_new->Branch("cl3d_xOverZ_firstlayer",   &_cl3d_xOverZ_firstlayer);
  tree_new->Branch("cl3d_yOverZ_firstlayer",   &_cl3d_yOverZ_firstlayer);
  tree_new->Branch("cl3d_z_firstlayer",   &_cl3d_z_firstlayer);

  tree_new->Branch("cl3d_clusters_n_lastlayer",   &_cl3d_clusters_n_lastlayer);
  tree_new->Branch("cl3d_xOverZ_lastlayer",   &_cl3d_xOverZ_lastlayer);
  tree_new->Branch("cl3d_yOverZ_lastlayer",   &_cl3d_yOverZ_lastlayer);
  tree_new->Branch("cl3d_z_lastlayer",   &_cl3d_z_lastlayer);

  for(int i=0;i<nentries;i++){

    if(i%100==0)
      cout<<"i="<<i<<endl;

    _tc_n = 0;
    _cl_n = 0;
    _cl3d_n = 0;
    
    _tc_eta = 0;
    _tc_phi = 0;
    _tc_energy = 0;
    _tc_z = 0;
    _tc_layer = 0;
    _tc_id = 0;
    _tc_multicluster_id = 0;

    _cl_pt = 0;
    _cl_eta = 0;
    _cl_phi = 0;
    _cl_energy = 0;
    _cl_layer = 0;
    _cl_id = 0;
    _cl_multicluster_id = 0;
    _cl_cells_id = 0;
    
    _cl3d_pt = 0;
    _cl3d_eta = 0;
    _cl3d_phi = 0;
    _cl3d_energy = 0;
    _cl3d_firstlayer = 0;
    _cl3d_showerlength = 0;
    _cl3d_id = 0;
    _cl3d_clusters_id = 0;

    _cl3d_closest_index.clear();
    _cl3d_closest_dR.clear();
  
    _cl3d_clusters_n_firstlayer.clear();
    _cl3d_xOverZ_firstlayer.clear();
    _cl3d_yOverZ_firstlayer.clear();
    _cl3d_z_firstlayer.clear();
    
    _cl3d_clusters_n_lastlayer.clear();
    _cl3d_xOverZ_lastlayer.clear();
    _cl3d_yOverZ_lastlayer.clear();
    _cl3d_z_lastlayer.clear();
    

     tree->GetEntry(i);

     map<unsigned int, unsigned int> tc_map; //First ID, Second index
     map<unsigned int, unsigned int> cl_map; //First ID, Second index

     for(unsigned int i_tc = 0; i_tc < _tc_n; i_tc++)
       tc_map[(*_tc_id)[i_tc]] = i_tc;
     for(unsigned int i_cl = 0; i_cl < _cl_n; i_cl++)
       cl_map[(*_cl_id)[i_cl]] = i_cl;


     for(unsigned int i_c3d = 0; i_c3d<_cl3d_n; i_c3d++){
       
       int firstlayer = (*_cl3d_firstlayer)[i_c3d];
       int lastlayer = firstlayer+(*_cl3d_showerlength)[i_c3d]-1;

       float z_firstlayer = 0;
       float z_lastlayer = 0;
       int n_c2d_firstlayer = 0;
       int n_c2d_lastlayer = 0;
       TLorentzVector firstlayer_tlv;
       TLorentzVector lastlayer_tlv;       
       
       for(auto& c2d : (*_cl3d_clusters_id)[i_c3d]){

	 int i_c2d = cl_map[c2d];
	 int layer = (*_cl_layer)[i_c2d];

	 if(layer==firstlayer){	   
	   z_firstlayer = (*_tc_z)[tc_map[(*_cl_cells_id)[i_c2d][0]]];
	   n_c2d_firstlayer++;
	   TLorentzVector C2D_tlv;
	   C2D_tlv.SetPtEtaPhiE((*_cl_pt)[i_c2d],(*_cl_eta)[i_c2d],(*_cl_phi)[i_c2d],(*_cl_energy)[i_c2d]);
	   firstlayer_tlv+=C2D_tlv;
	 }

	 if(layer==lastlayer){
	   z_lastlayer = (*_tc_z)[tc_map[(*_cl_cells_id)[i_c2d][0]]];
	   n_c2d_lastlayer++;
	   TLorentzVector C2D_tlv;
	   C2D_tlv.SetPtEtaPhiE((*_cl_pt)[i_c2d],(*_cl_eta)[i_c2d],(*_cl_phi)[i_c2d],(*_cl_energy)[i_c2d]);
	   lastlayer_tlv+=C2D_tlv;
	 }

       }

       float xOverZ_firstlayer = cos(firstlayer_tlv.Phi())/sinh(firstlayer_tlv.Eta());
       float yOverZ_firstlayer = sin(firstlayer_tlv.Phi())/sinh(firstlayer_tlv.Eta());
       float xOverZ_lastlayer = cos(lastlayer_tlv.Phi())/sinh(lastlayer_tlv.Eta());
       float yOverZ_lastlayer = sin(lastlayer_tlv.Phi())/sinh(lastlayer_tlv.Eta());
       
       _cl3d_clusters_n_firstlayer.push_back(n_c2d_firstlayer);
       _cl3d_xOverZ_firstlayer.push_back(xOverZ_firstlayer);
       _cl3d_yOverZ_firstlayer.push_back(yOverZ_firstlayer);
       _cl3d_z_firstlayer.push_back(z_firstlayer);
       
       _cl3d_clusters_n_lastlayer.push_back(n_c2d_lastlayer);
       _cl3d_xOverZ_lastlayer.push_back(xOverZ_lastlayer);
       _cl3d_yOverZ_lastlayer.push_back(yOverZ_lastlayer);
       _cl3d_z_lastlayer.push_back(z_lastlayer);
 

       int i_closest = -1;
       float dR_min = -1;

       float xOverZ1 = cos((*_cl3d_phi)[i_c3d])/sinh((*_cl3d_eta)[i_c3d]);
       float yOverZ1 = sin((*_cl3d_phi)[i_c3d])/sinh((*_cl3d_eta)[i_c3d]);

       for(unsigned int i2_c3d = 0; i2_c3d<_cl3d_n; i2_c3d++){    
	 
	 if(i2_c3d==i_c3d) continue;
	 if((*_cl3d_eta)[i_c3d]*(*_cl3d_eta)[i2_c3d]<0) continue;

	 float xOverZ2 = cos((*_cl3d_phi)[i2_c3d])/sinh((*_cl3d_eta)[i2_c3d]);
	 float yOverZ2 = sin((*_cl3d_phi)[i2_c3d])/sinh((*_cl3d_eta)[i2_c3d]);

	 float dR = sqrt( pow(xOverZ1-xOverZ2,2) + pow(yOverZ1-yOverZ2,2) );

	 if(dR_min<0. || dR<dR_min){
	   dR_min = dR;
	   i_closest = i2_c3d;
	 }

       }

       _cl3d_closest_index.push_back(i_closest);
       _cl3d_closest_dR.push_back(dR_min);

     }
	   

    tree_new->Fill();

  }


  tree_new->Write();
  f_new->Close();
  return;


}



void test(){

  TString filein="root://cms-xrd-global.cern.ch//store/user/tstreble/SinglePiPt25Eta1p6_2p8/SinglePi_Pt25_PU0_dRC3D_fullTC_C2D_18_06_11/180611_134720/0000/ntuple_1.root";
  TString treename="hgcalTriggerNtuplizer/HGCalTriggerNtuple";
  TString fileout="C3D_ext.root";

  add_C3D(filein,treename,fileout);

}
