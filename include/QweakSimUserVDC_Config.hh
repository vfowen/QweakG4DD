//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserVDC_Config.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:31:14 $
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
   \class QweakSimUserVDC_Config
    
   \ingroup root

   \brief ROOT Subtree structure for HDC geometry

   Stores the geometry information of a VDC DriftCell into the ROOT file for each event.
   This allows to simulate different DriftCell designs (like different wire spacing, wire stringing angle,
   drift cell height, VDC tilting angle) within one ROOT file and distinguish between them.
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:31:14 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserVDC_Config_h
#define QweakSimUserVDC_Config_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "TObject.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserVDC_Config : public TObject
{

private:

  Float_t CellWidthOnFrame;     ///< Width of drift cell on frame (mm)
  Float_t CellFullThickness;    ///< Thickness of drift cell (mm)
  Float_t CellUPlaneWireAngle;  ///< U plane wire angle (degrees)
  Float_t CellVPlaneWireAngle;  ///< V plane wire angle (degrees)

public:
  
  // Constructor
  QweakSimUserVDC_Config();
  // Destructor 
  virtual ~QweakSimUserVDC_Config();

  void     Initialize();

  void     StoreDCWidthOnFrame(Float_t dcw)  { CellWidthOnFrame = dcw; }
  Float_t    GetDCWidthOnFrame() const {return CellWidthOnFrame;}

  void     StoreDCFullThickness(Float_t dct)  { CellFullThickness = dct; }
  Float_t    GetDCFullThickness() const {return CellFullThickness;}

  void     StoreDCUPlaneWireAngle(Float_t dc_ua)  { CellUPlaneWireAngle = dc_ua; }
  Float_t    GetDCUPlaneWireAngle() const {return CellUPlaneWireAngle;}

  void     StoreDCVPlaneWireAngle(Float_t dc_va)  { CellVPlaneWireAngle = dc_va; }
  Float_t    GetDCVPlaneWireAngle() const {return CellVPlaneWireAngle;}

  //-----------------

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserVDC_Config,1)

};  // end class QweakSimUserVDC_Config         

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserVDC_Config.hh,v $
//      Revision 1.2  2005/12/27 19:31:14  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
