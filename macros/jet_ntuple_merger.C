
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include "Helpers.C"
#include <unordered_map>

using namespace std;



int HGC_layer(const uint32_t subdet, const uint32_t layer) {

  int hgclayer = -1;
  if(subdet==3) hgclayer=layer;//EE
  else if(subdet==4) hgclayer=layer+28;//FH
  else if(subdet==5) hgclayer=layer+40;//BH

  return hgclayer;

}




//Compute energy-weighted mean of any variable X in the cluster

float meanX(const std::vector<pair<float,float> >& energy_X_tc) {

  float Etot = 0;
  float X_sum = 0;

  for(const auto& energy_X : energy_X_tc){

    X_sum += energy_X.first*energy_X.second;
    Etot += energy_X.first;

  }

  float X_mean = 0;
  if(Etot>0) X_mean = X_sum/Etot;
  return X_mean;

}




//Compute energy-weighted RMS of any variable X in the cluster

float sigmaXX(const std::vector<pair<float,float> >& energy_X_tc, const float X_cluster) {

  float Etot = 0;
  float deltaX2_sum = 0;

  for(const auto& energy_X : energy_X_tc){

    deltaX2_sum += energy_X.first * pow(energy_X.second - X_cluster,2);
    Etot += energy_X.first;

  }

  float X_MSE = 0;
  if (Etot>0) X_MSE=deltaX2_sum/Etot;
  float X_RMS=sqrt(X_MSE);
  return X_RMS;

}


//Compute energy-weighted RMS of any variable X in the cluster
//Extra care needed because of deltaPhi

float sigmaPhiPhi(const std::vector<pair<float,float> >& energy_phi_tc, const float phi_cluster) {

  float Etot = 0;
  float deltaphi2_sum = 0;

  for(const auto& energy_phi : energy_phi_tc){

    deltaphi2_sum += energy_phi.first * pow(deltaPhi(energy_phi.second,phi_cluster),2);
    Etot += energy_phi.first;

  }

  float phi_MSE = 0;
  if (Etot>0) phi_MSE=deltaphi2_sum/Etot;
  float Spp=sqrt(phi_MSE);
  return Spp;

}





void add_jet(TString filein,  TString treename, TString filein_jet, TString treename_jet, TString fileout, bool JB_version=true){

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

  TChain * tree_jet = new TChain(treename_jet);
  tree_jet->Add(filein_jet);
  Long64_t nentries2 = tree_jet->GetEntries();
  if(nentries!=nentries2){
    cout<<"Inconsistent number of entries in two input files"<<endl;
    return;
  }

  
  int _tc_n;
  int _cl_n;
  int _cl3d_n;

  vector<float> *_tc_eta;
  vector<float> *_tc_phi;
  vector<float> *_tc_energy;
  vector<float> *_tc_z;
  vector<int> *_tc_layer;
  vector<int> *_tc_subdet;
  vector<unsigned int> *_tc_id;
  
  vector<float> *_cl_pt;
  vector<float> *_cl_eta;
  vector<float> *_cl_phi;
  vector<float> *_cl_energy;
  vector<unsigned int> *_cl_id;

  vector<float> *_cl3d_pt;
  vector<float> *_cl3d_eta;
  vector<float> *_cl3d_phi;
  vector<float> *_cl3d_energy;

  vector<float> *_jets_pt;
  vector<float> *_jets_eta;
  vector<float> *_jets_phi;
  vector<float> *_jets_energy;

  vector<vector<float> > *_jets_C3d_pt;
  vector<vector<float> > *_jets_C3d_eta;
  vector<vector<float> > *_jets_C3d_phi;
  vector<vector<float> > *_jets_C3d_energy;

  vector<vector<unsigned int> > *_cl_cells;
  vector<vector<unsigned int> > *_cl3d_clusters;
      
  //tree_new->SetBranchAddress("tc_n",     &_tc_n);
  tree->SetBranchAddress("cl_n",     &_cl_n);
  tree->SetBranchAddress("cl3d_n",   &_cl3d_n);
  
  tree->SetBranchAddress("tc_eta",    &_tc_eta);
  tree->SetBranchAddress("tc_phi",    &_tc_phi);
  tree->SetBranchAddress("tc_energy", &_tc_energy);
  tree->SetBranchAddress("tc_z", &_tc_z);
  tree->SetBranchAddress("tc_layer", &_tc_layer);
  tree->SetBranchAddress("tc_subdet", &_tc_subdet);
  if(JB_version)
    tree->SetBranchAddress("tc_id", &_tc_id);

  tree->SetBranchAddress("cl_pt",     &_cl_pt);
  tree->SetBranchAddress("cl_eta",    &_cl_eta);
  tree->SetBranchAddress("cl_phi",    &_cl_phi);
  tree->SetBranchAddress("cl_energy", &_cl_energy);
  if(JB_version)
    tree->SetBranchAddress("cl_id", &_cl_id);

  tree->SetBranchAddress("cl3d_pt",     &_cl3d_pt);
  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);

  tree_jet->SetBranchAddress("jets_pt",     &_jets_pt);
  tree_jet->SetBranchAddress("jets_eta",    &_jets_eta);
  tree_jet->SetBranchAddress("jets_phi",    &_jets_phi);
  tree_jet->SetBranchAddress("jets_energy", &_jets_energy);

  tree->SetBranchAddress("cl_cells",        &_cl_cells);
  tree->SetBranchAddress("cl3d_clusters",   &_cl3d_clusters);

  tree_jet->SetBranchAddress("jets_C3d_pt",     &_jets_C3d_pt);
  tree_jet->SetBranchAddress("jets_C3d_eta",    &_jets_C3d_eta);
  tree_jet->SetBranchAddress("jets_C3d_phi",    &_jets_C3d_phi);
  tree_jet->SetBranchAddress("jets_C3d_energy", &_jets_C3d_energy);

  TTree* tree_new=tree->GetTree()->CloneTree(0);
  TTree* tree_new2=tree_jet->GetTree()->CloneTree(0);
  tree_new->AddFriend(tree_new2);
  
  //New branches
  vector<float> _tc_pt;
  vector<int> _tc_HGClayer;
  vector<int> _cl_HGClayer;

  vector<int> _tc_cl; //index of C2d in which tc included
  vector<int> _cl_cl3d; //index of C3d in which cl included
  vector<int> _cl3d_jet; //index of jet in which cl3d included

  int _jets_n;
  vector<int> _jets_ncl3d;
  vector<vector<int> > _jets_cl3d; // list of cl3d included in jet

  vector<float> _cl3d_seetot_new;
  vector<float> _cl3d_spptot_new;
  vector<float> _cl3d_srrtot_new;
  vector<float> _cl3d_seemax_new;
  vector<float> _cl3d_sppmax_new;
  vector<float> _cl3d_srrmax_new;
  vector<float> _cl3d_seemax_layer_new;
  vector<float> _cl3d_sppmax_layer_new;
  vector<float> _cl3d_srrmax_layer_new;
  vector<float> _cl3d_see_quadsum_new;
  vector<float> _cl3d_spp_quadsum_new;
  vector<float> _cl3d_srr_quadsum_new;
  vector<float> _cl3d_szz_new;
  vector<float> _cl3d_r_mean;
  vector<float> _cl3d_z_mean;
  vector<int> _cl3d_first_HGClayer;

  vector<float> _jets_seetot;
  vector<float> _jets_spptot;
  vector<float> _jets_srrtot;
  vector<float> _jets_seetot_cl3d;
  vector<float> _jets_spptot_cl3d;
  vector<float> _jets_srrtot_cl3d;
  vector<float> _jets_seemax_cl3d;
  vector<float> _jets_sppmax_cl3d;
  vector<float> _jets_srrmax_cl3d;
  vector<float> _jets_see_quadsum_cl3d;
  vector<float> _jets_spp_quadsum_cl3d;
  vector<float> _jets_srr_quadsum_cl3d;
  vector<float> _jets_szz_cl3d;
  vector<float> _jets_firstlayer_avg;
 
  tree_new->Branch("tc_pt",     &_tc_pt);
  tree_new->Branch("tc_HGClayer",     &_tc_HGClayer);
  tree_new->Branch("cl_HGClayer",     &_cl_HGClayer);

  tree_new->Branch("tc_cl",     &_tc_cl);
  tree_new->Branch("cl_cl3d",   &_cl_cl3d);
  tree_new->Branch("cl3d_jet",  &_cl3d_jet);
 
  tree_new2->Branch("jets_n",    &_jets_n,   "jets_n/I");
  tree_new2->Branch("jets_ncl3d", &_jets_ncl3d);
  tree_new2->Branch("jets_cl3d", &_jets_cl3d);

  tree_new->Branch("cl3d_seetot_new", &_cl3d_seetot_new);
  tree_new->Branch("cl3d_spptot_new", &_cl3d_spptot_new);
  tree_new->Branch("cl3d_srrtot_new", &_cl3d_srrtot_new);
  tree_new->Branch("cl3d_seemax_new", &_cl3d_seemax_new);
  tree_new->Branch("cl3d_sppmax_new", &_cl3d_sppmax_new);
  tree_new->Branch("cl3d_srrmax_new", &_cl3d_srrmax_new);
  tree_new->Branch("cl3d_seemax_layer_new", &_cl3d_seemax_layer_new);
  tree_new->Branch("cl3d_sppmax_layer_new", &_cl3d_sppmax_layer_new);
  tree_new->Branch("cl3d_srrmax_layer_new", &_cl3d_srrmax_layer_new);
  tree_new->Branch("cl3d_see_quadsum_new", &_cl3d_see_quadsum_new);
  tree_new->Branch("cl3d_spp_quadsum_new", &_cl3d_spp_quadsum_new);
  tree_new->Branch("cl3d_srr_quadsum_new", &_cl3d_srr_quadsum_new);
  tree_new->Branch("cl3d_szz_new",    &_cl3d_szz_new);
  tree_new->Branch("cl3d_r_mean",     &_cl3d_r_mean);
  tree_new->Branch("cl3d_z_mean",     &_cl3d_z_mean);
  tree_new->Branch("cl3d_first_HGClayer",     &_cl3d_first_HGClayer);

  tree_new2->Branch("jets_seetot", &_jets_seetot);
  tree_new2->Branch("jets_spptot", &_jets_spptot);
  tree_new2->Branch("jets_srrtot", &_jets_srrtot);
  tree_new2->Branch("jets_seetot_cl3d", &_jets_seetot_cl3d);
  tree_new2->Branch("jets_spptot_cl3d", &_jets_spptot_cl3d);
  tree_new2->Branch("jets_srrtot_cl3d", &_jets_srrtot_cl3d);
  tree_new2->Branch("jets_seemax_cl3d", &_jets_seemax_cl3d);
  tree_new2->Branch("jets_sppmax_cl3d", &_jets_sppmax_cl3d);
  tree_new2->Branch("jets_srrmax_cl3d", &_jets_srrmax_cl3d);
  tree_new2->Branch("jets_see_quadsum_cl3d", &_jets_see_quadsum_cl3d);
  tree_new2->Branch("jets_spp_quadsum_cl3d", &_jets_spp_quadsum_cl3d);
  tree_new2->Branch("jets_srr_quadsum_cl3d", &_jets_srr_quadsum_cl3d);
  tree_new2->Branch("jets_szz_cl3d", &_jets_szz_cl3d);
  tree_new2->Branch("jets_firstlayer_avg", &_jets_firstlayer_avg);

  for(int i=0;i<nentries;i++){

    //if(i%10000==0)
      cout<<"i="<<i<<endl;
    
    _tc_n = 0;
    _cl_n = 0;
    _cl3d_n = 0;
  
    _tc_eta = 0;
    _tc_phi = 0;
    _tc_energy = 0;
    _tc_z = 0;
    _tc_layer = 0;
    _tc_subdet = 0;
    _tc_id = 0;

    _cl_pt = 0;
    _cl_eta = 0;
    _cl_phi = 0;
    _cl_energy = 0;
    _cl_id = 0;

    _cl3d_pt = 0;
    _cl3d_eta = 0;
    _cl3d_phi = 0;
    _cl3d_energy = 0;

    _jets_pt = 0;
    _jets_eta = 0;
    _jets_phi = 0;
    _jets_energy = 0;    
    
    _jets_C3d_pt = 0;
    _jets_C3d_eta = 0;
    _jets_C3d_phi = 0;
    _jets_C3d_energy = 0;
    
    _cl_cells = 0;
    _cl3d_clusters = 0;

    _jets_n = 0;
    _tc_pt.clear();
    _tc_HGClayer.clear();
    _cl_HGClayer.clear();

    _tc_cl.clear();
    _cl_cl3d.clear();
    _cl3d_jet.clear();
    _jets_ncl3d.clear();
    _jets_cl3d.clear();

    _cl3d_seetot_new.clear();
    _cl3d_spptot_new.clear();
    _cl3d_srrtot_new.clear();
    _cl3d_seemax_new.clear();
    _cl3d_sppmax_new.clear();
    _cl3d_srrmax_new.clear();
    _cl3d_seemax_layer_new.clear();
    _cl3d_sppmax_layer_new.clear();
    _cl3d_srrmax_layer_new.clear();
    _cl3d_see_quadsum_new.clear();
    _cl3d_spp_quadsum_new.clear();
    _cl3d_srr_quadsum_new.clear();
    _cl3d_szz_new.clear();
    _cl3d_r_mean.clear();
    _cl3d_z_mean.clear();
    _cl3d_first_HGClayer.clear();
   
    _jets_seetot.clear();
    _jets_spptot.clear();
    _jets_srrtot.clear();
    _jets_seetot_cl3d.clear();
    _jets_spptot_cl3d.clear();
    _jets_srrtot_cl3d.clear();
    _jets_seemax_cl3d.clear();
    _jets_sppmax_cl3d.clear();
    _jets_srrmax_cl3d.clear();
    _jets_see_quadsum_cl3d.clear();
    _jets_spp_quadsum_cl3d.clear();
    _jets_srr_quadsum_cl3d.clear();
    _jets_szz_cl3d.clear();
    _jets_firstlayer_avg.clear();
    
    tree->GetEntry(i);
    tree_jet->GetEntry(i);

    _tc_n = (*_tc_eta).size();
    _jets_n = (*_jets_C3d_pt).size();   

    map<unsigned int, unsigned int> tc_map; //First ID, Second index
    map<unsigned int, unsigned int> cl_map; //First ID, Second index

    for(unsigned int i_tc=0; i_tc<_tc_n; i_tc++){

      _tc_pt.emplace_back( (*_tc_energy)[i_tc]/TMath::CosH((*_tc_eta)[i_tc]) );

      int HGClayer = HGC_layer( (*_tc_subdet)[i_tc], (*_tc_layer)[i_tc] );
      _tc_HGClayer.emplace_back(HGClayer);
      
      if(JB_version)
	tc_map[(*_tc_id)[i_tc]] = i_tc;
      else
	tc_map[i_tc] = i_tc;

    }


    for(unsigned int i_cl=0; i_cl<(*_cl_cells).size(); i_cl++){

      int tc_index = tc_map[(*_cl_cells)[i_cl][0]];
      int HGClayer = HGC_layer( (*_tc_subdet)[tc_index], (*_tc_layer)[tc_index] );
      _cl_HGClayer.emplace_back(HGClayer);

      if(JB_version)
	cl_map[(*_cl_id)[i_cl]] = i_cl;
      else
	cl_map[i_cl] = i_cl;
    }
    
    
    //Cross-reference of objects

    _tc_cl.resize(_tc_n,-1);
    for(unsigned int i_cl=0; i_cl<(*_cl_cells).size(); i_cl++){
      for(unsigned int i_tc=0; i_tc<(*_cl_cells)[i_cl].size(); i_tc++){

	int tc_index = tc_map[(*_cl_cells)[i_cl][i_tc]];
	_tc_cl[tc_index] = i_cl;    

      }
    }

    _cl_cl3d.resize(_cl_n,-1);
    for(unsigned int i_cl3d=0; i_cl3d<(*_cl3d_clusters).size(); i_cl3d++){
      for(unsigned int i_cl=0; i_cl<(*_cl3d_clusters)[i_cl3d].size(); i_cl++){

	int cl_index = cl_map[(*_cl3d_clusters)[i_cl3d][i_cl]];
	_cl_cl3d[cl_index] = i_cl3d;

      }
    }


    for(unsigned int i_jet=0; i_jet<(*_jets_C3d_pt).size(); i_jet++){

      vector<int> cl3d_currentjet;

      for(unsigned int i_cl3d_jet=0; i_cl3d_jet<(*_jets_C3d_pt)[i_jet].size(); i_cl3d_jet++){
	
	TLorentzVector C3D_jet;
	C3D_jet.SetPtEtaPhiE((*_jets_C3d_pt)[i_jet][i_cl3d_jet],(*_jets_C3d_eta)[i_jet][i_cl3d_jet],(*_jets_C3d_phi)[i_jet][i_cl3d_jet],(*_jets_C3d_energy)[i_jet][i_cl3d_jet]);
	int i_cl3d_matched = -1;
	
	for(unsigned int i_cl3d=0; i_cl3d<(*_cl3d_pt).size(); i_cl3d++){
	  TLorentzVector C3D;
	  C3D.SetPtEtaPhiE((*_cl3d_pt)[i_cl3d],(*_cl3d_eta)[i_cl3d],(*_cl3d_phi)[i_cl3d],(*_cl3d_energy)[i_cl3d]);

	  if(C3D.DeltaR(C3D_jet)<0.01){
	    i_cl3d_matched = i_cl3d;
	    break;
	  }
	}
	
	cl3d_currentjet.emplace_back(i_cl3d_matched);

      }

      _jets_cl3d.emplace_back(cl3d_currentjet);
      _jets_ncl3d.emplace_back(cl3d_currentjet.size());

    }
    
    _cl3d_jet.resize(_cl3d_n,-1);
    for(unsigned int i_jet=0; i_jet<(_jets_cl3d).size(); i_jet++){
      for(unsigned int i_cl3d=0; i_cl3d<(_jets_cl3d)[i_jet].size(); i_cl3d++){
	_cl3d_jet[(_jets_cl3d)[i_jet][i_cl3d]] = i_jet;
      }
    }


    //Clusters shower-shape variables

    for(unsigned int i_cl3d=0; i_cl3d<(*_cl3d_clusters).size();i_cl3d++){

      std::vector<std::pair<float,float> > energy_eta_tc;
      std::vector<std::pair<float,float> > energy_phi_tc;
      std::vector<std::pair<float,float> > energy_r_tc;
      std::vector<std::pair<float,float> > energy_z_tc;

      std::unordered_map<int, std::vector<std::pair<float,float> > > layer_energy_eta_tc;
      std::unordered_map<int, std::vector<std::pair<float,float> > > layer_energy_phi_tc;
      std::unordered_map<int, std::vector<std::pair<float,float> > > layer_energy_r_tc;
      std::unordered_map<int, TLorentzVector> layer_LV;

      for(unsigned int i_cl=0; i_cl<(*_cl3d_clusters)[i_cl3d].size();i_cl++){

	int cl_index = cl_map[(*_cl3d_clusters)[i_cl3d][i_cl]];
	TLorentzVector clu_tlv;
	clu_tlv.SetPtEtaPhiE((*_cl_pt)[cl_index],(*_cl_eta)[cl_index],(*_cl_phi)[cl_index],(*_cl_energy)[cl_index]);

	int tc_index0 = tc_map[(*_cl_cells)[cl_index][0]];
	int layer = _tc_HGClayer[tc_index0];
	layer_LV[layer] += clu_tlv;

	for(unsigned int i_tc=0;i_tc<(*_cl_cells)[cl_index].size();i_tc++){

	  int tc_index = tc_map[(*_cl_cells)[cl_index][i_tc]];
	  float e_tc = (*_tc_energy)[tc_index];
	  float eta_tc = (*_tc_eta)[tc_index];
	  float phi_tc = (*_tc_phi)[tc_index];
	  float r_tc = 1/abs(TMath::ASinH(eta_tc));
	  float z_tc = (*_tc_z)[tc_index];	

	  energy_eta_tc.emplace_back(std::make_pair(e_tc,eta_tc));
	  energy_phi_tc.emplace_back(std::make_pair(e_tc,phi_tc));
	  energy_r_tc.emplace_back(std::make_pair(e_tc,r_tc));
	  energy_z_tc.emplace_back(std::make_pair(e_tc,z_tc));

	  layer_energy_eta_tc[layer].emplace_back(std::make_pair(e_tc,eta_tc));
	  layer_energy_phi_tc[layer].emplace_back(std::make_pair(e_tc,phi_tc));
	  layer_energy_r_tc[layer].emplace_back(std::make_pair(e_tc,r_tc));

	}

      }

      float cl3d_See_tot = sigmaXX(energy_eta_tc,(*_cl3d_eta)[i_cl3d]);
      float cl3d_Spp_tot = sigmaPhiPhi(energy_phi_tc,(*_cl3d_phi)[i_cl3d]);
      float cl3d_r_mean = meanX(energy_r_tc);
      float cl3d_Srr_tot = sigmaXX(energy_r_tc,cl3d_r_mean);
      float cl3d_z_mean = meanX(energy_z_tc);
      float cl3d_Szz_tot = sigmaXX(energy_z_tc,cl3d_z_mean);

      float cl3d_See_max = 0;
      float cl3d_Spp_max = 0;
      float cl3d_Srr_max = 0;
      float cl3d_See_max_layer = 0;
      float cl3d_Spp_max_layer = 0;
      float cl3d_Srr_max_layer = 0;
      float cl3d_See_quadsum = 0;
      float cl3d_Spp_quadsum = 0;
      float cl3d_Srr_quadsum = 0;
      float E_max_layer = 0;
      float E_tot = 0;

      int min_HGClayer = -1;

      for(auto& layer_iter : layer_LV){
	
	TLorentzVector LV = layer_iter.second;
	int layer = layer_iter.first;
	float See_layer = sigmaXX(layer_energy_eta_tc[layer],LV.Eta());
	float Spp_layer = sigmaPhiPhi(layer_energy_phi_tc[layer],LV.Phi());
	float r_mean_layer = meanX(layer_energy_r_tc[layer]);
	float Srr_layer = sigmaXX(layer_energy_r_tc[layer],r_mean_layer);

	if(min_HGClayer<0 || layer<min_HGClayer) min_HGClayer = layer;
	if(See_layer>cl3d_See_max) cl3d_See_max = See_layer;
	if(Spp_layer>cl3d_Spp_max) cl3d_Spp_max = Spp_layer;
	if(Srr_layer>cl3d_Srr_max) cl3d_Srr_max = See_layer;
	if(LV.E()>E_max_layer){
	  E_max_layer = LV.E();
	  cl3d_See_max_layer = See_layer;
	  cl3d_Spp_max_layer = Spp_layer;
	  cl3d_Srr_max_layer = Srr_layer;
	}
	
	cl3d_See_quadsum += LV.E()*pow(See_layer,2);
	cl3d_Spp_quadsum += LV.E()*pow(Spp_layer,2);
	cl3d_Srr_quadsum += LV.E()*pow(Srr_layer,2);
	E_tot += LV.E();

      }      

      _cl3d_seetot_new.emplace_back(cl3d_See_tot);
      _cl3d_spptot_new.emplace_back(cl3d_Spp_tot);
      _cl3d_srrtot_new.emplace_back(cl3d_Srr_tot);
      _cl3d_seemax_new.emplace_back(cl3d_See_max);
      _cl3d_sppmax_new.emplace_back(cl3d_Spp_max);
      _cl3d_srrmax_new.emplace_back(cl3d_Srr_max);
      _cl3d_seemax_layer_new.emplace_back(cl3d_See_max_layer);
      _cl3d_sppmax_layer_new.emplace_back(cl3d_Spp_max_layer);
      _cl3d_srrmax_layer_new.emplace_back(cl3d_Srr_max_layer);
      _cl3d_see_quadsum_new.emplace_back(cl3d_See_quadsum/E_tot);
      _cl3d_spp_quadsum_new.emplace_back(cl3d_Spp_quadsum/E_tot);
      _cl3d_srr_quadsum_new.emplace_back(cl3d_Srr_quadsum/E_tot);
      _cl3d_szz_new.emplace_back(cl3d_Szz_tot);
      _cl3d_r_mean.emplace_back(cl3d_r_mean);
      _cl3d_z_mean.emplace_back(cl3d_z_mean);
      _cl3d_first_HGClayer.emplace_back(min_HGClayer);
      
    }

    //Jet shower-shape variables
    
    for(unsigned int i_jet=0; i_jet<_jets_n; i_jet++){

      std::vector<std::pair<float,float> > energy_eta_c3d;
      std::vector<std::pair<float,float> > energy_phi_c3d;
      std::vector<std::pair<float,float> > energy_r_c3d;
      std::vector<std::pair<float,float> > energy_firstlayer_c3d;
      std::vector<std::pair<float,float> > energy_Seetot_c3d;
      std::vector<std::pair<float,float> > energy_Spptot_c3d;
      std::vector<std::pair<float,float> > energy_Srrtot_c3d;
      std::vector<std::pair<float,float> > energy_Seemax_c3d;
      std::vector<std::pair<float,float> > energy_Sppmax_c3d;
      std::vector<std::pair<float,float> > energy_Srrmax_c3d;
      std::vector<std::pair<float,float> > energy_Szz_c3d;

      

      for(unsigned int i_cl3d=0; i_cl3d<(_jets_cl3d)[i_jet].size();i_cl3d++){

	  int cl3d_index = (_jets_cl3d)[i_jet][i_cl3d];
	  float e_c3d = (*_cl3d_energy)[cl3d_index];
	  float eta_c3d = (*_cl3d_eta)[cl3d_index];
	  float phi_c3d = (*_cl3d_phi)[cl3d_index];
	  float r_c3d = 1/abs(TMath::ASinH(eta_c3d));
	  int first_HGClayer_c3d = _cl3d_first_HGClayer[cl3d_index];
	  float Seetot_c3d = _cl3d_seetot_new[i_cl3d];
	  float Spptot_c3d = _cl3d_spptot_new[i_cl3d];
	  float Srrtot_c3d = _cl3d_srrtot_new[i_cl3d];
	  float Seemax_c3d = _cl3d_seemax_new[i_cl3d];
	  float Sppmax_c3d = _cl3d_sppmax_new[i_cl3d];
	  float Srrmax_c3d = _cl3d_srrmax_new[i_cl3d];
	  float Szz_c3d = _cl3d_szz_new[i_cl3d];

	  energy_eta_c3d.emplace_back(std::make_pair(e_c3d,eta_c3d));
	  energy_phi_c3d.emplace_back(std::make_pair(e_c3d,phi_c3d));
	  energy_r_c3d.emplace_back(std::make_pair(e_c3d,r_c3d));	  
	  energy_firstlayer_c3d.emplace_back(std::make_pair(e_c3d,first_HGClayer_c3d));
	  energy_Seetot_c3d.emplace_back(std::make_pair(e_c3d,Seetot_c3d));
	  energy_Spptot_c3d.emplace_back(std::make_pair(e_c3d,Spptot_c3d));
	  energy_Srrtot_c3d.emplace_back(std::make_pair(e_c3d,Srrtot_c3d));
	  energy_Seemax_c3d.emplace_back(std::make_pair(e_c3d,Seemax_c3d));
	  energy_Sppmax_c3d.emplace_back(std::make_pair(e_c3d,Sppmax_c3d));
	  energy_Srrmax_c3d.emplace_back(std::make_pair(e_c3d,Srrmax_c3d));
	  energy_Szz_c3d.emplace_back(std::make_pair(e_c3d,Szz_c3d));
					 

      }



      float jet_See_tot = sigmaXX(energy_eta_c3d,(*_jets_eta)[i_jet]);
      float jet_Spp_tot = sigmaXX(energy_phi_c3d,(*_jets_phi)[i_jet]);
      float jet_Srr_tot = sigmaXX(energy_r_c3d,1/abs(TMath::ASinH((*_jets_eta)[i_jet])));

      float jet_Seetot_c3d = meanX(energy_Seetot_c3d);
      float jet_Spptot_c3d = meanX(energy_Spptot_c3d);
      float jet_Srrtot_c3d = meanX(energy_Srrtot_c3d);
      float jet_Seemax_c3d = meanX(energy_Seemax_c3d);
      float jet_Sppmax_c3d = meanX(energy_Sppmax_c3d);
      float jet_Srrmax_c3d = meanX(energy_Srrmax_c3d);
      float jet_Szz_c3d = meanX(energy_Szz_c3d);
      float jet_firstlayer_avg = meanX(energy_firstlayer_c3d);
      float jet_See_quadsum_c3d = pow(sigmaXX(energy_Seetot_c3d,0),2);
      float jet_Spp_quadsum_c3d = pow(sigmaXX(energy_Spptot_c3d,0),2);
      float jet_Srr_quadsum_c3d = pow(sigmaXX(energy_Srrtot_c3d,0),2);

      _jets_seetot.push_back(jet_See_tot);
      _jets_spptot.push_back(jet_Spp_tot);
      _jets_srrtot.push_back(jet_Srr_tot);
      _jets_seetot_cl3d.push_back(jet_Seetot_c3d);
      _jets_spptot_cl3d.push_back(jet_Spptot_c3d);
      _jets_srrtot_cl3d.push_back(jet_Srrtot_c3d);
      _jets_seemax_cl3d.push_back(jet_Seemax_c3d);
      _jets_sppmax_cl3d.push_back(jet_Sppmax_c3d);
      _jets_srrmax_cl3d.push_back(jet_Srrmax_c3d);    
      _jets_see_quadsum_cl3d.push_back(jet_See_quadsum_c3d);
      _jets_spp_quadsum_cl3d.push_back(jet_Spp_quadsum_c3d);
      _jets_srr_quadsum_cl3d.push_back(jet_Srr_quadsum_c3d);
      _jets_szz_cl3d.push_back(jet_Szz_c3d);
      _jets_firstlayer_avg.push_back(jet_firstlayer_avg);

    }
     

    tree_new->Fill();
    tree_new2->Fill();
  }

  tree_new->Write();
  tree_new2->Write();
  f_new->Close();
  return;


}



void test(){

  TString filein="/eos/user/k/klute/Nero/HGC930pre2_BH/QCD_Pt15To7000/911p1_NoPU/ntuple_0.root";
  TString treename="hgcalTriggerNtuplizer/HGCalTriggerNtuple";
  TString filein_jet="/afs/cern.ch/work/t/tstreble/private/FastJet_HGC/HGCTPGPerformance/qcd_flat_nopu.root";
  TString treename_jet="jets";
  TString fileout="test_jet.root";

  add_jet( filein, treename, filein_jet, treename_jet, fileout);


}
