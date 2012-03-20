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

from validation.cutCounters_cff import * #TW for convenience...

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


#create two generic PSet's for use in plotting

genericPSet_pre = PSet(
DirName      = "275_325Gev",
MinObjects   = 0,
MaxObjects   = 100,
minDR = 0.4 ,
mCut = 2.0 ,
StandardPlots     = True
)

genericPSet_post = PSet(
DirName      = "275_325Gev",
MinObjects   = 2,
MaxObjects   = 15,
minDR = 0.4 ,
mCut = 2.0 ,
StandardPlots     = True
)


def makePlotOp(OP = (), cutTree = None, cut = None, label = "", selection = ""):
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
  
  return out
  pass
  
  
def AddBinedHist(cutTree = None, OP = (), cut = None, htBins = [], TriggerDict = None,lab = "", selection = ""):
	"""docstring for AddBinedHist"""
	out = []
	if (selection == "none"):
		temp_cut = cut
		pOps = makePlotOp(cutTree = cutTree, OP = OP, cut = temp_cut, label = "%s"%(lab))
		out.append(pOps)
	elif ((selection == "pre") or (selection == "full")):
		for lower,upper in zip(htBins,htBins[1:]+[None]):
			if int(lower) == 325 and upper is None: continue
			if int(lower) == 375 and upper is None: continue
			if int(lower) == 475 and upper is None: continue
			if int(lower) == 675 and upper is None: continue
			lowerCut = eval("RECO_CommonHTCut(%d)"%lower)
			out.append(lowerCut)
			cutTree.TAttach(cut, lowerCut)
			print lower, "\n\n", upper, "\n\n"
			if upper:
				upperCut =  eval("RECO_CommonHTLessThanCut(%d)"%upper)
				out.append(upperCut)
				cutTree.TAttach(lowerCut,upperCut)
  			pOps = makePlotOp(cutTree = cutTree, OP = OP, cut = upperCut if upper else lowerCut, label = "%s%d%s"%(lab,lower, "_%d"%upper if upper else ""), selection = "pre")
  			out.append(pOps)

  	return out
  	pass

####
# Define some Cuts
####
NoiseFilt= OP_HadronicHBHEnoiseFilter()
GoodVertexMonster = OP_GoodEventSelection()
ht250_Trigger = RECO_CommonHTCut(250.)
initial_cut_zero = RECO_CommonHTCut(0.) #introduced by Chris
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
alpha = OP_CommonAlphaTCut(0.55)

#extra...?

DiJet5 = OP_NumComJets("==",2)

#Second MC!
def MakeMCTree(Threshold, Split = None):
  out = []

  secondJetET = OP_SecondJetEtCut(Threshold)

  HTBins = []

  if int(Threshold) is 100 and Split == None : HTBins = [375+100*i for i in range(6)]

  cutTreeMC = Tree("MC")
  #new initial cut here
  cutTreeMC.Attach(count_total)
  
  #plot first for the pre-selection sample
  out.append(AddBinedHist(cutTree = cutTreeMC,
      OP = ("TruthAnalysis",genericPSet_pre), cut = count_total,
      htBins = HTBins, TriggerDict = None,lab ="before_cuts", selection = "none"))
      
  # start filling cut tree with pre-selection cuts
  cutTreeMC.TAttach(count_total,ht250_Trigger)
  cutTreeMC.TAttach(ht250_Trigger,NoiseFilt) #if true on ht250 then go on to noisefilt
  cutTreeMC.TAttach(NoiseFilt,GoodVertexMonster)
  
  cutTreeMC.TAttach(GoodVertexMonster,recHitCut)
  cutTreeMC.TAttach(recHitCut,LeadingJetEta)
  cutTreeMC.TAttach(LeadingJetEta,secondJetET)
  cutTreeMC.TAttach(secondJetET,oddJet)
  cutTreeMC.TAttach(oddJet,badMuonInJet)
  cutTreeMC.TAttach(badMuonInJet,oddElectron)
  cutTreeMC.TAttach(oddElectron,oddPhoton)
  cutTreeMC.TAttach(oddPhoton,numComElectrons)
  cutTreeMC.TAttach(numComElectrons,numComPhotons)
  cutTreeMC.TAttach(numComPhotons,VertexPtOverHT)
  cutTreeMC.TAttach(VertexPtOverHT,htCut275)
  
  # fill plots for pre-selection
  out.append(AddBinedHist(cutTree = cutTreeMC,
      OP = ("TruthAnalysis",genericPSet_post), cut = htCut275,
      htBins = HTBins, TriggerDict = None,lab ="preselection_cuts", selection = "pre") )
  
  # perform final cuts
  cutTreeMC.TAttach(htCut275,DeadEcalCutMC)
  cutTreeMC.TAttach(DeadEcalCutMC,MHT_METCut)
  cutTreeMC.TAttach(MHT_METCut,ZeroMuon)
  cutTreeMC.TAttach(ZeroMuon, alpha)
  
  #plot again for post-selection sample
  out.append(AddBinedHist(cutTree = cutTreeMC,
      OP = ("TruthAnalysis",genericPSet_post), cut = alpha,
      htBins = HTBins, TriggerDict = None,lab ="fullselection_cuts", selection = "full"
      ) )
      
  return (cutTreeMC,secondJetET,out)


# Here are the Summer 11 MC samples!!!

from montecarlo.Summer11.DYJetsToLL_TuneZ2_M_50_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1_V15_03_14_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from montecarlo.Summer11.ZJetsToNuNu_50_HT_100_7TeV_madgraph_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.ZJetsToNuNu_100_HT_200_7TeV_madgraph_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.ZJetsToNuNu_200_HT_inf_7TeV_madgraph_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.QCD_Summer11_madgraph_All import *
from montecarlo.Summer11.TTJets_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.WJetsToLNu_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.WJetsToLNu_250_HT_300_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.WJetsToLNu_300_HT_inf_TuneZ2_7TeV_madgraph_tauola_Summer11_PU_S4_START42_V11_v1_V15_03_19_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
from montecarlo.Summer11.T_TuneZ2_t_channel_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.T_TuneZ2_tW_channel_DR_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.Tbar_TuneZ2_t_channel_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1 import *
from montecarlo.Summer11.Tbar_TuneZ2_tW_channel_DR_7TeV_powheg_tauola_Summer11_PU_S4_START42_V11_v1 import *

# PU S6
from montecarlo.Summer11.WW_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1 import *
from montecarlo.Summer11.WZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1 import *
from montecarlo.Summer11.ZZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1 import *

# Some Fall 11 or Spring 12 (not sure which)
from montecarlo.Summer11.QCD_BLepEnriched_TuneZ2_7TeV_pythia6_evtgen_Summer11_PU_S3_START42_V11_v1 import *

# CMSSM Signal Scan
#from montecarlo.mSUGRA_m0_220to3000_m12_100to1000_tanb_10andA0_0_7TeV_Pythia6Z_StoreResults_PU_START42_V11_FastSim_v5_V15_04_02_scan_msugra_Winter11_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1 import *
	
QCD_BLep_sample = [QCD_BLepEnriched_TuneZ2_7TeV_pythia6_evtgen_Summer11_PU_S3_START42_V11_v1]

DiBoson_sample = [WW_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1,
					WZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1,
					ZZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1]

#CMSSM_tanb10_scan = [mSUGRA_m0_220to3000_m12_100to1000_tanb_10andA0_0_7TeV_Pythia6Z_StoreResults_PU_START42_V11_FastSim_v5_V15_04_02_scan_msugra_Winter11_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1]
