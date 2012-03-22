#!/usr/bin/env python
import setupSUSY
from libFrameworkSUSY import *
from libchris import *
from libHadronic import *
from icf.core import PSet,Analysis
from time import strftime
import icf.utils as Utils
from batchGolden import *
from ra1objectid.vbtfElectronId_cff import *
from ra1objectid.vbtfMuonId_cff import *
from ra1objectid.ra3PhotonId_cff import *

default_common.Jets.PtCut = 50.*325./375.

vbtfMuonId_cff 			= Muon_IDFilter( vbtfmuonidps.ps()  )
cutTreeMC,junkVar,l 	= MakeMCTree(100.*325./375.)
vbtfElectronIdFilter	= Electron_IDFilter( vbtfelectronidWP95ps.ps() )
ra3PhotonIdFilter    	= Photon_IDFilter( ra3photonidps.ps() )

def addCutFlowMC(b) :
	b.AddMuonFilter("PreCC",vbtfMuonId_cff) #each one is defined as a routine in the class 'Analysis'
	b.AddPhotonFilter("PreCC",ra3PhotonIdFilter)
	b.AddElectronFilter("PreCC",vbtfElectronIdFilter)
  	b+=cutTreeMC
  	# note: these filters are just 'redefinitions' of common objects, i.e. NOT cuts

#AK5 Calo
conf_ak5_caloMC 			= deepcopy(defaultConfig) #as defined in framework
conf_ak5_caloMC.Ntuple 		= deepcopy(ak5_calo) #as defined in bG
conf_ak5_caloMC.XCleaning 	= deepcopy(default_cc) #as defined in bG
conf_ak5_caloMC.Common 		= deepcopy(default_common) #as defined in bG
conf_ak5_caloMC.Common.print_out()

anal_ak5_caloMC = Analysis("AK5Calo") #creates an instance of the class 'Analysis' called 'AK5Calo'
addCutFlowMC(anal_ak5_caloMC)

outDir = "../results_"+strftime("%d_%b_%H")+"//TruthAnalysis43_bmulti_HTBins_325/"
ensure_dir(outDir)

#mSUGRA_m0_220to3000_m12_100to1000_tanb_10andA0_0_7TeV_Pythia6Z_StoreResults_PU_START42_V11_FastSim_v5_V15_04_02_scan_msugra_Winter11_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1.File = mSUGRA_m0_220to3000_m12_100to1000_tanb_10andA0_0_7TeV_Pythia6Z_StoreResults_PU_START42_V11_FastSim_v5_V15_04_02_scan_msugra_Winter11_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1.File[0:2]
from montecarlo.test import *

anal_ak5_caloMC.Run(outDir,conf_ak5_caloMC,[test_pset])

