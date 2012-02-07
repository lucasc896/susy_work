#!/usr/bin/env python

import subprocess
import commands

def rmf(command_tmp):
    cmd=["srmrm", command_tmp]
    print cmd
    subprocess.call(cmd)
    print "---------------\n\n"


f = open('to_delete.txt', 'r')

output_lines = f.read()

do_remove=False

for line in range(len(output_lines)-1):
	if line==0:
		print output_lines.split("\n")[line]
		print "Is this the right type of directory?"
		ok = raw_input()
		if ok in ('y', 'ye', 'yes'):
			do_remove=True
		if ok in ('n', 'no', 'nop', 'nope'):
			do_remove=False
		
	if do_remove==True:
		rmf(output_lines.split("\n")[line])
	else:
		print "BE MORE CAREFUL WITH REMOVING FILES"