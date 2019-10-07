#!/usr/bin/env python
import os, re, subprocess
import commands
import math, time
import sys

print 
print 'START'
print 
########   YOU ONLY NEED TO FILL THE AREA BELOW   #########
########   customization  area #########
NumberOfJobs= 100
# number of jobs to be submitted
interval = 1 # number files to be processed in a single job, take care to split your file so that you run on all files. The last job might be with smaller number of files (the ones that remain).

InputDirList = [ 

#V8 (EXTENDED CLUSTER RADIUS)
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-Threshold-DR1p75/190610_161427/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-SuperTCs-DR1p75/190610_161652/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-SeedThreshold-DR1p75/190610_161347/0000",

#V9 HGG (DEFAULT CLUSTER RADIUS)
#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-Threshold/190612_085552/0000",

#WS

#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-Threshold-WS/190614_103104/0000",
#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-SuperTCs-WS/190614_103316/0000",
# "VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-SeedThreshold-WS/190614_103718/0000",
# "VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-ClusterRadius-WS/190614_103923/0000",

#"VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-Threshold-WS/190614_103007/0000",
#   "VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-SuperTCs-WS/190614_103237/0000",
# "VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-SeedThreshold-WS/190614_103645/0000",
#"VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-ClusterRadius-WS/190614_103833/0000",

#"VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-Default-WithTriggerCells-WS/190614_132424/0000",

#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-Decentralised/190709_130200/0000",
#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-MultiAlgo-Decentralised/190709_130228/0000",


#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-Decentralised/190717_141103/0000",
#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-MultiAlgo-Decentralised/190717_141958/0000",

#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-Threshold-WS/190617_142337/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-SuperTCs-WS/190617_155355/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-SeedThreshold-WS/190617_155622/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-ClusterRadius-WS/190617_/0000",


#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-Decentralised-BugFix/190718_161801/0000",
#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-MultiAlgo-Decentralised-BugFix/190718_161654/0000",


#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-Default/190726_142831/0000",
#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-Decentralised/190730_112632/0000",

#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-Decentralised/190731_092913/0000",

#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-Decentralised-SignalDriven/190822_123250/0000",
#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-Decentralised-SignalDriven/190905_140242/0000",


#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-Default-withTCs/190822_132142/0000",
#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-Default-withTCs/190916_134011/0000",


# "RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_QuarkGun-Neg-PU0-Decentralised/190802_100839/0000",
# "RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_QuarkGun-Neg-PU140-Decentralised/190802_100807/0000",
# "RelValDiQ_Pt20To300_Etam1p6Tom2p9/crab_QuarkGun-Neg-PU200-Decentralised/190802_100732/0000",
# "RelValDiQ_Pt20To300_Eta1p6To2p9/crab_QuarkGun-Pos-PU0-Decentralised/190802_100704/0000",
# "RelValDiQ_Pt20To300_Eta1p6To2p9/crab_QuarkGun-Pos-PU140-Decentralised/190802_100633/0000",
# "RelValDiQ_Pt20To300_Eta1p6To2p9/crab_QuarkGun-Pos-PU200-Decentralised/190802_100555/0000",


#SIGNAL DRIVEN
# "RelValDiQ_Pt20To300_Eta1p6To2p9/crab_QuarkGun-Pos-PU0-Decentralised/190924_151910/0000",
# "RelValDiQ_Pt20To300_Eta1p6To2p9/crab_QuarkGun-Pos-PU140-Decentralised/190924_151840/0000",
# "RelValDiQ_Pt20To300_Eta1p6To2p9/crab_QuarkGun-Pos-PU200-Decentralised/190924_151710/0000",
# "RelValDiQ_Pt20To300_Eta1p6To2p9/crab_QuarkGun-Pos-PU0-Decentralised/190926_093004/0000",
# "RelValDiQ_Pt20To300_Eta1p6To2p9/crab_QuarkGun-Pos-PU140-Decentralised/190926_093906/0000",
# "RelValDiQ_Pt20To300_Eta1p6To2p9/crab_QuarkGun-Pos-PU200-Decentralised/190926_093951/0000",



#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MixedFE-EM/190927_143347/0000",

#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-BestChoice-Coarser/191002_102809/0000",


"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU0-BestChoice-CoarserInH-Fix/191003_164218/0000",

   ]

Tag = "-DR0p2"
#Tag = ""
OutputDirList1=[  i.split("/")[1] for i in InputDirList ]
#OutputDirList=[  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/" + i.split("_")[1] for i in OutputDirList1 ]
#OutputDirList=[  "/vols/cms/snwebb/HGC_ntuples/VBF_HTT/" + i.split("_")[1] for i in OutputDirList1 ]
#OutputDirList=[  "/vols/cms/snwebb/HGC_ntuples/QuarkGun/" + i.split("_")[1] +Tag for i in OutputDirList1 ]


OutputDirList=[  "/vols/cms/snwebb/HGC_ntuples/VBF_HGG/" + i.split("_")[1] + Tag for i in OutputDirList1 ]
#OutputDirList=[  "/vols/cms/snwebb/HGC_ntuples/DoubleNu/" + i.split("_")[1] + Tag for i in OutputDirList1 ]



#ScriptName = "scripts/runJets.py" # script to be used with cmsRun
#FileList = "filelist.txt" # list with all the file directories
#queue = "8nh" # give bsub queue -- 8nm (8 minutes), 1nh (1 hour), 8nh, 1nd (1day), 2nd, 1nw (1 week), 2nw 
########   customization end   #########





TreeNames = [
#SEED THRESHOLD

# "Fp8ThresholdDummyHistomaxvardrth0Ntup",
# "Fp8ThresholdDummyHistomaxvardrth10Ntup",
# "Fp8ThresholdDummyHistomaxvardrth20Ntup",
# "Fp8ThresholdDummyHistomaxvardrth30Ntup",
# "Fp8ThresholdDummyHistomaxvardrth40Ntup",
# "Fp8ThresholdDummyHistomaxvardrth50Ntup",



#"Fp8ThresholdDummyHistomaxvardrth100Ntup",


#DRHO

# "Fp8ThresholdDummyHistomaxvardrdrho1p0Ntup",
# "Fp8ThresholdDummyHistomaxvardrdrho1p25Ntup",
# "Fp8ThresholdDummyHistomaxvardrdrho1p5Ntup",
# "Fp8ThresholdDummyHistomaxvardrdrho1p75Ntup",
# "Fp8ThresholdDummyHistomaxvardrdrho2p0Ntup",
# "Fp8ThresholdDummyHistomaxvardrdrho3p0Ntup",
# "Fp8ThresholdDummyHistomaxvardrdrho5p0Ntup",

#THRESHOLD
# "Fp8Threshold0p0DummyHistomaxvardrdrho1p0Ntup",
# # "Fp8Threshold0p5DummyHistomaxvardrdrho1p0Ntup",
# "Fp8Threshold1p0DummyHistomaxvardrdrho1p0Ntup",
# # "Fp8Threshold1p5DummyHistomaxvardrdrho1p0Ntup",
# "Fp8Threshold2p0DummyHistomaxvardrdrho1p0Ntup",
# "Fp8Threshold3p0DummyHistomaxvardrdrho1p0Ntup",

#SUPER TC

# "Fp8BestchoiceDummyHistomaxvardrdrho1p0Ntup",
# "Fp8Stc4161616DummyHistomaxvardrdrho1p0Ntup",
#"Fp8Stc4444FixedDummyHistomaxvardrdrho1p0Ntup",
# "Fp8EqualShare4444FixedDummyHistomaxvardrdrho1p0Ntup",
# "Fp8Onebit4444FixedDummyHistomaxvardrdrho1p0Ntup",

#SEED THRESHOLD

#  "Fp8ThresholdDummyHistomaxvardrth0Ntup",
#  "Fp8ThresholdDummyHistomaxvardrth10Ntup",
#  "Fp8ThresholdDummyHistomaxvardrth20Ntup",
# # "Fp8ThresholdDummyHistomaxvardrth30Ntup",
#  "Fp8ThresholdDummyHistomaxvardrth40Ntup",
# # "Fp8ThresholdDummyHistomaxvardrth50Ntup",


# #DRHO

# "Fp8ThresholdDummyHistomaxvardrdrho1p0Ntup",
# # "Fp8ThresholdDummyHistomaxvardrdrho1p25Ntup",
# "Fp8ThresholdDummyHistomaxvardrdrho1p5Ntup",
# # "Fp8ThresholdDummyHistomaxvardrdrho1p75Ntup",
# "Fp8ThresholdDummyHistomaxvardrdrho2p0Ntup",
# # "Fp8ThresholdDummyHistomaxvardrdrho3p0Ntup",
# "Fp8ThresholdDummyHistomaxvardrdrho5p0Ntup",



# "Fp8ThresholdDummyHistomaxNtup",
# "Fp8Stc4444FixedDummyHistomaxNtup",
# "Fp8BestchoiceDummyHistomaxNtup",


# "Fp8ThresholdDummyHistomaxNtup",
# "Fp8Stc4161616DummyHistomaxbin4Ntup",
# "Fp8BestchoiceDummyHistomaxNtup",

# "Fp8ThresholdDummyHistomaxNtup",
# "Fp8Stc4161616DummyHistomaxNtup",
# "Fp8BestchoiceDummyHistomaxNtup",

# "Fp8MixedDummyHistomaxNtup",

"Fp8BestchoiceDummyHistomaxNtup",
"Fp8BestchoiceCoarse1DummyHistomaxNtup",
"Fp8BestchoiceCoarse2DummyHistomaxNtup",
"Fp8BestchoiceCoarse4DummyHistomaxNtup",
"Fp8BestchoiceCoarse8DummyHistomaxNtup",
"Fp8BestchoiceCoarse16DummyHistomaxNtup",

#DEFAULT
#"hgcalTriggerNtuplizer",

 ]






##### loop for creating and sending jobs #####
for indir, outdir in zip( InputDirList, OutputDirList ):
   path = os.getcwd()
   print
   print 'do not worry about folder creation:'
   os.system("rm -r " + outdir + "/tmp")
   os.system("mkdir -p " + outdir + "/tmp")
   os.system("mkdir -p " + outdir + "/jet_ntuples_merged")
   if subprocess.call(["voms-proxy-info",'--exists']) == 1:
      print "Voms proxy does not exist:"
      os.system("voms-proxy-init -voms cms -valid 96:00")
   else:
      print "Voms proxy exists"
   print

   os.system("mkdir "+outdir+"/tmp/")
   os.chdir(outdir+"/tmp/")
   
   for treename in TreeNames:
##### loop for creating and sending jobs #####
      OutputFileNames = outdir + "/jet_ntuples_merged/ntuple_jet_merged_" + treename # base of the output file name, they will be saved in res directory
      for x in range(1, int(NumberOfJobs)+1):
         ##### creates directory and file list for job #######
#         os.system("mkdir "+outdir+"/tmp/"+str(x))
         #os.system("sed '"+str(1+interval*(x-1))+","+str(interval*x)+"!d' ../../"+FileList+" > list.txt ")
   
         ##### creates jobs #######
         jobname = treename+'_job_'+str(x)+'.sh'
         with open(jobname, 'w') as fout:                  
         
            fout.write("#!/bin/sh\n")
            fout.write("echo\n")
            fout.write("echo\n")
            fout.write("ulimit -c 0\n")
            fout.write("echo 'START---------------'\n")
            fout.write("echo 'WORKDIR ' ${PWD}\n")

            fout.write("trap \"echo SIGINT seen\"  SIGINT\n")
            fout.write("trap \"echo SIGUSR1 seen\" SIGUSR1\n")
            fout.write("trap \"echo SIGUSR2 seen\" SIGUSR2\n")
            fout.write("trap \"echo SIGTERM seen\" SIGTERM\n")
            fout.write("trap \"echo SIGXCPU seen\" SIGXCPU\n")
            
            fout.write("cd /home/hep/snwebb/hgcal/CMSSW_10_1_7/src\n")
            fout.write("eval `scramv1 runtime -sh`\n")
            fout.write("cd /home/hep/snwebb/hgcal/HGC_macros\n")
            #         fout.write("./jet_ntuple_merge --runtype jet --filein root://cms-xrd-global.cern.ch//store/user/sawebb/"+ indir + "/ntuple_"+str(x)+".root --filein_jet " + outdir+"/jet_ntuples/ntuple_jet_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
            fout.write("./jet_ntuple_merge --runtype jet --filein root://gfe02.grid.hep.ph.ic.ac.uk:1096//store/user/sawebb/"+ indir + "/ntuple_"+str(x)+".root --treename "+ treename +"/HGCalTriggerNtuple --treename_out "+ treename +"_Jet --filein_jet " + outdir+"/jet_ntuples/ntuple_jet_"+treename+"_"+str(x)+".root --treename_jet jets_" + treename +" --fileout " + OutputFileNames +"_"+str(x)+".root \n")


#            fout.write("./jet_ntuple_merge --runtype jet --filein root://gfe02.grid.hep.ph.ic.ac.uk:1096//store/user/sawebb/"+ indir + "/ntuple_"+str(x)+".root --treename "+ treename +"/HGCalTriggerNtuple --treename_out "+ treename +"_Jet --filein_jet " + outdir+"/jet_ntuples/ntuple_jet_hgcalTriggerNtuplizer_"+str(x)+".root --treename_jet jets_" + treename + " --fileout " + OutputFileNames +"_"+str(x)+".root \n")
            fout.write("echo 'STOP---------------'\n")
            fout.write("echo\n")
            fout.write("echo\n")

         os.system("chmod 755 " + jobname)
      
         ###### sends bjobs ######
         #os.system("bsub -q "+queue+" -o logs job.sh")
         os.system("qsub -cwd -q hep.q -l h_vmem=8G -l s_vmem=7.5G -l h_rt=2:0:0 -l s_rt=1:50:0 " + jobname)
         print "job nr " + str(x) + " submitted"
            
#         os.chdir("../..")
   
print
print "your jobs:"
os.system("qstat")
print
print 'END'
print
