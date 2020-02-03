#!/usr/bin/env python
import ROOT
import numpy as np
import sys

num = str(sys.argv[1])

chain = ROOT.TChain("hgcalTriggerNtuplizer/HGCalTriggerNtuple")
chain.Add("/vols/cms/snwebb/HGC_ntuples/DoubleNu/ntuple_"+num+".root")

chain.SetBranchStatus("*",0) 
chain.SetBranchStatus("tc_y",1)
chain.SetBranchStatus("tc_x",1)
chain.SetBranchStatus("tc_pt",1)
chain.SetBranchStatus("tc_eta",1)
#infile = ROOT.TFile("/vols/cms/snwebb/HGC_ntuples/DoubleNu/ntuple_1*.root","READ")

#tree = infile.Get("hgcalTriggerNtuplizer/HGCalTriggerNtuple")

#c = ROOT.TCanvas()
# hist1p = ROOT.TH1D("hist0p","",8000,0,8000)
# hist2p = ROOT.TH1D("hist120p","",8000,0,8000)
# hist3p = ROOT.TH1D("hist240p","",8000,0,8000)

# hist1n = ROOT.TH1D("hist0n","",8000,0,8000)
# hist2n = ROOT.TH1D("hist120n","",8000,0,8000)
# hist3n = ROOT.TH1D("hist240na","",8000,0,8000)

histtot = ROOT.TH1D("histtot","",8000,0,8000)


# hist = ROOT.TH1D("hist1","",360,0,360)
for j,entry in enumerate(chain):

    count1p = 0
    count2p = 0
    count3p = 0
    count1n = 0
    count2n = 0
    count3n = 0

    for i in range(len(entry.tc_y)):
        
        angle = 180+(180/np.pi)*np.arctan2(entry.tc_y[i],entry.tc_x[i])
        #        angle = 150

        if ( entry.tc_eta[i] > 0 ):
            if ( angle >= 0 and angle < 120):
                count1p+=1
            elif ( angle >= 120 and angle < 240):
                count2p+=1
            elif ( angle >= 240 and angle < 360):
                count3p+=1

        elif ( entry.tc_eta[i] <= 0 ):
            if ( angle >= 0 and angle < 120):
                count1n+=1
            elif ( angle >= 120 and angle < 240):
                count2n+=1
            elif ( angle >= 240 and angle < 360):
                count3n+=1

    # hist1p.Fill (count1p)
    # hist2p.Fill (count2p)
    # hist3p.Fill (count3p)
    # hist1n.Fill (count1n)
    # hist2n.Fill (count2n)
    # hist3n.Fill (count3n)
                               
    histtot.Fill (count1p)
    histtot.Fill (count2p)
    histtot.Fill (count3p)
    histtot.Fill (count1n)
    histtot.Fill (count2n)
    histtot.Fill (count3n)

    # print (j)
    # if (j>100): 
    #      break


outfile = ROOT.TFile("outhist_tcs_"+num+".root","RECREATE")
# hist1p.Write()
# hist2p.Write()
# hist3p.Write()
# hist1n.Write()
# hist2n.Write()
# hist3n.Write()
histtot.Write()
outfile.Close()
