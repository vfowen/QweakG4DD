//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserMainEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:30:33 $
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
   \class QweakSimUserMainEvent
    
   \brief Defines Top ROOT Tree structure of the ROOT file for each event.

          Primary.

	  Region1.

	  Region2.

	  Region3.

	  Cerenkov.
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserMainEvent_h
#define QweakSimUserMainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root include
#include "TObject.h"

// user includes
#include "QweakSimUserPrimaryEvent.hh"
#include "QweakSimUserTarget_MainEvent.hh"
#include "QweakSimUserGEM_MainEvent.hh"
#include "QweakSimUserHDC_MainEvent.hh"
#include "QweakSimUserVDC_MainEvent.hh"
#include "QweakSimUserTriggerScintillator_MainEvent.hh"
#include "QweakSimUserLeadGlass_MainEvent.hh"
#include "QweakSimUserPMTOnly_MainEvent.hh"
#include "QweakSimUserCerenkov_MainEvent.hh"
#include "QweakSimUserLumi_MainEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserMainEvent : public TObject
// class QweakSimUserMainEvent 
{

/** \page global_coordinate_system global coordinate system
 *
 *  The global coordinate system of the MC simulation is defined as follows:
 *  \li X-axis is in the horizontal direction beam-left,
 *  \li Y-axis is in the vertical direction up,
 *  \li Z-axis is along the beam line in the downstream direction.
 */

/** \page local_coordinate_system local coordinate system
 *
 *  The local coordinate system of the MC simulation is normally defined as follows:
 *  \li X-axis is along the longest detector edge in the non-dispersive direction beam-left for octant 3,
 *  \li Y-axis is along the shortest detector edge in the dispersive direction away from the beam line,
 *  \li Z-axis is perpendicular to the detector plane in the downstream direction.
 */

/** \page Lund_type Lund type
 *
 *  A complete list of Lund particle type codes is summarized in the PDG: http://pdg.lbl.gov/2011/reviews/rpp2011-rev-monte-carlo-numbering.pdf
 *
 *  The most important particle codes are:
 *  \li electron: 11
 *  \li photon: 22
 *  \li pion-: -211
 *  \li kaon-: -321
 *  \li proton: 2212
 *  \li neutron: 2112
 *
 */

/** \page geant3_type geant3 type
 *
 *  The only geant3 particle types that were used in the Qweak Monte Carlo are
 *  \li electron: 1
 *  \li positron: 2
 *  \li gamma: 3
 */

/** \defgroup root Variables include in the ROOT file
 *
 *  This group contains all variables that are included in the ROOT file.
 */

private:

public:

  QweakSimUserPrimaryEvent                     Primary;              ///< object containing primary particle info

  QweakSimUserTarget_MainEvent                 Target;               ///< object containing target hits

  QweakSimUserGEM_MainEvent                    Region1;              ///< object containing HDC info
  QweakSimUserHDC_MainEvent                    Region2;              ///< object containing HDC info
  QweakSimUserVDC_MainEvent                    Region3;              ///< object containing VDC info

  QweakSimUserTriggerScintillator_MainEvent    TriggerScintillator;  ///< object containing TriggerScintilliator info
	
  QweakSimUserLeadGlass_MainEvent              LeadGlass;            ///< tree containing LeadGlass info
  
  QweakSimUserPMTOnly_MainEvent		       PMTOnly;	             ///< tree containing PMTOnly info
	
  QweakSimUserCerenkov_MainEvent               Cerenkov;             ///< object containing Cerenkov detector info

  QweakSimUserLumi_MainEvent                   Lumi;                 ///< tree containing Lumi detector info

public:
    
  // Constructor
  QweakSimUserMainEvent() { };
  // Destructor 
  virtual ~QweakSimUserMainEvent() { };
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserMainEvent,1)

};  // end class QweakSimMainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 



