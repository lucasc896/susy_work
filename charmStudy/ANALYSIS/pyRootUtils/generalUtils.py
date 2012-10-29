#!/usr/bin/env python
# encoding: utf-8
"""
generalUtils.py

Created by Chris Lucas on 2012-10-28.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

import sys
import os
import ROOT as r
import math


class multiPlot(object):
  """Rate plot producer"""
  def __init__(self, hists = None):
    super(multiPlot, self).__init__()
    self.hists = hists
    self.listColors = [r.kBlack, r.kBlue+1, r.kAzure+10, r.kViolet-1]
    self.Debug = False
    self.DoGrid = True
    self.SetLogy = False
    self.xRange = []
    self.yRange = []
    self.hTitles = []
    self.canvTitle = ""
    self.lg = r.TLegend()
    self.ln1 = r.TLine()
    self.ln2 = r.TLine()
    self.ln3 = r.TLine()
    self.SetStyle()
  
  def makeMultiPlot(self):
    """docstring for MakeRatePlot"""
    c1 = r.TCanvas()
    if self.SetLogy: c1.SetLogy()

    self.MakeLegend()

    if not self.hTitles:
      for i in range( len(self.hists) ):
        self.hTitles.append( "hist_%d"%i )

    ctr=0

    for h, kCol, ttl in zip(self.hists, self.listColors, self.hTitles):
      if self.Debug: print "*** Hist: ", h
      if ctr==0:
        h.SetTitle( self.canvTitle )
        h.Draw("hist")
        h.GetYaxis().SetLabelSize(0.04)
        h.GetXaxis().SetTitleSize(0.04)
        if self.xRange:
          h.GetXaxis().SetRangeUser(self.xRange[0], self.xRange[1])
        if self.yRange:
          h.GetYaxis().SetRangeUser(self.yRange[0], self.yRange[1])

      h.SetLineWidth(2)
      h.SetLineColor(kCol)
      h.SetFillColor(0)
      h.Draw("histsame")
      self.lg.AddEntry(h, ttl, "L")
      ctr+=1

    if not self.SetLogy: self.ln1.Draw()
    if not self.SetLogy: self.ln2.Draw()
    if not self.SetLogy: self.ln3.Draw()
    self.lg.Draw()

    return c1

  def SetStyle(self):
    """docstring for SetStyle"""
    r.gStyle.SetOptStat(0)
    r.gStyle.SetOptTitle(0)
    r.gStyle.SetMarkerSize(2)

  def MakeLegend(self):
    """docstring for MakeLegend"""
    self.lg = r.TLegend(0.6, 0.68, 0.74, 0.87)

    self.lg.SetFillColor(0)
    #self.lg.SetFillStyle(0)
    self.lg.SetLineColor(0)
    self.lg.SetLineStyle(0)

  def DrawLine(self, xval=[]):
    """docstring for DrawLine"""
    self.ln1 = r.TLine(xval[0], self.yRange[0], xval[0], self.yRange[1])
    self.ln1.SetLineColor(16)
    self.ln1.SetLineStyle(2)

    self.ln2 = r.TLine(xval[1], self.yRange[0], xval[1], self.yRange[1])
    self.ln2.SetLineColor(16)
    self.ln2.SetLineStyle(2)

    self.ln3 = r.TLine(xval[2], self.yRange[0], xval[2], self.yRange[1])
    self.ln3.SetLineColor(16)
    self.ln3.SetLineStyle(2)        


class Print(object):
  """docstring for printPDF"""
  def __init__(self, Fname):
    super(Print, self).__init__()
    self.canvas = r.TCanvas()
    self.DoPageNum = True
    self.fname = Fname
    # self.rfile = r.TFile(self.fname[:-4]+".root",'RECREATE')
    self.pageCounter = 1
    self.open()


  def toFile(self,ob,title):
    """docstring for toFile"""
    # self.rfile.cd()
    # ob.SetName(title)
    # ob.SetTitle(title)
    # ob.Write()
    # ob = None
    pass

  def cd(self):
    """docstring for cd"""
    self.canvas.cd()
    pass


  def open(self, frontText = "<none>"):
    """docstring for open"""
    tpt1 = r.TText(0.07, 0.26, frontText)
    tpt2 = r.TText(0.07, 0.2, "Chris Lucas")
    tpt1.Draw()
    tpt2.Draw()
    self.canvas.Print(self.fname+"[")
    r.gPad.SetRightMargin(0.15)
    r.gPad.SetLeftMargin(0.15)
    r.gPad.SetTopMargin(0.1)
    r.gPad.SetBottomMargin(0.2)   

    pass


  def close(self):
    """docstring for close"""
    # self.rfile.Write()
    # self.rfile.Close()
    self.canvas.Print(self.fname+"]")
    pass


  def Clear(self):
    """docstring for Clear"""
    self.canvas.Clear()
    pass

  def SetLog(self,axis,BOOL):
    """docstring for SetLog"""
    if 'x' in axis:
      if BOOL:
        self.canvas.SetLogx()
      else:
        self.canvas.SetLogx(r.kFALSE)
    if 'y' in axis:
      if BOOL:
        self.canvas.SetLogy()
      else:
        self.canvas.SetLogy(r.kFALSE)
    pass

  def SetGrid(self,BOOL):
    """docstring for SetGrid"""
    if BOOL:
      self.canvas.SetGrid()
    else:
      self.canvas.SetGrid(r.kFALSE)
    pass


  def Print(self):
    """docstring for Print"""
    num = r.TLatex(0.95,0.01,"%d"%(self.pageCounter))
    num.SetNDC()
    if self.DoPageNum: num.Draw("same")
    # self.canvas.SetGridx()
    # self.canvas.SetGridy()
    self.canvas.Print(self.fname)
    self.pageCounter += 1
    pass

  def PrintCanvas(self, c1):
    """docstring for PrintCanvas"""
    num = r.TLatex(0.95,0.01,"%d"%(self.pageCounter))
    num.SetNDC()
    if self.DoPageNum: num.Draw("same")
    c1.Print(self.fname)
    self.pageCounter += 1
    pass

