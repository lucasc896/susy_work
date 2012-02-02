#!/usr/bin/env python

import setupSUSY
import data.Run2011.HT_Run2011AB as expr

from subprocess import *
import re


thismachine=Popen(["hostname"], shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True).communicate()


print str(thismachine)

#print a

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


ps = expr.HT_Run2011AB
# This is the source path. Leave as is for CASTOR.
#source = "srm://srm-cms.cern.ch/srm/managerv2?SFN="
source = "srm://gfe02.grid.hep.ph.ic.ac.uk:8443/srm/managerv2?SFN=/pnfs/hep.ph.ic.ac.uk/data/cms/"
#source = "srm://gfe02.grid.hep.ph.ic.ac.uk/srm/managerv2?SFN=/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/"
# This is the target path. Currently set to IC DCACHE. Change!
#target = "srm://gfe02.grid.hep.ph.ic.ac.uk/srm/managerv2?SFN=/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/"
#target = "srm://lcgse02.phy.bris.ac.uk:8444/srm/managerv2?SFN=/gpfs_phys/storm/cms/user/clucas/ICF/automated/2011_10_26_12_39_58/QCD_TuneZ2_HT-100To250_7TeV-madgraph.Summer11-PU_S4_START42_V11-v1.AODSIM/"
target = "srm://lcgse02.phy.bris.ac.uk:8444/srm/managerv2?SFN=/cms/user/clucas/ICF/automated/2011_11_11_15_48_22/HT.Run2011A-05Aug2011-v1.AOD/"
#target="srm://gfe02.grid.hep.ph.ic.ac.uk:8443/srm/managerv2?SFN=/pnfs/hep.ph.ic.ac.uk/data/cms/"

def filename(s):
    return s.split("/")[-1]

def filename_bris(s):
    tmps=s.split("/")[4:]
    s=""
    for i in range(len(tmps)-1):
        s=s+tmps[i]+"/"
    return s+tmps[len(tmps)-1]
    
if __name__ == "__main__":
    files_to_transfer = [f for f in ps.File]
    template="%s%s %s%s"
    for f1 in files_to_transfer:
        f1source=""
        if re.search("lcgui02",str(thismachine)) or re.search("soolin",str(thismachine)) or re.search("calgary",str(thismachine)) :
            f1source=filename_bris(f1)
        elif thismachine == "":
            print "no source files found"
        else :
            f1source=f1
        s = template % (source, f1source, target, filename(f1))
	print s    

