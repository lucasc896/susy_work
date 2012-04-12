#!/usr/bin/env python

import configuration_SCBooks as conf,sys,os,readline,getpass,string,fileinput,socket,datetime,re

def remove_multislash(inString) :
    return re.sub(r'//*','/',inString)

def print_and_execute(c) :
    print '',c,''
    os.system(c)
    return

def get_jobrow(db) :
    rows = db.execute('''select job.rowid,cmssw,susycaf,globalTag,dataset
                             from job join tag on tag.rowid=job.tagid join dset on dset.rowid=job.dsetid
                             where state="Unclaimed"''').fetchall()
    for row in rows:
        print row.keys()
        print ('\t'.join([str(item) for item in row]))[0:120] + "..."
    jobnumber = raw_input("\n\n\tWhich job?  ")
    if not jobnumber in [str(row['rowid']) for row in rows] :
        print jobnumber+' is not an `Unclaimed` job'
        db.disconnect()
        sys.exit()
    
    row = db.execute('''select job.rowid,jsonls,cmssw,addpkg,cvsup,cmds,scram_arch,susycaf,dataset,isData,globalTag,nonDefault
                         from job join tag on tag.rowid=job.tagid join dset on dset.rowid=job.dsetid
                         where state="Unclaimed" AND job.rowid='''+jobnumber).fetchone()
    return row

def setup_cmssw(job,path) :
    print_and_execute(
'''
#!/usr/bin/env bash
mkdir -p %(path)s
cd %(path)s
export SCRAM_ARCH=%(arch)s
scram project CMSSW %(cmssw)s
cd %(cmssw)s/src/
eval `scram runtime -sh`
cvs co -r %(susycaf)s -dSUSYBSMAnalysis/SusyCAF UserCode/SusyCAF
'''%{ "path":path, "arch":job["scram_arch"] if job["scram_arch"] else "$SCRAM_ARCH",
      "cmssw":job['cmssw'], "susycaf":job['susycaf'] } +''.join(['''
addpkg '''+pkg for pkg in job['addpkg'].split(',')] if job['addpkg'] else [''])+''.join(['''
cvs up -r '''+f for f in job['cvsup'].split(',')] if job['cvsup'] else [''])   +'''
'''+'\n'.join( job['cmds'].split(';') if job['cmds'] else [''])+'''
scram b -j 8
echo "\n\n\nCheck that everything built:"
scram b
''')
    return


def setup_output_dirs(option) :
    dirs = option["FULL_RPATH"].strip('/').split('/')
    print_and_execute('''
#!/usr/bin/env bash
rfmkdir -p %(FULL_RPATH)s
rfchmod 775 %(FULL_RPATH)s''' % option +''.join(['''
rfchmod 755 /'''+'/'.join(dirs[:-i]) for i in range(1,len(dirs)-dirs.index(option["USER"]))]))


def setup_crab(job,option) :

    SITE = { "CASTOR" : {"SE":"srm-cms.cern.ch",
                         "FULL_RPATH":"/castor/cern.ch/user/%(INITIAL)s/%(USER)s/%(RPATH)s",
                         "USER_REMOTE": "user/%(INITIAL)s/%(USER)s/%(RPATH)s",
                         "SCHEDULER":"glite",
                         "DBS_URL": option["DBS_URL"],
                         "EXTRA": "\n[USER]\nstorage_path=/srm/managerv2?SFN=/castor/cern.ch"
                         },
             "CAF"    : {"SE":"T2_CH_CAF",
                         "FULL_RPATH":"/castor/cern.ch/cms/store/caf/user/%(USER)s/%(RPATH)s" % option,
                         "USER_REMOTE":"%(RPATH)s",
                         "SCHEDULER":"caf",
                         "DBS_URL": (option["DBS_URL"] if option["DBS_URL"] \
                                     else None if job['dataset'].find('ExpressPhysics')<0 \
                                     else "http://cmsdbsprod.cern.ch/cms_dbs_caf_analysis_01/servlet/DBSServlet"),
                         "EXTRA":"\n[CAF]\nqueue=cmscaf1nd\n"
                         },
             "LONDON" : {"SE":"T2_UK_London_IC",
                         "FULL_RPATH":"/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/%(USER)s/%(RPATH)s" % option,
                         "USER_REMOTE":"%(RPATH)s",
                         "SCHEDULER":"glidein",
                         "DBS_URL": option["DBS_URL"],
                         "EXTRA": ""},
             "OSETHACK" : {"SE":"T2_UK_London_IC",
                           "FULL_RPATH":"/pnfs/hep.ph.ic.ac.uk/data/cms/store/user/%(USER)s/%(RPATH)s" % option,
                           "USER_REMOTE":"%(RPATH)s",
                           "SCHEDULER":"glidein",
                           "DBS_URL": "http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet",
                           "EXTRA": "[CRAB]\nserver_name=slc5ucsd\n[GRID]\nse_white_list=T1,T2\nce_white_list=T1,T2\n"},
              "FNAL" : {"SE":"cmssrm.fnal.gov",
              		"FULL_RPATH":"/pnfs/cms/WAX/11/store/user/lpcsusyra1/%(USER)s/%(RPATH)s" % option,
              		"USER_REMOTE":"/store/user/lpcsusyra1/%(USER)s/%(RPATH)s",
              		"SCHEDULER":"glidein",
                        "DBS_URL": option["DBS_URL"],
                        "EXTRA":""}
             }
             
    option["INITIAL"] = option["USER"][0]
    for key,val in SITE[option["SITE"]].items() :
        if val is None : continue
        option[key] = eval('\'\'\''+val+'\'\'\'%option')

    option["EVENTS"] = '''
lumis_per_job=30
total_number_of_lumis=-1
%s'''%('lumi_mask=%(PATH)s/jsonls.txt'%option if job['jsonls'] else '') if job['isData'] else '''
total_number_of_events=-1
events_per_job=20000'''
    
    option["DBS_URL"] = ("dbs_url="+option["DBS_URL"]) if option["DBS_URL"] else ""

    if option["SITE"] != "LONDON" and option["SITE"]!="OSETHACK" and option["SITE"]!="FNAL":
        setup_output_dirs(option)
    if not option["SPLIT"] and job['jsonls'] :
        file = open("%(PATH)s/jsonls.txt"%option,"w")
        print>>file,str(job['jsonls']).replace("'",'"')
        file.close()
    if option["SITE"]=="FNAL":
	crabfile = open("%(PATH)s/crab.cfg"%option,"w")
	print>>crabfile,'''
[CMSSW]
get_edm_output = 1
%(EVENTS)s
pset=SusyCAF_Tree_cfg.py
datasetpath=%(DATASET)s
use_parent=%(USE_PARENT)s
%(DBS_URL)s

[GRID]
virtual_organization=cms
ce_white_list=%(WHITELIST)s

[USER]
copy_data = 1
storage_element=%(SE)s
storage_path = /srm/managerv2?SFN=11
user_remote_dir=%(USER_REMOTE)s
check_user_remote_dir = 0

[CRAB]
cfg=crab.cfg
scheduler=%(SCHEDULER)s
use_server=%(SERVER)d
jobtype=cmssw

%(EXTRA)s
'''% option
	crabfile.close()
    else:
    	crabfile = open("%(PATH)s/crab.cfg"%option,"w")
    	print>>crabfile,'''
[CMSSW]
get_edm_output = 1
%(EVENTS)s
pset=SusyCAF_Tree_cfg.py
datasetpath=%(DATASET)s
use_parent=%(USE_PARENT)s
%(DBS_URL)s

[GRID]
virtual_organization=cms
ce_white_list=%(WHITELIST)s

[USER]
copy_data=1
user_remote_dir=%(USER_REMOTE)s
storage_element=%(SE)s

[CRAB]
cfg=crab.cfg
scheduler=%(SCHEDULER)s
use_server=%(SERVER)d
jobtype=cmssw

%(EXTRA)s
'''% option
    	crabfile.close()
    return


def setup_split(job,path) :
    jsonls = eval(job['jsonls'])
    for run in jsonls.keys() :
        jsonFile = open( '%s/%sjsonls.txt' % (path,run),"w")
        print>>jsonFile, '{ "%s":%s }'%(run,jsonls[run])
        jsonFile.close()

    mcrabfile = open(path+"/multicrab.cfg","w")
    print>>mcrabfile,'''
[MULTICRAB]
cfg=crab.cfg

[COMMON]
CMSSW.total_number_of_lumis=-1
CMSSW.lumis_per_job=10'''+''.join(['''

[Run%(run)s]
CMSSW.runselection=%(run)s
CMSSW.lumi_mask=%(path)s/%(run)sjsonls.txt
'''%{"run":run,"path":path} for run in jsonls.keys()])
    mcrabfile.close()
    return

def setup_multi(job,path) :
    mcrabfile = open(path+"/multicrab.cfg","w")
    print>>mcrabfile,'''
[MULTICRAB]
cfg=crab.cfg
    '''+''.join(['''
    
[%(label)s]
CMSSW.datasetpath=%(ds)s
''' % {"ds":ds,
       "label":ds.strip('/').replace(" ","_").replace("/",".")} \
                 for ds in job['DATASET'].split(',')])
    mcrabfile.close()
    return

def run_crab(job,path,MULTI) :
    print_and_execute('''
#!/usr/bin/env bash
    
source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh
cd %(path)s/%(cmssw)s/src/
eval `scram runtime -sh`
source %(crab_setup)s
cd %(path)s
python %(path)s/%(cmssw)s/src/SUSYBSMAnalysis/SusyCAF/test/susycaf_cfg.py isData=%(isData)d GlobalTag=%(gt)s::All %(other)s
%(crab)s -create -submit
%(crab)s -status &> crab.status
'''%{ "path" : path,
      "cmssw" : job['cmssw'],
      "isData" : job['isData'],
      "gt" : job['globalTag'],
      "other" : job['nonDefault'] if job['nonDefault'] else '',
      "crab" : "multicrab" if MULTI else "crab",
      "crab_setup" : "/afs/cern.ch/cms/ccs/wm/scripts/Crab/crab.sh"
      })
    return


def get_dashboard(path) :
    dash = []
    for line in fileinput.input(path+'/crab.status') :
        if line.find("Dashboard:")>0 :
            dash.append((line[line.find(":")+1:]).strip())
    return '"'+', '.join(dash)+'"'


def get_options(name) :
    option = {}
    timestamp = '_'.join(['%02d'% i for i in datetime.datetime.now().timetuple()[:6]])
    print "Choose output site:"
    for site in ["CASTOR","CAF","LONDON","OSETHACK", "FNAL"] : print '\t'+site
    option["SITE"] = raw_input("\t> ")
    option["SERVER"] = True if raw_input('Run Jobs via Server? [y/n]  ') in ['Y','y',1] else False
    option["SPLIT"] = True if job['jsonls'] and raw_input('Split by run with multicrab? [y/n]') in  ['Y','y',1] else False
    option["USER"] = getpass.getuser()
    option["NODE"] = socket.gethostname()
    option["PATH"] = '/'.join(['','tmp',option['USER'],name,timestamp,''])
    option["RPATH"] = '/'.join(['',name,'automated',timestamp,''])
    option["JOBID"] = job['rowid']
    option['DATASET'] = job['dataset']
    option["MULTI"] = len(job['dataset'].split(','))>1
    option["USE_PARENT"] = 0
    option["WHITELIST"] = raw_input("whitelist sites containing both RECO and RAW: ") if option["USE_PARENT"] else ""
    option["DBS_URL"] = ( raw_input("dbs_url: ") \
                          if raw_input("See advanced options? [y/n] ") in [1,'y','Y','yes','Yes'] \
                          else None )

    print 'You have specified:'
    for key in (["SITE","SERVER"] + \
        (["SPLIT"] if job['jsonls'] else []) + \
        (["WHITELIST"] if option["USE_PARENT"] else []) + \
        (["DBS_URL"] if option["DBS_URL"] else []) ):
        print key+": "+str(option[key])
    return option


db = conf.lockedDB()
db.connect()
job = get_jobrow( db )
option = get_options(db.name)

if option['SPLIT'] and option['MULTI'] :
    print "Cannot run over multiple datasets and also split by run."

elif(raw_input('\nDo it? [y/n] : ') in ['Y','y',1] and \
   not (option['SPLIT'] and option['MULTI'] )) :

    setup_cmssw( job, option["PATH"] )
    setup_crab( job, option)
    if option["SPLIT"] : setup_split( job, option['PATH'] )
    elif option["MULTI"] : setup_multi( job, option['PATH'] )
    run_crab( job, option["PATH"], option["SPLIT"] or option['MULTI'] )
    option["DASH"] = get_dashboard(option["PATH"])
    
    db.execute('''update job set
    state="Processing",
    user="%(USER)s",
    node="%(NODE)s",
    path="%(PATH)s",
    rpath="%(FULL_RPATH)s",
    dash=%(DASH)s where rowid=%(JOBID)d''' % option )

db.disconnect()
