#!/usr/bin/env python

import subprocess
import commands

good_set=True
bad_files="\n 		>>>>>> FILE ERRORS >>>>>> \n\n"

def checkf(command_temp):
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
    if (check1[14]!=tmpchk)&&(len(check1)!=len(check2)):
    	good_set=False
    	print "ERROR"
    	for i in range(len(check2)):
    		bad_files=bad_files+check2[i]
    	bad_files=bad_files+"\n"
    else:
		pass
	
p=commands.getstatusoutput("./mkfiletransfer.py")
output_lines = p[1].split("\n")

print "\n>>>>>>  Checking consistency of transferred files...\n"

for line in range(1,len(output_lines)):
	checkf(output_lines[line])

if good_set==True:
	print "\n >>>>>>  The dataset was transferred fully (congrats!)"
elif good_set==False:
	print "\n >>>>>>  There was an error with the transferred dataset"
	print bad_files
