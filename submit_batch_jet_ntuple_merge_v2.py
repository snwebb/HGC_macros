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

#Single Gamma

# dir  = "SingleGammaPt25Eta1p6_2p8/crab_SingleGammaPt25_PU0-threshold/181031_145212/0000"
# dirout = "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25_PU0_threshold_1031/"
#dir  = "SingleGammaPt25Eta1p6_2p8/crab_SingleGammaPt25_PU0-stc/181031_145114/0000"
#dirout = "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25_PU0_stc_1031/"

# dir  = "SingleGammaPt25Eta1p6_2p8/crab_SingleGamma-PU0-threshold-TCs-histoMax-DR03/181121_113118/0000"
# dirout = "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25/SingleGammaPt25_PU0_threshold_HistoMax/"
# dir  = "SingleGammaPt25Eta1p6_2p8/crab_SingleGamma-PU0-stc-TCs-histoMax-DR03/181121_113207/0000"
# dirout = "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25/SingleGammaPt25_PU0_stc_HistoMax/"
# dir  = "SingleGammaPt25Eta1p6_2p8/crab_SingleGamma-PU200-threshold-TCs-histoMax-DR03/181121_115525/0000"
# dirout = "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25/SingleGammaPt25_PU200_threshold_HistoMax/"
# dir  = "SingleGammaPt25Eta1p6_2p8/crab_SingleGamma-PU200-stc-TCs-histoMax-DR03/181121_115450/0000"
# dirout = "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25/SingleGammaPt25_PU200_stc_HistoMax/"

#VBF

# dir  = "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_threshold/181108_112741/0000"
# dirout = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_threshold/"
# dir  = "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_stc/181108_104142/0000"
# dirout = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv_stc/"

#Histomax algorithm
#dir  = "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_threshold-histoMax/181113_145731/0000"
#dirout = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU0_threshold_polarHisto_Max/"

#dir = "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_PU200-threshold-TCs-histoInterpolated1stOrder-DR03/181120_144304/0000"
#dir = "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_PU200-stc-TCs-histoInterpolated1stOrder-DR03/181120_144350/0000"
#dir = "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_PU200-thresold-TCs-histoInterpolated2ndOrder-DR03/181120_144511/0000"
#dir = "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_PU200-stc-TCs-histoInterpolated2ndOrder-DR03/181120_144618/0000"
#dirout = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Interpolated1stOrder"
#dirout = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated1stOrder"
#dirout = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Interpolated2ndOrder"
#dirout = "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated2ndOrder"

InputDirList = [ 
#   "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoMax-DR03/181126_114617/0000"
#   "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-DR03/181126_132117/0000",

#    "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoInterpolatedMax1stOrder-DR03/181126_114758/0000",
#    "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolatedMax1stOrder-DR03/181126_131953/0000",
   
#   "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoInterpolatedMax2ndOrder-DR03/181126_114720/0000",
 #   "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolatedMax2ndOrder-DR03/181126_132033/0000",
   
#    "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoModifiedMax-DR03/181126_132731/0000",
#   "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoModifiedMax-DR03/181126_132622/0000",

"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-0mipt-DR03-NS/181207_091543/0000",
 # "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DR03-NS/181207_091637/0000",
 # "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-10mipt-DR03-NS/181207_092457/0000",
 # "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-15mipt-DR03-NS/181207_092823/0000",
 # "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-20mipt-DR03-NS/181207_093448/0000",
   
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-0mipt-DR03-WE/181206_160504/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DR03-WE/181206_160621/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-10mipt-DR03-WE/181206_160725/0000",
"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-15mipt-DR03-WE/181206_160853/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-20mipt-DR03-WE/181206_161001/0000",
   ]
OutputDirList = [
#   "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Max",
   #"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Max",

   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Interpolated1stOrder",
#    "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated1stOrder",
 #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Interpolated2ndOrder",
 #   "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated2ndOrder",

  #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_ModMax",
##   "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_ModMax",

     "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-0mipt-DR03-NS",
     # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DR03-NS",
     # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-10mipt-DR03-NS",
     # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-15mipt-DR03-NS",
     # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-20mipt-DR03-NS",
#   "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-0mipt-DR03-WE",
#     "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DR03-WE",
  #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-10mipt-DR03-WE",
    "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-15mipt-DR03-WE",
  #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-20mipt-DR03-WE",
   ]


#ScriptName = "scripts/runJets.py" # script to be used with cmsRun
#FileList = "filelist.txt" # list with all the file directories
#queue = "8nh" # give bsub queue -- 8nm (8 minutes), 1nh (1 hour), 8nh, 1nd (1day), 2nd, 1nw (1 week), 2nw 
########   customization end   #########


##### loop for creating and sending jobs #####
for indir, outdir in zip( InputDirList, OutputDirList ):
   OutputFileNames = outdir + "/jet_ntuples_merged/ntuple_jet_merged" # base of the output file name, they will be saved in res directory
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

##### loop for creating and sending jobs #####
   for x in range(1, int(NumberOfJobs)+1):
   ##### creates directory and file list for job #######
      os.system("mkdir "+outdir+"/tmp/"+str(x))
      os.chdir(outdir+"/tmp/"+str(x))
   #os.system("sed '"+str(1+interval*(x-1))+","+str(interval*x)+"!d' ../../"+FileList+" > list.txt ")
      
   ##### creates jobs #######
      with open('job.sh', 'w') as fout:
         
         
         
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
         fout.write("./jet_ntuple_merge --filein root://cms-xrd-global.cern.ch//store/user/sawebb/"+ indir + "/ntuple_"+str(x)+".root --filein_jet " + outdir+"/jet_ntuples/ntuple_jet_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
         fout.write("echo 'STOP---------------'\n")
         fout.write("echo\n")
         fout.write("echo\n")

      os.system("chmod 755 job.sh")
      
   ###### sends bjobs ######
   #os.system("bsub -q "+queue+" -o logs job.sh")
      os.system("qsub -cwd -q hep.q -l h_vmem=12G -l s_vmem=11.7G -l h_rt=4:0:0 -l s_rt=3:50:0 job.sh")
      print "job nr " + str(x) + " submitted"
      
      os.chdir("../..")
   
print
print "your jobs:"
os.system("qstat")
print
print 'END'
print
