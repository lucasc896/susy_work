	#!/usr/bin/env python

import setupSUSY
import montecarlo.SMS_T2tt_Mgluino_225to1200_mLSP_0to1000_8TeV_Pythia6Z_Summer12_START52_V9_FSIM_v1_AODSIM as expr
from subprocess import *
import re


thismachine=Popen(["hostname"], shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True).communicate()


print str(thismachine)


#import samples.QCD_EMBCE_PSet as expr

# Procedure:
# ==========================
# 0. Get a grid environment and run voms-proxy-init --voms cms
# 1. Edit this file to choose pset and source and dest path (see below)
# 2. Do ./mkfiletransfer.py > fts1.txt (or call it whatever you want)
# 3. Do glite-transfer-submit -s https://lcgfts.gridpp.rl.ac.uk:8443/glite-data-transfer-fts/services/FileTransfer -f fts1.txt
#    This will return a guid (<GUID>)
# 4. Run glite-transfer-status -s https://lcgfts.gridpp.rl.ac.uk:8443/glite-data-transfer-fts/services/FileTransfer <GUID>
# 5. To get verbose status do: glite-transfer-status -lv -s https://lcgfts.gridpp.rl.ac.uk:8443/glite-data-transfer-fts/services/FileTransfer <GUID>

# Configuration:
# ==========================
# This is the pset whose files you wish to copy

ps = expr.SMS_T2tt_Mgluino_225to1200_mLSP_0to1000_8TeV_Pythia6Z_Summer12_START52_V9_FSIM_v1_AODSIM
# This is the source path. Leave as is for CASTOR.

target = "srm://gfe02.grid.hep.ph.ic.ac.uk:8443/srm/managerv2?SFN=/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/dburton/ICF/automated/2012_08_11_18_56_66/"

#source = "srm://lcgse02.phy.bris.ac.uk:8444/srm/managerv2?SFN=/cms/user/clucas/ICF/automated/2012_03_06_15_01_38/mSUGRA_m0_220to3000_m12_100to1000_tanb_10andA0_0_7TeV_Pythia6Z_StoreResults_PU_START42_V11_FastSim_v5_V15_04_02_scan_msugra_Winter11_jetCorrections_L1FastJet_L2Relative_L3Absolute_jetCollections_ak5calo_ak5pf_hbheNoiseFilterDefaultIsoReq_1/"
# This is the target path. Currently set to IC DCACHE. Change!
source = "srm://cmssrm.fnal.gov:8443/11/store/user/lpcsusyra1/"
#target = "srm://lcgse02.phy.bris.ac.uk:8444/srm/managerv2?SFN=/cms/user/clucas/ICF/automated/2012_03_06_13_53_20/SingleMu_Run2011B_PromptReco_v1/"


def filename(s):
    return s.split("/")[-1]
    #return s.split("/")[-2]+"/"+s.split("/")[-1]

def filename_bris(s):
    tmps=s.split("/")[12:]
    #print tmps
    s=""
    for i in range(len(tmps)-1):
        s=s+tmps[i]+"/"
        #print s
    return s+tmps[len(tmps)-1]
    
if __name__ == "__main__":
    files_to_transfer = [f for f in ps.File]
    template="%s%s %s%s"
    #template="%s%s"
    for f1 in files_to_transfer:
        f1source=""
        if re.search("lcgui02",str(thismachine)) or re.search("soolin",str(thismachine)) or re.search("calgary",str(thismachine)) :
            f1source=filename_bris(f1) 
        elif thismachine == "":
            print "no source files found"
        else :
            f1source=f1
        s = template % (source, f1source, target, filename(f1))
        #s = template % (target, filename(f1))
	
	#print filename(f1)
	print s   

