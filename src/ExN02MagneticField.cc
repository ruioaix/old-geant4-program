//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02MagneticField::ExN02MagneticField() :
    G4UniformMagField(G4ThreeVector())
{
    GetGlobalFieldManager()->SetDetectorField(this);
    GetGlobalFieldManager()->CreateChordFinder(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02MagneticField::ExN02MagneticField(G4ThreeVector fieldVector) : 
    G4UniformMagField(fieldVector)
{
    GetGlobalFieldManager()->SetDetectorField(this);    
    GetGlobalFieldManager()->CreateChordFinder(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02MagneticField::~ExN02MagneticField()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Set the value of the Global Field to fieldValue along X
//
void ExN02MagneticField::SetMagFieldValue(G4double fieldValue)
{
    SetMagFieldValue(G4ThreeVector(fieldValue,0,0));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Set the value of the Global Field
//
void ExN02MagneticField::SetMagFieldValue(G4ThreeVector fieldVector)
{
    // Find the Field Manager for the global field
    G4FieldManager* fieldMgr= GetGlobalFieldManager();

    if(fieldVector!=G4ThreeVector(0.,0.,0.))
    { 
        SetFieldValue(fieldVector);
        fieldMgr->SetDetectorField(this);
    } else {
        // If the new field's value is Zero, then it is best to
        //  insure that it is not used for propagation.
        G4MagneticField* magField = 0;
        fieldMgr->SetDetectorField(magField);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4FieldManager*  ExN02MagneticField::GetGlobalFieldManager()
{
    return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
