
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserGEM_SingleGEMEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:29:40 $
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
   \class QweakSimUserGEM_SingleGEMEvent
    
   \ingroup root

   \brief ROOT Subtree structure for SingleGEMEvent
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserGEM_SingleGEMEvent_h
#define QweakSimUserGEM_SingleGEMEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "TObject.h"

// user includes
#include "QweakSimUserGEM_WirePlaneEvent.hh"

// user classes
class QweakSimUserGEM_WirePlaneEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserGEM_SingleGEMEvent : public TObject
{

private:


public:

  QweakSimUserGEM_WirePlaneEvent  WirePlane;    ///< GEM wire plane hit information

public:
    
  // Constructor
  QweakSimUserGEM_SingleGEMEvent();
  // Destructor 
  virtual ~QweakSimUserGEM_SingleGEMEvent();
  
  void Initialize();
  void Clear(const Option_t* = 0);

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserGEM_SingleGEMEvent,1)
    
};  // end class QweakSimGEM_SingleGEMEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

