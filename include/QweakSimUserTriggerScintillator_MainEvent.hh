
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserTriggerScintillator_MainEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:31:00 $
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
   \class QweakSimUserTriggerScintillator_MainEvent
    
   \ingroup root

   \brief ROOT Subtree structure for Trigger Scintillator MainEvent
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:31:00 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserTriggerScintillator_MainEvent_h
#define QweakSimUserTriggerScintillator_MainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <vector>

// root includes
#include "TObject.h"

// user includes
#include "QweakSimUserTriggerScintillator_DetectorEvent.hh"
#include "QweakSimUserTriggerScintillator_PMTEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserTriggerScintillator_MainEvent : public TObject
{
public:

  //vector <QweakSimUserTriggerScintillator_DetectorEvent>  Detector;
  QweakSimUserTriggerScintillator_DetectorEvent  Detector;      ///< Detector event in the trigger scintillator
  QweakSimUserTriggerScintillator_PMTEvent       PMT;           ///< PMT event in the trigger scintillator

public:
    
  // Constructor
  QweakSimUserTriggerScintillator_MainEvent();
  // Destructor 
  virtual ~QweakSimUserTriggerScintillator_MainEvent();
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserTriggerScintillator_MainEvent,1)

};  // end class QweakSimTriggerScintillator_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserTriggerScintillator_MainEvent.hh,v $
//      Revision 1.2  2005/12/27 19:31:00  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
