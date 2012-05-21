//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NXChamberParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXChamberParameterisation::NXChamberParameterisation(  
        G4int    NoChambers, 
        G4double startZ,          //  Z of center of first 
        G4double spacingZ,        //  Z spacing of centers
        G4double widthChamber, 
        G4double lengthInitial, 
        G4double lengthFinal )
{
    fNoChambers =  NoChambers; 
    fStartZ     =  startZ; 
    fHalfWidth  =  widthChamber*0.5;
    fSpacing    =  spacingZ;
    fHalfLengthFirst = 0.5 * lengthInitial; 
    // fHalfLengthLast = lengthFinal;
    if( NoChambers > 0 ){
        fHalfLengthIncr =  0.5 * (lengthFinal-lengthInitial)/NoChambers;
        if (spacingZ < widthChamber) {
            G4Exception("NXChamberParameterisation construction: Width>Spacing");
        }
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXChamberParameterisation::~NXChamberParameterisation()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXChamberParameterisation::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
    G4double      Zposition= fStartZ + (copyNo+1) * fSpacing;
    G4ThreeVector origin(0,0,Zposition);
    physVol->SetTranslation(origin);
    physVol->SetRotation(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXChamberParameterisation::ComputeDimensions
(G4Box& trackerChamber, const G4int copyNo, const G4VPhysicalVolume*) const
{
    G4double  halfLength= fHalfLengthFirst + copyNo * fHalfLengthIncr;
    trackerChamber.SetXHalfLength(halfLength);
    trackerChamber.SetYHalfLength(halfLength);
    trackerChamber.SetZHalfLength(fHalfWidth);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
