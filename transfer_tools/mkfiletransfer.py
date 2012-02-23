#!/usr/bin/env python

import setupSUSY
import data.Run2011.HT_Run2011AB as expr
from subprocess import *
import re

thismachine=Popen(["hostname"], shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True).communicate()

print str(thismachine)

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
source = "srm://gfe02.grid.hep.ph.ic.ac.uk:8443/srm/managerv2?SFN=/pnfs/hep.ph.ic.ac.uk/data/cms/"

# This is the target path (don't forget a trailing '/')
target = "srm://lcgse02.phy.bris.ac.uk:8444/srm/managerv2?SFN=/cms/user/clucas/ICF/automated/2011_11_11_15_48_22/"

def filename(s):
    #return s.split("/")[-1]
    return s.split("/")[-2]+"/"+s.split("/")[-1]

def filename_bris(s):
    tmps=s.split("/")[4:]
    s=""
    for i in range(len(tmps)-1):
        s=s+tmps[i]+"/"
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
	print s    

