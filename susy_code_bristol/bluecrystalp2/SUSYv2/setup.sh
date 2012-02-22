#!/bin/bash
echo
echo "================================"
echo " Setting up your environment..."
echo "================================"
#-----------------------------------------------------------------------------
# Set your ROOTSYS and PYTHONDIR here
export SUSY_WORKING_SW_DIR=$HOME/susy_work/SUSYv2
MY_ROOTSYS='/gpfs_phys/cms-working/software/slc5_amd64_gcc434/lcg/root/5.27.06b-cms23/'
MY_PYTHONPATH=$SUSY_WORKING_SW_DIR/lib
MY_LD_LIBRARY_PATH=$MY_ROOTSYS/lib:/gpfs_phys/cms-working/software/slc5_amd64_gcc434/external/libjpg/8b/lib:/gpfs_phys/cms-working/software/slc5_amd64_gcc434/external/python/2.6.4-cms14/lib:/gpfs_phys/cms-working/software/slc5_amd64_gcc434/external/boost/1.44.0-cms3/lib:~/cms/slc5_amd64_gcc434/external/gcc/4.3.4/lib64:/gpfs_phys/cms-working/software/slc5_amd64_gcc434/external/xrootd/5.28.00d/lib:$SUSY_WORKING_SW_DIR/lib
export PATH=/gpfs_phys/cms-working/software/slc5_amd64_gcc434/external/python/2.6.4-cms14/bin:$PATH
#-----------------------------------------------------------------------------
#
#===============
# ROOTSYS setup
#===============
#if [ -z $ROOTSYS ]; then
#    echo "No ROOTSYS defined!"
export ROOTSYS=$MY_ROOTSYS
#else
#    echo "ROOTSYS already defined."
#fi
echo "-------------------------------------"
echo "ROOTSYS is " $ROOTSYS
echo "====================================="
#--------------------------------------------
#
#=================
# PYTHONDIR setup
#=================
#if [ -z $PYTHONDIR ]; then
#    echo "No PYTHONDIR defined!"
#    export PYTHONDIR=$MY_PYTHONDIR
#else
#    echo "PYTHONDIR already defined."
#fi
#echo "-------------------------------------"
#echo "PYTHONDIR is " $PYTHONDIR
#echo "====================================="
#--------------------------------------------
#
#
# Set up PATH
#=============
# Check PATH for /root/bin, add it if it isn't there
#----------------------------------------------------
#PATH_HAS_ROOT=$(echo $PATH | grep /root/bin)
#if [ -z $PATH_HAS_ROOT ]; then
    #echo "PATH does not have /root/bin."
    export PATH=$ROOTSYS/bin:$PATH
#else
#    echo "PATH already has a /root/bin"
#fi
# Check PATH for /Python/<version>/bin
#PATH_HAS_PYTHON=$(echo $PATH | grep /Python/2.5.4/slc4_amd64_gcc34/bin)
#if [ -z $PATH_HAS_PYTHON ]; then
#    echo "PATH does not have /Python/2.5.4/slc4_amd64_gcc34/bin"
#    export PATH=$PYTHONDIR/bin:$PATH
#else
#    echo "PATH already has a /Python/2.5.4/slc4_amd64_gcc34/bin"
#fi
#echo "-------------------------------------"
#echo "PATH is: " $PATH
#echo "====================================="
#echo
#

# Set up LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$MY_LD_LIBRARY_PATH
echo "LD_LIBRARY_PATH is:" $LD_LIBRARY_PATH

# Set up PYTHONPATH
export PYTHONPATH=$ROOTSYS/lib:$MY_PYTHONPATH
echo "PYTHONPATH is:" $PYTHONPATH

#echo "Generating fresh documentation with doxygen"
#doxygen Doxy_config

echo "====================================="
echo "Set-up complete."
echo "====================================="
echo
