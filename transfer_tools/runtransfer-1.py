#!/usr/bin/env python

import subprocess
import commands
import datetime

# by Chris Lucas
# last updated: 23/02/12

### ---------------------------------------------- ###
# To run this script (from this directory):
# 1. mkdir sample_transfers
# 2. touch sample_transfers/<transfername>.txt
# 3. change mkfiletransfer.py accordingly for the dataset being transferred
# 4. voms-proxy-init -voms cms
# 5. ./runtransfer-1.py
# 6. Upon completion, use checktransfer-2.py
### ---------------------------------------------- ###


fileName = 'sample_transfers/<transfername>.txt'

def copyf(command_temp):
    args=command_temp.split(" ")
    cmd=["lcg-cp",args[0],args[1]]
    print datetime.datetime.now().strftime("%Y-%m-%d %H:%M"), cmd
    f = open(fileName, 'r')
    for line in f:
    	if args[1] in line:
    		print "\n >>>> Skipping: File Already Copied \n"
    		return
    subprocess.call(cmd)
    f.close()
    f = open(fileName, 'a')
    f.write("%s\n" % args[1])
    f.close()
    print "---------------\n\n"
    
def checkf(command_temp):
    global good_set, bad_files
    args=command_temp.split(" ")
    cmd1="srmls "+args[0]
    cmd2="srmls "+args[1]
    check1=commands.getstatusoutput(cmd1)
    check2=commands.getstatusoutput(cmd2)
    check1=check1[1].split(" ")
    check2=check2[1].split(" ")
    num=len(check2[3].split("\n")[0].split("/"))
    
    if check1[2]!=check2[2]:
    	good_set=False
    	print "ERROR"
    	for i in range(len(check2)):
    		bad_files=bad_files+check2[i]
    	bad_files=bad_files+"\n"
    else:
	pass


p=commands.getstatusoutput("./mkfiletransfer.py")

output_lines = p[1].split("\n")



# run loop over mkfiletransfer output to copy files
for line in range(1,len(output_lines)):
	copyf(output_lines[line])
	
print "\n>>>>>>  Copying complete.\n"
#print "\n>>>>>>  Checking consistency of transferred files...\n"

# run loop to check transfer integrity
#for line in range(1,len(output_lines)):
#	checkf(output_lines[line])

#if good_set==True:
#	print "\n >>>>>>  The dataset was transferred fully (congrats!)"
#elif good_set==False:
#	print "\n >>>>>>  There was an error with the transferred dataset\n"
#	print bad_files
