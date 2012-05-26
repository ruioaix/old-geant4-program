//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef NXUserDetectorConstruction_h
#define NXUserDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "NXMagneticField.hh"

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;
class NXUIMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NXUserDetectorConstruction : public G4VUserDetectorConstruction
{
    public:

        NXUserDetectorConstruction();
        ~NXUserDetectorConstruction();

    public:

        G4VPhysicalVolume* Construct();

        const 
            G4VPhysicalVolume* GetTracker() {return physiTracker;};
        //G4double GetTrackerFullLength() {return fTrackerLength;};
        //G4double GetTargetFullLength()  {return fTargetLength;};
        G4double GetWorldFullLength()   {return fWorldLength;}; 

        void setTargetMaterial (G4String);
        void setTargetLengthZ (G4double);
        void setGapinTarget(G4double);
        void setChamberMaterial(G4String);
        void SetMagField(G4double);
        void SetMaxStep (G4double);     

    private:

        G4Box*             solidWorld;    // pointer to the solid envelope 
        G4LogicalVolume*   logicWorld;    // pointer to the logical envelope
        G4VPhysicalVolume* physiWorld;    // pointer to the physical envelope

        G4Box*             solidTarget;   // pointer to the solid Target
        G4LogicalVolume*   logicTarget;   // pointer to the logical Target
        G4VPhysicalVolume* physiTarget;   // pointer to the physical Target
        G4VPhysicalVolume* physiTargetArray[10];   // pointer to the physical Target

        G4Box*             solidTracker;  // pointer to the solid Tracker
        G4LogicalVolume*   logicTracker;  // pointer to the logical Tracker
        G4VPhysicalVolume* physiTracker;  // pointer to the physical Tracker

        G4Box*             solidChamber;  // pointer to the solid Chamber
        G4LogicalVolume*   logicChamber;  // pointer to the logical Chamber
        G4VPhysicalVolume* physiChamber;  // pointer to the physical Chamber

        G4Material*         TargetMater;  // pointer to the target  material
        G4Material*         ChamberMater; // pointer to the chamber material

        G4VPVParameterisation* chamberParam; // pointer to chamber parameterisation
        G4UserLimits* stepLimit;             // pointer to user step limits

        NXMagneticField* fpMagField;   // pointer to the magnetic field 

        NXUIMessenger* detectorMessenger;  // pointer to the Messenger

        G4double fWorldLength;            // Full length of the world volume
        G4int    NbOfChambers;            // Nb of chambers in the tracker region
        G4double GapinTarget;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
