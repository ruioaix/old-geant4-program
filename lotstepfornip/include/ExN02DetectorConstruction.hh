#ifndef ExN02DetectorConstruction_h
#define ExN02DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "ExN02MagneticField.hh"

class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;
class ExN02DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// 删掉了一些用不到的变量，加了一些会用到的变量。
class ExN02DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
     ExN02DetectorConstruction();
    ~ExN02DetectorConstruction();

  public:
  
     G4VPhysicalVolume* Construct();
     
     const 
     G4VPhysicalVolume* GetTracker() {return physiTracker;};
     G4double GetWorldFullLength()   {return fWorldLength;}; 
     
     void setTargetMaterial (G4String);
     void setChamberMaterial(G4String);
     void SetMagField(G4double);
     void SetMaxStep (G4double);     
     
  private:

     G4Box*             solidWorld;    // pointer to the solid envelope 
     G4LogicalVolume*   logicWorld;    // pointer to the logical envelope
     G4VPhysicalVolume* physiWorld;    // pointer to the physical envelope
     
     G4Tubs*             solidTarget;   // pointer to the solid Target
     G4LogicalVolume*   logicTarget;   // pointer to the logical Target
     G4VPhysicalVolume* physiTarget;   // pointer to the physical Target

     G4Tubs*             solidtarch;
     G4LogicalVolume*   logictarch;
     G4VPhysicalVolume* physitarch;
              
     G4Tubs*             solidTracker;  // pointer to the solid Tracker
     G4LogicalVolume*   logicTracker;  // pointer to the logical Tracker
     G4VPhysicalVolume* physiTracker;  // pointer to the physical Tracker
     
     G4Tubs*             solidChamber;  // pointer to the solid Chamber
     G4LogicalVolume*   logicChamber;  // pointer to the logical Chamber
     G4VPhysicalVolume* physiChamber;  // pointer to the physical Chamber
     
     G4Material*         TargetMater;  // pointer to the target  material
     G4Material*         ChamberMater; // pointer to the chamber material
     G4Material*         tarChamberMater; // pointer to the chamber material

     G4VPVParameterisation* chamberParam; // pointer to chamber parameterisation
     G4VPVParameterisation* tarchaparam;

     G4UserLimits* stepLimit;             // pointer to user step limits

     ExN02MagneticField* fpMagField;   // pointer to the magnetic field 
     
     ExN02DetectorMessenger* detectorMessenger;  // pointer to the Messenger
       
     G4double fWorldLength;            // Full length of the world volume
     G4int    NbOfChambers;            // Nb of chambers in the tracker region
     G4int    NbOftarChambers;            // Nb of chambers in the tracker region
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
