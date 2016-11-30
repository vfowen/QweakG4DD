#!/apps/python/PRO/bin/python
from subprocess import call
import sys,os,time

def main():

    ### always check that you have the ranges you need
    beamEnergy=[3, 5, 10, 30, 50, 100]
    yPos=[-100, -95, -90, -80, -60, -40, -20, -10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10, 20, 40, 60, 80, 90, 95, 100]
    yAng=[-89, -85, -80, -60, -40, -35, -30, -25, -20, -15, -10, -7.5, -5, -2.5, 0, 2.5, 5, 10, 15, 20, 25, 30, 35, 40, 60, 80, 85, 89]

    ### fixed values
    zP=576
    xP=335
    xA=23
    nrEv=3000

    ### logistic info
    sourceDir=""
    outputDir=""
    jobName="" ##this should be some unique name for each set of simulations
    email=""
    
    if not os.path.exists(sourceDir+"/jobs"):
        os.makedirs(sourceDir+"/jobs")
    f=open(sourceDir+"/scripts/jobs/"+jobName+".xml","w")
    f.write("<Request>\n")
    f.write("  <Email email=\""+email+"\" request=\"false\" job=\"true\"/>\n")
    f.write("  <Project name=\"qweak\"/>\n")
    #f.write("  <Track name=\"debug\"/>\n") ##For debug purposes instead of simulation below
    f.write("  <Track name=\"simulation\"/>\n")
    f.write("  <Name name=\""+jobName+"\"/>\n")
    f.write("  <OS name=\"centos65\"/>\n")
    f.write("  <Command><![CDATA[\n")
    f.write("QweakSimG4 myRun.mac\n")
    ### FIXME if you have a macro/executable that analyzes the root file you should put it here
    ##    f.write("./scriptNm <input values>\n")
    f.write("  ]]></Command>\n")
    f.write("  <Memory space=\"2000\" unit=\"MB\"/>\n")

    for yA in yAng: # y angle: along bar
        for yP in yPos: # y position: along bar
            for beamE in beamEnergy: # E of the beam
                jobFullName = jobName + "_" + str(beamE) + "_" + str(yA) + "_" + str(yP)
                print jobFullName
                createMacFile(outputDir, jobFullName,
                              xP, yP, zP, xA, yA,
                              beamE, nrEv)
                call(["cp",sourceDir+"/myQweakCerenkovOnly.mac",
                      outputDir+"/"+jobFullName+"/myQweakCerenkovOnly.mac"])              
                call(["cp",sourceDir+"/build/QweakSimG4",
                      outputDir+"/"+jobFullName+"/QweakSimG4"])
                ###FIXME if you have script you need to copy it over to the folder
                ## call(["cp",source+"/build/scriptNm",outputDir+"/"+jobFullName+"/scriptNm"])

                f.write("  <Job>\n")
                f.write("    <Input src=\""+outputDir+"/"+jobFullName+"/QweakSimG4\" dest=\"QweakSimG4\"/>\n")
                ####FIXME if you have a sript you need to put in here as well
                ##f.write("    <Input src=\""+outputDir+"/"+jobFullName+"/scriptNm\" dest=\"scriptNm\"/>\n")
                f.write("    <Input src=\""+outputDir+"/"+jobFullName+"/myQweakCerenkovOnly.mac\" dest=\"myQweakCerenkovOnly.mac\"/>\n")
                f.write("    <Input src=\""+outputDir+"/"+jobFullName+"/myRun.mac\" dest=\"myRun.mac\"/>\n")                
                f.write("    <Output src=\"QwSim_0.root\" dest=\""+outputDir+"/"+jobFullName+"/QwSim_0.root\"/>\n")
                ####FIXME if your script produces output you need to move it back to the folder
                ##f.write("    <Output src=\"scriptOut.root\" dest=\""+outputDir+"/"+jobFullName+"/scriptOut.root\"/>\n")
                f.write("    <Stdout dest=\""+outputDir+"/"+jobFullName+"/log/log.out\"/>\n")
                f.write("    <Stderr dest=\""+outputDir+"/"+jobFullName+"/log/log.err\"/>\n")
                f.write("  </Job>\n\n")

    
    f.write("</Request>\n")
    f.close()

    call(["swif","create","-workflow",jobName])
    call(["swif","add-jsub","-workflow",jobName,"-script",sourceDir+"/scripts/jobs/"+jobName+".xml"])
    call(["swif","run","-workflow",jobName])

    print "All done"
  
def createMacFile(outDir, jobNm, xP, yP, zP, xA, yA, beamE, nrEv):
    if not os.path.exists(outDir+"/"+jobNm+"/log"):
        os.makedirs(outDir+"/"+jobNm+"/log")
    
    f=open(outDir+"/"+jobNm+"/myRun.mac",'w')
    f.write("/control/execute myQweakCerenkovOnly.mac\n")
    f.write("/PrimaryEvent/SetBeamPositionX "+str(yP)+" cm\n")
    f.write("/PrimaryEvent/SetBeamPositionY "+str(xP)+" cm\n")
    f.write("/PrimaryEvent/SetBeamPositionZ "+str(zP)+" cm\n")
    f.write("/PrimaryEvent/SetBeamDirectionX "+str(yA)+" deg\n") 
    f.write("/PrimaryEvent/SetBeamDirectionY "+str(xA)+" deg\n")

    ## not sure if you have this option in your code
    f.write("/PrimaryEvent/SetFixedPosMom true\n") ##FIXME

    f.write("/PrimaryEvent/SetPolarization L\n")
    f.write("/EventGen/SetBeamEnergy    "+str(beamE)+" MeV\n")
    f.write("/TrackingAction/TrackingFlag 3\n")
    f.write("/EventGen/SelectOctant 3\n")
    seedA=int(time.time()/2000.) 
    seedB=int(time.time()/300.)  
    f.write("/random/setSeeds "+str(seedA)+" "+str(seedB)+"\n")
    f.write("/run/beamOn "+str(nrEv)+"\n")
    f.close()        
    return 0      
    
if __name__ == '__main__':
    main()
                  
