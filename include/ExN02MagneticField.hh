//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef ExN02MagneticField_H
#define ExN02MagneticField_H

#include "G4UniformMagField.hh"

class G4FieldManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


class ExN02MagneticField: public G4UniformMagField
{
    public:

        ExN02MagneticField(G4ThreeVector);  //  The value of the field
        ExN02MagneticField();               //  A zero field
        ~ExN02MagneticField();  

        //Set the field (fieldValue,0,0)
        void SetMagFieldValue(G4double fieldValue);
        void SetMagFieldValue(G4ThreeVector fieldVector);

        G4ThreeVector GetConstantFieldValue();

    protected:

        // Find the global Field Manager
        G4FieldManager* GetGlobalFieldManager();   // static 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
