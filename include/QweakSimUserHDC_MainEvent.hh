//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserHDC_MainEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:29:57 $
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
   \class QweakSimUserHDC_MainEvent
    
   \ingroup root

   \brief ROOT Subtree structure for HDC MainEvent
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:29:57 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserHDC_MainEvent_h
#define QweakSimUserHDC_MainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "TObject.h"

// user includes
#include "QweakSimUserHDC_SingleHDCEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserHDC_SingleHDCEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserHDC_MainEvent : public TObject
{

public:

  QweakSimUserHDC_SingleHDCEvent  ChamberFront; ///< Front HDC wire chamber hit information
  QweakSimUserHDC_SingleHDCEvent  ChamberBack;  ///< Back HDC wire chamber hit information

public:
    
  // Constructor
  QweakSimUserHDC_MainEvent();
  // Destructor 
  virtual ~QweakSimUserHDC_MainEvent();
  
  void Clear(const Option_t* = 0);
  
  // define a new Class known to ROOT
  ClassDef(QweakSimUserHDC_MainEvent,1)

};  // end class QweakSimHDC_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserHDC_MainEvent.hh,v $
//      Revision 1.2  2005/12/27 19:29:57  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
