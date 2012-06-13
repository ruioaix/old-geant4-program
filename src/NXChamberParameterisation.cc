//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NXChamberParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"

#include "G4LogicalVolume.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXChamberParameterisation::NXChamberParameterisation( G4double startZ )
{
    fStartZ     =  startZ; 
    G4NistManager* man=G4NistManager::Instance();
    Fe=man->FindOrBuildMaterial("G4_Fe"); //26
    Vacuum=new G4Material("Vacuum",1.0,1.01*g/mole,1.0E-25*g/cm3,kStateGas,2.73*kelvin, 3.0E-18*pascal);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXChamberParameterisation::~NXChamberParameterisation()
{
    delete Fe;
    delete Vacuum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXChamberParameterisation::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
    G4double      Zposition= fStartZ;
    physVol->SetTranslation(G4ThreeVector(0,0,Zposition));
    physVol->SetRotation(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXChamberParameterisation::ComputeDimensions
(G4Box& trackerChamber, const G4int copyNo, const G4VPhysicalVolume*) const
{
    trackerChamber.SetXHalfLength(2*cm);
    trackerChamber.SetYHalfLength(2*cm);
    trackerChamber.SetZHalfLength(0.5*cm);
}

G4Material* NXChamberParameterisation::ComputeMaterial (const G4int copyNo,G4VPhysicalVolume * physVol,const G4VTouchable*)
{
    if(copyNo%2 == 0) {
        physVol->GetLogicalVolume()->SetMaterial(Fe);
        return Fe; 
    }
    physVol->GetLogicalVolume()->SetMaterial(Vacuum);
    return Vacuum; 
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
