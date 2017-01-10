#!/apps/python/PRO/bin/python
from subprocess import call
import sys,os,time

def main():
    
    directory="/lustre/expphy/volatile/hallc/qweak/ciprian/farmoutput/g41001p01/sample/Mtx5e1_modTrj_glPhi_2PbVol_stp002mm"
    nEv=250000
    nrStop=5000
    nrStart=4084
    pol="V"
    nDist=203

    idRoot = pol+'_sampled_%03dk'% (nEv/1000)

    for nr in range(nrStart,nrStop): # repeat for nr jobs
        idN = idRoot+'_%05d'% (nr)
        print idN
        
        if not os.path.exists(directory+"/"+idN+"/log"):
            os.makedirs(directory+"/"+idN+"/log")

        if pol=="V":
            call("root -l -q -b ../rootScripts/samplePrimaryDist.C\\("+str(nEv)+",1,"+str(nr)+","+str(nDist)+"\\)",shell=True)
        else:
            call("root -l -q -b ../rootScripts/samplePrimaryDist.C\\("+str(nEv)+",-1,"+str(nr)+","+str(nDist)+"\\)",shell=True)
        
        call(["mv","positionMomentum_%d.in"%(nr),directory+"/"+idN+"/positionMomentum.in"])
        call(["mv","polarization_%d.in"%(nr),directory+"/"+idN+"/polarization.in"])

        
    print "I am all done"

                    
if __name__ == '__main__':
    main()
                            
