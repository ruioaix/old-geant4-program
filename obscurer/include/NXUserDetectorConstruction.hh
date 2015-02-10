#ifndef NXUserDetectorConstruction_h
#define NXUserDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4Box;
class G4Sphere;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;

class NXUserDetectorConstruction : public G4VUserDetectorConstruction
{
    public:

        NXUserDetectorConstruction();
        ~NXUserDetectorConstruction();

    public:

        G4VPhysicalVolume* Construct();
        G4double GetWorldFullLength()   {return worldLength;}; 

    private:

        G4Box*             solidWorld;    // pointer to the solid envelope 
        G4LogicalVolume*   logicWorld;    // pointer to the logical envelope
        G4VPhysicalVolume* physiWorld;    // pointer to the physical envelope

        G4Sphere*          solidTarget;   // pointer to the solid Target
        G4LogicalVolume*   logicTarget;   // pointer to the logical Target
        G4VPhysicalVolume* physiTarget;   // pointer to the physical Target

        G4Box*             solidAbsorber;    // pointer to the solid envelope 
        G4LogicalVolume*   logicAbsorber;    // pointer to the logical envelope
        G4VPhysicalVolume* physiAbsorber;    // pointer to the physical envelope

        G4UserLimits* stepLimit;             // pointer to user step limits

        G4double worldLength;            // Full length of the world volume
        G4double fTargetLength;
};

#endif
