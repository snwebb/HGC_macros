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
NumberOfJobs= 10 # number of jobs to be submitted
interval = 1 # number files to be processed in a single job, take care to split your file so that you run on all files. The last job might be with smaller number of files (the ones that remain).
InputDirList = [ "/vols/cms/snwebb/HGC_ntuples/DoubleNu/DoubleNu_PU200-stc/"]
OutputDirList = [ "/vols/cms/snwebb/HGC_ntuples/DoubleNu/DoubleNu_PU200-stc/" ]# base of the output file name, they will be saved in res directory

########   customization end   #########


##### loop for creating and sending jobs #####
for indir, outdir in zip( InputDirList, OutputDirList ):
   OutputFileNames = outdir + "/cone_ntuples/cone_ntuples" # base of the output file name, they will be saved in res directory
   path = os.getcwd()
   print
   print 'do not worry about folder creation:'
   os.system("rm -r " + outdir + "/putmp")
   os.system("mkdir -p " + outdir + "/putmp")
   os.system("mkdir -p " + outdir + "/cone_ntuples")
   if subprocess.call(["voms-proxy-info",'--exists']) == 1:
      print "Voms proxy does not exist:"
      os.system("voms-proxy-init -voms cms -valid 96:00")
   else:
      print "Voms proxy exists"
   print


##### loop for creating and sending jobs #####
   for x in range(1, int(NumberOfJobs)+1):
   ##### creates directory and file list for job #######
      os.system("mkdir "+outdir+ "/putmp/"+str(x))
      os.chdir(outdir+"/putmp/"+str(x))
      
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
#         fout.write("./jet_ntuple_merge --runtype pu --filein root://cms-xrd-global.cern.ch//store/user/sawebb/"+ indir + "/ntuple_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
         fout.write("./jet_ntuple_merge --runtype pu --filein "+ indir + "/ntuples/ntuple_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
         fout.write("echo 'STOP---------------'\n")
         fout.write("echo\n")
         fout.write("echo\n")
         
      os.system("chmod 755 job.sh")
   
   ###### sends bjobs ######
   #os.system("bsub -q "+queue+" -o logs job.sh")
#      os.system("qsub -cwd -q hep.q -l h_vmem=12G -l s_vmem=11.7G -l h_rt=4:0:0 -l s_rt=3:50:0 job.sh")
   #   os.system("/opt/exp_soft/cms/t3/t3submit_new job.sh")
      print "job nr " + str(x) + " submitted"
   
      os.chdir("../..")
      
print
print "your jobs:"
os.system("qstat")
print
print 'END'
print
