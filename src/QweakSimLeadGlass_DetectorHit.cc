
// QweakSimLeadGlass_DetectorHit.cc
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#include "QweakSimLeadGlass_DetectorHit.hh"

//--- geant4 includes
#include "G4Circle.hh"



/////// --------------------------------------------------------------------

G4Allocator<QweakSimLeadGlass_DetectorHit> QweakSimLeadGlass_DetectorHitAllocator;

/////// --------------------------------------------------------------------

QweakSimLeadGlass_DetectorHit::QweakSimLeadGlass_DetectorHit()
{
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
	
    //calculate in Event Action
    //originVertexThetaAngle      = 0.;
    //originVertexPhiAngle        = 0.;
	
    originVertexKineticEnergy     = 0.;
    originVertexTotalEnergy       = 0.;

    currentKineticEnergy          = 0.;
    currentTotalEnergy            = 0.;
	
    //primaryQ2                   = 0.;
    //crossSection                = 0.;
    //crossSectionWeight          = 0.;
	
    //calculated in Event Action
    //globalThetaAngle            = 0.;
    //globalPhiAngle              = 0.;
	
    //--- LeadGlass deposited energy
    depositedEnergyHit               = 0.;
	
    pLogV                         = 0;
}



/////// --------------------------------------------------------------------

QweakSimLeadGlass_DetectorHit::QweakSimLeadGlass_DetectorHit(G4int detector_id)
{
    detectorID = detector_id;
    time       = 0.;
    pLogV      = 0;
	
}



/////// --------------------------------------------------------------------

QweakSimLeadGlass_DetectorHit::~QweakSimLeadGlass_DetectorHit()
{;}



/////// --------------------------------------------------------------------

QweakSimLeadGlass_DetectorHit::QweakSimLeadGlass_DetectorHit(const QweakSimLeadGlass_DetectorHit &right)
: G4VHit() 
{
    detectorID     = right.detectorID;
	
    primaryEventNumber = right.primaryEventNumber;
	
    trackID        = right.trackID;

    particleName   = right.particleName;
    particleType   = right.particleType;
	
    time           = right.time;
	
    hasBeenHit     = right.hasBeenHit;
    edgeEventFlag  = right.edgeEventFlag;
    nbOfHits       = right.nbOfHits;
	
    worldPos       = right.worldPos;
    localPos       = right.localPos;
    localExitPos   = right.localExitPos;
    originVertexPosition          = right.originVertexPosition;
	
    worldMomentum                 = right.worldMomentum;
    localMomentum                 = right.localMomentum;
    currentMomentumDirection      = right.currentMomentumDirection;
    originVertexMomentumDirection = right.originVertexMomentumDirection;
    
    //originVertexThetaAngle      = right.originVertexthetaAngle;
    //originVertexPhiAngle        = right.originVertexPhiAngle;
	
    originVertexKineticEnergy     = right.originVertexKineticEnergy;
    originVertexTotalEnergy       = right.originVertexTotalEnergy;
	
    currentKineticEnergy          = right.currentKineticEnergy;
    currentTotalEnergy            = right.currentTotalEnergy;
	
    //primaryQ2                   = right.primaryQ2;
    //crossSection                = right.crossSection;
    //crossSectionWeight          = right.crossSectionWeight;
	
    //globalThetaAngle            = right.globalThetaAngle;
    //globalPhiAngle              = right.globalPhiAngle;
	
    //--- LeadGlass deposited energy
    depositedEnergyHit               = right.depositedEnergyHit;
	
    cellPos        = right.cellPos;
    cellRot        = right.cellRot;
    pLogV          = right.pLogV;
	
}



/////// --------------------------------------------------------------------

const QweakSimLeadGlass_DetectorHit& QweakSimLeadGlass_DetectorHit::operator=(const QweakSimLeadGlass_DetectorHit &right)
{
    detectorID     = right.detectorID;
	
    primaryEventNumber = right.primaryEventNumber;
	
    trackID        = right.trackID;
	
    particleName   = right.particleName;
    particleType   = right.particleType;
	
    time           = right.time;
	
    hasBeenHit     = right.hasBeenHit;
    edgeEventFlag  = right.edgeEventFlag;
    nbOfHits       = right.nbOfHits;
	
    worldPos       = right.worldPos;
    localPos       = right.localPos;
    localExitPos   = right.localExitPos;
    originVertexPosition          = right.originVertexPosition;

    worldMomentum                 = right.worldMomentum;
    localMomentum                 = right.localMomentum;
    currentMomentumDirection      = right.currentMomentumDirection;
    originVertexMomentumDirection = right.originVertexMomentumDirection;
	
    //originVertexThetaAngle      = right.originVertexthetaAngle;
    //originVertexPhiAngle        = right.originVertexPhiAngle;
    
    originVertexKineticEnergy     = right.originVertexKineticEnergy;
    originVertexTotalEnergy       = right.originVertexTotalEnergy;
	
    currentKineticEnergy          = right.currentKineticEnergy;
    currentTotalEnergy            = right.currentTotalEnergy;
	
    //primaryQ2                   = right.primaryQ2;
    //crossSection                = right.crossSection;
    //crossSectionWeight          = right.crossSectionWeight;
	
    //globalThetaAngle            = right.globalThetaAngle;
    //globalPhiAngle              = right.globalPhiAngle;
	
    //--- LeadGlass deposited energy
    depositedEnergyHit               = right.depositedEnergyHit;
	
    cellPos        = right.cellPos;
    cellRot        = right.cellRot;
    pLogV          = right.pLogV;
	
    return *this;
	
}



/////// --------------------------------------------------------------------

int QweakSimLeadGlass_DetectorHit::operator==(const QweakSimLeadGlass_DetectorHit & ) const
{
    //return (this==&right) ? 1 : 0;
    return 0;
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass_DetectorHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	
    if (pVVisManager)
    {
        //--- draw small yellow balls for the impact point
		
        G4Colour colourHit (255/255., 255/255., 0/255.);  // yellow
		
        G4VisAttributes attribs(colourHit);
		
        G4Circle circle(worldPos);
        circle.SetScreenSize(0.01);
        circle.SetFillStyle(G4Circle::filled);
        circle.SetVisAttributes(attribs);
		
        pVVisManager->Draw(circle);
		
        //--- draw/overlay a white drift cell for a hit
		
        // G4Transform3D trans(cellRot.inverse(),cellPos);
        // const G4VisAttributes* pVA = pLogV->GetVisAttributes();
        // if(pVA) attribs = *pVA;
        // G4Colour colourCell (1.,1.,1.);    // white
        // attribs.SetColour(colourCell);
        // attribs.SetForceSolid(true);
        // attribs.SetVisibility(true);
        // pVVisManager->Draw(*pLogV,attribs,trans);
		
    }
	
}



/////// --------------------------------------------------------------------

void QweakSimLeadGlass_DetectorHit::Print()
{
  G4cout << " LeadGlass[" << detectorID << "] : time " << time/ns
	 << " (nsec) --- local (x,y,z) [cm] " 
	 << worldPos.x()/cm << ", " 
	 << worldPos.y()/cm << ", " 
	 << worldPos.z()/cm
	 << G4endl << G4endl;
}



/////// --------------------------------------------------------------------



