//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimMagneticField_h
#define QweakSimMagneticField_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include <vector>

// geant4 includes
#include "G4ios.hh"
#include "G4String.hh"
#include "G4SystemOfUnits.hh"
#include "G4MagneticField.hh"

// user classes
template <class value_t, unsigned int value_n>
class QweakSimFieldMap;
class QweakSimMagneticFieldMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimMagneticField: public G4MagneticField
{
  private:

    /// Number of field component in the map (x,y,z,r,phi)
    static const unsigned int value_n = 3;

    /// Field map storage data type
    typedef float value_t;

    /// Messenger
    QweakSimMagneticFieldMessenger* fMagneticFieldMessenger;

  public:

    /// Default constructor
    QweakSimMagneticField();
    /// Virtual destructor
    virtual ~QweakSimMagneticField();


    /// Get the field value
    void GetFieldValue(const G4double point[4], G4double *field) const;

    /// Print the field value
    void PrintFieldValue(const G4double point[4]) const;


    /// Set the scale factor
    void SetScaleFactor(const double scalefactor) {
      fScaleFactor = scalefactor;
      G4cout << "Magnetic field scale factor is now: " << fScaleFactor << G4endl;
    };
    /// Get the scale factor
    double GetScaleFactor() const { return fScaleFactor; };

    /// Set the reference current
    void SetReferenceCurrent(const double referencecurrent) {
      fReferenceCurrent = referencecurrent;
      G4cout << "Magnetic field reference current is now: " << fReferenceCurrent << G4endl;
      if (fReferenceCurrent != 0)
        SetScaleFactor(fActualCurrent/fReferenceCurrent);
    };
    /// Get the reference current
    double GetReferenceCurrent() const { return fReferenceCurrent; };

    /// Set the actual current
    void SetActualCurrent(const double actualcurrent) {
      fActualCurrent = actualcurrent;
      G4cout << "Magnetic field actual current is now: " << fActualCurrent << G4endl;
      if (fReferenceCurrent != 0)
        SetScaleFactor(fActualCurrent/fReferenceCurrent);
    };
    /// Get the actual current
    double GetActualCurrent() const { return fActualCurrent; };


    /// Set the field rotation around z
    void SetRotation(const double rotation) {
      fRotation = rotation;
      fRotationCos = cos(rotation);
      fRotationSin = sin(rotation);
      G4cout << "Magnetic field rotation is now: " << fRotation/degree << " degree" << G4endl;
    };
    /// Get the field rotation around z
    double GetRotation() const { return fRotation; };

    /// Set the field translation along z
    void SetTranslation(const double translation) {
      fTranslation = translation;
      G4cout << "Magnetic field translation is now: " << fTranslation/cm << " cm" << G4endl;
    };
    /// Get the field translation along z
    double GetTranslation() const { return fTranslation; };


    /// Set the minimum
    void SetMinimum(const double value, const int i) {
      fMin.at(i) = value;
      G4cout << "Magnetic field grid min " << i << " is " << fMin.at(i) << " cm/radian" << G4endl;
    };
    /// Set the maximum
    void SetMaximum(const double value, const int i) {
      fMax.at(i) = value;
      G4cout << "Magnetic field grid max " << i << " is " << fMax.at(i) << " cm/radian" << G4endl;
    };
    /// Set the step
    void SetStep(const double value, const int i) {
      fStep.at(i) = value;
      G4cout << "Magnetic field grid step " << i << " is " << fStep.at(i) << " cm/radian" << G4endl;
    };
    /// Set the wrap
    void SetWrap(const int value, const int i) {
      fWrap.at(i) = value;
      G4cout << "Magnetic field grid wrap " << i << " is " << fWrap.at(i) << G4endl;
    };


    /// Read the field map
    void ReadFieldMap(const G4String& filename);
    void ReadFieldMapText(const G4String& filename);
    void ReadFieldMapBinary(const G4String& filename);

    /// Test the field map
    void TestFieldMap(const G4double point[4], const G4double exact[3]) const;

  private:

    QweakSimFieldMap<value_t,value_n>* fField;

    /// Field rotation and translation with respect to the z axis
    // Defined as rotation/translation of the map in the standard coordinate
    // system: rotation of +22.5 deg means that x in the map x is at +22.5 deg,
    // likewise a translation of +5 cm means that the zero in the map is at +5 cm
    // in the standard coordinate system.
    double fRotation, fRotationCos, fRotationSin;
    double fTranslation;

    /// Field map reference and actual currents
    double fScaleFactor;
    double fActualCurrent;
    double fReferenceCurrent;

    /// Field map grid definitions
    std::vector<double> fMin, fMax, fStep;
    std::vector<size_t> fWrap;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
