
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserVDC_MainEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:31:28 $
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
   \class QweakSimUserVDC_MainEvent
    
   \brief ROOT Subtree structure for HDC MainEvent

    A VDC Event contains the information of the DriftCell geometry, and stores
    events for the Front VDC and Back VDC:

    Region3.Config. 

    Region3.ChamberFront.

    Region3.ChamberBack.
   
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
//  Update Date:      $Date: 2005/12/27 19:31:28 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//=============================================================================
/**
   \class QweakSimUserVDC_MainEvent
    
   \ingroup root

   \brief Defines the Top Root tree structure for storing VDC events.

    A VDC Event contains the information of the DriftCell geometry, and stores
    events for the Front VDC and Back VDC:

    Region3.Config. 

    Region3.ChamberFront.

    Region3.ChamberBack.

 */
//=============================================================================
// 



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserVDC_MainEvent_h
#define QweakSimUserVDC_MainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "TObject.h"

// user includes
#include "QweakSimUserVDC_Config.hh"
#include "QweakSimUserVDC_SingleVDCEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserVDC_SingleVDCEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserVDC_MainEvent : public TObject
{
public:

  QweakSimUserVDC_Config          Config;       ///< Drift chamber configuration information
  QweakSimUserVDC_SingleVDCEvent  ChamberFront; ///< Front chamber hit information
  QweakSimUserVDC_SingleVDCEvent  ChamberBack;  ///< Back chamber hit information

public:
    
  // Constructor
  QweakSimUserVDC_MainEvent();
  // Destructor 
  virtual ~QweakSimUserVDC_MainEvent();
  
  void Clear(const Option_t* = 0);
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserVDC_MainEvent,1)

};  // end class QweakSimUserVDC_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserVDC_MainEvent.hh,v $
//      Revision 1.2  2005/12/27 19:31:28  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
