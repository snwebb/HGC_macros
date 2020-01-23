import ROOT as r
from array import array
from math import log10, floor
from SetPlotStyle import SetPlotStyle
SetPlotStyle()
r.gROOT.SetBatch()

etaRegions = [
    "1p7_1p9",
    "1p9_2p0",
    "2p0_2p1",
    "2p1_2p2",
    "2p2_2p3",
    "2p3_2p4",
    "2p4_2p5",
    "2p5_2p6",
    "2p6_2p8",
]

FEOptions = [
	'Threshold',
	'BestChoice',
	'STC',
	'Mixed'
]

inputFileFormat = 'plots/out_eta_cuts_{FEOption}_EtaParam_TEST/{FEOption}{etaRegion}_profile.root'

niceColours = [ 632, 600, 417, 604 ]

def parseMinMaxEta( etaRegion ) :
	minEta = float( etaRegion.split('_')[0].replace('p','.') )
	maxEta = float( etaRegion.split('_')[-1].replace('p','.') )
	return minEta, maxEta

def getMidEta(minEta, maxEta):
	if minEta < maxEta :
		return minEta + abs(maxEta - minEta) / 2
	else:
		return maxEta + abs(maxEta - minEta) / 2


allGraphs = {}

for index, FEOption in enumerate(FEOptions):
	for i_fitParam in range(3):
		canvas = r.TCanvas("can"+str(i_fitParam), "can"+str(i_fitParam), 800, 900)
		graph = r.TGraphErrors(len(etaRegions) )

		graph_up = r.TGraphErrors(len(etaRegions) )
		graph_down = r.TGraphErrors(len(etaRegions) )

		etas, fitParams = array( 'd' ), array( 'd' )

		for i, etaRegion in enumerate(etaRegions):
			# print inputFileFormat.format(etaRegion=etaRegion)
			inputFile = r.TFile( inputFileFormat.format(FEOption=FEOption, etaRegion=etaRegion), 'READ' )
			c1 = inputFile.Get('c1')
			f = c1.GetPrimitive('f_mean')
			f_up = c1.GetPrimitive('f_rmsup')
			f_down = c1.GetPrimitive('f_rmsdown')



			minEta, maxEta = parseMinMaxEta(etaRegion)
			midEta = getMidEta(minEta, maxEta)
			graph.SetPoint( i, midEta, f.GetParameter(i_fitParam))
			graph.SetPointError( i, 0, f.GetParError(i_fitParam))

			graph_up.SetPoint( i, midEta, f_up.GetParameter(i_fitParam))
			graph_up.SetPointError( i, 0, f_up.GetParError(i_fitParam))

			graph_down.SetPoint( i, midEta, f_down.GetParameter(i_fitParam))
			graph_down.SetPointError( i, 0, f_down.GetParError(i_fitParam))


		canvas.cd()
		graph.SetLineColor( niceColours[index] )
		graph.SetLineWidth( 2 )
		graph.SetMarkerColor( niceColours[index] )
		graph.SetMarkerStyle( 21 )

		fitFunction = None
		fitFunctionName = 'pol1'
		if i_fitParam == 0:
			fitFunctionName = 'pol2'
		elif i_fitParam == 1:
			fitFunctionName = 'pol2'

		graph.Fit(fitFunctionName, '0', '', 1.7, 2.8)
		fitFunction = graph.GetFunction(fitFunctionName)

		print 'Fit probability :',fitFunction.GetProb()

		graph_up.SetLineColor( 9 )
		graph_up.SetLineWidth( 2 )
		graph_up.SetMarkerColor( 9 )
		graph_up.SetMarkerStyle( 22 )

		graph_down.SetLineColor( 9 )
		graph_down.SetLineWidth( 2 )
		graph_down.SetMarkerColor( 9 )
		graph_down.SetMarkerStyle( 23 )

		mg = r.TMultiGraph();
		mg.Add(graph)

		mg.GetXaxis().SetTitle( '#eta' )
		yAxisTitle = 'x^{2} coefficient'
		if i_fitParam == 0:
			yAxisTitle = 'Intercept'
		elif i_fitParam == 1:
			yAxisTitle = 'x coefficient'
		mg.GetYaxis().SetTitle( yAxisTitle )


		print allGraphs
		if yAxisTitle not in allGraphs.keys():
			allGraphs[yAxisTitle] = {}
		allGraphs[yAxisTitle][FEOption] = graph.Clone()

	# raw_input('...')

r.gROOT.SetBatch(0)
for coefficient in allGraphs.keys():
	canvas = r.TCanvas("can_"+coefficient, "can_"+coefficient, 800, 900)
	mg = r.TMultiGraph();
	mg.GetXaxis().SetTitle( '|#eta|' )
	mg.GetYaxis().SetTitle( coefficient )
	legend = r.TLegend(0.2, 0.7, 0.5, 0.9)
	legend.SetFillStyle(0);
	legend.SetBorderSize(0);
	legend.SetTextSize(0.04);
	legend.SetTextFont(42);
	for FEOption, graph in allGraphs[coefficient].iteritems():
		mg.Add( graph )
		legend.AddEntry( graph, FEOption, 'P')
	mg.Draw('AP')

	legend.Draw()
	canvas.Update()
	mg.SetMinimum( mg.GetYaxis().GetXmin() * 0.8 );
	if coefficient is 'x^{2} coefficient':
		print r.gPad.GetLeftMargin()
		r.gPad.SetLeftMargin(0.2)
		mg.GetYaxis().SetTitleOffset(1.9)
	mg.SetMaximum( mg.GetYaxis().GetXmax() * 1.3 );
	canvas.Update()
	canvas.Print('calibParam_{coefficient}.pdf'.format(coefficient = coefficient))

