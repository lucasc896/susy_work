#!/bin/sh
source /gpfs/cluster/phys/cl7359/susy_work/SUSYv2/setup.sh
cd /gpfs/cluster/phys/cl7359/susy_work/SUSYv2/AlphaTPlots/python
./McNoSmear.py -j __susyJob__McNoSmear.py_20120220_11_41_27/job.json -J ${SGE_TASK_ID} -S __susyJob__McNoSmear.py_20120220_11_41_27/status/${SGE_TASK_ID}