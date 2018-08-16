#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <TMatrixD.h>
#include "TH1F.h"

using namespace std;

void write_C2Ds(vector<TString> filename, TString treename,
                TString fileout){


    std::ofstream out(fileout);
    TChain * tree = new TChain(treename);
    for(unsigned int i=0;i<filename.size();i++)
      tree->Add(filename[i]);
    int nentries = tree->GetEntries();

    vector<int>* _gen_pdgid;
    vector<float>* _gen_pt;
    vector<float>* _gen_eta;
    vector<float>* _gen_phi;
    vector<float>* _gen_energy;
    
    vector<float>* _cl_mipPt;
    vector<float>* _cl_pt;
    vector<float>* _cl_eta;
    vector<float>* _cl_phi;
    vector<int>* _cl_layer;
    vector<vector<unsigned int> >* _cl_cells_id;
    vector<float>* _tc_z;
    vector<uint32_t>* _tc_id;
    
    tree->SetBranchAddress("gen_pdgid", &_gen_pdgid);
    tree->SetBranchAddress("gen_pt", &_gen_pt);
    tree->SetBranchAddress("gen_eta", &_gen_eta);
    tree->SetBranchAddress("gen_phi", &_gen_phi);
    tree->SetBranchAddress("gen_energy", &_gen_energy);
    
    tree->SetBranchAddress("cl_mipPt", &_cl_mipPt);
    tree->SetBranchAddress("cl_pt", &_cl_pt);
    tree->SetBranchAddress("cl_eta", &_cl_eta);
    tree->SetBranchAddress("cl_phi", &_cl_phi);
    tree->SetBranchAddress("cl_layer", &_cl_layer);
    tree->SetBranchAddress("cl_cells_id", &_cl_cells_id);
    tree->SetBranchAddress("tc_z", &_tc_z);
    tree->SetBranchAddress("tc_id", &_tc_id);

    cout<<"n="<<nentries<<endl;
    //nentries = 1;

    for(int i=0;i<nentries;i++){

        if(i%100==0)
            cout<<"i="<<i<<endl;

            _gen_pdgid = 0;
            _gen_pt = 0;
            _gen_eta = 0;
            _gen_phi = 0;
            _gen_energy = 0;
        
            _cl_mipPt = 0;
            _cl_pt = 0;
            _cl_eta = 0;
            _cl_phi = 0;
            _cl_layer = 0;
            _cl_cells_id = 0;
            _tc_z = 0;
            _tc_id = 0;   

        tree->GetEntry(i);
 
	map<uint32_t,unsigned int> tc_map;
	for(unsigned int i_tc=0; i_tc<(*_tc_id).size(); i_tc++)
	    tc_map[(*_tc_id)[i_tc]] = i_tc;

        out<<i<<endl;
        out<<"0 ";
        for(unsigned int i_gen=0; i_gen<(*_gen_pdgid).size(); i_gen++){
            TLorentzVector gen_tlv;
            gen_tlv.SetPtEtaPhiE((*_gen_pt)[i_gen],(*_gen_eta)[i_gen],(*_gen_phi)[i_gen],(*_gen_energy)[i_gen]);
            if(gen_tlv.Eta()>0)
                out<<" "<<(*_gen_pdgid)[i_gen]<<" "<<gen_tlv.Px()<<" "<<gen_tlv.Py()<<" "<<gen_tlv.Pz()<<endl;
        }
        
        int n_c2d = 0;
        for(auto & eta : (*_cl_eta)){
            if(eta>0) n_c2d++;
        }
        out<<n_c2d<<endl;
        
	

        n_c2d = 0;
        for(unsigned int i_c2d=0;i_c2d<(*_cl_eta).size();i_c2d++){
            float eta = (*_cl_eta)[i_c2d];
            if(eta<0) continue;
            float z=(*_tc_z)[tc_map[(*_cl_cells_id)[i_c2d][0]]];
            float x=z/sinh(eta)*cos((*_cl_phi)[i_c2d]);
            float y=z/sinh(eta)*sin((*_cl_phi)[i_c2d]);
            out<<n_c2d<<" "<<(*_cl_layer)[i_c2d]<<" "<<x<<" "<<y<<" "<<(*_cl_mipPt)[i_c2d]<<" "<<(*_cl_pt)[i_c2d]<<endl;
            n_c2d++;
        }

 
        out<<"1 ";
        for(unsigned int i_gen=0; i_gen<(*_gen_pdgid).size(); i_gen++){
            TLorentzVector gen_tlv;
            gen_tlv.SetPtEtaPhiE((*_gen_pt)[i_gen],(*_gen_eta)[i_gen],(*_gen_phi)[i_gen],(*_gen_energy)[i_gen]);
            if(gen_tlv.Eta()<0)
                out<<" "<<(*_gen_pdgid)[i_gen]<<" "<<gen_tlv.Px()<<" "<<gen_tlv.Py()<<" "<<gen_tlv.Pz()<<endl;
        }
        
        n_c2d = 0;
        for(auto & eta : (*_cl_eta)){
            if(eta<0) n_c2d++;
        }
        out<<n_c2d<<endl;
        
        n_c2d = 0;
        for(unsigned int i_c2d=0;i_c2d<(*_cl_eta).size();i_c2d++){
            float eta = (*_cl_eta)[i_c2d];
            if(eta>0) continue;
            float z=(*_tc_z)[tc_map[(*_cl_cells_id)[i_c2d][0]]];
            float x=z/sinh(eta)*cos((*_cl_phi)[i_c2d]);
            float y=z/sinh(eta)*sin((*_cl_phi)[i_c2d]);
            out<<n_c2d<<" "<<(*_cl_layer)[i_c2d]<<" "<<x<<" "<<y<<" "<<(*_cl_mipPt)[i_c2d]<<" "<<(*_cl_pt)[i_c2d]<<endl;
            n_c2d++;
        }

    }


    return;

}
