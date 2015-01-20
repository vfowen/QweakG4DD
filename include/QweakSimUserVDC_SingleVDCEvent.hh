
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserVDC_SingleVDCEvent.hh
   $Date: Fri Jul  3 14:19:13 CDT 2009$
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
   \class QweakSimUserVDC_SingleVDCEvent
    
   \ingroup root

   \brief ROOT Subtree structure for VDC SingleVDCEvent

   Stores the data structure related to a VDC Hit into the ROOT file for each event.
   A VDC Hit contains the information of a WirePlane Hit and/or a DriftCell Hit
  
   Region3.ChamberFront.WirePlane

   Region3.ChamberFront.DriftCell	

   Region3.ChamberBack.WirePlane

   Region3.ChamberBack.DriftCell	

    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserVDC_SingleVDCEvent_h
#define QweakSimUserVDC_SingleVDCEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "TObject.h"

// user includes
#include "QweakSimUserVDC_WirePlaneEvent.hh"
#include "QweakSimUserVDC_DriftCellEvent.hh"

// user classes
class QweakSimUserVDC_WirePlaneEvent;
class QweakSimUserVDC_DriftCellEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserVDC_SingleVDCEvent : public TObject
{

private:


public:

  QweakSimUserVDC_WirePlaneEvent  WirePlaneU;   ///< U wire plane hit information
  QweakSimUserVDC_WirePlaneEvent  WirePlaneV;   ///< V wire plane hit information

  QweakSimUserVDC_DriftCellEvent  DriftCell;    ///< Drift cell hit information

public:
    
  // Constructor
  QweakSimUserVDC_SingleVDCEvent();
  // Destructor 
  virtual ~QweakSimUserVDC_SingleVDCEvent();
  
  void Initialize();
  void Clear(const Option_t* = 0);
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserVDC_SingleVDCEvent,1)
    
};  // end class QweakSimUserVDC_SingleVDCEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserVDC_SingleVDCEvent.hh,v $
//      Revision 1.2  2005/12/27 19:31:36  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

