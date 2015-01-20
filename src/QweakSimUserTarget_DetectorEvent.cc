
// QweakSimUserTarget_DetectorEvent.cc
// Wouter Deconinck
// 2014-10-07

/////// --------------------------------------------------------------------

#include "QweakSimUserTarget_DetectorEvent.hh"

/////// --------------------------------------------------------------------

ClassImp(QweakSimUserTarget_DetectorEvent)

/////// --------------------------------------------------------------------

void QweakSimUserTarget_DetectorEvent::Initialize()
{
    PrimaryEventNumber = 0;
	
    TrackID.clear();
	
    ParticleName.clear();
    ParticleType.clear();
	
    GlobalTimeOfHit.clear();
	
    HasBeenHit = 0;
    NbOfHits   = 0;

    HitGlobalPositionX.clear();
    HitGlobalPositionY.clear();
    HitGlobalPositionZ.clear();
	
    HitLocalPositionX.clear();
    HitLocalPositionY.clear();
    HitLocalPositionZ.clear();
	
    HitLocalExitPositionX.clear();
    HitLocalExitPositionY.clear();
    HitLocalExitPositionZ.clear();
    
    OriginVertexPositionX.clear();
    OriginVertexPositionY.clear(); 
    OriginVertexPositionZ.clear();

    LocalVertexMomentumDirectionX.clear();
    LocalVertexMomentumDirectionY.clear();
    LocalVertexMomentumDirectionZ.clear();
	
    OriginVertexMomentumDirectionX.clear();
    OriginVertexMomentumDirectionY.clear();
    OriginVertexMomentumDirectionZ.clear();
    
    OriginVertexThetaAngle.clear();
    OriginVertexPhiAngle.clear();
	
    OriginVertexKineticEnergy.clear(); 
    OriginVertexTotalEnergy.clear(); 
	
    LocalVertexKineticEnergy.clear();  
    LocalVertexTotalEnergy.clear();   

    GlobalPhiAngle.clear(); 
    GlobalThetaAngle.clear();

    ElasticCrossSection.clear();
    ElasticScatteredEnergy.clear();
    ElasticMomentumTransfer.clear();

    //--- deposited energy in the Target in one step
    DepositedEnergy.clear(); 
    //--- total deposited energy in the Target in one event
    TotalDepositedEnergy             = 0.0;
}

/////// --------------------------------------------------------------------
