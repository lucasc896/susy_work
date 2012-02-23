#!/usr/bin/env python

import subprocess
import commands

# by Chris Lucas
# last updated: 23/02/12

### ---------------------------------------------- ###
# To run this script (from this directory):
# 1. change mkfiletransfer.py accordingly for the dataset being transferred
# 2. ./checktransfer-2.py
# 3. any mistransferred files will have their errors printed at termination
# 4. running ./mkfiletransfer.py will give the arguements for lcg-cp to
#    fix these problem files
# 5. run ./checktransfer-2.py again to confirm consistency of dataset
### ---------------------------------------------- ###

good_set=True
bad_files="\n 		>>>>>> FILE ERRORS >>>>>> \n\n"

def checkf(command_temp, evnum):
    global good_set, bad_files
    args=command_temp.split(" ")
    cmd1="lcg-ls -l "+args[0]
    cmd2="lcg-ls -l "+args[1]
    check1=commands.getstatusoutput(cmd1)
    check2=commands.getstatusoutput(cmd2)
    check1=check1[1].split(" ")
    check2=check2[1].split(" ")
    
    # input a temporary variable in case file does not exist (ie. no check2[14] element)
    try:
    	tmpchk = check2[14]
    except IndexError:
    	tmpchk = 0
    
    # check if two files are of the same size
    if check1[14]!=tmpchk:
    	good_set=False
    	print "ERROR ", evnum
    	for i in range(len(check2)):
    		bad_files=bad_files+check2[i]
    	bad_files=bad_files+"\n"
    else:
		pass
	
p=commands.getstatusoutput("./mkfiletransfer2.py")
output_lines = p[1].split("\n")

print "\n>>>>>>  Checking consistency of transferred files..."

for line in range(1,len(output_lines)):
	checkf(output_lines[line], line)

if good_set==True:
	print "\n>>>>>>  The dataset was transferred fully (CONGRATS!) \n"
elif good_set==False:
	print "\n>>>>>>  There was an error with the transferred dataset"
	print bad_files
