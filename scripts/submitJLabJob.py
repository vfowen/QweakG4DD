#!/apps/python/PRO/bin/python
from subprocess import call
import sys
import os
import time

def createMacFile(directory,idname,xPos,yPos,zPos,beamE,nEv,nr):
    if not os.path.exists(directory+"/jobs/"+idname):
        os.makedirs(directory+"/jobs/"+idname)
   
    f=open(directory+"/jobs/"+idname+"/myRun.mac",'w')
    f.write("/control/execute myQweakCerenkovOnly.mac\n")
    f.write("/PrimaryEvent/SetBeamPositionX "+str(xPos)+" cm\n")
    f.write("/PrimaryEvent/SetBeamPositionY "+str(yPos)+" cm\n")
    f.write("/PrimaryEvent/SetBeamPositionZ "+str(zPos)+" cm\n")
    f.write("/EventGen/SetBeamEnergy    "+str(beamE)+" MeV\n")
    f.write("/TrackingAction/TrackingFlag 3\n")
    f.write("/EventGen/SelectOctant 1\n")
    seedA=int(time.time())+100000000000+nr
    seedB=int(time.time()*100)++10000000000000+nr
    f.write("/random/setSeeds "+str(seedA)+" "+str(seedB)+"\n")
    f.write("/run/beamOn "+str(nEv)+"\n")
    f.close()
    return 0

def createXMLfile(idname,directory,email,source):
    if not os.path.exists(directory+"/jobs/"+idname+"/log"):
        os.makedirs(directory+"/jobs/"+idname+"/log")
    
    f=open(directory+"/jobs/"+idname+"/job.xml","w")
    f.write("<Request>\n")
    f.write("  <Email email=\""+email+"\" request=\"false\" job=\"true\"/>\n")
    f.write("  <Project name=\"qweak\"/>\n")
    f.write("  <Track name=\"simulation\"/>\n")
    f.write("  <Name name=\""+idname+"\"/>\n")
    f.write("  <OS name=\"centos62\"/>\n")
    f.write("  <Command><![CDATA[\n")
    f.write("cd "+directory+"/jobs/"+idname+"\n")
    f.write("rm -rf QweakSimG4\n")
    f.write("rm -rf myQweakCerenkovOnly.mac\n")
    f.write("ln -s "+source+"/build/QweakSimG4 QweakSimG4\n")
    f.write("ln -s "+source+"/myQweakCerenkovOnly.mac myQweakCerenkovOnly.mac\n")
    f.write("QweakSimG4 myRun.mac\n")
    f.write("  ]]></Command>\n")
    f.write("  <Memory space=\"1200\" unit=\"MB\"/>\n")
    f.write("  <TimeLimit unit=\"minutes\" time=\"4320\"/>\n")
    f.write("  <Job>\n")
    f.write("    <Output src=\"QwSim.root\" dest=\""+directory+"/jobs/"+idname+"/QwSim.root\"/>\n")
    f.write("    <Stdout dest=\""+directory+"/jobs/"+idname+"/log/log.out\"/>\n")
    f.write("    <Stderr dest=\""+directory+"/jobs/"+idname+"/log/log.err\"/>\n")
    f.write("  </Job>\n")
    f.write("</Request>\n")
    f.close()

#    os.chmod(directory+"/condor/"+idname+"/cheOther.csh",0755)
    return 0

def main():
    
    _xPos=[0]
#    _xPos=[-10,-5,0,5,10]
    _email="ciprian@jlab.org"
    _source="/w/hallc-scifs2/qweak/ciprian/QweakG4DD"
    _directory="/lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput"
    _nEv=10000
    _beamE=1160
    _nr=20
    submit=1
    
    for xP in _xPos: # x position of the beam
      for nr in range(25,_nr+25): # repeat for nr jobs
	yP=335.0
	zP=560.0
	_idN= 'L_%04d_%06.2f_%06.2f_%06.2f_%03d'% (_beamE,xP,yP,zP,nr) 
	createMacFile(_directory,_idN,xP,yP,zP,_beamE,_nEv,nr)
	createXMLfile(_idN,_directory,_email,_source)

	if submit==1:
	  print "submitting X position", xP," for the ",nr," time"
	  call(["jsub","-xml",_directory+"/jobs/"+_idN+"/job.xml"])
	else:
	  print "do not submit ",submit
    
                    
if __name__ == '__main__':
    main()
                            
