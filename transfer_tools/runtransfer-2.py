#!/usr/bin/env python

import subprocess
import commands
import datetime

### Run: voms-proxy-init -voms cms -vomslife 20:00

## Make sure to change the fileName to something unique for the sample being transferred


fileName = 'sample_transfers/ICHEP/T2tt_8tev_FNALtoIC.txt'
bad_files = "\n 		>>>>>> FILE ERRORS >>>>>> \n\n"

cmd1 = ["touch", fileName]
subprocess.call(cmd1)

print " >>>>>> Opening file: ", fileName
f = open(fileName, 'r')
fileContent = f.read()
f.close()

fileContent =  fileContent.split('\n')


def copyf(command_temp, fileContent):
	args=command_temp.split(" ")
	cmd=["lcg-cp", "-v", args[0], args[1]]
	print datetime.datetime.now().strftime("%Y-%m-%d %H:%M"), cmd
	for k in range(len(fileContent)):
		if args[1] == fileContent[k]:
			print ">> File already copied: Skipping command"
			print "---------------\n\n"
			return
	print ">> Running Copy command"
	subprocess.call(cmd)
	print "---------------\n\n"


def checkf(command_temp, evnum):
	global bad_files
	good_trans=True
	args=command_temp.split(" ")
	cmd1="lcg-ls -l "+args[0]
	cmd2="lcg-ls -l "+args[1]
	check1=commands.getstatusoutput(cmd1)
	check2=commands.getstatusoutput(cmd2)
	# get the file sizes
	check1=check1[1].split(" ")
	check2=check2[1].split(" ")
	
	# check for file errors return a small error message
	# check for file error at target
	try:
		tmpchk2 = check2[14]
	except IndexError:
		tmpchk2 = 0
    # check for file error at source
	try:
		tmpchk1 = check1[14]
	except IndexError:
		print check1
		good_trans==False
		for i in range(len(check1)):
			bad_files=bad_files+check1[i]
		bad_files=bad_files+"\n"
		return good_trans
    
    # check if the size at source and size at target are different
	if check1[14]!=tmpchk2:
		good_trans = False
		for i in range(len(check2)):
			bad_files=bad_files+check2[i]
		bad_files=bad_files+"\n"
	else:
		pass  
	return good_trans


def fileWrite(fileContent_tmp):
	f=open(fileName, 'w')
	print "\n >>>>>>> Writing to file: ", fileName, "\n\n"
	for j in range(len(fileContent_tmp)):
		f.write(fileContent_tmp[j]+"\n")
	f.close()


p=commands.getstatusoutput("python mkfiletransfer2.py")
output_lines = p[1].split("\n")

# note, skips the first line of the mkfiletransfer output
for i in range(1, len(output_lines)):
	copyf(output_lines[i], fileContent)
	#checkf(output_lines[i], i)
	if checkf(output_lines[i], i):
		fileContent.append(output_lines[i].split(" ")[1])
	else:
		print "bad transfer"
	if i%10==0:
		fileWrite(fileContent)
		
print bad_files

f=open(fileName, 'w')
for j in range(len(fileContent)):
	f.write(fileContent[j]+"\n")
f.close()

print "\n>>>>>>  Copying complete.\n"
