//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef NXMagneticField_H
#define NXMagneticField_H

#include "G4UniformMagField.hh"

class G4FieldManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


class NXMagneticField: public G4UniformMagField
{
    public:

        NXMagneticField(G4ThreeVector);  //  The value of the field
        NXMagneticField();               //  A zero field
        ~NXMagneticField();  

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
