#!/usr/bin/env python
import setupSUSY
from libFrameworkSUSY import *
#from libbryn import *
from libHadronic import *
from libOneLepton import *
from lib_data_Submit import *
from icf.core import PSet,Analysis
from time import strftime
import icf.utils as Utils
from batchGolden import *
from ra1objectid.vbtfElectronId_cff import *
from ra1objectid.vbtfMuonId_cff import *
from ra1objectid.ra3PhotonId_cff import *
from ra1objectid.ra3PhotonId2012_cff import *

default_common.Jets.PtCut=50.*(275./375.)
cutTreeMC, junkVar,junkVar2,junkVar3,l = MakeMCTree(100.*(275./375.),Muon = None)
vbtfMuonId_cff = Muon_IDFilter( vbtfmuonidps.ps()  )
ra3PhotonIdFilter    = Photon_IDFilter2012( ra3photonid2012ps.ps() )
CustomEleID = Electron_Egamma_Veto()
CustomMuID = OL_TightMuID(mu_2012_had.ps())

#vertex_reweight = GoodVertexReweighting(PSet(GoodVertexWeights = switches()["reweight_samples"][number][0]).ps())
#pileup_reweight = PileUpReweighting(PSet(PileUpWeights =switches()["reweight_samples"][number][0] ).ps())

def addCutFlowMC(b) :
  #b.AddWeightFilter("Weight", vertex_reweight)
#  b.AddWeightFilter("Weight", pileup_reweight)
  b.AddMuonFilter("PreCC",CustomMuID)
  b.AddPhotonFilter("PreCC",ra3PhotonIdFilter)
  b.AddElectronFilter("PreCC",CustomEleID)
  b+=cutTreeMC

#AK5 Calo
conf_ak5_caloMC = deepcopy(defaultConfig)
conf_ak5_caloMC.Ntuple = deepcopy(ak5_calo)
conf_ak5_caloMC.XCleaning = deepcopy(default_cc)
conf_ak5_caloMC.Common = deepcopy(default_common)
conf_ak5_caloMC.Common.print_out()
anal_ak5_caloMC=Analysis("AK5Calo")
addCutFlowMC(anal_ak5_caloMC)

from montecarlo.Summer12.FNAL.ICHEP.ZZ_TuneZ2star_8TeV_pythia6_tauola_Summer12_PU_S7_START52_V9_v1_AODSIM_2_gTag_START52_V9B_ICHEP import *
ZZ_TuneZ2star_8TeV_pythia6_tauola_Summer12_PU_S7_START52_V9_v1_AODSIM_2_gTag_START52_V9B_ICHEP.File=ZZ_TuneZ2star_8TeV_pythia6_tauola_Summer12_PU_S7_START52_V9_v1_AODSIM_2_gTag_START52_V9B_ICHEP.File[0:1]

testSample = [ZZ_TuneZ2star_8TeV_pythia6_tauola_Summer12_PU_S7_START52_V9_v1_AODSIM_2_gTag_START52_V9B_ICHEP]

outDir = "../../results_"+strftime("%d_%b")+"//NoSmear37/"
ensure_dir(outDir)

#from CMSSM_Skim import *
anal_ak5_caloMC.Run(outDir,conf_ak5_caloMC,testSample)
