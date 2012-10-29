#!/usr/bin/env python
# encoding: utf-8
"""
bTagPlots.py

Created by Chris Lucas on 2012-10-28.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

from sys import argv
from generalUtils import *

if len(argv) > 1:
    cmd = argv[1]

r.gROOT.SetBatch(True)

inList = {
    "QCD":("_375_",
        ["jet_response",
        "bMatched_response",
        "cMatched_response",
        "lMatched_response"],
        "../rootfiles/bTagEff_Study/outQCD_bTagEff_csvm.root",
        [0.01, 40000.], [100., 80000.]),
    
    "TTbar":("_375_",
        ["jet_response",
        "bMatched_response",
        "cMatched_response",
        "lMatched_response"],
        "../rootfiles/bTagEff_Study/outTTbar_bTagEff_csvm.root",
        [0.01, 2000.], [60., 70000.]),
    
    "WJets":("_375_",
        ["jet_response",
        "bMatched_response",
        "cMatched_response",
        "lMatched_response"],
        "../rootfiles/bTagEff_Study/outWJets_bTagEff_csvm.root",
        [0.01, 2000.], [2., 70000.]),    
}


for key, val in inList.items():
    histList = []

    #if cmd not in key: continue
    rFile = r.TFile.Open( val[2] )
    for hist in val[1]:

        histDir = "%s/%s"%(val[0], hist)
        h = rFile.Get( histDir )
        histList.append( h )
    outFileName = key

    c1 = Print("bTagEff_%s.pdf"%outFileName)
    
    multi = multiPlot( hists=histList )
    multi.hTitles = ["All", "bMatched", "cMatched", "lMatched"]
    
    multi.xRange = [0., 1.]
    multi.yRange = val[3]
    multi.DrawLine([.898,.679,.244])
    multi.canvTitle = key

    c1.PrintCanvas( multi.makeMultiPlot() )
    
    #do logY version
    multi.yRange = val[4]
    multi.SetLogy = True
    
    c1.PrintCanvas( multi.makeMultiPlot() )
    
    del multi
    c1.close()

pass

