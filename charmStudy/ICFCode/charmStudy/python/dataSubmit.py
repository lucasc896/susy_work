#!/usr/bin/env python

import setupSUSY
from libFrameworkSUSY import *
from lib_charmStudy import *
from libHadronic import *
from libOneLepton import *
from icf.core import PSet,Analysis
from time import strftime
from batchGolden import *
from ra1objectid.vbtfElectronId_cff import *
from ra1objectid.vbtfMuonId_cff import *
from ra1objectid.ra3PhotonId_cff import *
from ra1objectid.ra3PhotonId2012_cff import *

vbtfMuonId_cff = Muon_IDFilter( vbtfmuonidps.ps()  )
vbtfElectronIdFilter = Electron_IDFilter( vbtfelectronidWP95ps.ps() )
ra3PhotonIdFilter    = Photon_IDFilter2012( ra3photonid2012ps.ps() )
CustomEleID = Electron_Egamma_Veto()
CustomMuID = OL_TightMuID(mu_2012_had.ps())
#  Change the settings from golden to use the lowest scaled bin.
default_common.Jets.PtCut=50.*(275./375.)
cutTree,blah,blah2,l = MakeDataTree(100.*(275./375.), Muon = None)

def addCutFlowData(a) :
  a.AddMuonFilter("PreCC",CustomMuID)
  a.AddPhotonFilter("PreCC",ra3PhotonIdFilter)
  a.AddElectronFilter("PreCC",CustomEleID)
  a+=cutTree

# AK5 Calo

conf_ak5_caloData = deepcopy(defaultConfig)
conf_ak5_caloData.Ntuple = deepcopy(ak5_calo)
conf_ak5_caloData.XCleaning = deepcopy(default_cc)
conf_ak5_caloData.Common = deepcopy(default_common)
# conf_ak5_calo.Common.print_out()
anal_ak5_caloData=Analysis("AK5Calo")
addCutFlowData(anal_ak5_caloData)


from data.Run2012.FNAL.HTMHT_Run2012C_PromptReco_v1_V17_0_taus_0_doTypeIMetReco_1_clucasJob310 import *
from data.Run2012.FNAL.HTMHT_Run2012C_PromptReco_v2_V17_0_taus_0_doTypeIMetReco_1_clucasJob310 import *

from data.Run2012.FNAL.SingleMu_Run2012C_PromptReco_v1_V17_0_taus_0_doTypeIMetReco_1_clucasJob308 import *
from data.Run2012.FNAL.SingleMu_Run2012C_PromptReco_v2_V17_0_taus_0_doTypeIMetReco_1_clucasJob308 import *

from data.Run2012.FNAL.JetHT_Run2012C_PromptReco_v1_V17_0_taus_0_doTypeIMetReco_1_clucasJob320 import *
from data.Run2012.FNAL.JetHT_Run2012C_PromptReco_v2_V17_0_taus_0_doTypeIMetReco_1_clucasJob320 import *

from data.Run2012.FNAL.SinglePhoton_Run2012C_PromptReco_v1_V17_0_taus_0_doTypeIMetReco_1_clucasJob322 import *
from data.Run2012.FNAL.SinglePhoton_Run2012C_PromptReco_v2_V17_0_taus_0_doTypeIMetReco_1_clucasJob322 import *

HTMHT_Update = [HTMHT_Run2012C_PromptReco_v1_V17_0_taus_0_doTypeIMetReco_1_clucasJob310,HTMHT_Run2012C_PromptReco_v2_V17_0_taus_0_doTypeIMetReco_1_clucasJob310]
SinMu_Update = [SingleMu_Run2012C_PromptReco_v1_V17_0_taus_0_doTypeIMetReco_1_clucasJob308,SingleMu_Run2012C_PromptReco_v2_V17_0_taus_0_doTypeIMetReco_1_clucasJob308]
JetHT_Update = [JetHT_Run2012C_PromptReco_v1_V17_0_taus_0_doTypeIMetReco_1_clucasJob320, JetHT_Run2012C_PromptReco_v2_V17_0_taus_0_doTypeIMetReco_1_clucasJob320]
Photon_Update = [SinglePhoton_Run2012C_PromptReco_v1_V17_0_taus_0_doTypeIMetReco_1_clucasJob322, SinglePhoton_Run2012C_PromptReco_v2_V17_0_taus_0_doTypeIMetReco_1_clucasJob322]

totalUpdate = HTMHT_Update + SinMu_Update

from data.Run2012.FNAL.HCP.HT_Run2012A_13Jul2012_v1_V17_5_taus_0_yeshaqJob358 import *
from data.Run2012.FNAL.HCP.HT_Run2012A_recover_06Aug2012_v1_V17_5_taus_0_yeshaqJob359 import *
HT_Run2012A_13Jul2012_v1_V17_5_taus_0_yeshaqJob358.File = HT_Run2012A_13Jul2012_v1_V17_5_taus_0_yeshaqJob358.File[20:21]
HT_Run2012A = [HT_Run2012A_13Jul2012_v1_V17_5_taus_0_yeshaqJob358]

#outDir = "../Split_Jsons_"+strftime("%d_%b")+"/Data37/"
outDir = "../results_"+strftime("%d_%b")+"//Data37"
ensure_dir(outDir)
anal_ak5_caloData.Run(outDir,conf_ak5_caloData,HT_Run2012A)

