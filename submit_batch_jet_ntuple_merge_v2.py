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
#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU0-BestChoice-CoarserInH-Fix/191003_164218/0000",
#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-SuperTC-Old/191004_084722/0000",
#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-SuperTC-Validation/191004_083722/0000",
#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-SuperTC-SignalDriven/191028_142710/0000",

#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-SuperTC-ScintillatorStudies/191031_115118/0000",

#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-Standard/191114_072918/0000",
#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-Standard/191115_164927/0000",

#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-BestChoice-CoarserInH/191127_100629/0000",
#
#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-BestChoice-Coarse/191217_155430/0000",
#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-BestChoice-Coarse/191217_134059/0000",


#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-OOP/191220_104900/0000",
#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-OOP/191220_104729/0000",


"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-OOP-LargerDR/200107_111137/0000",
#"NeutrinoGun_E_10GeV/crab_DoubleNu-PU200-OOP-LargerDR/200107_111003/0000",



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

 # "Fp8ThresholdDummyHistomaxNtup",
 # "Fp8Stc4161616DummyHistomaxNtup",
 # "Fp8BestchoiceDummyHistomaxNtup",
 # "Fp8MixedDummyHistomaxNtup",
   
 #   "Fp8BestchoiceDummyHistomaxNtup",
 #   "Fp8BestchoiceCoarse1DummyHistomaxNtup",
 #   "Fp8BestchoiceCoarse2DummyHistomaxNtup",
 #   "Fp8BestchoiceCoarse4DummyHistomaxNtup",
 #   "Fp8BestchoiceCoarse8DummyHistomaxNtup",
#   "Fp8BestchoiceCoarse16DummyHistomaxNtup",


#OOT from JB
# "NoOOTThresholdDummyHistomaxxydr015GenmatchGenclustersntuple",
# "NoOOTMixedbcstcDummyHistomaxxydr015GenmatchGenclustersntuple",
# "OOT1ThresholdDummyHistomaxxydr015GenmatchGenclustersntuple",
# "OOT1MixedbcstcDummyHistomaxxydr015GenmatchGenclustersntuple",
# "OOT2ThresholdDummyHistomaxxydr015GenmatchGenclustersntuple",
# "OOT2MixedbcstcDummyHistomaxxydr015GenmatchGenclustersntuple",
"NoOOTThresholdDummyHistomaxxydr015Genclustersntuple",
"NoOOTMixedbcstcDummyHistomaxxydr015Genclustersntuple",
"OOT1ThresholdDummyHistomaxxydr015Genclustersntuple",
"OOT1MixedbcstcDummyHistomaxxydr015Genclustersntuple",
"OOT2ThresholdDummyHistomaxxydr015Genclustersntuple",
"OOT2MixedbcstcDummyHistomaxxydr015Genclustersntuple",

#DEFAULT
#"hgcalTriggerNtuplizer",

# "Fp8StcSigDriv1DummyHistomaxNtup",
# "Fp8StcSigDriv2DummyHistomaxNtup",
# "Fp8StcSigDriv3DummyHistomaxNtup",

# "Fp8Stc416164DummyHistomaxNtup",
# "Fp8Stc416164CoarseDummyHistomaxNtup",
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
            fout.write("./jet_ntuple_merge --runtype jet --filein root://gfe02.grid.hep.ph.ic.ac.uk:1096//store/user/sawebb/"+ indir + "/ntuple_"+str(x)+".root --treename "+ treename +"/HGCalTriggerNtuple --treename_out "+ treename +"_Jet --filein_jet " + outdir+"/jet_ntuples/ntuple_jet_"+treename+"_"+str(x)+".root --treename_jet jets_" + treename +" --fileout " + OutputFileNames +"_"+str(x)+".root \n")
            fout.write("echo 'STOP---------------'\n")
            fout.write("echo\n")
            fout.write("echo\n")

         os.system("chmod 755 " + jobname)
      
         ###### sends bjobs ######
         # os.system("bsub -q "+queue+" -o logs job.sh")
         os.system("qsub -cwd -q hep.q -l h_vmem=8G -l s_vmem=7.5G -l h_rt=2:0:0 -l s_rt=1:50:0 " + jobname)
         print "job nr " + str(x) + " submitted"
            
#         os.chdir("../..")
   
print
print "your jobs:"
os.system("qstat")
print
print 'END'
print
