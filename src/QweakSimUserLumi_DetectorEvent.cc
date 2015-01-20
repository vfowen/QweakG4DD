
// QweakSimUserLumi_DetectorEvent.cc

/////// --------------------------------------------------------------------

#include "QweakSimUserLumi_DetectorEvent.hh"

/////// --------------------------------------------------------------------

ClassImp(QweakSimUserLumi_DetectorEvent)

/////// --------------------------------------------------------------------

QweakSimUserLumi_DetectorEvent::QweakSimUserLumi_DetectorEvent() 
{
    SecondaryElectronCount         = 0;
    Initialize();
} 



/////// --------------------------------------------------------------------

QweakSimUserLumi_DetectorEvent::~QweakSimUserLumi_DetectorEvent()
{;}



/////// --------------------------------------------------------------------

void QweakSimUserLumi_DetectorEvent::Initialize()
{
    //DetectorID                   = 0.0;
	
    PrimaryEventNumber             = 0;
	
    TrackID.clear();
	
    ParticleName.clear();
    ParticleType.clear();
	
    GlobalTimeOfHit.clear();
	
    HasBeenHit                     = 0;
    EdgeEventFlag.clear();
    NbOfHits                       = 0;
	
    //if(SecondaryElectronCount)
    //{
    //    delete[] SecElecLocalOriginX;
    //    delete[] SecElecLocalOriginY;
    //    delete[] SecElecLocalOriginZ;
    //
    //    delete[] SecElecLocalMomentumX;
    //    delete[] SecElecLocalMomentumY;
    //    delete[] SecElecLocalMomentumZ;
    //
    //    delete[] SecElecLocalEnergy;
    //}
	
    //if(SecondaryElectronCount)
    //{
    //
    //    SecElecLocalOriginX.clear();
    //    SecElecLocalOriginY.clear();
    //    SecElecLocalOriginZ.clear();
    //
    //    SecElecLocalMomentumX.clear();
    //    SecElecLocalMomentumY.clear();
    //    SecElecLocalMomentumZ.clear();
    //
    //    SecElecLocalEnergy.clear();
    //}
    //
	
    //SecondaryElectronCount         = 0;
	
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
    
    //PrimaryQ2                      = 0.0;
    //CrossSection                   = 0.0;
    //CrossSectionWeight             = 0.0;
	
    GlobalPhiAngle.clear(); 
    GlobalThetaAngle.clear();
	
    //--- deposited energy in the Lumi in one step
    DepositedEnergy.clear(); 
    TotalDepositedEnergy             = 0.0;
}



/////// --------------------------------------------------------------------

// void QweakSimUserLumi_DetectorEvent::AddSecondaryElectronEvent(Float_t XO, Float_t YO, Float_t ZO,
//                                                                               Float_t XM, Float_t YM, Float_t ZM,
//                                                                               Float_t Eng)
// {
//   G4int cnt = SecondaryElectronCount;
//
//   Float_t *tmp1X = NULL;
//   Float_t *tmp1Y = NULL;
//   Float_t *tmp1Z = NULL;
//
//   Float_t *tmp2X = NULL;
//   Float_t *tmp2Y = NULL;
//   Float_t *tmp2Z = NULL;
//
//   Float_t *tmp3 = NULL;
//
//   if(cnt){
//     tmp1X = new Float_t[cnt];
//     tmp1Y = new Float_t[cnt];
//     tmp1Z = new Float_t[cnt];
//
//     tmp2X = new Float_t[cnt];
//     tmp2Y = new Float_t[cnt];
//     tmp2Z = new Float_t[cnt];
//
//     tmp3 = new Float_t[cnt];
//   }
//
//   for(Int_t i = 0; i < cnt; i++){
//     tmp1X[i] = SecElecLocalOriginX[i];
//     tmp1Y[i] = SecElecLocalOriginY[i];
//     tmp1Z[i] = SecElecLocalOriginZ[i];
//
//     tmp2X[i] = SecElecLocalMomentumX[i];
//     tmp2Y[i] = SecElecLocalMomentumY[i];
//     tmp2Z[i] = SecElecLocalMomentumZ[i];
//
//     tmp3[i]  = SecElecLocalEnergy[i];
//   }
//
//   if(cnt && SecElecLocalOriginX) delete[] SecElecLocalOriginX;
//   if(cnt && SecElecLocalOriginY) delete[] SecElecLocalOriginY;
//   if(cnt && SecElecLocalOriginZ) delete[] SecElecLocalOriginZ;
//
//   if(cnt && SecElecLocalMomentumX) delete[] SecElecLocalMomentumX;
//   if(cnt && SecElecLocalMomentumX) delete[] SecElecLocalMomentumY;
//   if(cnt && SecElecLocalMomentumX) delete[] SecElecLocalMomentumZ;
//
//   if(cnt && SecElecLocalEnergy) delete[] SecElecLocalEnergy;
//
//   SecElecLocalOriginX   = new Float_t[cnt+1];
//   SecElecLocalOriginY   = new Float_t[cnt+1];
//   SecElecLocalOriginZ   = new Float_t[cnt+1];
//
//   SecElecLocalMomentumX = new Float_t[cnt+1];
//   SecElecLocalMomentumY = new Float_t[cnt+1];
//   SecElecLocalMomentumZ = new Float_t[cnt+1];
//
//   SecElecLocalEnergy    = new Float_t[cnt+1];
//
//   for(Int_t i = 0; i < cnt; i++) {
//     SecElecLocalOriginX[i]   = tmp1X[i];
//     SecElecLocalOriginY[i]   = tmp1Y[i];
//     SecElecLocalOriginZ[i]   = tmp1Z[i];
//
//     SecElecLocalMomentumX[i] = tmp2X[i];
//     SecElecLocalMomentumY[i] = tmp2Y[i];
//     SecElecLocalMomentumZ[i] = tmp2Z[i];
//
//     SecElecLocalEnergy[i]    = tmp3[i] ;
//   }

//   SecElecLocalOriginX.push_back(XO);
//   SecElecLocalOriginY.push_back(YO);
//   SecElecLocalOriginZ.push_back(YO);
//
//   SecElecLocalMomentumX.push_back(XM);
//   SecElecLocalMomentumY.push_back(YM);
//   SecElecLocalMomentumZ.push_back(ZM);
//
//   SecElecLocalEnergy.push_back(Eng);

//   if(cnt){
//     delete[] tmp1X;
//     delete[] tmp1Y;
//     delete[] tmp1Z;
//
//     delete[] tmp2X;
//     delete[] tmp2Y;
//     delete[] tmp2Z;
//
//     delete[] tmp3;
//   }
//
//   SecondaryElectronCount++;
// }
//



/////// --------------------------------------------------------------------



