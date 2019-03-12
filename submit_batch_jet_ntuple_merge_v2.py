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

#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-0mipt-DR03-NS/181207_091543/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DR03-NS/181207_091637/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-10mipt-DR03-NS/181207_092457/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-15mipt-DR03-NS/181207_092823/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-20mipt-DR03-NS/181207_093448/0000",
   
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-0mipt-DR03-WE/181206_160504/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DR03-WE/181206_160621/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-10mipt-DR03-WE/181206_160725/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-15mipt-DR03-WE/181206_160853/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-20mipt-DR03-WE/181206_161001/0000",

#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA016-DRB02-NS/181212_124134/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA018-DRB02-NS/181212_124221/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA020-DRB02-NS/181212_124338/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA025-DRB02-NS/181212_124434/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA030-DRB02-NS/181212_124527/0000",

# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-5mipt-DRA015-DRB02-NS/181217_154547/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-5mipt-DRA020-DRB02-NS/181217_154732/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-5mipt-DRA030-DRB02-NS/181217_154932/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS/181217_155131/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-5mipt-DRA050-DRB02-NS/181217_155258/0000",


# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-5mipt-DRA050-DRB02-NS/181217_155258/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS/181217_155131/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU0-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS/190104_150739/0000",
   
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-DRA040-DRB00-NS-new/190111_103822/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-DRA040-DRB01-NS-new/190111_103702/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-DRA040-DRB03-NS-new/190111_103608/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_DoubleNu-PU200-stc-TCs-histoMax-DRA040-DRB040-NS/190131_153537/0000",
#"DoubleNuE1Eta14_31/crab_DoubleNu-PU200-stc-TCs-histoMax-DRA040-DRB020-NS/190118_101937/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS/190204_132500/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS/190204_132500/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stcV2-TCs-histoMax-DRA04-DRB00-NS/190206_144245/0000",

# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS/190204_132500/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stcV3-TCs-histoMax-DRA04-DRB00-NS/190207_144328/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-4416r-TCs-histoMax-DRA04-DRB00-NS/190212_131615/0000",

# "SingleGammaPt25Eta1p6_2p8/crab_SingleGamma-PU0-stc-wThresh-TCs-histoMax-DRA040-DRB00-NS/190213_132501/0000",
# "SingleGammaPt25Eta1p6_2p8/crab_SingleGamma-PU200-stc-wThresh-TCs-histoMax-DRA040-DRB00-NS/190213_132546/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-stc-TCs-histoMax-DRA04-DRB00-NS-cl3dpt0/190213_133412/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU0-stc-TCs-histoMax-DRAInf-DRB00-NS/190213_133629/0000",


# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoMax-DRA04-DRB00-NS-cl3dpt0/190218_105344/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-bestChoice-TCs-histoMax-DRA04-DRB00-NS/190218_100922/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoMax-DRA04-DRB00-NS-cl3dpt0/190218_105344/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoMax-DRA04-DRB02-NS-cl3dpt0/190218_105239/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoMax-DRA03-DRB02-NS-cl3dpt0/190218_105557/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoMax-DRAInf-DRB02-NS-cl3dpt0/190218_105804/0000",

# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRA04-DRB00-NS-cl3dpt0/190218_111203/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRA04-DRB02-NS-cl3dpt0/190218_111038/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRAInf-DRB02-NS-cl3dpt0/190218_111609/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRA03-DRB02-NS-cl3dpt0/190218_111406/0000",

# "SingleGammaPt25Eta1p6_2p8/crab_SingleGamma-PU200-stc-TCs-histoMax-DRA040-DRB00-NS/190218_134311/0000",

#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA01-NS/190221_150229/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA02-NS/190221_114421/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA03-NS/190221_114516/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA04-NS/190221_114611/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-CurrentDefault/190221_114714/0000",


# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-NewDefault-histoMax-0mipt/190226_164146/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-NewDefault-histoMax-5mipt/190226_164230/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-NewDefault-histoMax-10mipt/190226_164305/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC16-NewDefault-histoMax-0mipt/190226_164715/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC16-NewDefault-histoMax-5mipt/190226_164643/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC16-NewDefault-histoMax-10mipt/190226_164611/0000",

# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-histoMax-DRA04-DRB02-10mipt/190226_164844/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC16-histoMax-DRA04-DRB02-10mipt/190226_164801/0000",

#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-NewDefault-histoMax-15mipt/190226_164337/0000",
#"VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-NewDefault-histoMax-20mipt/190226_164403/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC16-NewDefault-histoMax-15mipt/190226_164538/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC16-NewDefault-histoMax-20mipt/190226_164452/0000",


 # "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-LbyLx1-DRB02-10mipt/190304_103514/0000",
 # "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-LbyLx1p5-DRB02-10mipt/190304_103651/0000",
 # "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-LbyLx2-DRB02-10mipt/190304_103726/0000",

# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-LbyLx1p25-DRB02-10mipt/190304_160621/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-LbyLx1p25-DRB00-10mipt/190304_163003/0000",

# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-LbyLx1p25-BLbyL0-10mipt/190305_095422/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-threshold-LbyLx1p25-BLbyL0p5-10mipt/190305_094944/0000",

# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC4-LbyLx1p25-BLbyL0-10mipt/190305_101439/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC4-LbyLx1p25-BLbyL0p5-10mipt/190305_101351/0000",

# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC16-LbyLx1p25-BLbyL0-10mipt/190305_101225/0000",
# "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC16-LbyLx1p25-BLbyL0p5-10mipt/190305_101307/0000",

    "VBF_HToInvisible_M125_14TeV_powheg_pythia8/crab_VBF-PU200-STC4-EqualSpread-LbyLx1p25-BLbyL0-10mipt/190307_170810/0000",

   ]
OutputDirList = [

 "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC4-EqualSpread-LbyLx1p25-BLbyL0-10mipt",

   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-LbyLx1p25-DRB02-10mipt",
   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-LbyLx1p25-DRB00-10mipt",

   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-LbyLx1p25-BLbyL0-10mipt",
   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-LbyLx1p25-BLbyL0p5-10mipt",

   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC4-LbyLx1p25-BLbyL0-10mipt",
   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC4-LbyLx1p25-BLbyL0p5-10mipt",

   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC16-LbyLx1p25-BLbyL0-10mipt",
   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC16-LbyLx1p25-BLbyL0p5-10mipt",


 # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-LbyLx1-DRB02-10mipt",            
 # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-LbyLx1p5-DRB02-10mipt",            
 # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-LbyLx2-DRB02-10mipt",            

# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-NewDefault-histoMax-0mipt",            
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-NewDefault-histoMax-5mipt",            
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-NewDefault-histoMax-10mipt",           
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC16-NewDefault-histoMax-0mipt",      
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC16-NewDefault-histoMax-5mipt",      
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC16-NewDefault-histoMax-10mipt",     

# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-histoMax-DRA04-DRB02-10mipt",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC16-histoMax-DRA04-DRB02-10mipt",    

#"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-NewDefault-histoMax-15mipt",           
#"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-NewDefault-histoMax-20mipt",           
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC16-NewDefault-histoMax-15mipt",     
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-STC16-NewDefault-histoMax-20mipt",     

#Presentation

# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-TCs",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-bestChoice-TCs-histoMax-DRA04-DRB00-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-DRA04-DRB00-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-DRA04-DRB02-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-DRA03-DRB02-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-DRAInf-DRB02-NS",

# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRA04-DRB00-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRA04-DRB02-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRAInf-DRB02-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoInterpolated1stOrder-5mipt-DRA03-DRB02-NS",

# "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25/SingleGamma-PU200-stc-TCs-histoMax-DRA040-DRB00-NS",


#"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA01-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA02-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA03-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-threshold-TCs-histoMax-LayerDependentDRA04-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-CurrentDefault",









# "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25/SingleGamma-PU0-stc-wThresh-TCs-histoMax-DRA040-DRB00-NS",
# "/vols/cms/snwebb/HGC_ntuples/SingleGammaPt25/SingleGamma-PU2000-stc-wThresh-TCs-histoMax-DRA040-DRB00-NS",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA04-DRB00-NS-cl3dpt0",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU0-stc-TCs-histoMax-DRAInf-DRB00-NS",

#"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-4416r-TCs-histoMax-DRA04-DRB00-NS/",
#"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet5p0/",
#"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet10p0/",
#"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet1p0/",
#"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS-Jet2p0/",
#"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stcV2-TCs-histoMax-DRA04-DRB00-NS/",
#"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stcV3-TCs-histoMax-DRA04-DRB00-NS/",
 #"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRAInf-DRB00-NS/",
#   "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Max",
   #"/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Max",

   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Interpolated1stOrder",
#    "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated1stOrder",
 #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_Interpolated2ndOrder",
 #   "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_Interpolated2ndOrder",

  #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_threshold_polarHisto_ModMax",
##   "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF_Hinv_PU200_stc_polarHisto_ModMax",

#     "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-0mipt-DR03-NS",
#     "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DR03-NS",
#     "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-10mipt-DR03-NS",
#     "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-15mipt-DR03-NS",
#     "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-20mipt-DR03-NS",
#   "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-0mipt-DR03-WE",
#     "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DR03-WE",
  #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-10mipt-DR03-WE",
 #   "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-15mipt-DR03-WE",
  #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-20mipt-DR03-WE",
#  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA016-DRB02-NS/",
 #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA018-DRB02-NS/",
 #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA020-DRB02-NS/",
 #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA025-DRB02-NS/",
 # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoInterpolated1stOrder-5mipt-DRA030-DRB02-NS/",

 # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA015-DRB02-NS/",
 #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA020-DRB02-NS/",
 #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA030-DRB02-NS/",
 #  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS/",
 # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA050-DRB02-NS/",

# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-TCs/",
# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU0-stc-TCs-TCs/",

#  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS-JET01/",
#  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU0-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS/",
#  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU0-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS-2/",
   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA040-DRB00-NS/",
   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA040-DRB01-NS/",
   # "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA040-DRB03-NS/",

# "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-DRA040-DRB04-NS/",


#  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU0-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS-newpu/",

#  "/vols/cms/snwebb/HGC_ntuples/DoubleNu/DoubleNu-PU200-stc-TCs-histoMax-DRA040-DRB02-NS/",


#  "/vols/cms/snwebb/HGC_ntuples/VBF_Hinv/VBF-PU200-stc-TCs-histoMax-5mipt-DRA040-DRB02-NS-pu21/",
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
#         fout.write("./jet_ntuple_merge --runtype jet --filein root://cms-xrd-global.cern.ch//store/user/sawebb/"+ indir + "/ntuple_"+str(x)+".root --filein_jet " + outdir+"/jet_ntuples/ntuple_jet_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
         fout.write("./jet_ntuple_merge --runtype jet --filein root://gfe02.grid.hep.ph.ic.ac.uk:1096//store/user/sawebb/"+ indir + "/ntuple_"+str(x)+".root --filein_jet " + outdir+"/jet_ntuples/ntuple_jet_"+str(x)+".root --fileout " + OutputFileNames +"_"+str(x)+".root \n")
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
