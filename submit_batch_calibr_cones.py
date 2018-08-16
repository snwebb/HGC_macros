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
NumberOfJobs= 500 # number of jobs to be submitted
interval = 1 # number files to be processed in a single job, take care to split your file so that you run on all files. The last job might be with smaller number of files (the ones that remain).
OutputFileNames = "/data_CMS/cms/strebler/HGC/SingleNu_PU200_JB/calibr_cone_ntuples/calibr_cone_ntuples" # base of the output file name, they will be saved in res directory
ScriptName = "scripts/runJets.py" # script to be used with cmsRun
#FileList = "filelist.txt" # list with all the file directories
queue = "8nh" # give bsub queue -- 8nm (8 minutes), 1nh (1 hour), 8nh, 1nd (1day), 2nd, 1nw (1 week), 2nw 
########   customization end   #########

path = os.getcwd()
print
print 'do not worry about folder creation:'
os.system("rm -r tmp")
os.system("mkdir tmp")
os.system("mkdir res")
print

##### loop for creating and sending jobs #####
for x in range(1, int(NumberOfJobs)+1):
   ##### creates directory and file list for job #######
   os.system("mkdir tmp/"+str(x))
   os.chdir("tmp/"+str(x))
   #os.system("sed '"+str(1+interval*(x-1))+","+str(interval*x)+"!d' ../../"+FileList+" > list.txt ")
   
   ##### creates jobs #######
   with open('job.sh', 'w') as fout:
      fout.write("#!/bin/sh\n")
      fout.write("echo\n")
      fout.write("echo\n")
      fout.write("echo 'START---------------'\n")
      fout.write("echo 'WORKDIR ' ${PWD}\n")
      fout.write("cd /home/llr/cms/strebler/CMSSW_9_2_5_patch2/src\n")
      fout.write("eval `scramv1 runtime -sh`\n")
      fout.write("cd /home/llr/cms/strebler/HGC_macros\n")
      fout.write("root -b -l <<EOF\n")
      fout.write(".L calibrate_layer.C+\n")
      fout.write("calibrate_layer(\"/data_CMS/cms/strebler/HGC/SingleNu_PU200_JB/cone_ntuples/cone_ntuples_"+str(x)+".root\",\"HGCalTriggerNtuple\",\""+OutputFileNames+"_"+str(x)+".root\",true,false,true);\n")
      fout.write(".q\n")
      fout.write("EOF\n")
      fout.write("echo 'STOP---------------'\n")
      fout.write("echo\n")
      fout.write("echo\n")
   os.system("chmod 755 job.sh")
   
   ###### sends bjobs ######
   #os.system("bsub -q "+queue+" -o logs job.sh")
   os.system("/opt/exp_soft/cms/t3/t3submit_new job.sh")
   print "job nr " + str(x) + " submitted"
   
   os.chdir("../..")
   
print
print "your jobs:"
os.system("t3stat")
print
print 'END'
print
