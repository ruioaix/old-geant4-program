#include "NXUserDetectorConstruction.hh"
#include "NXSensitiveDetector.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
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
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4UnitsTable.hh"

//#define scale (3.08e13*km / 1000000)
#define scale (m)
#define densityscalefactor (scale*scale*scale/(parsec*1.*parsec*parsec))

NXUserDetectorConstruction::NXUserDetectorConstruction() :
    solidWorld(0),  logicWorld(0),  physiWorld(0),
    solidTarget(0), logicTarget(0), physiTarget(0), 
    stepLimit(0), 
    worldLength(5.*scale), fTargetLength(0)
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
    //G4Material* absMaterial=man->FindOrBuildMaterial("G4_Fe");;
    G4Element* elFe = new G4Element("Iron"    ,"Fe", 26., 55.85*g/mole);
    G4Element* elH  = new G4Element("Hydrogen","H" ,  1., 1.01*g/mole);
    G4double density     = 1.0e38*g/(densityscalefactor*parsec*parsec*parsec);
    density = 1e15*g/m3 * (densityscalefactor*parsec*parsec*parsec);
    G4double pressure    = 1.e-19*pascal;
    G4double temperature = 10*kelvin;
    G4Material* GalGas = new G4Material("GalacticGas", density, 2, kStateGas, temperature, pressure);
    GalGas->AddElement(elH,  99.9*perCent);
    GalGas->AddElement(elFe, 0.1*perCent);
    G4double absThickness=1e-20*scale;
    G4Material*  absMaterial = GalGas;

    G4cout<<"construct: target solid"<<G4endl;
    solidAbsorber = new G4Box("target", absThickness / 2., 1.*scale, 1.*scale);
    G4cout<<"construct: target logic"<<G4endl;
    logicAbsorber = new G4LogicalVolume(solidAbsorber, absMaterial,"Target",0,0,0);
    G4cout<<"construct: target physic"<<G4endl;
    physiAbsorber = new G4PVPlacement(0,               // no rotation
                G4ThreeVector(1.*scale,0,0),  // at (x,y,z)
                logicAbsorber,     // its logical volume				  
                "Absorber",        // its name
                logicWorld,      // its mother  volume
                false,           // no boolean operations
                0);              // copy number 
    
    G4cout<<"construct: target material"<<G4endl;
    fTargetLength=worldLength/1000;

    G4cout<<"construct: target solid"<<G4endl;
    solidTarget = new G4Sphere("target", worldLength/2 - fTargetLength, worldLength/2, 
		0, 2*pi, 0, pi);
    G4cout<<"construct: target logic"<<G4endl;
    logicTarget = new G4LogicalVolume(solidTarget,Vacuum,"Target",0,0,0);
    G4cout<<"construct: target physic"<<G4endl;
    physiTarget = new G4PVPlacement(0,               // no rotation
                G4ThreeVector(0,0,0),  // at (x,y,z)
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



