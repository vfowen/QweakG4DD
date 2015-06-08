//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**

   \file QweakSimMaterial.hh
   $Revision: 1.2 $
   $Date: 2005/12/27 19:25:44 $
   \author Klaus Hans Grimm

*/
//=============================================================================
//
//=============================================================================
//
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimMaterial

   \brief Definition of elements and materials

   Placeholder for a long explaination

 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
//
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:25:44 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
//
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimMaterial_H
#define QweakSimMaterial_H 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimSystemOfUnits.hh"

// geant4 includes
#include "G4NistManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimMaterial
{
  public:
    QweakSimMaterial() {
      fNistManager = G4NistManager::Instance();
      fNistManager->SetVerbose(1);
    };
    virtual ~QweakSimMaterial() { };

  public:
    void  DefineMaterials();

    G4Material* GetMaterial(G4String material) {
      // Search list of custom materials
      G4Material* ptrToMaterial = G4Material::GetMaterial(material);
      // Search list of NIST materials
      if (ptrToMaterial == 0) {
        ptrToMaterial = fNistManager->FindOrBuildMaterial(material);
      }
      return ptrToMaterial;
    }

  G4NistManager* fNistManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
//
//      $Revisions$
//      $Log: QweakSimMaterial.hh,v $
//      Revision 1.2  2005/12/27 19:25:44  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//


