//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NXUserDetectorConstruction.hh"
#include "NXSensitiveDetector.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

#include "G4NistManager.hh"

NXUserDetectorConstruction::NXUserDetectorConstruction() :
    solidWorld(0),  logicWorld(0),  physiWorld(0),
    solidTarget(0), logicTarget(0), physiTarget(0), 
    stepLimit(0), 
    worldLength(100*m), fTargetLength(0)
{
}

NXUserDetectorConstruction::~NXUserDetectorConstruction()
{
    delete stepLimit;
}

G4VPhysicalVolume* NXUserDetectorConstruction::Construct()
{
    G4cout<<"NXUserDetectorConstruction::Construct: "<<G4endl;
    G4NistManager* man=G4NistManager::Instance();
    //G4Material* Vacuum = new G4Material("Vacuum",1.0,1.01*g/mole,1.0E-25*g/cm3,kStateGas,2.73*kelvin,3.0E-18*pascal);
    G4Material* Vacuum    = man->FindOrBuildMaterial("G4_Galactic");


    //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
    // World

    G4double worldboxside = worldLength / 2;

    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(worldLength);
    G4cout<<"construct: world solid"<<G4endl;
    solidWorld= new G4Box("World",worldboxside,worldboxside,worldboxside);
    G4cout<<"construct: world logic"<<G4endl;
    logicWorld= new G4LogicalVolume( solidWorld, Vacuum, "World", 0, 0, 0);

    //  Must place the World Physical volume unrotated at (0,0,0).
    // 
    G4cout<<"construct: world physic"<<G4endl;
    physiWorld = new G4PVPlacement(0,               // no rotation
            G4ThreeVector(0, 0, 0), // at (0,0,0)
            logicWorld,      // its logical volume
            "World",         // its name
            0,               // its mother  volume
            false,           // no boolean operations
            0);              // copy number

    //------------------------------ 
    // Target
    //------------------------------
    G4cout<<"construct: target material"<<G4endl;
    G4Material* absMaterial=man->FindOrBuildMaterial("G4_Fe");;
    G4double absThickness=1*mm;

    G4cout<<"construct: target solid"<<G4endl;
    solidAbsorber = new G4Box("target", 1*m, 1*m, absThickness / 2);
    G4cout<<"construct: target logic"<<G4endl;
    logicAbsorber = new G4LogicalVolume(solidAbsorber, absMaterial,"Target",0,0,0);
    G4cout<<"construct: target physic"<<G4endl;
    physiAbsorber = new G4PVPlacement(0,               // no rotation
                G4ThreeVector(0,0,0.5*m),  // at (x,y,z)
                logicAbsorber,     // its logical volume				  
                "Absorber",        // its name
                logicWorld,      // its mother  volume
                false,           // no boolean operations
                0);              // copy number 
    
    G4cout<<"construct: target material"<<G4endl;
    fTargetLength=1*mm;
    G4double fHalfTargetLength=0.5*fTargetLength;

    G4cout<<"construct: target solid"<<G4endl;
    solidTarget = new G4Box("target", 1*m, 1*m, fHalfTargetLength);
    G4cout<<"construct: target logic"<<G4endl;
    logicTarget = new G4LogicalVolume(solidTarget,Vacuum,"Target",0,0,0);
    G4cout<<"construct: target physic"<<G4endl;
    physiTarget = new G4PVPlacement(0,               // no rotation
                G4ThreeVector(0,0,1*m),  // at (x,y,z)
                logicTarget,     // its logical volume				  
                "Target",        // its name
                logicWorld,      // its mother  volume
                false,           // no boolean operations
                0);              // copy number 

    //------------------------------------------------ 
    // Sensitive detectors
    //------------------------------------------------ 

    
    G4cout<<"construct: detector"<<G4endl;
    G4String trackerChamberSDname = "nipXray/NXSensitiveDetector";
    NXSensitiveDetector* aTrackerSD = new NXSensitiveDetector(trackerChamberSDname);
    G4cout<<"construct: adding detector to SDM"<<G4endl;
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector( aTrackerSD );
    logicTarget->SetSensitiveDetector( aTrackerSD );
    
    G4cout<<"construct: setting user steps"<<G4endl;
    G4double maxStep = 0.5*cm;
    stepLimit = new G4UserLimits(maxStep);
    //logicTracker->SetUserLimits(stepLimit);
    
    
    G4cout<<"construct: returning constructed world"<<G4endl;
    return physiWorld;
}



