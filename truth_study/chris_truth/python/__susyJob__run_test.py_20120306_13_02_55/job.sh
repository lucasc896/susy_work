#!/bin/sh
source /gpfs/cluster/phys/cl7359/susy_work/SUSYv2/setup.sh
cd /gpfs/cluster/phys/cl7359/susy_work/SUSYv2/chris_truth/python
./run_test.py -j __susyJob__run_test.py_20120306_13_02_55/job.json -J ${PBS_ARRAYID} -S __susyJob__run_test.py_20120306_13_02_55/status/${PBS_ARRAYID}
