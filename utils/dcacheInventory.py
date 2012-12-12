#!/usr/bin/env python
# encoding: utf-8
"""
dcacheInventory.py

Created by Chris Lucas on 2012-12-12.
Copyright (c) 2012 University of Bristol. All rights reserved.
"""

from optparse import OptionParser

parser = OptionParser()

parser.add_option("-n", "--nameSizes",
                  action="store_true", dest="doNameSize", default=False,
                  help="output names with sizes")
parser.add_option("-t", "--total",
                  action="store_true", dest="doTotalSize", default=False,
                  help="output total size from input file")
parser.add_option("-c", "--cutLines",
                  action="store_true", dest="doCutLines", default=False,
                  help="output lines that meet certain cuts (defined in 'switches')")
parser.add_option("-s", "--sampleSizes",
                  action="store_true", dest="doSampleSize", default=False,
                  help="output sample types with sizes")

(options, args) = parser.parse_args()


## ------------------------------------------------------- ##

def switches():

   myDict = {
      "sizeCut":600, #size cut in GB
      "nameCut":["", "QCD", "Run201", "WJet", "ZJet", "GJet"][0] #to select out a sample type
   }

   return myDict

## ------------------------------------------------------- ##

def sizeCalc(sizeList=None):

   total = 0

   if "str" in str( type(sizeList) ):
      sizeList = [sizeList]

   for s in sizeList:
      if "T" in s:
         total += float( s[:-1] )*1000
      elif "G" in s:
         total += float( s[:-1] )
   
   return total

## ------------------------------------------------------- ##

# load file
iF = open("lpcsusyra1_duOut_reduced.txt" ,'r')

# load content of file
fileCont = []
for line in iF:
   fileCont.append(line)


tmpPaths=[]
size=[]
names=[]

if options.doCutLines:
   print "\n" + "*"*35
   print ">>> Lines that meet the cuts:"
   print "\t Size > %f GB"%switches()['sizeCut']
   print "\t Name including '%s'"%switches()["nameCut"]
   print "*"*35+"\n"

for line in fileCont:
   tmpDir=""
   tmpName=""

   # only consider ICF ntuple maker dirs
   if "ICF/automated" not in line: continue

   tmpDir = line.split("\t")[1]
   tmpName = tmpDir.split("/")[8]
   tmpSize = line.split("\t")[0]

   size.append(tmpSize)
   
   if tmpName not in names:
      names.append(tmpName)

   if options.doCutLines:

      if sizeCalc(tmpSize) > switches()["sizeCut"] and switches()["nameCut"] in tmpDir:
         print line

# calculate total size from list
totalSize = sizeCalc(size)


if options.doTotalSize:
   print "\n*** Total Size (from input txt file): %.1f GB\n"%totalSize


# calculate who's to blame (me...!)
if options.doNameSize:

   print "\n>>> Getting name specific sizes.\n"

   for n in names:
      tmpSize = []
   
      for line in fileCont:
         if n in line:
            tmpSize.append(line.split("\t")[0])
      
      print "User: %s (%.1f GB)"%(n, sizeCalc(tmpSize))


# sample specific sizes
if options.doSampleSize:
   
   print "\n>>> Getting sample specific sizes.\n"

   samples = {
            "QCD":[],
            "ZJet":[],
            "WJet":[],
            "DYJet":[],
            "GJet":[],
            "WW":[],
            "ZZ":[],
            "WZ":[],
            "SMS":[],
            "Run201":[]
            }

   undtmp = []


   for line in fileCont:
      if len(line.split("\t")) <2: continue
      
      tmpSize  = line.split("\t")[0]
      tmpDir   = line.split("\t")[1]

      if "ICF/automated" not in tmpDir:
         undtmp.append(tmpSize)
      else:
         if len(tmpDir.split("/")) < 13:
            undtmp.append(tmpSize)
         else:
            for key, val in samples.iteritems():
               if key in tmpDir:
                  val.append(tmpSize)
   samples["Undefined"]=undtmp

   subTotal = 0
   for key, val in samples.iteritems():
      if key=="Run201": key="Data"
      print "Sample: %s (%.1f GB)"%(key, sizeCalc(val))
      subTotal += sizeCalc(val)

   print "\n*** Total from sample analysis: %.1f GB\n"%subTotal


