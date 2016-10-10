#ifndef QweaSimAnalyzingPower_h
#define QweaSimAnalyzingPower_h

#include "TGraph.h"
#include "math.h"
#include "MSAnalyzingPowerData.hh"
#include "QweakSimSystemOfUnits.hh"
#include "G4StokesVector.hh"

inline G4double Mott(G4double energy, G4double theta);

inline G4double AnalyzingPower(G4double energy, G4double cth, G4double factor,G4bool debugPrint=false){

  G4double theta = acos(cth);

  G4double ahat = -35e-6 * 207./82.;
  G4double twoPhoton = ahat * sqrt(4.*pow(energy/1000.,2) * sin(theta/2.) );
  if(factor<0)
    twoPhoton *= abs(factor);
  if( fabs(twoPhoton) > 1 ) twoPhoton = 1. * twoPhoton/fabs(twoPhoton);
  
  G4double mott = Mott(energy,theta/pi *180.);
  if(factor>0)
    mott *= factor;
  if( fabs(mott) > 1 ) mott = 1. * mott/fabs(mott);
  
  //if(mott<0) mott=0;

  if(debugPrint)
    G4cout<<__LINE__<<":"<<__PRETTY_FUNCTION__<<G4endl
	  <<"\tenergy\ttheta(rad)\tmott\ttheta(deg)\tfactor"<<G4endl
	  <<"\t"<<energy<<"\t"<<theta<<"\t"<<mott<<"\t"<<theta/pi*180<<"\t"<<factor<<G4endl;

  if(factor<0)
    return twoPhoton;
  else if(factor>0)
    return mott;
  else
    return twoPhoton + mott ;  
}

inline G4double Mott(G4double energy, G4double theta){

  if( (energy>40 && theta>150) || (energy>200) )
    return 0;  
  
  const int nEnergy=12;
  TGraph *c[nEnergy];
  for(int i=0;i<nEnergy;i++) c[i]=new TGraph();

  const int nEntries1=606;
  const int nEntries2=1800;
  const int nEntries3=1482;

  for(int i=0;i<nEntries1;i++){
    c[0]->SetPoint(i,motX3[i],motY3[i]);
    c[1]->SetPoint(i,motX5[i],motY5[i]);
    c[2]->SetPoint(i,motX6[i],motY6[i]);
    c[3]->SetPoint(i,motX8[i],motY8[i]);
  }

  for(int i=0;i<nEntries2;i++){
    if(mott10X[i]>0 && mott10X[i]<2) continue;
    c[4]->SetPoint(i,mott10X[i],mott10Y[i]);
    c[5]->SetPoint(i,mott15X[i],mott15Y[i]);
    c[6]->SetPoint(i,mott30X[i],mott30Y[i]);
    c[7]->SetPoint(i,mott35X[i],mott35Y[i]);
    c[8]->SetPoint(i,mott40X[i],mott40Y[i]);
  }

  for(int i=0;i<nEntries3;i++){
    c[9]->SetPoint(i,mott50X[i],mott50Y[i]);
    c[10]->SetPoint(i,mott100X[i],mott100Y[i]);
    c[11]->SetPoint(i,mott200X[i],mott200Y[i]);
  }

  TGraph *a=new TGraph();
  const G4double oneE[nEnergy]={3,5,6,8,10,15,30,35,40,50,100,200};
  
  for(int i=0;i<nEnergy;i++){
    a->SetPoint(i,oneE[i],c[i]->Eval(theta,0,""));
  }

  G4double mott = a->Eval(energy,0,"");
  
  for(int i=0;i<nEnergy;i++) delete c[i];
  delete a;
  
  return mott;
}

inline void PolarizationTransfer(G4ThreeVector ki, G4ThreeVector kf,
				 G4ThreeVector polI, G4ThreeVector &polF,
				 G4bool debugPrint=false){
  if(debugPrint){
    G4cout<<"Polarization Transfer: "<<G4endl;
  }

  G4StokesVector beamPol = polI;
  if(debugPrint){
    G4cout<<"\t"<<__LINE__<<":"<<__PRETTY_FUNCTION__<<G4endl
	  <<"\t\tInitial beam pol(X,Y,Z): "<<beamPol.getX()<<"t"
	  <<beamPol.getY()<<"\t"<<beamPol.getZ()<<G4endl;
  }

  G4ThreeVector  nInteractionFrame = (ki.cross(kf)).unit();
  if(debugPrint){
    G4cout<<"\t"<<__LINE__<<":"<<__PRETTY_FUNCTION__<<G4endl
	  <<"\t\tnormal(X,Y,Z): "<<nInteractionFrame.getX()<<"t"
	  <<nInteractionFrame.getY()<<"\t"<<nInteractionFrame.getZ()<<G4endl;
  }
  
  // transform polarization from ki-local into Stokes
  beamPol.RotateAz(nInteractionFrame,ki);
  if(debugPrint){
    G4cout<<"\t"<<__LINE__<<":"<<__PRETTY_FUNCTION__<<G4endl
	  <<"\t\tStokes beam pol(X,Y,Z): "<<beamPol.getX()<<"t"
	  <<beamPol.getY()<<"\t"<<beamPol.getZ()<<G4endl;
  }

  //polarization transfer
  //G4double interactionTheta = ki*kf;
  //beamPol.rotateY( - acos(interactionTheta) + alpha); //where alpha=atan(U/T)

  //rotate from Stokes frame into kf-local
  beamPol.InvRotateAz(nInteractionFrame,kf);
  if(debugPrint){
    G4cout<<"\t"<<__LINE__<<":"<<__PRETTY_FUNCTION__<<G4endl
	  <<"\t\tkf beam pol(X,Y,Z): "<<beamPol.getX()<<"t"
	  <<beamPol.getY()<<"\t"<<beamPol.getZ()<<G4endl;
  }

  polF = (G4ThreeVector)beamPol;
}

#endif
