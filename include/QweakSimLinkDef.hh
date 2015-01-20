
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserMainEvent_LinkDef.hh

   $Revision: 1.3 $	
   $Date: 2006/01/31 20:18:07 $

   \author Klaus Hans Grimm
     
*/
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/01/31 20:18:07 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================



#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class QweakSimUserRunInformation+;

#pragma link C++ class QweakSimUserMainEvent+;

#pragma link C++ class QweakSimUserPrimaryEvent+;

#pragma link C++ class QweakSimUserTarget_MainEvent+;
#pragma link C++ class QweakSimUserTarget_DetectorEvent+;

#pragma link C++ class QweakSimUserGEM_MainEvent+;
#pragma link C++ class QweakSimUserGEM_SingleGEMEvent+;
#pragma link C++ class QweakSimUserGEM_WirePlaneEvent+;

#pragma link C++ class QweakSimUserHDC_MainEvent+;
#pragma link C++ class QweakSimUserHDC_SingleHDCEvent+;
#pragma link C++ class QweakSimUserHDC_WirePlaneEvent+;

#pragma link C++ class QweakSimUserVDC_MainEvent+;
#pragma link C++ class QweakSimUserVDC_Config+;
#pragma link C++ class QweakSimUserVDC_SingleVDCEvent+;
#pragma link C++ class QweakSimUserVDC_WirePlaneEvent+;
#pragma link C++ class QweakSimUserVDC_DriftCellEvent+;

#pragma link C++ class QweakSimUserTriggerScintillator_MainEvent+;
#pragma link C++ class QweakSimUserTriggerScintillator_DetectorEvent+;
#pragma link C++ class QweakSimUserTriggerScintillator_PMTEvent+;

#pragma link C++ class QweakSimUserLeadGlass_MainEvent+;
#pragma link C++ class QweakSimUserLeadGlass_DetectorEvent+;
#pragma link C++ class QweakSimUserLeadGlass_PMTEvent+;

#pragma link C++ class QweakSimUserPMTOnly_MainEvent+;
#pragma link C++ class QweakSimUserPMTOnly_DetectorEvent+;
#pragma link C++ class QweakSimUserPMTOnly_PMTEvent+;

#pragma link C++ class QweakSimUserLumi_MainEvent+;
#pragma link C++ class QweakSimUserLumi_DetectorEvent+;

#pragma link C++ class QweakSimUserCerenkov_MainEvent+;
#pragma link C++ class QweakSimUserCerenkov_OctantEvent+;
#pragma link C++ class QweakSimUserCerenkov_DetectorEvent+;
#pragma link C++ class QweakSimUserCerenkov_PMTEvent+;

#endif


//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserMainEvent_LinkDef.hh,v $
//      Revision 1.3  2006/01/31 20:18:07  grimm
//      Added the header EPEvent into the Root dictionary generation.
//
//      Revision 1.2  2005/12/27 19:30:39  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
