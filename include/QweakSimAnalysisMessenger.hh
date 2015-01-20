/*
 * QweakSimAnalysisMessenger.hh
 *
 *  Created on: May 19, 2011
 *      Author: wdconinc
 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimAnalysisMessenger_h
#define QweakSimAnalysisMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

// user classes
class QweakSimAnalysis;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimAnalysisMessenger: public G4UImessenger
{
  public:

    // Constructor
    QweakSimAnalysisMessenger(QweakSimAnalysis* analysis);
    // Virtual destructor
    virtual ~QweakSimAnalysisMessenger();

    // Parsing function
    void SetNewValue(G4UIcommand*, G4String);

  private:

    // Private default constructor
    QweakSimAnalysisMessenger();

    // Pointer to the object
    QweakSimAnalysis*     pAnalysis;

    // Directories and commands
    G4UIdirectory*        fAnalysisDir;
    G4UIcmdWithAString*   fRootFileStemCmd;
    G4UIcmdWithAString*   fRootFileNameCmd;

};

#endif
