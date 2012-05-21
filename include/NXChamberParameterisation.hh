//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef NXChamberParameterisation_H
#define NXChamberParameterisation_H 1

#include "globals.hh"
#include "G4VPVParameterisation.hh"

class G4VPhysicalVolume;
class G4Box;

// Dummy declarations to get rid of warnings ...
class G4Trd;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Torus;
class G4Para;
class G4Hype;
class G4Tubs;
class G4Polycone;
class G4Polyhedra;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NXChamberParameterisation : public G4VPVParameterisation
{ 
    public:

        NXChamberParameterisation(G4int    NoChambers, 
                G4double startZ, 
                G4double spacing,
                G4double widthChamber, 
                G4double lengthInitial,
                G4double lengthFinal );

        virtual				 
            ~NXChamberParameterisation();

        void ComputeTransformation (const G4int copyNo,
                G4VPhysicalVolume* physVol) const;

        void ComputeDimensions (G4Box & trackerLayer, const G4int copyNo,
                const G4VPhysicalVolume* physVol) const;

    private:  // Dummy declarations to get rid of warnings ...

        void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Tubs&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
        void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}
    private:

        G4int    fNoChambers;   
        G4double fStartZ;
        G4double fHalfWidth;    //  The half-width of each tracker chamber
        G4double fSpacing;      //  The distance between the chambers' center
        G4double fHalfLengthFirst;  //  The first half-length 
        G4double fHalfLengthIncr;   //  The Increment for the half-length 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


