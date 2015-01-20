//=============================================================================
//
//  File     QweakSimWShutters.hh
//  Revision 1.0
//  Date     02/06/2012
//  Author   Kurtis Bartlett
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef QweakSimWShutters_h
#define QweakSimWShutters_h 1

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//  geant4 includes
#include "G4LogicalVolume.hh"

//  user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimWShuttersMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//  user classes
class QweakSimWShuttersMessenger;
class QweakSimMaterial;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimWShutters
{

  private:

	G4int             WShutterNum;
	QweakSimMaterial* pMaterial;

    G4LogicalVolume*   WShutters_Logical;
    G4VPhysicalVolume* WShutters_Physical;
    G4Box*			   WShutters_Box;
    G4Trap*			   WShutters_Trap;
    G4VSolid*          WShutters_Solid;
    //G4Box* 			   WShutters_Solid;
    G4Material*        WShutters_Material;
    G4VisAttributes*   WShutters_VisAtt;

    G4RotationMatrix* Rot;
    G4RotationMatrix* WRot;


    QweakSimWShuttersMessenger* WShutters_Messenger;  //  pointer to the Messenger

    G4double WShutters_Length_X;
    G4double WShutters_Length_Y;
    G4double WShutters_Length_Z;

 //   G4double MD7_CenterYPosition;
 //   G4double MD7_CenterZPosition;

    G4double WShutters_CenterXPosition;
    G4double WShutters_CenterYPosition;
    G4double WShutters_CenterZPosition;

  public:

      //!Constructor
      QweakSimWShutters(G4int n);

      //!Destructor
      ~QweakSimWShutters();

      void ConstructWShutters(G4VPhysicalVolume*);

      void DestroyComponent();

      void     SetWShutters_CenterPositionInX(G4double xPos);
      void     SetWShutters_CenterPositionInY(G4double yPos);
      void     SetWShutters_CenterPositionInZ(G4double zPos);

      G4double GetWShutters_CenterPositionInX()    {return WShutters_CenterXPosition;}
      G4double GetWShutters_CenterPositionInY()    {return WShutters_CenterYPosition;}
      G4double GetWShutters_CenterPositionInZ()    {return WShutters_CenterZPosition;}

      void SetWShuttersMaterial(G4String);

      void SetWShutters_LengthInX(G4double dim)  {WShutters_Length_X = dim;}
      void SetWShutters_LengthInY(G4double dim)  {WShutters_Length_Y = dim;}
      void SetWShutters_LengthInZ(G4double dim)  {WShutters_Length_Z = dim;}

      G4double GetWShutters_LengthInX()          {return WShutters_Length_X;}
      G4double GetWShutters_LengthInY()          {return WShutters_Length_Y;}
      G4double GetWShutters_LengthInZ()          {return WShutters_Length_Z;}

      //G4LogicalVolume*   getWShuttersLogicalVolume()  {return WShutters_Logical;}
      //G4VPhysicalVolume* getWShuttersPhysicalVolume() {return WShutters_Physical;}

      void  SetWShuttersNumber(G4int n)                    {       WShutterNum = n;}
      G4int GetWShuttersNumber()                           {return WShutterNum;}

      void SetEnabled();
      void SetDisabled();

      void SetWShutters_Material(G4String);

  };

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

  #endif

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

