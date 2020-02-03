import ROOT as r
from array import array
from math import log10, floor
from SetPlotStyle import SetPlotStyle
from collections import OrderedDict
SetPlotStyle()



methodsAndInputFiles = OrderedDict()
# methodsAndInputFiles['Threshold'] = 'plots/out_eta_cuts_Threshold_EtaParam_TEST/Threshold1p7_2p8_profileresolution.root'
# methodsAndInputFiles['Best Choice'] = 'plots/out_eta_cuts_BestChoice_EtaParam_TEST/BestChoice1p7_2p8_profileresolution.root'
# methodsAndInputFiles['STC'] = 'plots/out_eta_cuts_STC_EtaParam_TEST/STC1p7_2p8_profileresolution.root'


# methodsAndInputFiles['Inclusive'] = 'plots/out_eta_cuts_Threshold_EtaParam_TEST/Threshold1p7_2p8_profileresolution.root'
# methodsAndInputFiles['1.7 < |#eta| < 1.9'] = 'plots/out_eta_cuts_Threshold_EtaParam_TEST/Threshold1p7_1p9_profileresolution.root'
# methodsAndInputFiles['2.6 < |#eta| < 2.8'] = 'plots/out_eta_cuts_Threshold_EtaParam_TEST/Threshold2p6_2p8_profileresolution.root'
# methodsAndInputFiles['Calibration in jet #eta bins'] = 'plots/out_eta_cuts_Threshold_EtaParam_TEST/EtaCalibrated/Thresholdprofileresolution.root'

# Before Eta Calibration
methodsAndInputFiles['Threshold'] = 'plots/out_eta_cuts_ThresholdNew_EtaParam_TEST/Threshold1p7_2p8_profileresolution.root'
methodsAndInputFiles['Best Choice'] = 'plots/out_eta_cuts_BestChoice_EtaParam_TEST/BestChoice1p7_2p8_profileresolution.root'
methodsAndInputFiles['STC'] = 'plots/out_eta_cuts_STC_EtaParam_TEST/STC1p7_2p8_profileresolution.root'
methodsAndInputFiles['Mixed'] = 'plots/out_eta_cuts_Mixed_EtaParam_TEST/Mixed1p7_2p8_profileresolution.root'

# After Eta Calibration
# methodsAndInputFiles['Threshold'] = 'plots/out_eta_cuts_ThresholdNew_EtaParam_TEST/EtaCalibrated/Thresholdprofileresolution.root'
# methodsAndInputFiles['Best Choice'] = 'plots/out_eta_cuts_BestChoice_EtaParam_TEST/EtaCalibrated/BestChoiceprofileresolution.root'
# methodsAndInputFiles['STC'] = 'plots/out_eta_cuts_STC_EtaParam_TEST/EtaCalibrated/STCprofileresolution.root'
# methodsAndInputFiles['Mixed'] = 'plots/out_eta_cuts_Mixed_EtaParam_TEST/EtaCalibrated/Mixedprofileresolution.root'

niceColours = [ 632, 600, 417, 604 ]

canvas = r.TCanvas("can", "can", 900, 900)
legend = r.TLegend(0.3, 0.6, 0.8, 0.8)
legend.SetFillStyle(0);
legend.SetBorderSize(0);
legend.SetTextSize(0.04);
legend.SetTextFont(42);

for i, (method, inputFileName) in enumerate( methodsAndInputFiles.iteritems() ):
	inputFile = r.TFile( inputFileName, 'READ' )
	c1 = inputFile.Get('c1')
	g = c1.GetPrimitive('Graph')

	g.GetXaxis().SetTitle('gen p_{T}')
	g.GetYaxis().SetTitle('Resolution')
	g.SetLineColor(niceColours[i])
	g.SetMarkerColor(niceColours[i])
	g.SetMarkerStyle(1)
	g.SetMarkerSize(1)

	legend.AddEntry( g, method, 'LP')

	canvas.cd()
	if i == 0:
		g.Draw('AP')
	else :
		g.Draw('PSAME')
legend.Draw()
canvas.SetGridy()
canvas.Update()
# raw_input('...')

canvas.Print('compareResolutions.pdf')
