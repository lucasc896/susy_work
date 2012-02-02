#!/usr/bin/env python

import subprocess
import commands

def copyf(command_temp):
    args=command_temp.split(" ")
    cmd=["lcg-cp",args[0],args[1]]
    print cmd
    subprocess.call(cmd)
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
