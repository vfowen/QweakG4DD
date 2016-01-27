#!/apps/python/PRO/bin/python
from subprocess import call
import sys,os,time

def main():
    
    #center, x,y,z=0,335,560
    _xP=0.#cm 
    _yP=335.0
    _zP=571.9
    _Px=0.#deg
    _Py=0.
    _beamE=1160#MeV
    #_fixedPosMom=True
    _tracking=2# 2=no optical ph and 10x faster than 3=full
    _email="ciprian@jlab.org"
    _source="/w/hallc-scifs2/qweak/ciprian/simCodeG410/QweakG4DD"
    _directory="/lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput/g41001p01/mott/updateCH/sampled"
    _nEv=80000
    _nrStop=200
    _nrStart=0
    _pol="f"
    _polT="mV" #V for + helicity mV for - helicity
    submit=1
    
    for nr in range(_nrStart,_nrStop): # repeat for nr jobs
        _idN= _polT+'_sampled_%03dk_%03d'% (_nEv/1000,nr) 
        createMacFile(_directory,_idN,_xP,_yP,_zP,_Px,_Py,_tracking,_beamE,_pol,_nEv,nr)
        createXMLfile(_idN,_directory,_email,_source)

        ##create input files
        seedA=int(time.time())+1000000*nr+nr
        if _polT=="V":
            call("root -l -q -b ../rootScripts/samplePrimaryDist.C\\("+str(seedA)+","+str(_nEv)+",1\\)",shell=True)
        else:
            call("root -l -q -b ../rootScripts/samplePrimaryDist.C\\("+str(seedA)+","+str(_nEv)+",-1\\)",shell=True)
        call(["mv","positionMomentum.in",_directory+"/"+_idN+"/positionMomentum.in"])
        call(["mv","polarization.in",_directory+"/"+_idN+"/polarization.in"])

        call(["cp",_source+"/build/QweakSimG4",_directory+"/"+_idN+"/QweakSimG4"])
        call(["cp",_source+"/myQweakCerenkovOnly.mac",_directory+"/"+_idN+"/myQweakCerenkovOnly.mac"])

	if submit==1:
            print "submitting position sampled with id",_idN," for the ",nr,"th time"
            call(["jsub","-xml",_directory+"/"+_idN+"/job.xml"])
	else:
            print "Not submitting position sampled with id",_idN," for the ",nr,"th time"

    print "I am all done"

def createMacFile(directory,idname,
                  xPos,yPos,zPos,
                  Px,Py,tracking,
                  beamE,pol,nEv,nr):
    if not os.path.exists(directory+"/"+idname):
        os.makedirs(directory+"/"+idname)
   
    f=open(directory+"/"+idname+"/myRun.mac",'w')
    f.write("/control/execute myQweakCerenkovOnly.mac\n")
    f.write("/PrimaryEvent/SetBeamPositionX "+str(xPos)+" cm\n")
    f.write("/PrimaryEvent/SetBeamPositionY "+str(yPos)+" cm\n")
    f.write("/PrimaryEvent/SetBeamPositionZ "+str(zPos)+" cm\n")
    f.write("/PrimaryEvent/SetBeamDirectionX "+str(Px)+" deg\n")
    f.write("/PrimaryEvent/SetBeamDirectionY "+str(Py)+" deg\n")
    f.write("/PrimaryEvent/SetFixedPosMom false\n")
    f.write("/PrimaryEvent/SetPolarization "+pol+"\n")
    f.write("/EventGen/SetBeamEnergy    "+str(beamE)+" MeV\n")
    f.write("/TrackingAction/TrackingFlag "+str(tracking)+"\n")
    f.write("/EventGen/SelectOctant 3\n")
    seedA=int(time.time())+      1000000*nr+nr
    seedB=int(time.time()*100)+100000000*nr+nr
    f.write("/random/setSeeds "+str(seedA)+" "+str(seedB)+"\n")
    f.write("/run/beamOn "+str(nEv)+"\n")
    f.close()
    return 0

def createXMLfile(idname,directory,email,source):
    if not os.path.exists(directory+"/"+idname+"/log"):
        os.makedirs(directory+"/"+idname+"/log")
    
    f=open(directory+"/"+idname+"/job.xml","w")
    f.write("<Request>\n")
    f.write("  <Email email=\""+email+"\" request=\"false\" job=\"true\"/>\n")
    f.write("  <Project name=\"qweak\"/>\n")
    f.write("  <Track name=\"simulation\"/>\n")
    f.write("  <Name name=\""+idname+"\"/>\n")
    f.write("  <OS name=\"centos65\"/>\n")
    f.write("  <Command><![CDATA[\n")
    f.write("cd "+directory+"/"+idname+"\n")
    f.write("QweakSimG4 myRun.mac\n")
    f.write("  ]]></Command>\n")
    f.write("  <Memory space=\"1200\" unit=\"MB\"/>\n")
    f.write("  <TimeLimit unit=\"minutes\" time=\"2000\"/>\n")
    f.write("  <Job>\n")
    f.write("    <Stdout dest=\""+directory+"/"+idname+"/log/log.out\"/>\n")
    f.write("    <Stderr dest=\""+directory+"/"+idname+"/log/log.err\"/>\n")
    f.write("  </Job>\n")
    f.write("</Request>\n")
    f.close()
    return 0
                    
if __name__ == '__main__':
    main()
                            
