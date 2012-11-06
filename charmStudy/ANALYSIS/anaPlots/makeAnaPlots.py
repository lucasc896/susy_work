#!/usr/bin/env python
# encoding: utf-8
"""
bTagPlots.py

Created by Chris Lucas on 2012-10-30.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

from sys import argv, exit
from generalUtils import *

r.TH1.SetDefaultSumw2()

#open loads of files - one per sample

#put interesting hists in specific 

def drawMyPlot(hists=None, hTitle="", rVal=None):

  aPlot = anaPlot(hists, hTitle)
  aPlot.makeSinglePlot(rVal)
  del aPlot

def makeSomePlots(files=None, dirs=None, bMulti=None, hist=None, sinHists=None, rebinVals=None, singleRebinVals=None):

  bMutliHists = {
    "0b":["_0"],
    "1b":["_1"],
    "2b":["_2"],
    "3b":["_3"],
    "4b":["_4"],
    "ge1b":["_1", "_2", "_3", "_4", "_5"],
    "ge2b":["_2", "_3", "_4", "_5"],
    "ge3b":["_3", "_4", "_5"],
    "ge4b":["_4", "_5"],
    "inc":["_0", "_1", "_2", "_3", "_4", "_5"],}


  rFile = r.TFile.Open(files[0])

  #plot b-Multi plots
  for hT, rVal in zip(hist, rebinVals):
    for b in bMulti:
      histList = []
      for d in dirs:
        for suf in bMutliHists[b]:
          h = rFile.Get("%s/%s%s"%(d, hT, suf))
          histList.append(h)
      aPlot = anaPlot(histList, "%s_%s"%(hT, b))
      aPlot.makeSinglePlot(rVal, 1.)
      del aPlot   

  #plot single plots
  for hT, rVal in zip(sinHists, singleRebinVals):
    histList = []
    for d in dirs:
      h = rFile.Get("%s/%s"%(d, hT))
      histList.append(h)
    aPlot = anaPlot(histList, hT)
    aPlot.makeSinglePlot(rVal, 1.)
    del aPlot


files=["../rootfiles/anaPlots/outT2bb_300_anaPlots.root"]
#files = []
dirs=["noCuts_0_10000"]
bMulti=["inc"]
singleHists=["stopGenPtScal",
        "stopGenPtVect",
        "delPhi_vs_scalGenPt",
        "dPhiStopCharm",
        "dPhiNeutCharm",
        "dPhiStopNeut"]
hists=["MET",
    "MHT",
    "commHT",
    "hadronicAlphaTZoom",
    "leadJetdelPhi",
    "MHToverMET",
    "jetPt",
    "leadJetPt",
    "subLeadJetPt"]
rebin=[10, 10, 10, 1, 1, 1, 10, 10, 10]
singleRebin=[10, 10, 4, 1, 1, 1]

if len(hists) != len(rebin):
  print "\n*** Ensure 'hists' and 'rebin' are the same length\n"
  sys.exit()
if len(singleHists) != len(singleRebin):
  print "\n*** Ensure 'sinlgeHists' and 'sinlgeRebin' are the same length\n"
  sys.exit()

makeSomePlots(files, dirs, bMulti, hists, singleHists, rebin, singleRebin)
