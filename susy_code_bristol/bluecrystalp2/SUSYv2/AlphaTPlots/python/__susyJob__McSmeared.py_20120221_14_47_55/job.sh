#!/bin/sh
source /gpfs/cluster/phys/cl7359/susy_work/SUSYv2/setup.sh
cd /gpfs/cluster/phys/cl7359/susy_work/SUSYv2/AlphaTPlots/python
./McSmeared.py -j __susyJob__McSmeared.py_20120221_14_47_55/job.json -J ${PBS_ARRAYID} -S __susyJob__McSmeared.py_20120221_14_47_55/status/${PBS_ARRAYID}
pwd