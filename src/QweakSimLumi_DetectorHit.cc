/*

   \file QweakSimLumi_DetectorHit.cc
   \author Wade Duvall

*/

#include "G4Circle.hh"
#include "QweakSimLumi_DetectorHit.hh"

// G4Allocator... what does this do again?
G4Allocator<QweakSimLumi_DetectorHit> QweakSimLumi_DetectorHitAllocator;

QweakSimLumi_DetectorHit::QweakSimLumi_DetectorHit() {
    detectorID                    = -1;
    primaryEventNumber            = -1;
    trackID                       = -1.;

    particleName                  = "None";
    particleType                  = -1;

    time                          = 0.;

    hasBeenHit                    = 0;
    edgeEventFlag                 = 0;
    nbOfHits                      = 0;

    worldPos                      = G4ThreeVector(0.0,0.0,0.0);
    localPos                      = G4ThreeVector(0.0,0.0,0.0);
    localExitPos                  = G4ThreeVector(0.0,0.0,0.0);
    originVertexPosition          = G4ThreeVector(0.0,0.0,0.0);

    worldMomentum                 = G4ThreeVector(0.0,0.0,0.0);
    localMomentum                 = G4ThreeVector(0.0,0.0,0.0);
    currentMomentumDirection      = G4ThreeVector(0.0,0.0,0.0);
    originVertexMomentumDirection = G4ThreeVector(0.0,0.0,0.0);

    originVertexKineticEnergy     = 0.;
    originVertexTotalEnergy       = 0.;

    currentKineticEnergy          = 0.;
    currentTotalEnergy            = 0.;

    depositedEnergyHit            = 0.;

    pLogV                         = 0;
}

QweakSimLumi_DetectorHit::QweakSimLumi_DetectorHit(G4int detector_id) {
    detectorID = detector_id;
    time       = 0.;
    pLogV      = 0;
}

QweakSimLumi_DetectorHit::~QweakSimLumi_DetectorHit() {;}

QweakSimLumi_DetectorHit::QweakSimLumi_DetectorHit(const QweakSimLumi_DetectorHit &right)
: G4VHit() {
    detectorID                    = right.detectorID;
    primaryEventNumber            = right.primaryEventNumber;
    trackID                       = right.trackID;
    
    particleName                  = right.particleName;
    particleType                  = right.particleType;

    time                          = right.time;

    hasBeenHit                    = right.hasBeenHit;
    edgeEventFlag                 = right.edgeEventFlag;
    nbOfHits                      = right.nbOfHits;

    worldPos                      = right.worldPos;
    localPos                      = right.localPos;
    localExitPos                  = right.localExitPos;
    originVertexPosition          = right.originVertexPosition;

    worldMomentum                 = right.worldMomentum;
    localMomentum                 = right.localMomentum;
    currentMomentumDirection      = right.currentMomentumDirection;
    originVertexMomentumDirection = right.originVertexMomentumDirection;

    originVertexKineticEnergy     = right.originVertexKineticEnergy;
    originVertexTotalEnergy       = right.originVertexTotalEnergy;

    currentKineticEnergy          = right.currentKineticEnergy;
    currentTotalEnergy            = right.currentTotalEnergy;

    depositedEnergyHit            = right.depositedEnergyHit;

    cellPos                       = right.cellPos;
    cellRot                       = right.cellRot;

    pLogV                         = right.pLogV;
}

const QweakSimLumi_DetectorHit& QweakSimLumi_DetectorHit::operator=(const QweakSimLumi_DetectorHit &right) {
    detectorID                    = right.detectorID;
    primaryEventNumber            = right.primaryEventNumber;
    trackID                       = right.trackID;
    
    particleName                  = right.particleName;
    particleType                  = right.particleType;

    time                          = right.time;

    hasBeenHit                    = right.hasBeenHit;
    edgeEventFlag                 = right.edgeEventFlag;
    nbOfHits                      = right.nbOfHits;

    worldPos                      = right.worldPos;
    localPos                      = right.localPos;
    localExitPos                  = right.localExitPos;
    originVertexPosition          = right.originVertexPosition;

    worldMomentum                 = right.worldMomentum;
    localMomentum                 = right.localMomentum;
    currentMomentumDirection      = right.currentMomentumDirection;
    originVertexMomentumDirection = right.originVertexMomentumDirection;

    originVertexKineticEnergy     = right.originVertexKineticEnergy;
    originVertexTotalEnergy       = right.originVertexTotalEnergy;

    currentKineticEnergy          = right.currentKineticEnergy;
    currentTotalEnergy            = right.currentTotalEnergy;

    depositedEnergyHit            = right.depositedEnergyHit;

    cellPos                       = right.cellPos;
    cellRot                       = right.cellRot;
    pLogV                         = right.pLogV;

    return *this;
}

int QweakSimLumi_DetectorHit::operator==(const QweakSimLumi_DetectorHit&) const {
    return 0;
}

void QweakSimLumi_DetectorHit::Draw() {
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

    if(pVVisManager) {
        G4Colour colourHit (255/255., 255/255., 0/255.);  // yellow

        G4VisAttributes attribs(colourHit);

        G4Circle circle(worldPos);
        circle.SetScreenSize(0.01);
        circle.SetFillStyle(G4Circle::filled);
        circle.SetVisAttributes(attribs);

        pVVisManager->Draw(circle);
    }
}

void QweakSimLumi_DetectorHit::Print() {
    G4cout << " Lumi[" << detectorID << "] : time " << time/ns
        << " (nsec) --- local (x,y,z) [cm] "
        << worldPos.x()/cm << ", "
        << worldPos.y()/cm << ", "
        << worldPos.z()/cm
        << G4endl << G4endl;
}
