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

#WORKSHOP

#V9 (DEFAULT CLUSTER RADIUS)
#"VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-Threshold/190610_093502/0000",
#  "VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-SuperTCs/190610_093658/0000",
#   "VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-SeedThreshold/190610_093753/0000",
#   "VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-ClusterRadius/190610_093841/0000",
#"VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-Default-WithTriggerCells/190610_120552/0000",

#V8 (DEFAULT CLUSTER RADIUS)
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-Threshold/190610_142648/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-SuperTCs/190610_142730/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-SeedThreshold/190610_142831/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-ClusterRadius/190610_142908/0000",
"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-Default-WithTriggerCells/190610_143015/0000",

#V9 (EXTENDED CLUSTER RADIUS)
# "VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-Threshold-DR1p75/190610_160411/0000",
# "VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-SuperTCs-DR1p75/190610_160541/0000",
# "VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-SeedThreshold-DR1p75/190610_161108/0000",


#V8 (EXTENDED CLUSTER RADIUS)
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-Threshold-DR1p75/190610_161427/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-SuperTCs-DR1p75/190610_161652/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-SeedThreshold-DR1p75/190610_161347/0000",




#V9 HGG (DEFAULT CLUSTER RADIUS)
#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-Threshold/190612_085552/0000",



#WS




#"VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-Threshold-WS/190614_103104/0000",
#    "VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-SuperTCs-WS/190614_103316/0000",
# "VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-SeedThreshold-WS/190614_103718/0000",
# "VBFHToGG_M-125_14TeV_powheg_pythia8/crab_VBF-HGG-PU200-MultiAlgo-ClusterRadius-WS/190614_103923/0000",

#"VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-Threshold-WS/190614_103007/0000",
#   "VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-SuperTCs-WS/190614_103237/0000",
# "VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-SeedThreshold-WS/190614_103645/0000",
#"VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-MultiAlgo-ClusterRadius-WS/190614_103833/0000",




#"VBFHToTauTau_M125_14TeV_powheg_pythia8/crab_VBF-HTT-PU200-Default-WithTriggerCells-WS/190614_132424/0000",



#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-Threshold-WS/190617_142337/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-SuperTCs-WS/190617_155355/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-SeedThreshold-WS/190617_155622/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-MultiAlgo-ClusterRadius-WS/190617_/0000",


   ]
OutputDirList1=[  i.split("/")[1] for i in InputDirList ]
OutputDirList=[  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/" + i.split("_")[1] for i in OutputDirList1 ]
#OutputDirList=[  "/vols/cms/snwebb/HGC_ntuples/VBF_HGG/" + i.split("_")[1] for i in OutputDirList1 ]
#OutputDirList=[  "/vols/cms/snwebb/HGC_ntuples/VBF_HTT/" + i.split("_")[1] for i in OutputDirList1 ]



#ScriptName = "scripts/runJets.py" # script to be used with cmsRun
#FileList = "filelist.txt" # list with all the file directories
#queue = "8nh" # give bsub queue -- 8nm (8 minutes), 1nh (1 hour), 8nh, 1nd (1day), 2nd, 1nw (1 week), 2nw 
########   customization end   #########



#TreeNames = ["hgcalTriggerNtuplizer"]



TreeNames = [
#THRESHOLD
# "Fp8Threshold0p0DummyHistomaxvardrth10Ntup",
# #"Fp8Threshold0p5DummyHistomaxvardrth10Ntup",
# "Fp8Threshold1p0DummyHistomaxvardrth10Ntup",
# #"Fp8Threshold1p5DummyHistomaxvardrth10Ntup",
# "Fp8Threshold2p0DummyHistomaxvardrth10Ntup",
# "Fp8Threshold3p0DummyHistomaxvardrth10Ntup",
#THRESHOLD EXTENDED
# "Fp8Threshold0p0DummyHistomaxvardrdrho1p75Ntup",
# "Fp8Threshold0p5DummyHistomaxvardrdrho1p75Ntup",
# "Fp8Threshold1p0DummyHistomaxvardrdrho1p75Ntup",
# "Fp8Threshold1p5DummyHistomaxvardrdrho1p75Ntup",
# "Fp8Threshold2p0DummyHistomaxvardrdrho1p75Ntup",
# "Fp8Threshold3p0DummyHistomaxvardrdrho1p75Ntup",

   # "Fp8Threshold0p0DummyHistomaxvardrdrho1p0Ntup",
   # "Fp8Threshold0p5DummyHistomaxvardrdrho1p0Ntup",
   # "Fp8Threshold1p0DummyHistomaxvardrdrho1p0Ntup",
   # "Fp8Threshold1p5DummyHistomaxvardrdrho1p0Ntup",
   # "Fp8Threshold2p0DummyHistomaxvardrdrho1p0Ntup",
   # "Fp8Threshold3p0DummyHistomaxvardrdrho1p0Ntup",

#SUPER TC
# "Fp8BestchoiceDummyHistomaxvardrth10Ntup",
# "Fp8Stc4161616DummyHistomaxvardrth10Ntup",
# "Fp8Stc4444FixedDummyHistomaxvardrth10Ntup",
# "Fp8EqualShare4444FixedDummyHistomaxvardrth10Ntup",
# "Fp8Onebit4444FixedDummyHistomaxvardrth10Ntup",

#SUPER TC EXTENDED
# "Fp8BestchoiceDummyHistomaxvardrdrho1p75Ntup",
# "Fp8Stc4161616DummyHistomaxvardrdrho1p75Ntup",
# "Fp8Stc4444FixedDummyHistomaxvardrdrho1p75Ntup",
# "Fp8EqualShare4444FixedDummyHistomaxvardrdrho1p75Ntup",
#"Fp8Onebit4444FixedDummyHistomaxvardrdrho1p75Ntup",

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


#DEFAULT
"hgcalTriggerNtuplizer",





#NEW




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
# "Fp8Stc4444FixedDummyHistomaxvardrdrho1p0Ntup",
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
