#!/apps/python/PRO/bin/python
from subprocess import call
import sys,os,time

def main():
    
    #center, x,y,z=0,335,560
    _xP=0.
    _yP=335.0
    _zP=560.
    _Px=0.#deg
    _Py=0.
    _beamE=1160#MeV
    _tracking=2# 2=no optical ph and 10x faster than 3=full
    _email="ciprian@jlab.org"
    _source="/lustre/expphy/work/hallc/qweak/ciprian/simCodeG410/QweakG4DD"
    _directory="/lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput/g41001p01/mott/updateCH/mottX1e2/005mStep"
    _nEv=50000
    _nrStop=1000
    _nrStart=500
    _pol="V"
    submit=1

    idRoot= _pol+'x_%04d_%06.2f_%06.2f_%06.2f_%06.2f_%06.2f'% (_beamE,_xP,_yP,_zP,_Px,_Py) 
    for nr in range(_nrStart,_nrStop): # repeat for nr jobs
        _idN= idRoot+'_%04d'%(nr) 
        createMacFile(_directory,_idN,_xP,_yP,_zP,_Px,_Py,_tracking,_beamE,_pol,_nEv,nr)
        call(["cp",_source+"/build/QweakSimG4",_directory+"/jobs/"+_idN+"/QweakSimG4"])
        call(["cp",_source+"/build/QweakAna",_directory+"/jobs/"+_idN+"/QweakAna"])
        call(["cp",_source+"/myQweakCerenkovOnly.mac",_directory+"/jobs/"+_idN+"/myQweakCerenkovOnly.mac"])

    createXMLfile(_source,_directory,idRoot,_nrStart,_nrStop,_email)
    if submit==1:
        print "submitting position (", _xP,_yP,_zP,")"
        print " and momDirection (",_Px,_Py,") with pol",_pol," between ",_nrStart,_nrStop
        call(["jsub","-xml",_source+"/scripts/jobs/"+idRoot+".xml"])
    else:
        print "do not submit ",submit

    print "I am all done"

def createMacFile(directory,idname,
                  xPos,yPos,zPos,
                  Px,Py,tracking,
                  beamE,pol,nEv,nr):
    if not os.path.exists(directory+"/jobs/"+idname+"/log"):
        os.makedirs(directory+"/jobs/"+idname+"/log")
   
    f=open(directory+"/jobs/"+idname+"/myRun.mac",'w')
    f.write("/control/execute myQweakCerenkovOnly.mac\n")
    f.write("/PrimaryEvent/SetBeamPositionX "+str(xPos)+" cm\n")
    f.write("/PrimaryEvent/SetBeamPositionY "+str(yPos)+" cm\n")
    f.write("/PrimaryEvent/SetBeamPositionZ "+str(zPos)+" cm\n")
    f.write("/PrimaryEvent/SetBeamDirectionX "+str(Px)+" deg\n")
    f.write("/PrimaryEvent/SetBeamDirectionY "+str(Py)+" deg\n")
    f.write("/PrimaryEvent/SetFixedPosMom true\n")
    f.write("/PrimaryEvent/SetPolarization "+pol+"\n")
    f.write("/EventGen/SetBeamEnergy    "+str(beamE)+" MeV\n")
    f.write("/TrackingAction/TrackingFlag "+str(tracking)+"\n")
    f.write("/EventGen/SelectOctant 3\n")
    seedA=int(time.time()/2000.)+   100*nr+nr
    seedB=int(time.time()/300. ) +10000*nr+nr
    f.write("/random/setSeeds "+str(seedA)+" "+str(seedB)+"\n")
    f.write("/run/beamOn "+str(nEv)+"\n")
    f.close()
    return 0

def createXMLfile(source,writeDir,idRoot,nStart,nStop,email):
    
    if not os.path.exists(source+"/scripts/jobs"):
        os.makedirs(source+"/scripts/jobs")

    f=open(source+"/scripts/jobs/"+idRoot+".xml","w")
    f.write("<Request>\n")
    f.write("  <Email email=\""+email+"\" request=\"false\" job=\"true\"/>\n")
    f.write("  <Project name=\"qweak\"/>\n")
#    f.write("  <Track name=\"debug\"/>\n")
    f.write("  <Track name=\"simulation\"/>\n")
    f.write("  <Name name=\""+idRoot+"\"/>\n")
    f.write("  <OS name=\"centos65\"/>\n")
    f.write("  <Command><![CDATA[\n")
    f.write("QweakSimG4 myRun.mac\n")
    f.write("QweakAna 3 QwSim_0.root\n")
    f.write("  ]]></Command>\n")
    f.write("  <Memory space=\"2000\" unit=\"MB\"/>\n")

    for nr in range(nStart,nStop): # repeat for nr jobs
        f.write("  <Job>\n")
        idName= writeDir+"/jobs/"+idRoot+'_%04d'%(nr)
        f.write("    <Input src=\""+idName+"/QweakSimG4\" dest=\"QweakSimG4\"/>\n")
        f.write("    <Input src=\""+idName+"/QweakAna\" dest=\"QweakAna\"/>\n")
        f.write("    <Input src=\""+idName+"/myQweakCerenkovOnly.mac\" dest=\"myQweakCerenkovOnly.mac\"/>\n")
        f.write("    <Input src=\""+idName+"/myRun.mac\" dest=\"myRun.mac\"/>\n")
        f.write("    <Output src=\"QwSim_0.root\" dest=\""+idName+"/QwSim_0.root\"/>\n")
        f.write("    <Output src=\"o_tuple.root\" dest=\""+idName+"/o_tuple.root\"/>\n")
        f.write("    <Output src=\"o_dist.root\" dest=\""+idName+"/o_dist.root\"/>\n")
        f.write("    <Stdout dest=\""+idName+"/log/log.out\"/>\n")
        f.write("    <Stderr dest=\""+idName+"/log/log.err\"/>\n")
        f.write("  </Job>\n\n")

    f.write("</Request>\n")
    f.close()
    return 0

                    
if __name__ == '__main__':
    main()
                            
