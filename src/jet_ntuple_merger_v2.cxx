#include "jet_ntuple_merger_v2.h"

jet_ntuple_merger_v2::jet_ntuple_merger_v2(){

}

int jet_ntuple_merger_v2::HGC_layer(const uint32_t subdet, const uint32_t layer) {

  int hgclayer = -1;
  if(subdet==3) hgclayer=layer;//EE
  else if(subdet==4) hgclayer=layer+28;//FH
  else if(subdet==5) hgclayer=layer+40;//BH

  return hgclayer;

}


//Compute energy-weighted mean of any variable X in the cluster

float jet_ntuple_merger_v2::meanX(const std::vector<std::pair<float,float> >& energy_X_tc) {

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

float jet_ntuple_merger_v2::sigmaXX(const std::vector<std::pair<float,float> >& energy_X_tc, const float X_cluster) {

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

float jet_ntuple_merger_v2::sigmaPhiPhi(const std::vector<std::pair<float,float> >& energy_phi_tc, const float phi_cluster) {

  float Etot = 0;
  float deltaphi2_sum = 0;

  for(const auto& energy_phi : energy_phi_tc){

    deltaphi2_sum += energy_phi.first * pow(helper.deltaPhi(energy_phi.second,phi_cluster),2);
    Etot += energy_phi.first;

  }

  float phi_MSE = 0;
  if (Etot>0) phi_MSE=deltaphi2_sum/Etot;
  float Spp=sqrt(phi_MSE);
  return Spp;

}

void jet_ntuple_merger_v2::add_jet(TString filein,  TString treename, TString filein_jet, TString treename_jet, TString fileout){

  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    std::cout<<fileout<<" already exists, please delete it before converting again"<<std::endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");

  TChain * tree = new TChain(treename);
  tree->Add(filein);
  Long64_t nentries = tree->GetEntries();
  std::cout<<"nentries="<<nentries<<std::endl;

  TChain * tree_jet = new TChain(treename_jet);
  tree_jet->Add(filein_jet);
  Long64_t nentries2 = tree_jet->GetEntries();
  if(nentries!=nentries2){
    std::cout<<"Inconsistent number of entries in two input files"<<std::endl;
    //return;
  }

  
  int _tc_n;
  int _cl_n;
  int _cl3d_n;

  std::vector<float> *_tc_eta;
  std::vector<float> *_tc_phi;
  std::vector<float> *_tc_energy;
  std::vector<float> *_tc_z;
  std::vector<int> *_tc_layer;
  std::vector<int> *_tc_subdet;
  std::vector<unsigned int> *_tc_id;
  
  std::vector<float> *_cl_pt;
  std::vector<float> *_cl_mipPt;
  std::vector<float> *_cl_eta;
  std::vector<float> *_cl_phi;
  std::vector<float> *_cl_energy;
  std::vector<unsigned int> *_cl_id;

  std::vector<float> *_cl3d_pt;
  std::vector<float> *_cl3d_eta;
  std::vector<float> *_cl3d_phi;
  std::vector<float> *_cl3d_energy;
  std::vector<unsigned int> *_cl3d_id;
  std::vector<int> *_cl3d_firstlayer;

  std::vector<float> *_jets_pt;
  std::vector<float> *_jets_eta;
  std::vector<float> *_jets_phi;
  std::vector<float> *_jets_energy;

  std::vector<std::vector<float> > *_jets_C3d_pt;
  std::vector<std::vector<float> > *_jets_C3d_eta;
  std::vector<std::vector<float> > *_jets_C3d_phi;
  std::vector<std::vector<float> > *_jets_C3d_energy;

  std::vector<std::vector<unsigned int> > *_cl_cells_id;
  std::vector<std::vector<unsigned int> > *_cl3d_clusters_id;

  std::vector<int> *_gen_id;
  std::vector<int> *_gen_status;
  std::vector<float> *_gen_pt;
  std::vector<float> *_gen_eta;
  std::vector<float> *_gen_phi;
  std::vector<float> *_gen_energy;
  
  std::vector<float> *_genjet_pt;
  std::vector<float> *_genjet_eta;
  std::vector<float> *_genjet_phi;
  std::vector<float> *_genjet_energy;

  std::vector<float> *_gentau_vis_pt;
  std::vector<float> *_gentau_vis_eta;
  std::vector<float> *_gentau_vis_phi;
  std::vector<float> *_gentau_vis_energy;
      
  tree->SetBranchAddress("tc_n",     &_tc_n);
  tree->SetBranchAddress("cl_n",     &_cl_n);
  tree->SetBranchAddress("cl3d_n",   &_cl3d_n);
  
  tree->SetBranchAddress("tc_eta",    &_tc_eta);
  tree->SetBranchAddress("tc_phi",    &_tc_phi);
  tree->SetBranchAddress("tc_energy", &_tc_energy);
  tree->SetBranchAddress("tc_z",      &_tc_z);
  tree->SetBranchAddress("tc_layer",  &_tc_layer);
  tree->SetBranchAddress("tc_subdet", &_tc_subdet);
  tree->SetBranchAddress("tc_id",     &_tc_id);

  tree->SetBranchAddress("cl_pt",     &_cl_pt);
  tree->SetBranchAddress("cl_mipPt",  &_cl_mipPt);
  tree->SetBranchAddress("cl_eta",    &_cl_eta);
  tree->SetBranchAddress("cl_phi",    &_cl_phi);
  tree->SetBranchAddress("cl_energy", &_cl_energy);
  tree->SetBranchAddress("cl_id",     &_cl_id);

  tree->SetBranchAddress("cl3d_pt",     &_cl3d_pt);
  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);
  tree->SetBranchAddress("cl3d_id",     &_cl3d_id);
  tree->SetBranchAddress("cl3d_firstlayer",    &_cl3d_firstlayer);

  tree->SetBranchAddress("cl_cells_id",        &_cl_cells_id);
  tree->SetBranchAddress("cl3d_clusters_id",   &_cl3d_clusters_id);

  tree_jet->SetBranchAddress("jets_pt",     &_jets_pt);
  tree_jet->SetBranchAddress("jets_eta",    &_jets_eta);
  tree_jet->SetBranchAddress("jets_phi",    &_jets_phi);
  tree_jet->SetBranchAddress("jets_energy", &_jets_energy);

  tree_jet->SetBranchAddress("jets_C3d_pt",     &_jets_C3d_pt);
  tree_jet->SetBranchAddress("jets_C3d_eta",    &_jets_C3d_eta);
  tree_jet->SetBranchAddress("jets_C3d_phi",    &_jets_C3d_phi);
  tree_jet->SetBranchAddress("jets_C3d_energy", &_jets_C3d_energy);

  //tree->SetBranchAddress("gen_id",     &_gen_id);
  tree->SetBranchAddress("gen_pdgid",     &_gen_id);
  tree->SetBranchAddress("gen_status", &_gen_status);
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_phi",    &_gen_phi);
  tree->SetBranchAddress("gen_energy", &_gen_energy);
      
  tree->SetBranchAddress("genjet_pt",     &_genjet_pt);
  tree->SetBranchAddress("genjet_eta",    &_genjet_eta);
  tree->SetBranchAddress("genjet_phi",    &_genjet_phi);
  tree->SetBranchAddress("genjet_energy", &_genjet_energy);

  tree->SetBranchAddress("gentau_vis_pt",     &_gentau_vis_pt);
  tree->SetBranchAddress("gentau_vis_eta",    &_gentau_vis_eta);
  tree->SetBranchAddress("gentau_vis_phi",    &_gentau_vis_phi);
  tree->SetBranchAddress("gentau_vis_energy", &_gentau_vis_energy);

  TTree* tree_new = new TTree("HGCalTriggerNtupleJet","HGCalTriggerNtupleJet");
  tree_new->AddFriend(treename,filein);
  TString filejet_friend = "/vols/cms/snwebb/HGC_ntuples/" + filein_jet(29,filein_jet.Length());
  tree_new->AddFriend(treename_jet,filejet_friend);

  
  //New branches
  std::vector<int> _tc_HGClayer;
  std::vector<int> _cl_HGClayer;

  std::vector<int> _tc_cl;
  std::vector<int> _tc_cl3d;
  std::vector<int> _cl_cl3d;  
  std::vector<int> _tc_jet; //index of jet in which tc included
  std::vector<int> _cl_jet; //index of jet in which cl included
  std::vector<int> _cl3d_jet; //index of jet in which cl3d included

  std::vector<std::vector<int> > _cl_cells;
  std::vector<std::vector<int> > _cl3d_clusters;

  int _jets_n;
  std::vector<int> _jets_ncl3d;
  std::vector<std::vector<int> > _jets_cl3d; // list of cl3d included in jet
  std::vector<std::vector<unsigned int> > _jets_cl3d_id;

  std::vector<float> _cl3d_r_mean;
  std::vector<float> _cl3d_z_mean;
  std::vector<std::vector<float> > _layer_cl3d_energy_fraction; //layer_cl3d_energy_fraction[i][j] = fraction of cl3d j energy included up to layer i
  std::vector<float> _cl3d_Fisher_jet;
  std::vector<float> _cl3d_Fisher_cl3d;

  std::vector<float> _jets_mipPt;
  std::vector<float> _jets_seetot;
  std::vector<float> _jets_spptot;
  std::vector<float> _jets_srrtot;
  std::vector<float> _jets_firstlayer_avg;
  std::vector<std::vector<float> > _layer_jets_energy_fraction; //layer_jets_energy_fraction[i][j] = fraction of jet j energy included up to layer i
  std::vector<float> _jets_Fisher_VBF;

  std::vector<float> _jets_PU_subtr_cone_C3D;
  std::vector<float> _jets_PU_subtr_cone_tc;
  std::vector<float> _jets_PU_subtr_cone_GEO_C3D;

  bool _isVBF;
  std::vector<int> _VBF_parton_gen;
  std::vector<int> _VBF_parton_genjet;
  std::vector<int> _VBF_parton_jets;

  std::vector<int> _gentau_jets;

  std::vector<float> _jets_clean_pt;
  std::vector<float> _jets_clean_eta;
  std::vector<float> _jets_clean_phi;
  std::vector<float> _jets_clean_energy;


  tree_new->Branch("tc_HGClayer",     &_tc_HGClayer);
  tree_new->Branch("cl_HGClayer",     &_cl_HGClayer);

  tree_new->Branch("tc_cl",     &_tc_cl);
  tree_new->Branch("tc_cl3d",   &_tc_cl3d);
  tree_new->Branch("cl_cl3d",   &_cl_cl3d);

  tree_new->Branch("tc_jet",    &_tc_jet);
  tree_new->Branch("cl_jet",    &_cl_jet);
  tree_new->Branch("cl3d_jet",  &_cl3d_jet);

  tree_new->Branch("cl_cells",    &_cl_cells);
  tree_new->Branch("cl3d_clusters",    &_cl3d_clusters);
 
  tree_new->Branch("jets_n",    &_jets_n,   "jets_n/I");
  tree_new->Branch("jets_ncl3d", &_jets_ncl3d);
  tree_new->Branch("jets_cl3d", &_jets_cl3d);
  tree_new->Branch("jets_cl3d_id", &_jets_cl3d_id);

  tree_new->Branch("cl3d_r_mean",     &_cl3d_r_mean);
  tree_new->Branch("cl3d_z_mean",     &_cl3d_z_mean);
  tree_new->Branch("layer_cl3d_energy_fraction", &_layer_cl3d_energy_fraction);
  tree_new->Branch("cl3d_Fisher_jet", &_cl3d_Fisher_jet);
  tree_new->Branch("cl3d_Fisher_cl3d", &_cl3d_Fisher_cl3d);


  tree_new->Branch("jets_mipPt", &_jets_mipPt);
  tree_new->Branch("jets_seetot", &_jets_seetot);
  tree_new->Branch("jets_spptot", &_jets_spptot);
  tree_new->Branch("jets_srrtot", &_jets_srrtot);
  tree_new->Branch("jets_firstlayer_avg", &_jets_firstlayer_avg);
  tree_new->Branch("layer_jets_energy_fraction", &_layer_jets_energy_fraction);
  tree_new->Branch("jets_Fisher_VBF", &_jets_Fisher_VBF);

  tree_new->Branch("jets_PU_subtr_cone_C3D", &_jets_PU_subtr_cone_C3D);
  tree_new->Branch("jets_PU_subtr_cone_tc", &_jets_PU_subtr_cone_tc);
  tree_new->Branch("jets_PU_subtr_cone_GEO_C3D", &_jets_PU_subtr_cone_GEO_C3D);

  tree_new->Branch("isVBF", &_isVBF, "isVBF/O");
  tree_new->Branch("VBF_parton_gen", &_VBF_parton_gen);
  tree_new->Branch("VBF_parton_genjet", &_VBF_parton_genjet);
  tree_new->Branch("VBF_parton_jets", &_VBF_parton_jets);

  tree_new->Branch("gentau_jets", &_gentau_jets);

  tree_new->Branch("jets_clean_pt", &_jets_clean_pt);
  tree_new->Branch("jets_clean_eta", &_jets_clean_eta);
  tree_new->Branch("jets_clean_phi", &_jets_clean_phi);
  tree_new->Branch("jets_clean_energy", &_jets_clean_energy);
 

  TFile* f_PU_cone_eta = TFile::Open("PU_cone_vs_eta.root");
  TProfile* prof_cone_tc = (TProfile*)f_PU_cone_eta->Get("prof_cone_tc");
  TProfile* prof_cone_C3D = (TProfile*)f_PU_cone_eta->Get("prof_cone_C3D");
  prof_cone_tc->SetDirectory(0);
  prof_cone_C3D->SetDirectory(0);
  f_PU_cone_eta->Close();

  TFile* f_PU_cone_eta_GEO = TFile::Open("PU_cone_vs_eta_C2D_dR.root");
  TProfile* prof_cone_GEO_C3D = (TProfile*)f_PU_cone_eta_GEO->Get("prof_cone_C3D");
  prof_cone_GEO_C3D->SetDirectory(0);
  f_PU_cone_eta_GEO->Close();

  int N = std::min(nentries,nentries2);
  for(int i=0;i<N;i++){

    if(i%1000==0)
      std::cout<<"i="<<i<<std::endl;
    
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
    _cl_mipPt = 0;
    _cl_eta = 0;
    _cl_phi = 0;
    _cl_energy = 0;
    _cl_id = 0;

    _cl3d_pt = 0;
    _cl3d_eta = 0;
    _cl3d_phi = 0;
    _cl3d_energy = 0;
    _cl3d_id = 0;
    _cl3d_firstlayer = 0;

    _cl_cells_id = 0;
    _cl3d_clusters_id = 0;

    _jets_pt = 0;
    _jets_eta = 0;
    _jets_phi = 0;
    _jets_energy = 0;  
    
    _jets_C3d_pt = 0;
    _jets_C3d_eta = 0;
    _jets_C3d_phi = 0;
    _jets_C3d_energy = 0; 

    _gen_id = 0;
    _gen_status = 0;
    _gen_pt = 0;
    _gen_eta = 0;
    _gen_phi = 0;
    _gen_energy = 0;
    
    _genjet_pt = 0;
    _genjet_eta = 0;
    _genjet_phi = 0;
    _genjet_energy = 0;

    _gentau_vis_pt = 0;
    _gentau_vis_eta = 0;
    _gentau_vis_phi = 0;
    _gentau_vis_energy = 0;
    
    _jets_n = 0;
    _tc_HGClayer.clear();
    _cl_HGClayer.clear();

    _tc_cl.clear();
    _tc_cl3d.clear();
    _cl_cl3d.clear();  

    _tc_jet.clear();
    _cl_jet.clear();
    _cl3d_jet.clear();

    _cl_cells.clear();
    _cl3d_clusters.clear();

    _jets_ncl3d.clear();
    _jets_cl3d.clear();
    _jets_cl3d_id.clear();

    _cl3d_r_mean.clear();
    _cl3d_z_mean.clear();
    _layer_cl3d_energy_fraction.clear();    
    _cl3d_Fisher_jet.clear();
    _cl3d_Fisher_cl3d.clear();
    

    _jets_mipPt.clear();
    _jets_seetot.clear();
    _jets_spptot.clear();
    _jets_srrtot.clear();
    _jets_firstlayer_avg.clear();
    _layer_jets_energy_fraction.clear();
    _jets_Fisher_VBF.clear();

    _jets_PU_subtr_cone_C3D.clear();   
    _jets_PU_subtr_cone_tc.clear();   
    _jets_PU_subtr_cone_GEO_C3D.clear(); 

    _VBF_parton_gen.clear();
    _VBF_parton_genjet.clear();
    _VBF_parton_jets.clear();

    _gentau_jets.clear();

    _jets_clean_pt.clear();
    _jets_clean_eta.clear();
    _jets_clean_phi.clear();
    _jets_clean_energy.clear();  

    
    tree->GetEntry(i);
    tree_jet->GetEntry(i);

    _jets_n = (*_jets_C3d_pt).size();   
  
    std::map<unsigned int, unsigned int> tc_map; //First ID, Second index
    std::map<unsigned int, unsigned int> cl_map; //First ID, Second index
    std::map<unsigned int, unsigned int> cl3d_map; //First ID, Second index

    for(int i_tc=0; i_tc<_tc_n; i_tc++){      

      int HGClayer = HGC_layer( (*_tc_subdet)[i_tc], (*_tc_layer)[i_tc] );
      _tc_HGClayer.emplace_back(HGClayer);          
      tc_map[(*_tc_id)[i_tc]] = i_tc;

    }

    for(unsigned int i_cl=0; i_cl<(*_cl_cells_id).size(); i_cl++){

      int tc_index = tc_map[(*_cl_cells_id)[i_cl][0]];
      int HGClayer = HGC_layer( (*_tc_subdet)[tc_index], (*_tc_layer)[tc_index] );
      _cl_HGClayer.emplace_back(HGClayer);
      cl_map[(*_cl_id)[i_cl]] = i_cl;
 
    }

    for(unsigned int i_c3d=0; i_c3d<(*_cl3d_clusters_id).size(); i_c3d++){

      cl3d_map[(*_cl3d_id)[i_c3d]] = i_c3d;

    }    


    _cl_cells.resize((*_cl_cells_id).size());
    for(unsigned int i_cl=0; i_cl<(*_cl_cells_id).size(); i_cl++){
      for(unsigned int i_tc=0; i_tc<(*_cl_cells_id)[i_cl].size(); i_tc++){
	_cl_cells[i_cl].push_back(tc_map[(*_cl_cells_id)[i_cl][i_tc]]);
      }
    }

    _cl3d_clusters.resize((*_cl3d_clusters_id).size());
    for(unsigned int i_cl3d=0; i_cl3d<(*_cl3d_clusters_id).size(); i_cl3d++){
      for(unsigned int i_cl=0; i_cl<(*_cl3d_clusters_id)[i_cl3d].size(); i_cl++){
	_cl3d_clusters[i_cl3d].push_back(cl_map[(*_cl3d_clusters_id)[i_cl3d][i_cl]]);
      }
    }

    _jets_cl3d_id.resize((*_jets_C3d_pt).size());
    _jets_cl3d.resize((*_jets_C3d_pt).size());
    for(unsigned int i_jet=0; i_jet<(*_jets_C3d_pt).size(); i_jet++){

      std::vector<int> cl3d_currentjet;
      std::vector<int> cl3d_id_currentjet;

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

	_jets_cl3d[i_jet].emplace_back(i_cl3d_matched);
	_jets_cl3d_id[i_jet].emplace_back((*_cl3d_id)[i_cl3d_matched]);

      }

  
      _jets_ncl3d.emplace_back(_jets_cl3d[i_jet].size());

    }    


    //Cross-reference of objects

    _tc_cl.resize(_tc_n,-1);
    for(unsigned int i_cl=0; i_cl<(_cl_cells).size(); i_cl++){
      for(unsigned int i_tc=0; i_tc<(_cl_cells)[i_cl].size(); i_tc++){

	int tc_index = (_cl_cells)[i_cl][i_tc];	
	_tc_cl[tc_index] = i_cl;    
	
      }
    }
              
    _tc_cl3d.resize(_tc_n,-1);
    _cl_cl3d.resize(_cl_n,-1);
    for(unsigned int i_cl3d=0; i_cl3d<(_cl3d_clusters).size(); i_cl3d++){      
      for(unsigned int i_cl=0; i_cl<(_cl3d_clusters)[i_cl3d].size(); i_cl++){

	int cl_index = (_cl3d_clusters)[i_cl3d][i_cl];
	_cl_cl3d[cl_index] = i_cl3d;
	
	for(unsigned int i_tc=0; i_tc<(_cl_cells)[cl_index].size(); i_tc++){

	  int tc_index = (_cl_cells)[cl_index][i_tc];
	  _tc_cl3d[tc_index] = i_cl3d;    

	}

      }
    }

    _tc_jet.resize(_tc_n,-1);
    _cl_jet.resize(_cl_n,-1);
    _cl3d_jet.resize(_cl3d_n,-1);
    for(unsigned int i_jet=0; i_jet<(_jets_cl3d).size(); i_jet++){

      for(unsigned int i_cl3d=0; i_cl3d<(_jets_cl3d)[i_jet].size(); i_cl3d++){

	int cl3d_index = (_jets_cl3d)[i_jet][i_cl3d];	
	_cl3d_jet[cl3d_index] = i_jet;

	for(unsigned int i_cl=0; i_cl<(_cl3d_clusters)[cl3d_index].size(); i_cl++){
	  int cl_index = (_cl3d_clusters)[cl3d_index][i_cl];
	  _cl_jet[cl_index] = i_jet;

	  for(unsigned int i_tc=0; i_tc<(_cl_cells)[cl_index].size(); i_tc++){
	    int tc_index = (_cl_cells)[cl_index][i_tc];
	    _tc_jet[tc_index] = i_jet;	  
	  }

	}

      }

    }
  


    //Clusters shower-shape variables

    for(unsigned int i_cl3d=0; i_cl3d<(_cl3d_clusters).size();i_cl3d++){

      std::vector<std::pair<float,float> > energy_r_tc;
      std::vector<std::pair<float,float> > energy_z_tc;


      for(unsigned int i_cl=0; i_cl<(_cl3d_clusters)[i_cl3d].size();i_cl++){

	int cl_index = (_cl3d_clusters)[i_cl3d][i_cl];

	for(unsigned int i_tc=0;i_tc<(_cl_cells)[cl_index].size();i_tc++){

	  int tc_index = (_cl_cells)[cl_index][i_tc];
	  float e_tc = (*_tc_energy)[tc_index];
	  float eta_tc = (*_tc_eta)[tc_index];
	  float r_tc = 1/abs(TMath::ASinH(eta_tc));
	  float z_tc = (*_tc_z)[tc_index];	

	  energy_r_tc.emplace_back(std::make_pair(e_tc,r_tc));
	  energy_z_tc.emplace_back(std::make_pair(e_tc,z_tc));

	}

      }


      float cl3d_r_mean = meanX(energy_r_tc);
      float cl3d_z_mean = meanX(energy_z_tc);       

      _cl3d_r_mean.emplace_back(cl3d_r_mean);
      _cl3d_z_mean.emplace_back(cl3d_z_mean);

      std::map<int, float> layer_mipPt;
      float tot_mipPt = 0.;

      _layer_cl3d_energy_fraction.resize(53);
      
      for(unsigned int i_cl=0; i_cl<(_cl3d_clusters)[i_cl3d].size(); i_cl++){
	int cl_index = (_cl3d_clusters)[i_cl3d][i_cl];
	layer_mipPt[_cl_HGClayer[cl_index]] += (*_cl_mipPt)[cl_index];
	tot_mipPt += (*_cl_mipPt)[cl_index];
      }

      _layer_cl3d_energy_fraction[0].push_back({0});

      for(unsigned int i_layer=1;i_layer<53;i_layer++){

	float fraction = _layer_cl3d_energy_fraction[i_layer-1].back() + layer_mipPt[i_layer]/tot_mipPt;
	_layer_cl3d_energy_fraction[i_layer].push_back(fraction);
      }


      float Fisher_jet = 0;
      float Fisher_cl3d = 0;

      for(unsigned int k=0; k<26; k++){
	int k_layer = -1;
	if(k<14) k_layer = 2*k+1;
	else k_layer = k+15;	
	Fisher_jet+=weights_Fisher[k]*layer_mipPt[k_layer]/tot_mipPt;
	Fisher_cl3d-=weights_Fisher_c3d[k]*layer_mipPt[k_layer]/tot_mipPt; //Weights are all negative	
      }

      _cl3d_Fisher_jet.push_back(Fisher_jet);
      _cl3d_Fisher_cl3d.push_back(Fisher_cl3d);
      
    }

  
    //Jet shower-shape variables
    _layer_jets_energy_fraction.resize(53);


    for(int i_jet=0; i_jet<_jets_n; i_jet++){

      std::vector<std::pair<float,float> > energy_eta_c3d;
      std::vector<std::pair<float,float> > energy_phi_c3d;
      std::vector<std::pair<float,float> > energy_r_c3d;
      std::vector<std::pair<float,float> > energy_firstlayer_c3d;

      std::map<int, float> layer_mipPt;
      float tot_mipPt = 0.;

      TLorentzVector clean_jet;
      
      for(unsigned int i_cl3d=0; i_cl3d<(_jets_cl3d)[i_jet].size();i_cl3d++){

	  int cl3d_index = (_jets_cl3d)[i_jet][i_cl3d];
	  float e_c3d = (*_cl3d_energy)[cl3d_index];
	  float eta_c3d = (*_cl3d_eta)[cl3d_index];
	  float phi_c3d = (*_cl3d_phi)[cl3d_index];
	  float r_c3d = 1/abs(TMath::ASinH(eta_c3d));
	  int first_HGClayer_c3d = (*_cl3d_firstlayer)[cl3d_index];

	  energy_eta_c3d.emplace_back(std::make_pair(e_c3d,eta_c3d));
	  energy_phi_c3d.emplace_back(std::make_pair(e_c3d,phi_c3d));
	  energy_r_c3d.emplace_back(std::make_pair(e_c3d,r_c3d));	  
	  energy_firstlayer_c3d.emplace_back(std::make_pair(e_c3d,first_HGClayer_c3d));	

	  for(unsigned int i_cl=0; i_cl<(_cl3d_clusters)[cl3d_index].size(); i_cl++){

	    int cl_index = (_cl3d_clusters)[cl3d_index][i_cl];
	    layer_mipPt[_cl_HGClayer[cl_index]] += (*_cl_mipPt)[cl_index];
	    tot_mipPt += (*_cl_mipPt)[cl_index];

	  }
		
	  float fraction_layer5 = (_layer_cl3d_energy_fraction)[5][cl3d_index];
	  //if(fraction_layer5<0.2){
	  if(fraction_layer5<(-8.24148e-02*abs((*_cl3d_eta)[cl3d_index])+3.67900e-01)){
	    TLorentzVector C3D;
	    C3D.SetPtEtaPhiE((*_cl3d_pt)[cl3d_index],(*_cl3d_eta)[cl3d_index],(*_cl3d_phi)[cl3d_index],(*_cl3d_energy)[cl3d_index]);
	    clean_jet+=C3D;
	  }
	  
      }


      float jet_See_tot = sigmaXX(energy_eta_c3d,(*_jets_eta)[i_jet]);
      float jet_Spp_tot = sigmaXX(energy_phi_c3d,(*_jets_phi)[i_jet]);
      float jet_Srr_tot = sigmaXX(energy_r_c3d,1/abs(TMath::ASinH((*_jets_eta)[i_jet])));
      float jet_firstlayer_avg = meanX(energy_firstlayer_c3d);

      _jets_mipPt.push_back(tot_mipPt);
      _jets_seetot.push_back(jet_See_tot);
      _jets_spptot.push_back(jet_Spp_tot);
      _jets_srrtot.push_back(jet_Srr_tot);   
      _jets_firstlayer_avg.push_back(jet_firstlayer_avg);

      _layer_jets_energy_fraction[0].push_back({0});

      for(unsigned int i_layer=1;i_layer<53;i_layer++){

	float fraction = _layer_jets_energy_fraction[i_layer-1].back() + layer_mipPt[i_layer]/tot_mipPt;
	_layer_jets_energy_fraction[i_layer].push_back(fraction);
      }
      
      int i_bin = prof_cone_tc->FindBin(fabs((*_jets_eta)[i_jet]));
      _jets_PU_subtr_cone_C3D.emplace_back(prof_cone_C3D->GetBinContent(i_bin));      
      _jets_PU_subtr_cone_tc.emplace_back(prof_cone_tc->GetBinContent(i_bin));
      _jets_PU_subtr_cone_GEO_C3D.emplace_back(prof_cone_GEO_C3D->GetBinContent(i_bin));        

      _jets_clean_pt.push_back(clean_jet.Pt());
      _jets_clean_eta.push_back(clean_jet.Eta());
      _jets_clean_phi.push_back(clean_jet.Phi());
      _jets_clean_energy.push_back(clean_jet.E());

      float Fisher = 0;

      for(unsigned int k=0; k<38; k++){
	int k_layer = -1;
	if(k<14) k_layer = 2*k+1;
	else k_layer = k+15;	
	Fisher+=weights_Fisher[k]*layer_mipPt[k_layer]/tot_mipPt;
      }

      _jets_Fisher_VBF.push_back(Fisher);      


    }
     

    _isVBF = true;

    for(unsigned int i_gen=0; i_gen<(*_gen_id).size(); i_gen++){
      if(abs((*_gen_id)[i_gen])==21 && (*_gen_status)[i_gen]==21) //Gluon splitting in initial partons
	_isVBF = false;
      if(abs((*_gen_id)[i_gen])<6 && (*_gen_status)[i_gen]==23)
	_VBF_parton_gen.emplace_back(i_gen);
    }

    for(unsigned int i_VBF=0; i_VBF<_VBF_parton_gen.size(); i_VBF++){

      TLorentzVector VBF_parton;
      int i_gen = _VBF_parton_gen[i_VBF];
      VBF_parton.SetPtEtaPhiE((*_gen_pt)[i_gen], (*_gen_eta)[i_gen], (*_gen_phi)[i_gen], (*_gen_energy)[i_gen]);     

      float dR_min = -1.;
      int i_VBF_genjet = -1;
      
      for(unsigned int i_genjet=0; i_genjet<(*_genjet_pt).size(); i_genjet++){
	TLorentzVector genjet;
	genjet.SetPtEtaPhiE((*_genjet_pt)[i_genjet],(*_genjet_eta)[i_genjet],(*_genjet_phi)[i_genjet],(*_genjet_energy)[i_genjet]);
	float dR = genjet.DeltaR(VBF_parton);
	if((dR_min<0 && dR<0.5) || dR<dR_min){
	  dR_min = dR;
	  i_VBF_genjet = i_genjet;
	}
      }
      
      _VBF_parton_genjet.emplace_back(i_VBF_genjet);
      TLorentzVector VBF_genjet;
      VBF_genjet.SetPtEtaPhiE((*_genjet_pt)[i_VBF_genjet],(*_genjet_eta)[i_VBF_genjet],(*_genjet_phi)[i_VBF_genjet],(*_genjet_energy)[i_VBF_genjet]);
      
      dR_min = -1.;
      int i_VBF_jet = -1;
      
      for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){
	TLorentzVector jet;
	jet.SetPtEtaPhiE((*_jets_pt)[i_jet],(*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_energy)[i_jet]);	
	float dR = jet.DeltaR(VBF_genjet);
	if((dR_min<0 && dR<0.5) || dR<dR_min){
	  dR_min = dR;
	  i_VBF_jet = i_jet;
	}
      }            					     
      
      _VBF_parton_jets.emplace_back(i_VBF_jet);
      
    }


    for(unsigned int i_gen=0; i_gen<(*_gentau_vis_pt).size(); i_gen++){

      TLorentzVector gentau;
      gentau.SetPtEtaPhiE((*_gentau_vis_pt)[i_gen], (*_gentau_vis_eta)[i_gen], (*_gentau_vis_phi)[i_gen], (*_gentau_vis_energy)[i_gen]);     

      float dR_min = -1.;
      int i_gentau_jet = -1;
      
      for(unsigned int i_jet=0; i_jet<(*_jets_pt).size(); i_jet++){
	TLorentzVector jet;
	jet.SetPtEtaPhiE((*_jets_pt)[i_jet],(*_jets_eta)[i_jet],(*_jets_phi)[i_jet],(*_jets_energy)[i_jet]);	
	float dR = jet.DeltaR(gentau);
	//if((dR_min<0 && dR<0.5) || dR<dR_min){
	if((dR_min<0 && dR<0.3) || dR<dR_min){
	  dR_min = dR;
	  i_gentau_jet = i_jet;
	}
      }            					     
      
      _gentau_jets.emplace_back(i_gentau_jet);
      
    }




    // Steps: Fill 2D histogram either with Trigger Cell or 2D clustering information
    // Find seeds using one of several methods
    // Form the 3D clusters using these seeds



    // //Find seeds (new implementation)

    // /* seeds determined with local maximum criteria */
    //  std::vector<std::vector<double> seedPositions;
    // std::vector<GlobalPoint> seedPositions;
    // Histogram histoCluster = fillHistoClusters(clustersPtrs); //key[0] = z.side(), key[1] = bin_R, key[2] = bin_phi, content = MIPTs summed along depth
    // seedPositions = computeMaxSeeds(histoCluster);
    










    

    tree_new->Fill();
  }

  f_new->cd();
  tree_new->Write();
  f_new->Close();
  return;


}



void jet_ntuple_merger_v2::test(){

  TString filein="root://cms-xrd-global.cern.ch//store/user/tstreble/VBF_HToInvisible_M125_14TeV_powheg_pythia8/VBF_Hinv_93X_PU0_dRC2D_JetPU0cal_18_01_08/180108_163440/0000/ntuple_12.root";
  TString treename="hgcalTriggerNtuplizer/HGCalTriggerNtuple";
  TString filein_jet="/data_CMS/cms/strebler/HGC/VBF_Hinv_PU0_C2D_dR_JetPU0cal/jet_ntuples/ntuple_jet_12.root";
  TString treename_jet="jets";
  TString fileout="test_jet.root";

  add_jet( filein, treename, filein_jet, treename_jet, fileout);


}

