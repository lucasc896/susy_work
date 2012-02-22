# The following line will change the ntuple type
NTUPLE_TYPE = _ICF_

ROOTSYS_INC=/gpfs_phys/cms-working/software/slc5_amd64_gcc434/lcg/root/5.27.06b-cms23/include/
ROOTSYS_LIB=/gpfs_phys/cms-working/software/slc5_amd64_gcc434/lcg/root/5.27.06b-cms23/lib/
ROOTSYS_BIN=/gpfs_phys/cms-working/software/slc5_amd64_gcc434/lcg/root/5.27.06b-cms23/bin/

PYTHON_INC=/gpfs_phys/cms-working/software/slc5_amd64_gcc434/external/python/2.6.4-cms14/include/python2.6/
PYTHON_LIB=-lpython2.6

ROOT_EXTRA_LIBS=-lMathCore -lMathMore -lGenVector
BOOST_PYTHON_LIB=-lboost_python
INCDIR_EXTRA=-I/gpfs_phys/cms-working/software/slc5_amd64_gcc434/external/python/2.6.4-cms14/include/python2.6 -I/gpfs_phys/cms-working/software/slc5_amd64_gcc434/external/boost/1.44.0-cms3/include
LINK_SEARCH_EXTRA=-L/gpfs_phys/cms-working/software/slc5_amd64_gcc434/external/python/2.6.4-cms14/lib -L/gpfs_phys/cms-working/software/slc5_amd64_gcc434/external/boost/1.44.0-cms3/lib
PLATFORM=linux
