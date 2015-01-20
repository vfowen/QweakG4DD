
// QweakSimLeadGlassMessenger.hh
// Fang Guo
// 2012/07/31

/////// --------------------------------------------------------------------

#ifndef QweakSimLeadGlassMessenger_h
#define QweakSimLeadGlassMessenger_h 1

/////// --------------------------------------------------------------------

//--- user includes
#include "QweakSimMessengerDeclaration.hh"

//--- user classes
class QweakSimLeadGlass;

/////// --------------------------------------------------------------------

class QweakSimLeadGlassMessenger: public G4UImessenger
{
	
public:
	
    QweakSimLeadGlassMessenger(QweakSimLeadGlass*);
    ~QweakSimLeadGlassMessenger();
	
    void SetNewValue(G4UIcommand*, G4String);
    
private:
	
    QweakSimLeadGlass*         myLeadGlass;
    
    G4UIdirectory*             LeadGlassDir;
	
    G4UIcmdWithAString*        LeadGlass_SetMaterial_Cmd;
	
    G4UIcmdWithADoubleAndUnit* LeadGlass_SetCenterPositionInX_Cmd;
    G4UIcmdWithADoubleAndUnit* LeadGlass_SetCenterPositionInY_Cmd;
    G4UIcmdWithADoubleAndUnit* LeadGlass_SetCenterPositionInZ_Cmd;
	
    G4UIcmdWithADoubleAndUnit* LeadGlass_SetTiltAngleInX_Cmd;
    G4UIcmdWithADoubleAndUnit* LeadGlass_SetTiltAngleInY_Cmd;
    G4UIcmdWithADoubleAndUnit* LeadGlass_SetTiltAngleInZ_Cmd;

    G4UIcmdWithoutParameter*   LeadGlass_SetEnabled_Cmd;
    G4UIcmdWithoutParameter*   LeadGlass_SetDisabled_Cmd;
};

/////// --------------------------------------------------------------------

#endif

/////// --------------------------------------------------------------------

