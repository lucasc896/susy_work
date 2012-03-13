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

vbtfMuonId_cff 			= Muon_IDFilter( vbtfmuonidps.ps()  )
cutTreeMC,junkVar,l 	= MakeMCTree(100.)
vbtfElectronIdFilter	= Electron_IDFilter( vbtfelectronidWP95ps.ps() )
ra3PhotonIdFilter    	= Photon_IDFilter( ra3photonidps.ps() )

def addCutFlowMC(b) :
#  b.AddWeightFilter("Weight", vertex_reweight)
  b.AddMuonFilter("PreCC",vbtfMuonId_cff) #each one is defined as a routine in the class 'Analysis'
  b.AddPhotonFilter("PreCC",ra3PhotonIdFilter)
  b.AddElectronFilter("PreCC",vbtfElectronIdFilter)
  b+=cutTreeMC

#AK5 Calo
conf_ak5_caloMC 			= deepcopy(defaultConfig) #as defined in framework
conf_ak5_caloMC.Ntuple 		= deepcopy(ak5_calo) #as defined in bG
conf_ak5_caloMC.XCleaning 	= deepcopy(default_cc) #as defined in bG
conf_ak5_caloMC.Common 		= deepcopy(default_common) #as defined in bG
conf_ak5_caloMC.Common.print_out()

anal_ak5_caloMC = Analysis("AK5Calo") #creates an instance of the class 'Analysis' called 'AK5Calo'
addCutFlowMC(anal_ak5_caloMC)

outDir = "../results_"+strftime("%d_%b_%H")+"//TruthAnalysis_BLep/"
ensure_dir(outDir)

#from montecarlo.Summer11.QCD_BLepEnriched_TuneZ2_7TeV_pythia6_evtgen_Summer11_PU_S3_START42_V11_v1 import *
#from montecarlo.Summer11.ZZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1 import *
#ZZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1.File = ZZ_TuneZ2_7TeV_pythia6_tauola_Fall11_PU_S6_START42_V14B_v1.File[0:5]

from montecarlo.Summer11.test import *

anal_ak5_caloMC.Run(outDir,conf_ak5_caloMC,[test_pset])
#anal_ak5_caloMC.Run(outDir,conf_ak5_caloMC,QCD_BLep_sample)

