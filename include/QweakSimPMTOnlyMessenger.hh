
// QweakSimPMTOnlyMessenger.hh
// Marty McHugh
// 2013-06-11

/////// --------------------------------------------------------------------

#ifndef QweakSimPMTOnlyMessenger_hh
#define QweakSimPMTOnlyMessenger_hh 1

/////// --------------------------------------------------------------------

//--- user includes
#include "QweakSimMessengerDeclaration.hh"

//--- user classes
class QweakSimPMTOnly;

/////// --------------------------------------------------------------------

class QweakSimPMTOnlyMessenger: public G4UImessenger
{
	
public:
	
    QweakSimPMTOnlyMessenger(QweakSimPMTOnly*);
    ~QweakSimPMTOnlyMessenger();
	
    void SetNewValue(G4UIcommand*, G4String);
    
private:
	
    QweakSimPMTOnly*         myPMTOnly;
    
    G4UIdirectory*             PMTOnlyDir;
	
    G4UIcmdWithAString*        PMTOnly_SetMaterial_Cmd;
	
    G4UIcmdWithADoubleAndUnit* PMTOnly_SetCenterPositionInX_Cmd;
    G4UIcmdWithADoubleAndUnit* PMTOnly_SetCenterPositionInY_Cmd;
    G4UIcmdWithADoubleAndUnit* PMTOnly_SetCenterPositionInZ_Cmd;

    G4UIcmdWithoutParameter*   PMTOnly_FindMotherCenter_Cmd;
	
    G4UIcmdWithADoubleAndUnit* PMTOnly_SetTiltAngleInX_Cmd;
    G4UIcmdWithADoubleAndUnit* PMTOnly_SetTiltAngleInY_Cmd;
    G4UIcmdWithADoubleAndUnit* PMTOnly_SetTiltAngleInZ_Cmd;

    G4UIcmdWithoutParameter*   PMTOnly_SetEnabled_Cmd;
    G4UIcmdWithoutParameter*   PMTOnly_SetDisabled_Cmd;
};

/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------

