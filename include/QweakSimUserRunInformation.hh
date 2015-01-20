//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimUserRunInformation_h
#define QweakSimUserRunInformation_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// root includes
#include <TObject.h>
#include <TString.h>
#include <TList.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimUserRunInformation: public TObject {

 public:

  QweakSimUserRunInformation();
  virtual ~QweakSimUserRunInformation();

  TList Conditions;

  ClassDef(QweakSimUserRunInformation,1);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

