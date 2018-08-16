#include <TProfile.h>
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


vector<float> w_CMSSW={ 0.01837f, 0.03056f, 0.01626f, 0.01439f, 0.01345f, 0.01858f, 0.02049f, 0.01690f, 0.02080f, 0.01680f, 0.02384f, 0.03011f, 0.02746f, 0.04687f, 0.07882f, 0.05558f, 0.06093f, 0.06108f, 0.06576f, 0.04657f, 0.06294f, 0.06101f, 0.05173f, 0.04929f, 0.06993f, 0.06735f, 0.11990f, 0.12533f, 0.14323f, 0.15329f, 0.10478f, 0.10934f, 0.16139f, 0.17466f, 0.10805f, 0.12167f, 0.11710f, 0.32805f };


vector<float> w_ele = { 0.0315296f, 0.0408293f, 0.0150209f, 0.0165825f, 0.0159977f, 0.0201057f, 0.0221555f, 0.0212066f, 0.0216312f, 0.0231152f, 0.0130021f, 0.0284077f, 0.0396848f, 0.0857259f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f };

vector<float> w_pi={ 0.0450490f, 0.0887811f, 0.0641374f, 0.0291493f, 0.0190718f, 0.0288119f, 0.0248522f, 0.0366860f, 0.0346548f, 0.0211779f, 0.0465951f, 0.0542372f, 0.0302660f, 0.0786376f, 0.111167f, 0.0981555f, 0.0789776f, 0.0793981f, 0.0930590f, 0.0744720f, 0.0751901f, 0.0966343f, 0.0754141f, 0.0667657f, 0.114315f, 0.0958396f, 0.164691f, 0.259054f, 0.185976f, 0.177570f, 0.193845f, 0.201758f, 0.252186f, 0.238876f, 0.240978f, 0.253122f, 0.223324f, 0.442479f };

vector<float> w_pi_0p03={ 0.04061f, 0.07529f, 0.06072f, 0.03183f, 0.01289f, 0.02675f, 0.02352f, 0.03314f, 0.03307f, 0.02171f, 0.04042f, 0.05145f, 0.03184f, 0.06969f, 0.10039f, 0.08870f, 0.07423f, 0.07795f, 0.07519f, 0.07958f, 0.07425f, 0.07630f, 0.08161f, 0.08090f, 0.07426f, 0.09975f, 0.16045f, 0.21663f, 0.17990f, 0.16721f, 0.18368f, 0.18779f, 0.21295f, 0.20231f, 0.22705f, 0.20772f, 0.18630f, 0.37267f };


  vector<float> w_ele_EE_pi_FHBH={ 0.0315296f, 0.0408293f, 0.0150209f, 0.0165825f, 0.0159977f, 0.0201057f, 0.0221555f, 0.0212066f, 0.0216312f, 0.0231152f, 0.0130021f, 0.0284077f, 0.0396848f, 0.0857259f, 0.128157f, 0.100178f, 0.0814956f, 0.0846578f, 0.0956920f, 0.0744095f, 0.0806987f, 0.0971122f, 0.0746902f, 0.0682125f, 0.121283f, 0.0964139f, 0.163284f, 0.260826f, 0.193073f, 0.176211f, 0.196318f, 0.203934f, 0.255920f, 0.242489f, 0.241993f, 0.268752f, 0.218642f, 0.454196f };

 vector<float> w_ele_EE_pi_FHBH2 = { 0.0315296f, 0.0408293f, 0.0150209f, 0.0165825f, 0.0159977f, 0.0201057f, 0.0221555f, 0.0212066f, 0.0216312f, 0.0231152f, 0.0130021f, 0.0284077f, 0.0396848f, 0.0857259f, 0.111167f, 0.0981555f, 0.0789776f, 0.0793981f, 0.0930590f, 0.0744720f, 0.0751901f, 0.0966343f, 0.0754141f, 0.0667657f, 0.114315f, 0.0958396f, 0.164691f, 0.259054f, 0.185976f, 0.177570f, 0.193845f, 0.201758f, 0.252186f, 0.238876f, 0.240978f, 0.253122f, 0.223324f, 0.442479f };

vector<float> w_ele_cl_max= { 0.02189f, 0.01972f, 0.01503f, 0.01451f, 0.01618f, 0.01760f, 0.01938f, 0.02087f, 0.02008f, 0.02191f, 0.02388f, 0.03111f, 0.02537f, 0.03411f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f };

 vector<float> w_pi_cl_max={ 0.04730f, 0.04611f, 0.03502f, 0.02446f, 0.01004f, 0.02006f, 0.02167f, 0.02523f, 0.02575f, 0.02451f, 0.03055f, 0.04021f, 0.02498f, 0.05625f, 0.08272f, 0.06352f, 0.05882f, 0.06604f, 0.05771f, 0.06576f, 0.05832f, 0.06158f, 0.06702f, 0.06298f, 0.05742f, 0.07674f, 0.14287f, 0.15466f, 0.15225f, 0.13660f, 0.13080f, 0.16656f, 0.14004f, 0.14848f, 0.18169f, 0.16826f, 0.15742f, 0.24095f };


vector<float> w_ele_EE_max= { 0.03173f, 0.04066f, 0.01491f, 0.01661f, 0.01604f, 0.02014f, 0.02216f, 0.02127f, 0.02162f, 0.02272f, 0.01266f, 0.02798f, 0.05063f, 0.05702f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f };

 vector<float> w_pi_EE_max={ 0.03414f, 0.07193f, 0.05372f, 0.02801f, 0.01702f, 0.02640f, 0.02650f, 0.03163f, 0.02885f, 0.02384f, 0.04158f, 0.03134f, 0.04327f, 0.06811f, 0.09541f, 0.07938f, 0.07179f, 0.07798f, 0.06699f, 0.07447f, 0.07253f, 0.07262f, 0.07892f, 0.07255f, 0.07318f, 0.09353f, 0.16199f, 0.19828f, 0.17500f, 0.15950f, 0.16978f, 0.19100f, 0.18342f, 0.19530f, 0.23197f, 0.20561f, 0.18797f, 0.29651f };

vector<float> w_ele_EH_max= { 0.00723f, 0.03492f, 0.01960f, 0.01451f, 0.01590f, 0.01816f, 0.01907f, 0.02029f, 0.02388f, 0.02521f, 0.02278f, 0.02568f, 0.01356f, 0.07127f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f, 0.00000f };

 vector<float> w_pi_EH_max={ 0.06347f, 0.06170f, 0.06603f, 0.03385f, 0.01094f, 0.02371f, 0.02217f, 0.03264f, 0.03631f, 0.02156f, 0.04413f, 0.06380f, 0.01986f, 0.07624f, 0.11009f, 0.09512f, 0.07822f, 0.07708f, 0.09144f, 0.07834f, 0.07143f, 0.09362f, 0.07241f, 0.07357f, 0.10885f, 0.09446f, 0.16490f, 0.25348f, 0.19142f, 0.16819f, 0.19386f, 0.20562f, 0.23315f, 0.22765f, 0.26445f, 0.24891f, 0.22453f, 0.43762f };


void add_genmatch(TString filein,  TString treename, TString fileout){

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

  int _cl3d_n;  

  vector<int> *_tc_id;
  vector<int> *_tc_layer;
  vector<float> *_tc_pt;
  vector<float> *_tc_eta;
  vector<float> *_tc_phi;
  vector<float> *_tc_energy;
  vector<float> *_tc_mipPt;  

  vector<int> *_cl_id;
  vector<int> *_cl_layer;
  vector<float> *_cl_pt;
  vector<float> *_cl_eta;
  vector<float> *_cl_phi;
  vector<float> *_cl_energy;
  vector<float> *_cl_mipPt;  

  vector<float> *_cl3d_pt;
  vector<float> *_cl3d_eta;
  vector<float> *_cl3d_phi;
  vector<float> *_cl3d_energy;
  vector<unsigned int> *_cl3d_id;

  vector<int> *_gen_status;
  vector<float> *_gen_pt;
  vector<float> *_gen_eta;
  vector<float> *_gen_phi;
  vector<float> *_gen_energy;

  vector<vector<unsigned int> >* _cl3d_clusters_id;      

  tree->SetBranchAddress("tc_pt",     &_tc_pt);
  tree->SetBranchAddress("tc_eta",    &_tc_eta);
  tree->SetBranchAddress("tc_phi",    &_tc_phi);
  tree->SetBranchAddress("tc_energy", &_tc_energy);
  tree->SetBranchAddress("tc_id",     &_tc_id);
  tree->SetBranchAddress("tc_mipPt",  &_tc_mipPt);
  tree->SetBranchAddress("tc_layer",  &_tc_layer);

  tree->SetBranchAddress("cl_pt",     &_cl_pt);
  tree->SetBranchAddress("cl_eta",    &_cl_eta);
  tree->SetBranchAddress("cl_phi",    &_cl_phi);
  tree->SetBranchAddress("cl_energy", &_cl_energy);
  tree->SetBranchAddress("cl_id",     &_cl_id);
  tree->SetBranchAddress("cl_mipPt",  &_cl_mipPt);
  tree->SetBranchAddress("cl_layer",  &_cl_layer);

  tree->SetBranchAddress("cl3d_n",   &_cl3d_n);

  tree->SetBranchAddress("cl3d_pt",    &_cl3d_pt);
  tree->SetBranchAddress("cl3d_eta",    &_cl3d_eta);
  tree->SetBranchAddress("cl3d_phi",    &_cl3d_phi);
  tree->SetBranchAddress("cl3d_energy", &_cl3d_energy);
  tree->SetBranchAddress("cl3d_id",     &_cl3d_id);

  tree->SetBranchAddress("gen_status", &_gen_status);
  tree->SetBranchAddress("gen_pt",     &_gen_pt);
  tree->SetBranchAddress("gen_eta",    &_gen_eta);
  tree->SetBranchAddress("gen_phi",    &_gen_phi);
  tree->SetBranchAddress("gen_energy", &_gen_energy);
      
  tree->SetBranchAddress("cl3d_clusters_id",     &_cl3d_clusters_id);


  TTree* tree_new = new TTree("HGCalTriggerNtuple","HGCalTriggerNtuple");
  //tree_new->AddFriend(treename,filein);
  tree_new = tree->GetTree()->CloneTree(0);
  
  //New branches
  vector<int> _gen_C3D;
  vector<int> _gen_C3D_max;
  tree_new->Branch("gen_cl3d", &_gen_C3D);
  tree_new->Branch("gen_cl3d_max", &_gen_C3D_max);

  vector<float> _gen_SC_C3D_0p1_pt;
  vector<float> _gen_SC_C3D_0p1_eta;
  vector<float> _gen_SC_C3D_0p1_phi;
  vector<float> _gen_SC_C3D_0p1_energy;
  vector<float> _gen_SC_C3D_0p1_pt_sum;
  vector<float> _gen_SC_C3D_0p1_pt_new_ele;
  vector<float> _gen_SC_C3D_0p1_pt_new_pi;
  vector<unsigned int> _gen_SC_C3D_0p1_n_cl3d;
  vector<vector<unsigned int> > _gen_SC_C3D_0p1_cl3d_id;
  tree_new->Branch("gen_SC_C3D_0p1_pt", &_gen_SC_C3D_0p1_pt);
  tree_new->Branch("gen_SC_C3D_0p1_eta", &_gen_SC_C3D_0p1_eta);
  tree_new->Branch("gen_SC_C3D_0p1_phi", &_gen_SC_C3D_0p1_phi);
  tree_new->Branch("gen_SC_C3D_0p1_energy", &_gen_SC_C3D_0p1_energy);
  tree_new->Branch("gen_SC_C3D_0p1_pt_sum", &_gen_SC_C3D_0p1_pt_sum);
  tree_new->Branch("gen_SC_C3D_0p1_pt_new_ele", &_gen_SC_C3D_0p1_pt_new_ele);
  tree_new->Branch("gen_SC_C3D_0p1_pt_new_pi", &_gen_SC_C3D_0p1_pt_new_pi);
  tree_new->Branch("gen_SC_C3D_0p1_n_cl3d", &_gen_SC_C3D_0p1_n_cl3d);
  tree_new->Branch("gen_SC_C3D_0p1_cl3d_id", &_gen_SC_C3D_0p1_cl3d_id);

  vector<float> _gen_SC_C3D_0p3_pt;
  vector<float> _gen_SC_C3D_0p3_eta;
  vector<float> _gen_SC_C3D_0p3_phi;
  vector<float> _gen_SC_C3D_0p3_energy;
  vector<float> _gen_SC_C3D_0p3_pt_sum;
  vector<unsigned int> _gen_SC_C3D_0p3_n_cl3d;
  vector<vector<unsigned int> > _gen_SC_C3D_0p3_cl3d_id;
  tree_new->Branch("gen_SC_C3D_0p3_pt", &_gen_SC_C3D_0p3_pt);
  tree_new->Branch("gen_SC_C3D_0p3_eta", &_gen_SC_C3D_0p3_eta);
  tree_new->Branch("gen_SC_C3D_0p3_phi", &_gen_SC_C3D_0p3_phi);
  tree_new->Branch("gen_SC_C3D_0p3_energy", &_gen_SC_C3D_0p3_energy);
  tree_new->Branch("gen_SC_C3D_0p3_pt_sum", &_gen_SC_C3D_0p3_pt_sum);
  tree_new->Branch("gen_SC_C3D_0p3_n_cl3d", &_gen_SC_C3D_0p3_n_cl3d);
  tree_new->Branch("gen_SC_C3D_0p3_cl3d_id", &_gen_SC_C3D_0p3_cl3d_id);


  vector<float> _cl_dR_gen_C3D;
  tree_new->Branch("cl_dR_gen_cl3d", &_cl_dR_gen_C3D);
   
  vector<float> _cl3d_pt_new_ele;
  vector<float> _cl3d_pt_new_pi;
  vector<float> _cl3d_pt_new_pi_0p03;
  vector<float> _cl3d_pt_new_ele_EE_pi_FHBH;
  vector<float> _cl3d_pt_new_ele_EE_pi_FHBH2;
  tree_new->Branch("cl3d_pt_new_ele", &_cl3d_pt_new_ele);
  tree_new->Branch("cl3d_pt_new_pi", &_cl3d_pt_new_pi);
  tree_new->Branch("cl3d_pt_new_pi_0p03", &_cl3d_pt_new_pi_0p03);
  tree_new->Branch("cl3d_pt_new_ele_EE_pi_FHBH", &_cl3d_pt_new_ele_EE_pi_FHBH);
  tree_new->Branch("cl3d_pt_new_ele_EE_pi_FHBH2", &_cl3d_pt_new_ele_EE_pi_FHBH2);

  vector<float> _cl_max_mipPt;
  vector<int> _cl_max_layer;
  vector<float> _cl_max_pt;
  vector<float> _cl_max_eta;
  vector<float> _cl_max_phi;
  vector<float> _cl_max_energy;
  vector<vector<unsigned int> > _cl_max_cells_id;

  vector<float> _cl3d_max_pt_ele;
  vector<float> _cl3d_max_pt_pi;
  vector<float> _cl3d_max_eta;
  vector<float> _cl3d_max_phi;
  vector<float> _cl3d_max_energy;
  vector<vector<unsigned int> > _cl3d_max_clusters_id;

  tree_new->Branch("cl_max_mipPt", &_cl_max_mipPt);
  tree_new->Branch("cl_max_layer", &_cl_max_layer);
  tree_new->Branch("cl_max_pt",    &_cl_max_pt);
  tree_new->Branch("cl_max_eta",   &_cl_max_eta);
  tree_new->Branch("cl_max_phi",   &_cl_max_phi);
  tree_new->Branch("cl_max_energy", &_cl_max_energy);
  tree_new->Branch("cl_max_cells_id", &_cl_max_cells_id);

  tree_new->Branch("cl3d_max_pt_ele",    &_cl3d_max_pt_ele);
  tree_new->Branch("cl3d_max_pt_pi",    &_cl3d_max_pt_pi);
  tree_new->Branch("cl3d_max_eta",   &_cl3d_max_eta);
  tree_new->Branch("cl3d_max_phi",   &_cl3d_max_phi);
  tree_new->Branch("cl3d_max_energy", &_cl3d_max_energy);
  tree_new->Branch("cl3d_max_clusters_id", &_cl3d_max_clusters_id);

  vector<float> _cl_max_cl2_mipPt;
  vector<int> _cl_max_cl2_layer;
  vector<float> _cl_max_cl2_pt_ele;
  vector<float> _cl_max_cl2_pt_pi;
  vector<float> _cl_max_cl2_eta;
  vector<float> _cl_max_cl2_phi;
  vector<float> _cl_max_cl2_energy;

  tree_new->Branch("cl_max_cl2_mipPt", &_cl_max_cl2_mipPt);
  tree_new->Branch("cl_max_cl2_layer", &_cl_max_cl2_layer);
  tree_new->Branch("cl_max_cl2_pt_ele",    &_cl_max_cl2_pt_ele);
  tree_new->Branch("cl_max_cl2_pt_pi",    &_cl_max_cl2_pt_pi);
  tree_new->Branch("cl_max_cl2_eta",   &_cl_max_cl2_eta);
  tree_new->Branch("cl_max_cl2_phi",   &_cl_max_cl2_phi);
  tree_new->Branch("cl_max_cl2_energy", &_cl_max_cl2_energy);

  vector<float> _cl3d_max_cl2_pt_ele;
  vector<float> _cl3d_max_cl2_pt_pi;
  vector<float> _cl3d_max_cl2_eta;
  vector<float> _cl3d_max_cl2_phi;
  vector<float> _cl3d_max_cl2_energy;
  vector<vector<unsigned int> > _cl3d_max_cl2_clusters_id;

  tree_new->Branch("cl3d_max_cl2_pt_ele",    &_cl3d_max_cl2_pt_ele);
  tree_new->Branch("cl3d_max_cl2_pt_pi",    &_cl3d_max_cl2_pt_pi);
  tree_new->Branch("cl3d_max_cl2_eta",   &_cl3d_max_cl2_eta);
  tree_new->Branch("cl3d_max_cl2_phi",   &_cl3d_max_cl2_phi);
  tree_new->Branch("cl3d_max_cl2_energy", &_cl3d_max_cl2_energy);
  tree_new->Branch("cl3d_max_cl2_clusters_id", &_cl3d_max_cl2_clusters_id);

  vector<float> _cl_EE_max_mipPt;
  vector<int> _cl_EE_max_layer;
  vector<float> _cl_EE_max_pt;
  vector<float> _cl_EE_max_eta;
  vector<float> _cl_EE_max_phi;
  vector<float> _cl_EE_max_energy;

  vector<float> _cl3d_EE_max_pt_ele;
  vector<float> _cl3d_EE_max_pt_pi;
  vector<float> _cl3d_EE_max_eta;
  vector<float> _cl3d_EE_max_phi;
  vector<float> _cl3d_EE_max_energy;
  vector<vector<unsigned int> > _cl3d_EE_max_clusters_id;

  tree_new->Branch("cl_EE_max_mipPt", &_cl_EE_max_mipPt);
  tree_new->Branch("cl_EE_max_layer", &_cl_EE_max_layer);
  tree_new->Branch("cl_EE_max_pt",    &_cl_EE_max_pt);
  tree_new->Branch("cl_EE_max_eta",   &_cl_EE_max_eta);
  tree_new->Branch("cl_EE_max_phi",   &_cl_EE_max_phi);
  tree_new->Branch("cl_EE_max_energy", &_cl_EE_max_energy);

  tree_new->Branch("cl3d_EE_max_pt_ele",    &_cl3d_EE_max_pt_ele);
  tree_new->Branch("cl3d_EE_max_pt_pi",    &_cl3d_EE_max_pt_pi);
  tree_new->Branch("cl3d_EE_max_eta",   &_cl3d_EE_max_eta);
  tree_new->Branch("cl3d_EE_max_phi",   &_cl3d_EE_max_phi);
  tree_new->Branch("cl3d_EE_max_energy", &_cl3d_EE_max_energy);  
  tree_new->Branch("cl3d_EE_max_clusters_id", &_cl3d_EE_max_clusters_id);


  vector<float> _cl_EH_max_mipPt;
  vector<int> _cl_EH_max_layer;
  vector<float> _cl_EH_max_pt;
  vector<float> _cl_EH_max_eta;
  vector<float> _cl_EH_max_phi;
  vector<float> _cl_EH_max_energy;

  vector<float> _cl3d_EH_max_pt_ele;
  vector<float> _cl3d_EH_max_pt_pi;
  vector<float> _cl3d_EH_max_eta;
  vector<float> _cl3d_EH_max_phi;
  vector<float> _cl3d_EH_max_energy;
  vector<vector<unsigned int> > _cl3d_EH_max_clusters_id;


  tree_new->Branch("cl_EH_max_mipPt", &_cl_EH_max_mipPt);
  tree_new->Branch("cl_EH_max_layer", &_cl_EH_max_layer);
  tree_new->Branch("cl_EH_max_pt",    &_cl_EH_max_pt);
  tree_new->Branch("cl_EH_max_eta",   &_cl_EH_max_eta);
  tree_new->Branch("cl_EH_max_phi",   &_cl_EH_max_phi);
  tree_new->Branch("cl_EH_max_energy", &_cl_EH_max_energy);

  tree_new->Branch("cl3d_EH_max_pt_ele",  &_cl3d_EH_max_pt_ele);
  tree_new->Branch("cl3d_EH_max_pt_pi",   &_cl3d_EH_max_pt_pi);
  tree_new->Branch("cl3d_EH_max_eta",   &_cl3d_EH_max_eta);
  tree_new->Branch("cl3d_EH_max_phi",   &_cl3d_EH_max_phi);
  tree_new->Branch("cl3d_EH_max_energy", &_cl3d_EH_max_energy); 
  tree_new->Branch("cl3d_EH_max_clusters_id", &_cl3d_EH_max_clusters_id); 


  int N = nentries;
  N=min(4000,N);
  for(int i=0;i<N;i++){
  
    if(i%100==0)
      cout<<"i="<<i<<endl;

    _tc_id = 0;
    _tc_layer = 0;
    _tc_pt = 0;
    _tc_eta = 0;
    _tc_phi = 0;
    _tc_energy = 0;
    _tc_mipPt = 0;

    _cl_id = 0;
    _cl_layer = 0;
    _cl_pt = 0;
    _cl_eta = 0;
    _cl_phi = 0;
    _cl_energy = 0;
    _cl_mipPt = 0;
    
    _cl3d_n = 0;

    _cl3d_pt = 0;
    _cl3d_eta = 0;
    _cl3d_phi = 0;
    _cl3d_energy = 0;
    _cl3d_id = 0;

    _gen_status = 0;
    _gen_pt = 0;
    _gen_eta = 0;
    _gen_phi = 0;
    _gen_energy = 0;    

    _cl3d_clusters_id = 0;

    _gen_C3D.clear();
    _gen_C3D_max.clear();
    _cl_dR_gen_C3D.clear();

    _gen_SC_C3D_0p3_pt.clear();
    _gen_SC_C3D_0p3_eta.clear();
    _gen_SC_C3D_0p3_phi.clear();
    _gen_SC_C3D_0p3_energy.clear();
    _gen_SC_C3D_0p3_pt_sum.clear();
    _gen_SC_C3D_0p3_n_cl3d.clear();
    _gen_SC_C3D_0p3_cl3d_id.clear();

    _gen_SC_C3D_0p1_pt.clear();
    _gen_SC_C3D_0p1_eta.clear();
    _gen_SC_C3D_0p1_phi.clear();
    _gen_SC_C3D_0p1_energy.clear();
    _gen_SC_C3D_0p1_pt_sum.clear();
    _gen_SC_C3D_0p1_pt_new_ele.clear();
    _gen_SC_C3D_0p1_pt_new_pi.clear();
    _gen_SC_C3D_0p1_n_cl3d.clear();
    _gen_SC_C3D_0p1_cl3d_id.clear();

    _cl3d_pt_new_ele.clear();
    _cl3d_pt_new_pi.clear();
    _cl3d_pt_new_pi_0p03.clear();
    _cl3d_pt_new_ele_EE_pi_FHBH.clear();
    _cl3d_pt_new_ele_EE_pi_FHBH2.clear();

    _cl_max_mipPt.clear();
    _cl_max_layer.clear();
    _cl_max_pt.clear();
    _cl_max_eta.clear();
    _cl_max_phi.clear();
    _cl_max_energy.clear();
    _cl_max_cells_id.clear();

    _cl3d_max_pt_ele.clear();
    _cl3d_max_pt_pi.clear();
    _cl3d_max_eta.clear();
    _cl3d_max_phi.clear();
    _cl3d_max_energy.clear();
    _cl3d_max_clusters_id.clear(); 

    _cl_max_cl2_mipPt.clear();
    _cl_max_cl2_layer.clear();
    _cl_max_cl2_pt_ele.clear();
    _cl_max_cl2_pt_pi.clear();
    _cl_max_cl2_eta.clear();
    _cl_max_cl2_phi.clear();
    _cl_max_cl2_energy.clear();

    _cl3d_max_cl2_pt_ele.clear();
    _cl3d_max_cl2_pt_pi.clear();
    _cl3d_max_cl2_eta.clear();
    _cl3d_max_cl2_phi.clear();
    _cl3d_max_cl2_energy.clear();
    _cl3d_max_cl2_clusters_id.clear();  


    _cl_EE_max_mipPt.clear();
    _cl_EE_max_layer.clear();
    _cl_EE_max_pt.clear();
    _cl_EE_max_eta.clear();
    _cl_EE_max_phi.clear();
    _cl_EE_max_energy.clear();

    _cl3d_EE_max_pt_ele.clear();
    _cl3d_EE_max_pt_pi.clear();
    _cl3d_EE_max_eta.clear();
    _cl3d_EE_max_phi.clear();
    _cl3d_EE_max_energy.clear();
    _cl3d_EE_max_clusters_id.clear();  

    _cl_EH_max_mipPt.clear();
    _cl_EH_max_layer.clear();
    _cl_EH_max_pt.clear();
    _cl_EH_max_eta.clear();
    _cl_EH_max_phi.clear();
    _cl_EH_max_energy.clear();

    _cl3d_EH_max_pt_ele.clear();
    _cl3d_EH_max_pt_pi.clear();
    _cl3d_EH_max_eta.clear();
    _cl3d_EH_max_phi.clear();
    _cl3d_EH_max_energy.clear();
    _cl3d_EH_max_clusters_id.clear();  

    tree->GetEntry(i);
    
    map<unsigned int, unsigned int> tc_map; //First ID, Second index
    map<unsigned int, unsigned int> cl_map; //First ID, Second index
    
    for(unsigned int i_tc = 0; i_tc < (*_tc_id).size(); i_tc++)
      tc_map[(*_tc_id)[i_tc]] = i_tc;  

    for(unsigned int i_cl = 0; i_cl < (*_cl_id).size(); i_cl++)
      cl_map[(*_cl_id)[i_cl]] = i_cl;  

    for(unsigned int i_gen=0; i_gen<(*_gen_pt).size(); i_gen++){
      
      TLorentzVector gen_tlv;    
      gen_tlv.SetPtEtaPhiE((*_gen_pt)[i_gen], (*_gen_eta)[i_gen], (*_gen_phi)[i_gen], (*_gen_energy)[i_gen]);     

      float pT_max = -1.;
      int i_C3D_gen = -1;      
      
      for(unsigned int i_c3d=0; i_c3d<(*_cl3d_pt).size(); i_c3d++){
	TLorentzVector c3d;
	c3d.SetPtEtaPhiE((*_cl3d_pt)[i_c3d],(*_cl3d_eta)[i_c3d],(*_cl3d_phi)[i_c3d],(*_cl3d_energy)[i_c3d]);	
	float dR = c3d.DeltaR(gen_tlv);
	if((pT_max<0 && dR<0.3) || (dR<0.3 && c3d.Pt()>pT_max)){
	    pT_max = c3d.Pt();
	    i_C3D_gen = i_c3d;
	}
      }            					     
      
      _gen_C3D.emplace_back(i_C3D_gen);
      if(gen_tlv.Eta()>0) _gen_C3D_max.emplace_back(0);
      else _gen_C3D_max.emplace_back(1);
 
    }



    for(unsigned int i_c3d=0; i_c3d<(*_cl3d_pt).size(); i_c3d++){

      vector<float> cl3d_layer_MIPpt(53);
      
      for(auto & i_c2d : (*_cl3d_clusters_id)[i_c3d]){      
	cl3d_layer_MIPpt[(*_cl_layer)[cl_map[i_c2d]]] += (*_cl_mipPt)[cl_map[i_c2d]];
      }

      float pT_new_ele = 0;
      float pT_new_pi = 0;
      float pT_new_pi_0p03 = 0;
      float pT_new_ele_EE_pi_FHBH = 0;
      float pT_new_ele_EE_pi_FHBH2 = 0;       

      for(unsigned int i=0; i<38; i++){    
	  int i_layer = -1;
	  if(i<14) i_layer = 2*i+1;
	  else i_layer = i+15;	  
	  pT_new_ele+=w_ele[i]*cl3d_layer_MIPpt[i_layer];
	  pT_new_pi+=w_pi[i]*cl3d_layer_MIPpt[i_layer];
	  pT_new_pi_0p03+=w_pi_0p03[i]*cl3d_layer_MIPpt[i_layer];
	  pT_new_ele_EE_pi_FHBH+=w_ele_EE_pi_FHBH[i]*cl3d_layer_MIPpt[i_layer];
	  pT_new_ele_EE_pi_FHBH2+=w_ele_EE_pi_FHBH2[i]*cl3d_layer_MIPpt[i_layer];
      }

      _cl3d_pt_new_ele.push_back(pT_new_ele);
      _cl3d_pt_new_pi.push_back(pT_new_pi);
      _cl3d_pt_new_pi_0p03.push_back(pT_new_pi_0p03);
      _cl3d_pt_new_ele_EE_pi_FHBH.push_back(pT_new_ele_EE_pi_FHBH);
      _cl3d_pt_new_ele_EE_pi_FHBH2.push_back(pT_new_ele_EE_pi_FHBH2);

    }


    for(unsigned int i_gen=0; i_gen<(*_gen_pt).size(); i_gen++){
      
      TLorentzVector gen_tlv;    
      gen_tlv.SetPtEtaPhiE((*_gen_pt)[i_gen], (*_gen_eta)[i_gen], (*_gen_phi)[i_gen], (*_gen_energy)[i_gen]);

      TLorentzVector SC_0p3;
      vector<unsigned int> SC_0p3_cl3d_id;
      TLorentzVector SC_0p1;
      vector<unsigned int> SC_0p1_cl3d_id;
     
      for(unsigned int i_c3d=0; i_c3d<(*_cl3d_pt).size(); i_c3d++){
	TLorentzVector c3d;
	c3d.SetPtEtaPhiE((*_cl3d_pt)[i_c3d],(*_cl3d_eta)[i_c3d],(*_cl3d_phi)[i_c3d],(*_cl3d_energy)[i_c3d]);	
	float dR = c3d.DeltaR(gen_tlv);
	if(dR<0.3){
	  SC_0p3+=c3d;
	  SC_0p3_cl3d_id.push_back(i_c3d);	
	  if(dR<0.1){
	    SC_0p1+=c3d;
	    SC_0p1_cl3d_id.push_back(i_c3d);
	  }
	}
      }


      _gen_SC_C3D_0p1_pt.push_back(SC_0p1.Pt());
      _gen_SC_C3D_0p1_eta.push_back(SC_0p1.Eta());
      _gen_SC_C3D_0p1_phi.push_back(SC_0p1.Pt());
      _gen_SC_C3D_0p1_energy.push_back(SC_0p1.E());
      _gen_SC_C3D_0p1_n_cl3d.push_back(SC_0p1_cl3d_id.size());
      _gen_SC_C3D_0p1_cl3d_id.push_back(SC_0p1_cl3d_id);

      _gen_SC_C3D_0p3_pt.push_back(SC_0p3.Pt());
      _gen_SC_C3D_0p3_eta.push_back(SC_0p3.Eta());
      _gen_SC_C3D_0p3_phi.push_back(SC_0p3.Pt());
      _gen_SC_C3D_0p3_energy.push_back(SC_0p3.E());
      _gen_SC_C3D_0p3_n_cl3d.push_back(SC_0p3_cl3d_id.size());
      _gen_SC_C3D_0p3_cl3d_id.push_back(SC_0p3_cl3d_id);
      
      float pt_sum=0;
      float pt_new_ele=0;
      float pt_new_pi=0;
      for(auto i_c3d : SC_0p1_cl3d_id){
	pt_sum+=(*_cl3d_pt)[i_c3d];
	pt_new_ele+=(_cl3d_pt_new_ele)[i_c3d];
	pt_new_pi+=(_cl3d_pt_new_pi)[i_c3d];
      }
      _gen_SC_C3D_0p1_pt_sum.push_back(pt_sum);
      _gen_SC_C3D_0p1_pt_sum.push_back(pt_new_ele);
      _gen_SC_C3D_0p1_pt_sum.push_back(pt_new_pi);
      
      pt_sum=0;      
      for(auto i_c3d : SC_0p3_cl3d_id){
	pt_sum+=(*_cl3d_pt)[i_c3d];
      }
      _gen_SC_C3D_0p3_pt_sum.push_back(pt_sum);
      

    }

      

    map<int,vector<unsigned int> > tc_eta_pos; //first = layer, second = list of TCs
    map<int,vector<unsigned int> > tc_eta_neg; //first = layer, second = list of TCs


    for(unsigned int i_tc=0; i_tc<(*_tc_eta).size(); i_tc++){
      if((*_tc_eta)[i_tc]>0) tc_eta_pos[(*_tc_layer)[i_tc]].emplace_back(i_tc);
      else tc_eta_neg[(*_tc_layer)[i_tc]].emplace_back(i_tc);
    }

    TLorentzVector cl3d_max_eta_pos;
    vector<unsigned int> cl_max_eta_pos;
    unsigned int i_cl = 0;
    float cl3d_eta_pos_pt_ele = 0;
    float cl3d_eta_pos_pt_pi = 0;

    for(auto& key : tc_eta_pos){
      
      int layer = key.first;
      TLorentzVector cl_tlv;
      vector<unsigned int> cells_id;
      float mipPt = 0;

      for(auto& i_tc : key.second){

	TLorentzVector tc_tlv;
	tc_tlv.SetPtEtaPhiM((*_tc_mipPt)[i_tc],(*_tc_eta)[i_tc],(*_tc_phi)[i_tc],0.);
	cl_tlv+=tc_tlv;
	mipPt += (*_tc_mipPt)[i_tc];
	cells_id.push_back((*_tc_id)[i_tc]);	

      }

      _cl_max_mipPt.push_back(mipPt);
      _cl_max_layer.push_back(layer);
      _cl_max_pt.push_back(cl_tlv.Pt());
      _cl_max_eta.push_back(cl_tlv.Eta());
      _cl_max_phi.push_back(cl_tlv.Phi());
      _cl_max_energy.push_back(cl_tlv.E());
      _cl_max_cells_id.push_back(cells_id);

      cl3d_max_eta_pos += cl_tlv;
      cl_max_eta_pos.push_back(i_cl);

      int i_layer = -1;
      if(layer<25) i_layer = (layer-1)/2;
      else i_layer = layer-12;
      cl3d_eta_pos_pt_ele += w_ele_cl_max[i_layer]*mipPt;
      cl3d_eta_pos_pt_pi += w_pi_cl_max[i_layer]*mipPt;

      i_cl++;

    }


    TLorentzVector cl3d_max_eta_neg;
    vector<unsigned int> cl_max_eta_neg;
    float cl3d_eta_neg_pt_ele = 0;
    float cl3d_eta_neg_pt_pi = 0;


    for(auto& key : tc_eta_neg){
      
      int layer = key.first;
      TLorentzVector cl_tlv;
      vector<unsigned int> cells_id;
      float mipPt = 0;


      for(auto& i_tc : key.second){

	TLorentzVector tc_tlv;
	tc_tlv.SetPtEtaPhiM((*_tc_mipPt)[i_tc],(*_tc_eta)[i_tc],(*_tc_phi)[i_tc],0.);
	cl_tlv+=tc_tlv;
	mipPt += (*_tc_mipPt)[i_tc];
	cells_id.push_back((*_tc_id)[i_tc]);

      }

      _cl_max_mipPt.push_back(mipPt);
      _cl_max_layer.push_back(layer);
      _cl_max_pt.push_back(cl_tlv.Pt());
      _cl_max_eta.push_back(cl_tlv.Eta());
      _cl_max_phi.push_back(cl_tlv.Phi());
      _cl_max_energy.push_back(cl_tlv.E());
      _cl_max_cells_id.push_back(cells_id);

      cl3d_max_eta_neg += cl_tlv;
      cl_max_eta_neg.push_back(i_cl);

      int i_layer = -1;
      if(layer<25) i_layer = (layer-1)/2;
      else i_layer = layer-12; 

      cl3d_eta_neg_pt_ele += w_ele_cl_max[i_layer]*mipPt;
      cl3d_eta_neg_pt_pi += w_pi_cl_max[i_layer]*mipPt;

      i_cl++;

    }


   _cl3d_max_pt_ele.push_back(cl3d_eta_pos_pt_ele);
   _cl3d_max_pt_pi.push_back(cl3d_eta_pos_pt_pi);
   _cl3d_max_eta.push_back(cl3d_max_eta_pos.Eta());
   _cl3d_max_phi.push_back(cl3d_max_eta_pos.Phi());
   _cl3d_max_energy.push_back(cl3d_max_eta_pos.E());
   _cl3d_max_clusters_id.push_back(cl_max_eta_pos);

   _cl3d_max_pt_ele.push_back(cl3d_eta_neg_pt_ele);
   _cl3d_max_pt_pi.push_back(cl3d_eta_neg_pt_pi);
   _cl3d_max_eta.push_back(cl3d_max_eta_neg.Eta());
   _cl3d_max_phi.push_back(cl3d_max_eta_neg.Phi());
   _cl3d_max_energy.push_back(cl3d_max_eta_neg.E());
   _cl3d_max_clusters_id.push_back(cl_max_eta_neg);


   map<int,vector<unsigned int> > cl_eta_pos; //first = layer, second = list of TCs
   map<int,vector<unsigned int> > cl_eta_neg; //first = layer, second = list of TCs
   vector<unsigned int> cl_eta_pos_vect;
   vector<unsigned int> cl_eta_neg_vect;


    for(unsigned int i_cl=0; i_cl<(*_cl_eta).size(); i_cl++){
      if((*_cl_eta)[i_cl]>0){
	cl_eta_pos[(*_cl_layer)[i_cl]].emplace_back(i_cl);
	cl_eta_pos_vect.emplace_back((*_cl_id)[i_cl]);
      }
      else{
	cl_eta_neg[(*_cl_layer)[i_cl]].emplace_back(i_cl);
	cl_eta_neg_vect.emplace_back((*_cl_id)[i_cl]);
      }
    }


    TLorentzVector cl3d_max_cl2_eta_pos;
    float cl3d_cl2_eta_pos_pt_ele = 0;
    float cl3d_cl2_eta_pos_pt_pi = 0;

    for(auto& key : cl_eta_pos){
      
      int layer = key.first;
      float mipPt = 0;

      TLorentzVector cl_max;

      for(auto& i_cl : key.second){

	TLorentzVector cl_tlv;
	cl_tlv.SetPtEtaPhiM((*_cl_mipPt)[i_cl],(*_cl_eta)[i_cl],(*_cl_phi)[i_cl],0.);
	mipPt += (*_cl_mipPt)[i_cl];
	cl_max += cl_tlv;

      }

      int i_layer = -1;
      if(layer<25) i_layer = (layer-1)/2;
      else i_layer = layer-12;

      _cl_max_cl2_mipPt.push_back(mipPt);
      _cl_max_cl2_layer.push_back(layer);
      _cl_max_cl2_pt_ele.push_back(w_ele_cl_max[i_layer]*mipPt);
      _cl_max_cl2_pt_pi.push_back(w_pi_cl_max[i_layer]*mipPt);
      _cl_max_cl2_eta.push_back(cl_max.Eta());
      _cl_max_cl2_phi.push_back(cl_max.Phi());
      _cl_max_cl2_energy.push_back(cl_max.E());

      cl3d_max_cl2_eta_pos += cl_max;
      cl3d_cl2_eta_pos_pt_ele += w_ele_cl_max[i_layer]*mipPt;
      cl3d_cl2_eta_pos_pt_pi += w_pi_cl_max[i_layer]*mipPt;


    }


    TLorentzVector cl3d_max_cl2_eta_neg;
    float cl3d_cl2_eta_neg_pt_ele = 0;
    float cl3d_cl2_eta_neg_pt_pi = 0;

    for(auto& key : cl_eta_neg){
      
      int layer = key.first;
      float mipPt = 0;

      TLorentzVector cl_max;

      for(auto& i_cl : key.second){

	TLorentzVector cl_tlv;
	cl_tlv.SetPtEtaPhiM((*_cl_mipPt)[i_cl],(*_cl_eta)[i_cl],(*_cl_phi)[i_cl],0.);
	mipPt += (*_cl_mipPt)[i_cl];
	cl_max += cl_tlv;

      }


      int i_layer = -1;
      if(layer<25) i_layer = (layer-1)/2;
      else i_layer = layer-12;

      _cl_max_cl2_mipPt.push_back(mipPt);
      _cl_max_cl2_layer.push_back(layer);
      _cl_max_cl2_pt_ele.push_back(w_ele_cl_max[i_layer]*mipPt);
      _cl_max_cl2_pt_pi.push_back(w_pi_cl_max[i_layer]*mipPt);
      _cl_max_cl2_eta.push_back(cl_max.Eta());
      _cl_max_cl2_phi.push_back(cl_max.Phi());
      _cl_max_cl2_energy.push_back(cl_max.E());

      cl3d_max_cl2_eta_neg += cl_max;
      cl3d_cl2_eta_neg_pt_ele += w_ele_cl_max[i_layer]*mipPt;
      cl3d_cl2_eta_neg_pt_pi += w_pi_cl_max[i_layer]*mipPt;


    }


   _cl3d_max_cl2_pt_ele.push_back(cl3d_cl2_eta_pos_pt_ele);
   _cl3d_max_cl2_pt_pi.push_back(cl3d_cl2_eta_pos_pt_pi);
   _cl3d_max_cl2_eta.push_back(cl3d_max_cl2_eta_pos.Eta());
   _cl3d_max_cl2_phi.push_back(cl3d_max_cl2_eta_pos.Phi());
   _cl3d_max_cl2_energy.push_back(cl3d_max_cl2_eta_pos.E());
   _cl3d_max_cl2_clusters_id.push_back(cl_eta_pos_vect);

   _cl3d_max_cl2_pt_ele.push_back(cl3d_cl2_eta_neg_pt_ele);
   _cl3d_max_cl2_pt_pi.push_back(cl3d_cl2_eta_neg_pt_pi);
   _cl3d_max_cl2_eta.push_back(cl3d_max_cl2_eta_neg.Eta());
   _cl3d_max_cl2_phi.push_back(cl3d_max_cl2_eta_neg.Phi());
   _cl3d_max_cl2_energy.push_back(cl3d_max_cl2_eta_neg.E());
   _cl3d_max_cl2_clusters_id.push_back(cl_eta_neg_vect);



   uint i_cl_EE = 0;
   uint i_cl_EH = 0;
   

   for(unsigned int i_c3d=0; i_c3d<(*_cl3d_pt).size(); i_c3d++){

     float pt_ele_EE = 0;
     float pt_pi_EE = 0;
     TLorentzVector cl3d_EE_tlv;
     vector<unsigned int> cl3d_EE_clusters;
     
     float pt_ele_EH = 0;
     float pt_pi_EH = 0;
     TLorentzVector cl3d_EH_tlv;
     vector<unsigned int> cl3d_EH_clusters;
     
     for(auto & i_c2d : (*_cl3d_clusters_id)[i_c3d]){   

       int layer = (*_cl_layer)[cl_map[i_c2d]];
       float mipPt = (*_cl_mipPt)[cl_map[i_c2d]];

       int i_layer = -1;
       if(layer<25) i_layer = (layer-1)/2;
       else i_layer = layer-12;

       int i_cl = cl_map[i_c2d];

       TLorentzVector cl_tlv;
       cl_tlv.SetPtEtaPhiM((*_cl_mipPt)[i_cl],(*_cl_eta)[i_cl],(*_cl_phi)[i_cl],0.);
       cl3d_EH_tlv += cl_tlv;
       
       if(layer<25){

	 pt_ele_EE += w_ele_EE_max[i_layer]*mipPt;
	 pt_pi_EE += w_pi_EE_max[i_layer]*mipPt;

	 _cl_EE_max_mipPt.push_back(mipPt);
	 _cl_EE_max_layer.push_back(layer);
	 _cl_EE_max_pt.push_back((*_cl_pt)[cl_map[i_c2d]]);
	 _cl_EE_max_eta.push_back((*_cl_eta)[cl_map[i_c2d]]);
	 _cl_EE_max_phi.push_back((*_cl_phi)[cl_map[i_c2d]]);
	 _cl_EE_max_energy.push_back((*_cl_energy)[cl_map[i_c2d]]);	 
	 cl3d_EE_clusters.push_back(i_cl_EE);
	 i_cl_EE++;
       }
       else{

	 pt_ele_EH += w_ele_EH_max[i_layer]*mipPt;
	 pt_pi_EH += w_pi_EH_max[i_layer]*mipPt;

	 _cl_EH_max_mipPt.push_back((*_cl_mipPt)[cl_map[i_c2d]]);
	 _cl_EH_max_layer.push_back(layer);
	 _cl_EH_max_pt.push_back((*_cl_pt)[cl_map[i_c2d]]);
	 _cl_EH_max_eta.push_back((*_cl_eta)[cl_map[i_c2d]]);
	 _cl_EH_max_phi.push_back((*_cl_phi)[cl_map[i_c2d]]);
	 _cl_EH_max_energy.push_back((*_cl_energy)[cl_map[i_c2d]]);	 
	 cl3d_EH_clusters.push_back(i_cl_EH);
	 i_cl_EH++;
       }

     }


     map<int,vector<unsigned int> > cl_eta_pos_neg = cl_eta_pos;
     if((*_cl3d_eta)[i_c3d]<0) cl_eta_pos_neg = cl_eta_neg;
     

     for(auto& key : cl_eta_pos_neg){
      
       int layer = key.first;
       float mipPt = 0;

       int i_layer = -1;
       if(layer<25) i_layer = (layer-1)/2;
       else i_layer = layer-12;

       TLorentzVector cl_sum_tlv;

       for(auto& i_cl : key.second){

	 TLorentzVector cl_tlv;
	 cl_tlv.SetPtEtaPhiM((*_cl_mipPt)[i_cl],(*_cl_eta)[i_cl],(*_cl_phi)[i_cl],0.);
	 mipPt += (*_cl_mipPt)[i_cl];
	 cl_sum_tlv += cl_tlv;

       }



       if(layer>=25){
	 pt_ele_EE += w_ele_EE_max[i_layer]*mipPt;
	 pt_pi_EE += w_pi_EE_max[i_layer]*mipPt;	
	 cl3d_EE_tlv += cl_sum_tlv;	 

	 _cl_EE_max_mipPt.push_back(mipPt);
	 _cl_EE_max_layer.push_back(layer);
	 _cl_EE_max_pt.push_back(cl_sum_tlv.Pt());
	 _cl_EE_max_eta.push_back(cl_sum_tlv.Eta());
	 _cl_EE_max_phi.push_back(cl_sum_tlv.Phi());
	 _cl_EE_max_energy.push_back(cl_sum_tlv.E());	 
	 cl3d_EE_clusters.push_back(i_cl_EE);
	 i_cl_EE++;
       }
       else{
	 pt_ele_EH += w_ele_EH_max[i_layer]*mipPt;
	 pt_pi_EH += w_pi_EH_max[i_layer]*mipPt;	
	 cl3d_EH_tlv += cl_sum_tlv;

	 _cl_EH_max_mipPt.push_back(mipPt);
	 _cl_EH_max_layer.push_back(layer);
	 _cl_EH_max_pt.push_back(cl_sum_tlv.Pt());
	 _cl_EH_max_eta.push_back(cl_sum_tlv.Eta());
	 _cl_EH_max_phi.push_back(cl_sum_tlv.Phi());
	 _cl_EH_max_energy.push_back(cl_sum_tlv.E());	 
	 cl3d_EH_clusters.push_back(i_cl_EH);
	 i_cl_EH++;
       }

     }

     
   _cl3d_EE_max_pt_ele.push_back(pt_ele_EE);
   _cl3d_EE_max_pt_pi.push_back(pt_pi_EE);
   _cl3d_EE_max_eta.push_back(cl3d_EE_tlv.Eta());
   _cl3d_EE_max_phi.push_back(cl3d_EE_tlv.Phi());
   _cl3d_EE_max_energy.push_back(cl3d_EE_tlv.E());
   _cl3d_EE_max_clusters_id.push_back(cl3d_EE_clusters);


   _cl3d_EH_max_pt_ele.push_back(pt_ele_EH);
   _cl3d_EH_max_pt_pi.push_back(pt_pi_EH);
   _cl3d_EH_max_eta.push_back(cl3d_EH_tlv.Eta());
   _cl3d_EH_max_phi.push_back(cl3d_EH_tlv.Phi());
   _cl3d_EH_max_energy.push_back(cl3d_EH_tlv.E());
   _cl3d_EH_max_clusters_id.push_back(cl3d_EH_clusters);


   }



   
   for(unsigned int i_cl = 0; i_cl < (*_cl_phi).size(); i_cl++){
     
     float dR = 9999.;
     
     float xOverZ_c2d = cos((*_cl_phi)[i_cl])/sinh((*_cl_eta)[i_cl]);
     float yOverZ_c2d = sin((*_cl_phi)[i_cl])/sinh((*_cl_eta)[i_cl]);
     
     int i_C3D_gen = -1;
     for(unsigned int i_gen=0; i_gen<(*_gen_eta).size(); i_gen++){
       if((*_gen_eta)[i_gen]*(*_cl_eta)[i_cl]>0){
	 i_C3D_gen = _gen_C3D[i_gen];
	 break;
       }
     }
     
     if(i_C3D_gen>=0){
       float xOverZ_c3d = cos((*_cl3d_phi)[i_C3D_gen])/sinh((*_cl3d_eta)[i_C3D_gen]);
       float yOverZ_c3d = sin((*_cl3d_phi)[i_C3D_gen])/sinh((*_cl3d_eta)[i_C3D_gen]);
       
       dR = sqrt(pow(xOverZ_c2d-xOverZ_c3d,2)+pow(yOverZ_c2d-yOverZ_c3d,2));
     }

     _cl_dR_gen_C3D.push_back(dR);
  

   }



    tree_new->Fill();
  }

  f_new->cd();
  tree_new->Write();
  f_new->Close();
  return;


}







void test(){

  TString filein="root://cms-xrd-global.cern.ch//store/user/tstreble/SinglePiPt25Eta1p6_2p8/SinglePi_Pt25_PU0_C3D_polarHisto_dR0p03_18_08_10/180810_182602/0000/ntuple_1.root";
  TString treename="hgcalTriggerNtuplizer/HGCalTriggerNtuple";
  TString fileout="/vols/cms/tstreble/HGC_ntuples/C3D_dRHisto_test/test_pi_C3D_polarHisto_dR0p03.root";

  add_genmatch( filein, treename, fileout);


}
