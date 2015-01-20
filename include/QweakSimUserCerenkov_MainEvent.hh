//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserCerenkov_MainEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:28:38 $
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
   \class QweakSimUserCerenkov_MainEvent
    
   \ingroup root

   \brief ROOT Subtree structure for Cerenkov MainEvent
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:28:38 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserCerenkov_MainEvent_h
#define QweakSimUserCerenkov_MainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <vector>

// root includes
#include "TObject.h"

// user includes
#include "QweakSimUserCerenkov_DetectorEvent.hh"
#include "QweakSimUserCerenkov_OctantEvent.hh"
#include "QweakSimUserCerenkov_PMTEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserCerenkov_MainEvent : public TObject
{

public:

  //std::vector <QweakSimUserCerenkov_OctantEvent> Octant;      ///< Cerenkov detector octant hit information
  QweakSimUserCerenkov_DetectorEvent  Detector;                 ///< Cerenkov detector hit information
  QweakSimUserCerenkov_PMTEvent       PMT;                      ///< PMT hit information

public:
    
  // Constructor
  QweakSimUserCerenkov_MainEvent();
  // Destructor 
  virtual ~QweakSimUserCerenkov_MainEvent();
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserCerenkov_MainEvent,1)

};  // end class QweakSimCerenkov_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserCerenkov_MainEvent.hh,v $
//      Revision 1.2  2005/12/27 19:28:38  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

