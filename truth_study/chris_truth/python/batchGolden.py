#!/usr/bin/env python

import errno
import os
import setupSUSY
from libFrameworkSUSY import *
from libHadronic import *
from libWPol import *
from libOneLepton import *
from libchris import *
from icf.core import PSet,Analysis
from time import strftime
from icf.config import defaultConfig
from icf.utils import json_to_pset
from copy import deepcopy

def ensure_dir(path):
	try:
		os.makedirs(path)
	except OSError as exc: # this doesnt work for python <2.5 (which, of course, blue crystal has)
		if exc.errno == errno.EEXIST:
			pass
		else: raise

default_ntuple = deepcopy(defaultConfig.Ntuple) #imports the default ntuple structure

default_ntuple.Electrons=PSet(
Prefix="electron",
Suffix="Pat",
LooseID="EIDLoose",
TightID="EIDTight",
)
default_ntuple.Muons=PSet(
Prefix="muon",
Suffix="Pat",
LooseID="IsGlobalMuon",
TightID="IDGlobalMuonPromptTight",
)
default_ntuple.SecMuons=PSet(
    Prefix="muon",
    Suffix="PF")
default_ntuple.Taus=PSet(
Prefix="tau",
Suffix="Pat",
LooseID="TauIdbyTaNCfrOnePercent",
TightID="TauIdbyTaNCfrTenthPercent"
)
default_ntuple.Jets=PSet(
Prefix="ic5Jet",
Suffix="Pat",
Uncorrected=False,
)
default_ntuple.Photons=PSet(
Prefix="photon",
Suffix="Pat",
)

ic5_calo = deepcopy(default_ntuple)
ic5_calo.Jets.Prefix="ic5Jet"

ak5_calo = deepcopy(default_ntuple)
ak5_calo.Jets.Prefix="ak5Jet"

ak5_jpt = deepcopy(default_ntuple)
ak5_jpt.Jets.Prefix="ak5JetJPT"

ak5_pf = deepcopy(default_ntuple)
ak5_pf.Jets.Prefix="ak5JetPF"
ak5_pf.TerJets.Prefix="ak5Jet"

ak7_calo = deepcopy(default_ntuple)
ak7_calo.Jets.Prefix="ak7Jet"


# -----------------------------------------------------------------------------
# Cross-cleaning settings

default_cc = deepcopy(defaultConfig.XCleaning)
default_cc.Verbose=False
default_cc.MuonJet=True
default_cc.ElectronJet=True
default_cc.PhotonJet=True
default_cc.ResolveConflicts=True
default_cc.Jets.PtCut=10.0
default_cc.Jets.EtaCut=10.0
default_cc.Muons.ModifyJetEnergy=True
default_cc.Muons.PtCut=10.0
default_cc.Muons.EtaCut=2.5
default_cc.Muons.TrkIsoCut=-1.
default_cc.Muons.CombIsoCut=0.15
default_cc.Muons.MuonJetDeltaR=0.5
default_cc.Muons.MuonIsoTypePtCutoff=0.
default_cc.Muons.RequireLooseIdForInitialFilter=False
default_cc.Electrons.PtCut=10.0
default_cc.Electrons.EtaCut=2.5
default_cc.Electrons.TrkIsoCut=-1.0
default_cc.Electrons.CombIsoCut=0.15
default_cc.Electrons.ElectronJetDeltaR=0.5
default_cc.Electrons.ElectronIsoTypePtCutoff=0.
default_cc.Electrons.ElectronLooseIdRequired=True
default_cc.Electrons.ElectronTightIdRequired=False
default_cc.Electrons.RequireLooseIdForInitialFilter=False
default_cc.Photons.EtCut=25.0
default_cc.Photons.EtaCut=2.5
default_cc.Photons.TrkIsoCut=2.0
default_cc.Photons.CaloIsoCut=0.2
default_cc.Photons.IDReq=3
default_cc.Photons.UseID=True
default_cc.Photons.PhotonJetDeltaR=0.5
default_cc.Photons.PhotonIsoTypePtCutoff=30.
# -----------------------------------------------------------------------------
# Definition of common objects
default_common = deepcopy(defaultConfig.Common)
default_common.ApplyXCleaning=True
default_common.Jets.PtCut=50.0
default_common.Jets.EtaCut=3.0
default_common.Jets.ApplyID=True
default_common.Jets.TightID=False
default_common.Electrons.PtCut=10.0
default_common.Electrons.EtaCut=2.5
default_common.Electrons.TrkIsoCut=-1.
default_common.Electrons.CombIsoCut=0.15
default_common.Electrons.ApplyID = True
default_common.Electrons.TightID = False
default_common.Electrons.RequireLooseForOdd = True
default_common.Muons.PtCut=10.0
default_common.Muons.EtaCut=2.5
default_common.Muons.TrkIsoCut=-1.
default_common.Muons.CombIsoCut=0.15
default_common.Muons.ApplyID = True
default_common.Muons.TightID = True
default_common.Muons.RequireLooseForOdd = True
default_common.Photons.EtCut=25.0
# default_common.Photons.EtaCut=2.5
default_common.Photons.UseID=True
# the photon cuts are NOT read anyway
# default_common.Photons.TrkIsoRel=0.
# default_common.Photons.TrkIsoCut=99999.
# default_common.Photons.EcalIsoRel=0.
# default_common.Photons.EcalIsoCut=99999.
# default_common.Photons.HcalIsoRel=0.
# default_common.Photons.HcalIsoCut=99999.
# default_common.Photons.HadOverEmCut=0.5
# default_common.Photons.SigmaIetaIetaCut=0.5
##default_common.Photons.CaloIsoCut=99999.
default_common.Photons.IDReq = 3
default_common.Photons.RequireLooseForOdd = True

skim_ps=PSet(
    SkimName = "myskim",
    DropBranches = False,
    Branches = [
        " keep * "
        ]
)
skim = SkimOp(skim_ps.ps())


#Plot the common plots!

genericPSet = PSet(
DirName      = "275_325Gev",
MinObjects   = 2,
MaxObjects   = 15,
minDR = 0.4 ,
mCut = 2.0 ,
StandardPlots     = True,
)

def makePlotOp(OP = (), cutTree = None, cut = None, label = ""):
  """docstring for makePlotOp"""
  out = []
  if OP[1] != None:
    plotpset = deepcopy(OP[1])
    plotpset.DirName = label
    print plotpset.DirName
    op = eval(OP[0]+"(plotpset.ps())")
  else:
    op = eval(OP[0])
  out.append(op)
  cutTree.TAttach(cut,op)
  alpha = OP_CommonAlphaTCut(0.55)
  dump = EventDump()
  skim_ps=PSet(
    SkimName = "myskim",
    DropBranches = False,
    Branches = [
        " keep * "
        ]
  )
  skim = SkimOp(skim_ps.ps())
  # out.append(skim)
  # out.append(skim_ps)
  cutTree.TAttach(cut,alpha)
  cutTree.TAttach(alpha,dump)
  # cutTree.TAttach(alpha,skim)
  out.append(alpha)
  out.append(dump)
  return out
  pass
  
  
def AddBinedHist(cutTree = None, OP = (), cut = None, htBins = [],TriggerDict = None,lab = ""):
  """docstring for AddBinedHist"""
  out = []
  if TriggerDict is not None:
      for lower,upper in zip(htBins,htBins[1:]+[None]):
        # print "Lower , Upper =", lower , upper
        if int(lower) == 325 and upper is None: continue
        if int(lower) == 375 and upper is None: continue
        if int(lower) == 475 and upper is None: continue
        if int(lower) == 675 and upper is None: continue
        # print "continue should have happened now"
        lowerCut = eval("RECO_CommonHTCut(%d)"%lower)
        triggerps = PSet(Verbose = False,
        UsePreScaledTriggers = False,
        Triggers = [])
        triggerps.Triggers = TriggerDict["%d%s"%(lower, "_%d"%upper if upper else "")]
        Trigger = OP_MultiTrigger( triggerps.ps() )
        out.append(triggerps)
        out.append(Trigger)
        out.append(lowerCut)
        cutTree.TAttach(cut,Trigger)
        cutTree.TAttach(Trigger,lowerCut)
        if upper:
          upperCut =  eval("RECO_CommonHTLessThanCut(%d)"%upper)
          out.append(upperCut)
          cutTree.TAttach(lowerCut,upperCut)
        pOps = makePlotOp(cutTree = cutTree, OP = OP, cut = upperCut if upper else lowerCut, label = "%s%d%s"%(lab,lower, "_%d"%upper if upper else ""))
        out.append(pOps) 
  else:
      for lower,upper in zip(htBins,htBins[1:]+[None]):
        # print "Lower , Upper =", lower , upper
        if int(lower) == 325 and upper is None: continue
        if int(lower) == 375 and upper is None: continue
        if int(lower) == 475 and upper is None: continue
        if int(lower) == 675 and upper is None: continue
        # print "continue should have happened now"
        lowerCut = eval("RECO_CommonHTCut(%d)"%lower)
        out.append(lowerCut)
        cutTree.TAttach(cut,lowerCut)
        if upper:
          upperCut =  eval("RECO_CommonHTLessThanCut(%d)"%upper)
          out.append(upperCut)
          cutTree.TAttach(lowerCut,upperCut)
        pOps = makePlotOp(cutTree = cutTree, OP = OP, cut = upperCut if upper else lowerCut, label = "%s%d%s"%(lab,lower, "_%d"%upper if upper else ""))
        out.append(pOps)
  return out
  pass

####
# Define some Cuts
####
NoiseFilt= OP_HadronicHBHEnoiseFilter()
GoodVertexMonster = OP_GoodEventSelection()
ht250_Trigger = RECO_CommonHTCut(250.)
recHitCut = OP_SumRecHitPtCut(30.)
LeadingJetEta = OP_FirstJetEta(2.5)
oddJet = OP_OddJet()
oddMuon = OP_OddMuon()
oddElectron = OP_OddElectron()
oddPhoton = OP_OddPhoton()
badMuonInJet = OP_BadMuonInJet()
numComElectrons = OP_NumComElectrons("<=",0)
numComPhotons = OP_NumComPhotons("<=",0)
VertexPtOverHT = OP_SumVertexPtOverHT(0.1)
htCut275 = RECO_CommonHTCut(275.)
DeadEcalCutMC =   OP_DeadECALCut(0.3,0.3,0.5,30.,10,0,"./deadRegionList_START38_V12.txt")
MHTCut = OP_CommonMHTCut(0.)
MHT_METCut = OP_MHToverMET(1.25,50.)
DiJet5 = OP_NumComJets("==",2)
ZeroMuon = OP_NumComMuons("<=",0)
recHitCut = OP_SumRecHitPtCut(30.)
ZeroMuon = OP_NumComMuons("<=",0)
json_ouput = JSONOutput("filtered")
OneMuon = OP_NumComMuons("==",1)
ZMassCut = RECO_2ndMuonMass(25.0, 91.2, False, "all")
PFMTCut30 = RECO_PFMTCut(30.0)
DiMuon = OP_NumComMuons("==",2)
ZMass_2Muons = RECO_2ndMuonMass(25.0, 91.2, True, "OS")
minDRMuonJetCut = RECO_MuonJetDRCut(0.5)
minDRMuonJetCutDiMuon = RECO_MuonJetDRCut(0.5)
Mu45PtCut = OP_UpperMuPtCut(1000.0)


#Second MC!
def MakeMCTree(Threshold, Muon = None,Split = None):
  out = []

  HTBins = []
  
  if int(Threshold) is 100 and Split == None : HTBins = [375+100*i for i in range(6)]
  if int(Threshold) is 100 and Split == "Muon_All" : HTBins = [375+100*i for i in range(6)]
  if int(Threshold) is 73 : HTBins = [275.,325.]
  if int(Threshold) is 86 : HTBins = [325.,375.]
  secondJetET = OP_SecondJetEtCut(Threshold)
  cutTreeMC = Tree("MC")
  cutTreeMC.Attach(ht250_Trigger)
  cutTreeMC.TAttach(ht250_Trigger,NoiseFilt)
  cutTreeMC.TAttach(NoiseFilt,GoodVertexMonster)
  cutTreeMC.TAttach(GoodVertexMonster,recHitCut)
  cutTreeMC.TAttach(recHitCut,LeadingJetEta)
  cutTreeMC.TAttach(LeadingJetEta,secondJetET)
  cutTreeMC.TAttach(secondJetET,oddJet)
  cutTreeMC.TAttach(oddJet,badMuonInJet)
  cutTreeMC.TAttach(badMuonInJet,
  #oddMuon)
  #cutTreeMC.TAttach(oddMuon,
  oddElectron)
  cutTreeMC.TAttach(oddElectron,oddPhoton)
  cutTreeMC.TAttach(oddPhoton,numComElectrons)
  cutTreeMC.TAttach(numComElectrons,numComPhotons)
  cutTreeMC.TAttach(numComPhotons,VertexPtOverHT)
  cutTreeMC.TAttach(VertexPtOverHT,htCut275)
  cutTreeMC.TAttach(htCut275,DeadEcalCutMC)
 
  #Here be plots after all the cuts!!
  cutTreeMC.TAttach(DeadEcalCutMC,MHT_METCut)
  if Muon == None:
      cutTreeMC.TAttach(MHT_METCut,ZeroMuon)

      out.append(AddBinedHist(cutTree = cutTreeMC,
      OP = ("TruthAnalysis",genericPSet), cut = ZeroMuon,
      htBins = HTBins,TriggerDict = None,lab ="") )

  else:
      if Split == "Muon_All":
          cutTreeMC.TAttach(MHT_METCut,Mu45PtCut)
          cutTreeMC.TAttach(Mu45PtCut,minDRMuonJetCut)
      else: cutTreeMC.TAttach(MHT_METCut,minDRMuonJetCut)
      cutTreeMC.TAttach(minDRMuonJetCut,OneMuon)
      cutTreeMC.TAttach(OneMuon,ZMassCut)
      cutTreeMC.TAttach(ZMassCut,PFMTCut30)

      out.append(AddBinedHist(cutTree = cutTreeMC,
      OP = ("TruthAnalysis",genericPSet), cut = PFMTCut30,
      htBins = HTBins,TriggerDict = None ,lab = "OneMuon_") )

      out.append(AddBinedHist(cutTree = cutTreeMC,
      OP = ("TruthAnalysis",genericPSet), cut = PFMTCut30,
      htBins = HTBins,TriggerDict = None ,lab = "OneMuonWeek_") )



      cutTreeMC.TAttach(minDRMuonJetCut,DiMuon)
      cutTreeMC.TAttach(DiMuon,ZMass_2Muons)
    
      out.append(AddBinedHist(cutTree = cutTreeMC,
      OP = ("TruthAnalysis",genericPSet), cut = ZMass_2Muons,
      htBins = HTBins,TriggerDict = None ,lab = "DiMuon_") )

  
  return (cutTreeMC,secondJetET,out)


# Define the custom muon ID

mu_id_higher = PSet(
    doJetLoop = False,
    MuID = "Tight",
    MinPt = 10.,
    MaxEta = 2.1,
    MaxIsolation = 0.1,
    DRMuJet = 0.3,
    MaxGlbTrkDxy = 0.02,
    MinGlbTrkNumOfValidHits = 11,
    SegMatch2GlbMu = 1,
    PixelHitsOnInrTrk = 1,
    MaxInrTrkDz = 1.
        )


mu_id_lower = PSet(
    doJetLoop = False,
    MuID = "Tight",
    MinPt = 10.,
    MaxEta = 2.5,
    MaxIsolation = 0.1,
    DRMuJet = 0.3,
    MaxGlbTrkDxy = 0.02,
    MinGlbTrkNumOfValidHits = 11,
    SegMatch2GlbMu = 1,
    PixelHitsOnInrTrk = 1,
    MaxInrTrkDz = 1.
        )



vertex_reweight_PUS4 = GoodVertexReweighting(
PSet(GoodVertexWeights = [1.0, 0.071182041228993354, 0.3788533298983548, 0.70212224756460717, 0.95912926863057879,
 1.1063323506805849, 1.1826257455177471, 1.2297382718782017, 1.2772830447358376, 1.4266446590805815, 1.5732065775636328, 
 1.8401056375971667, 2.1784909215394999, 2.506266882602076, 3.3335988825191176, 4.687787057503483, 6.8602191807881647, 
 11.198474011060968, 14.883466002768214, 20.878255333866864, 1.0, 1.0, 1.0, 1.0, 1.0]).ps())

vertex_reweight_PUS6 = GoodVertexReweighting(
PSet(GoodVertexWeights =[1.0, 0.6747792521746856, 1.0448420078821972, 1.3055015002285708, 1.3983895957384924, 1.4093911155782819, 1.3850308438481276, 1.3018072225453758, 1.1623455679439036, 1.0517773707737472, 0.89838694986924372, 0.76765214151467354, 0.63185640954246791, 0.49262105848611853, 0.42787145593782405, 0.3847054078776958, 0.35778382190253444, 0.34148368315539618, 0.28535617241618649, 0.24963682196802897, 0.15231738209843554, 0.10766396055685283, 0.066294358386045707, 0.039350814964675719, 0.071293966061105704] ).ps())
