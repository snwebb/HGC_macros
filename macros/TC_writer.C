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

void write_TCs(vector<TString> filename, TString treename,
	       TString fileout, int nevents=-1){


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
    
    vector<float>* _tc_mipPt;
    vector<float>* _tc_pt;
    vector<float>* _tc_eta;
    vector<float>* _tc_x;
    vector<float>* _tc_y;
    vector<int>* _tc_layer;
    
    tree->SetBranchAddress("gen_pdgid", &_gen_pdgid);
    tree->SetBranchAddress("gen_pt", &_gen_pt);
    tree->SetBranchAddress("gen_eta", &_gen_eta);
    tree->SetBranchAddress("gen_phi", &_gen_phi);
    tree->SetBranchAddress("gen_energy", &_gen_energy);
    
    tree->SetBranchAddress("tc_mipPt", &_tc_mipPt);
    tree->SetBranchAddress("tc_pt", &_tc_pt);
    tree->SetBranchAddress("tc_eta", &_tc_eta);
    tree->SetBranchAddress("tc_x", &_tc_x);
    tree->SetBranchAddress("tc_y", &_tc_y); 
    tree->SetBranchAddress("tc_layer", &_tc_layer); 

    cout<<"n="<<nentries<<endl;
    //nentries = 1;
    if(nevents>0)
      nentries = min(nevents,nentries);

    for(int i=0;i<nentries;i++){

        if(i%100==0)
            cout<<"i="<<i<<endl;

	_gen_pdgid = 0;
	_gen_pt = 0;
	_gen_eta = 0;
	_gen_phi = 0;
	_gen_energy = 0;
        
	_tc_mipPt = 0;
	_tc_pt = 0;
	_tc_eta = 0;
	_tc_x = 0;
	_tc_y = 0;
	_tc_layer = 0;
        
        tree->GetEntry(i);
 
        out<<i<<endl;
        out<<"0 ";	
        for(unsigned int i_gen=0; i_gen<(*_gen_pdgid).size(); i_gen++){
            TLorentzVector gen_tlv;
            gen_tlv.SetPtEtaPhiE((*_gen_pt)[i_gen],(*_gen_eta)[i_gen],(*_gen_phi)[i_gen],(*_gen_energy)[i_gen]);
            if(gen_tlv.Eta()>0)
	      out<<" "<<(*_gen_pdgid)[i_gen]<<" "<<gen_tlv.Px()<<" "<<gen_tlv.Py()<<" "<<gen_tlv.Pz();
        }
	out<<endl;

        int n_tc = 0;
        for(auto & eta : (*_tc_eta)){
            if(eta>0) n_tc++;
        }
        out<<n_tc<<endl;
        	
	
        n_tc = 0;
        for(unsigned int i_tc=0;i_tc<(*_tc_eta).size();i_tc++){
	  float eta = (*_tc_eta)[i_tc];
	  if(eta<0) continue;
	  float x=(*_tc_x)[i_tc];
	  float y=(*_tc_y)[i_tc];
	  out<<n_tc<<" "<<(*_tc_layer)[i_tc]<<" "<<x<<" "<<y<<" "<<(*_tc_mipPt)[i_tc]<<" "<<(*_tc_pt)[i_tc]<<endl;
	  n_tc++;
	}

 
        out<<"1 ";
        for(unsigned int i_gen=0; i_gen<(*_gen_pdgid).size(); i_gen++){
            TLorentzVector gen_tlv;
            gen_tlv.SetPtEtaPhiE((*_gen_pt)[i_gen],(*_gen_eta)[i_gen],(*_gen_phi)[i_gen],(*_gen_energy)[i_gen]);
            if(gen_tlv.Eta()<0)
                out<<" "<<(*_gen_pdgid)[i_gen]<<" "<<gen_tlv.Px()<<" "<<gen_tlv.Py()<<" "<<gen_tlv.Pz();
        }
	out<<endl;	

	n_tc = 0;
        for(auto & eta : (*_tc_eta)){
	  if(eta<0) n_tc++;
        }
        out<<n_tc<<endl;
        	
	
        n_tc = 0;
        for(unsigned int i_tc=0;i_tc<(*_tc_eta).size();i_tc++){
	  float eta = (*_tc_eta)[i_tc];
	  if(eta>0) continue;
	  float x=(*_tc_x)[i_tc];
	  float y=(*_tc_y)[i_tc];
	  out<<n_tc<<" "<<(*_tc_layer)[i_tc]<<" "<<x<<" "<<y<<" "<<(*_tc_mipPt)[i_tc]<<" "<<(*_tc_pt)[i_tc]<<endl;
	  n_tc++;
	}

    }


    return;

}
