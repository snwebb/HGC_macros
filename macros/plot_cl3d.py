import ROOT
import numpy as np

#infile = ROOT.TFile("/vols/cms/snwebb/HGC_ntuples/DoubleNu/ntuple_1.root","READ")

chain = ROOT.TChain("hgcalTriggerNtuplizer/HGCalTriggerNtuple")
# for i in range 10:
#     chain.Add("/vols/cms/snwebb/HGC_ntuples/DoubleNu/ntuple_"+str(i)+".root")

chain.Add("/vols/cms/snwebb/HGC_ntuples/DoubleNu/ntuple_*.root")
#tree = infile.Get("hgcalTriggerNtuplizer/HGCalTriggerNtuple")

#c = ROOT.TCanvas()
hist1p = ROOT.TH1D("hist0p","",200,0,200)
hist2p = ROOT.TH1D("hist120p","",200,0,200)
hist3p = ROOT.TH1D("hist240p","",200,0,200)

hist1n = ROOT.TH1D("hist0n","",200,0,200)
hist2n = ROOT.TH1D("hist120n","",200,0,200)
hist3n = ROOT.TH1D("hist240na","",200,0,200)

histtot = ROOT.TH1D("histtot","",200,0,200)

for j,entry in enumerate(chain):

    count1p = 0
    count2p = 0
    count3p = 0
    count1n = 0
    count2n = 0
    count3n = 0

    for i in range(len(entry.cl3d_phi)):

        if ( entry.cl3d_pt[i] < 1.0):
            continue;

        angle = 180+(entry.cl3d_phi[i]*(180/np.pi))

        if ( entry.cl3d_eta[i] > 0 ):

            if ( angle >= 0 and angle < 120):
                count1p+=1
            elif ( angle >= 120 and angle < 240):
                count2p+=1
            elif ( angle >= 240 and angle < 360):
                count3p+=1

        elif ( entry.cl3d_eta[i] <= 0 ):
            if ( angle >= 0 and angle < 120):
                count1n+=1
            elif ( angle >= 120 and angle < 240):
                count2n+=1
            elif ( angle >= 240 and angle < 360):
                count3n+=1

    hist1p.Fill (count1p)
    hist2p.Fill (count2p)
    hist3p.Fill (count3p)
    hist1n.Fill (count1n)
    hist2n.Fill (count2n)
    hist3n.Fill (count3n)

    histtot.Fill (count1p)
    histtot.Fill (count2p)
    histtot.Fill (count3p)
    histtot.Fill (count1n)
    histtot.Fill (count2n)
    histtot.Fill (count3n)


    # if (j>10): 
    #     break


outfile = ROOT.TFile("outhist_cl3d_all.root","RECREATE")
hist1p.Write()
hist2p.Write()
hist3p.Write()
hist1n.Write()
hist2n.Write()
hist3n.Write()
histtot.Write()
outfile.Close()
