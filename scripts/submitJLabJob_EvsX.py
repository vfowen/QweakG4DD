#!/apps/python/PRO/bin/python
from subprocess import call
import sys
import os
import time

def createMacFile(directory,idname,xPos,yPos,zPos,beamE,pol,nEv,nr):
    if not os.path.exists(directory+"/jobs/"+idname):
        os.makedirs(directory+"/jobs/"+idname)
   
    f=open(directory+"/jobs/"+idname+"/myRun.mac",'w')
    f.write("/control/execute myQweakCerenkovOnly.mac\n")
    f.write("/PrimaryEvent/SetBeamPositionX "+str(xPos)+" cm\n")
    f.write("/PrimaryEvent/SetBeamPositionY "+str(yPos)+" cm\n")
    f.write("/PrimaryEvent/SetBeamPositionZ "+str(zPos)+" cm\n")
    f.write("/PrimaryEvent/SetPolarization "+pol+"\n")
    f.write("/EventGen/SetBeamEnergy    "+str(beamE)+" MeV\n")
    f.write("/TrackingAction/TrackingFlag 3\n")
    f.write("/EventGen/SelectOctant 3\n")
    seedA=int(time.time())+10000000+nr
    seedB=int(time.time()*100)++1000000000+nr
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

    return 0

def main():
    
#    _xPos=[0]
    _xPos=[-0.1,-0.05,-0.04,-0.03,-0.02,-0.01,0,0.01,0.02,0.03,0.04,0.05,0.1]
    _email="ciprian@jlab.org"
    _source="/w/hallc-scifs2/qweak/ciprian/QweakG4DD"
    _directory="/lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput"
    _nEv=10000
    _beamE=[5,10,15,20,25,30,35,40,45,50]
    _nr=1
    _nSt=0
    _pol="V"
    submit=0
    
    for xP in _xPos: # x position of the beam
      for beamE in _beamE: # E of the beam
	for nr in range(_nSt,_nr+_nSt): # repeat for nr jobs
	  yP=335.0
	  zP=576.0 #in front of MD no Pb
	  _idN= _pol+'_%04d_%06.2f_%06.2f_%06.2f_%03d'% (beamE,xP,yP,zP,nr) 
	  createMacFile(_directory,_idN,xP,yP,zP,beamE,_pol,_nEv,nr)
	  createXMLfile(_idN,_directory,_email,_source)
	  call(["cp",_source+"/build/QweakSimG4",_directory+"/jobs/"+_idN+"/QweakSimG4"])
	  call(["cp",_source+"/myQweakCerenkovOnly.mac",_directory+"/jobs/"+_idN+"/myQweakCerenkovOnly.mac"])

	  if submit==1:
	    print "submitting X position", xP," for the ",nr," time"," with E ",beamE
	    call(["jsub","-xml",_directory+"/jobs/"+_idN+"/job.xml"])
	  else:
	    print "do not submit ",submit
    
                    
if __name__ == '__main__':
    main()
                            
