//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserGEM_MainEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:29:34 $
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
   \class QweakSimUserGEM_MainEvent
    
   \ingroup root

   \brief ROOT Subtree structure for GEM MainEvent
    
 */
//=============================================================================
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserGEM_MainEvent_h
#define QweakSimUserGEM_MainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "TObject.h"

// user includes
#include "QweakSimUserGEM_SingleGEMEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserGEM_SingleGEMEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserGEM_MainEvent : public TObject
{

public:

  QweakSimUserGEM_SingleGEMEvent  ChamberFront; ///< Front GEM chamber hit information
  QweakSimUserGEM_SingleGEMEvent  ChamberBack;  ///< Back GEM chamber hit information

public:
    
  // Constructor
  QweakSimUserGEM_MainEvent();
  // Destructor 
  virtual ~QweakSimUserGEM_MainEvent();
  
  void Clear(const Option_t* = 0);
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserGEM_MainEvent,1)

};  // end class QweakSimGEM_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

