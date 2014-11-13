#ifndef TargetChamberParameterisation_H
#define TargetChamberParameterisation_H 1

#include "globals.hh"
#include "G4VPVParameterisation.hh"
#include "G4NistManager.hh"

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

class TargetChamberParameterisation : public G4VPVParameterisation
{ 
  public:
  
    TargetChamberParameterisation(G4int    NoChambers, G4double startZ );

    virtual				 
   ~TargetChamberParameterisation();
   
    void ComputeTransformation (const G4int copyNo,
                                G4VPhysicalVolume* physVol) const;
    
    void ComputeDimensions (G4Tubs & trackerLayer, const G4int copyNo,
                            const G4VPhysicalVolume* physVol) const;

//这个函数是添加的，看g4pvparameterisation的源代码就知道了。
	G4Material* ComputeMaterial(const G4int repNo,G4VPhysicalVolume *currentVol,
							const G4VTouchable *parentTouch=0);

  private:  // Dummy declarations to get rid of warnings ...

    void ComputeDimensions (G4Trd&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Trap&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Cons&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Sphere&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Orb&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Torus&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Para&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Hype&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Box&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Polycone&,const G4int,const G4VPhysicalVolume*) const {}
    void ComputeDimensions (G4Polyhedra&,const G4int,const G4VPhysicalVolume*) const {}
  private:

    G4int    fNoChambers;   
    G4double fStartZ;
    G4Material* Fe;
    G4Material* W;
    G4Material* PMMANist;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


