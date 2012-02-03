#!/bin/sh
source /gpfs/cluster/phys/cl7359/susy_work/SUSYv2/setup.sh
cd /gpfs/cluster/phys/cl7359/susy_work/SUSYv2/AlphaTPlots/python
./Data.py -j __susyJob__Data.py_20120131_16_34_00/job.json -J ${SGE_TASK_ID} -S __susyJob__Data.py_20120131_16_34_00/status/${SGE_TASK_ID}