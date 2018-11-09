#!/usr/bin/env python
import os, re
import commands
import math, time
import sys

print 
print 'START'
print 
########   YOU ONLY NEED TO FILL THE AREA BELOW   #########
########   customization  area #########
NumberOfJobs= 50
# number of jobs to be submitted
interval = 1 # number files to be processed in a single job, take care to split your file so that you run on all files. The last job might be with smaller number of files (the ones that remain).

#Single Gamma

# dir  = "SingleGammaPt25Eta1p6_2p8/crab_SingleGammaPt25_PU0-threshold/181031_145212/0000"
# dirout = "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25_PU0_threshold_1031/"
#dir  = "SingleGammaPt25Eta1p6_2p8/crab_SingleGammaPt25_PU0-stc/181031_145114/0000"
#dirout = "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25_PU0_stc_1031/"

#VBF

dir  = "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_threshold/181108_112741/0000"
dirout = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_threshold/"
# dir  = "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_stc/181108_104142/0000"
# dirout = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_stc/"

OutputFileNames = dirout + "jet_ntuples_merged/ntuple_jet_merged" # base of the output file name, they will be saved in res directory
ScriptName = "scripts/runJets.py" # script to be used with cmsRun
#FileList = "filelist.txt" # list with all the file directories
queue = "8nh" # give bsub queue -- 8nm (8 minutes), 1nh (1 hour), 8nh, 1nd (1day), 2nd, 1nw (1 week), 2nw 
########   customization end   #########

path = os.getcwd()
print
print 'do not worry about folder creation:'
os.system("rm -r " + dirout + "tmp")
os.system("mkdir -p " + dirout + "tmp")
os.system("mkdir -p " + dirout + "jet_ntuples_merged")
print

##### loop for creating and sending jobs #####
for x in range(1, int(NumberOfJobs)+1):
   ##### creates directory and file list for job #######
   os.system("mkdir "+dirout+"tmp/"+str(x))
   os.chdir(dirout+"tmp/"+str(x))
   #os.system("sed '"+str(1+interval*(x-1))+","+str(interval*x)+"!d' ../../"+FileList+" > list.txt ")
   
   ##### creates jobs #######
   with open('job.sh', 'w') as fout:



      fout.write("#!/bin/sh\n")
      fout.write("echo\n")
      fout.write("echo\n")
      fout.write("echo 'START---------------'\n")
      fout.write("echo 'WORKDIR ' ${PWD}\n")
      fout.write("cd /home/hep/snwebb/hgcal/CMSSW_10_1_7/src\n")
      fout.write("eval `scramv1 runtime -sh`\n")
      fout.write("cd /home/hep/snwebb/hgcal/HGC_macros\n")
#      fout.write("root -b -l <<EOF\n")
      fout.write("./jet_ntuple_merge --filein root://cms-xrd-global.cern.ch//store/user/sawebb/"+ dir + "/ntuple_"+str(x)+".root --filein_jet " + dirout+"/jet_ntuples/ntuple_jet_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
#      fout.write("add_jet(\"root://cms-xrd-global.cern.ch//store/user/sawebb/"+ dir + "/ntuple_"+str(x)+".root\",\"hgcalTriggerNtuplizer/HGCalTriggerNtuple\",\"" + dirout+"/jet_ntuples/ntuple_jet_"+str(x)+".root\",\"jets\",\""+OutputFileNames+"_"+str(x)+".root\");\n")      
 #     fout.write(".q\n")
  #    fout.write("EOF\n")
      fout.write("echo 'STOP---------------'\n")
      fout.write("echo\n")
      fout.write("echo\n")


#       fout.write("#!/bin/sh\n")
#       fout.write("echo\n")
#       fout.write("echo\n")
#       fout.write("echo 'START---------------'\n")
#       fout.write("echo 'WORKDIR ' ${PWD}\n")
#       fout.write("cd /home/hep/snwebb/hgcal/CMSSW_10_1_7/src\n")
#       fout.write("eval `scramv1 runtime -sh`\n")
# #      fout.write("export X509_USER_PROXY=/home/hep/tstreble/myVoms/x509up_u1255448\n")
#       fout.write("cd /home/hep/snwebb/hgcal/HGC_macros\n")
#       fout.write("root -b -l <<EOF\n")
#       fout.write(".L jet_ntuple_merger_v2.C+\n")
# #      fout.write("add_jet(\"" + dir + "/ntuples/ntuple_"+str(x)+".root\",\"hgcalTriggerNtuplizer/HGCalTriggerNtuple\",\""+dir+"/jet_ntuples/ntuple_jet_"+str(x)+".root\",\"jets\",\""+OutputFileNames+"_"+str(x)+".root\");\n")      
#       fout.write("add_jet(\"root://cms-xrd-global.cern.ch//store/user/sawebb/"+ dir + "/ntuple_"+str(x)+".root\",\"hgcalTriggerNtuplizer/HGCalTriggerNtuple\",\"" + dirout+"/jet_ntuples/ntuple_jet_"+str(x)+".root\",\"jets\",\""+OutputFileNames+"_"+str(x)+".root\");\n")      
#       fout.write(".q\n")
#       fout.write("EOF\n")
#       fout.write("echo 'STOP---------------'\n")
#       fout.write("echo\n")
#       fout.write("echo\n")
   os.system("chmod 755 job.sh")
   
   ###### sends bjobs ######
   #os.system("bsub -q "+queue+" -o logs job.sh")
   os.system("qsub -cwd -q hep.q -l h_vmem=12G -l h_rt=2:0:0 -l s_rt=1:50:0 job.sh")
   print "job nr " + str(x) + " submitted"
   
   os.chdir("../..")
   
print
print "your jobs:"
os.system("qstat")
print
print 'END'
print
