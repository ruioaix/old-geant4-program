//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NXUserDetectorConstruction.hh"
#include "NXUIMessenger.hh"
#include "NXChamberParameterisation.hh"
#include "NXMagneticField.hh"
#include "NXSensitiveDetector.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXUserDetectorConstruction::NXUserDetectorConstruction() :
    solidWorld(0),  logicWorld(0),  physiWorld(0),
    solidTarget(0), logicTarget(0), physiTarget(0), 
    solidTracker(0),logicTracker(0),physiTracker(0), 
    solidoneFe(0),logiconeFe(0),physioneFe(0), 
    solidoneSD(0),logiconeSD(0),physioneSD(0), 
    solidChamber(0),logicChamber(0),physiChamber(0), 
    TargetMater(0), ChamberMater(0),chamberParam(0),
    stepLimit(0), fpMagField(0),
    fWorldLength(0.), GapinTarget(0), fTargetLength(0),
    NbOfChambers(0) 
{
    //In NXMagneticField, the constructor does everything. now there is no MagneticField, because there is no G4threevector variable in () and it mean the MagneticField is zero.
    fpMagField = new NXMagneticField();
    detectorMessenger = new NXUIMessenger(this);
    for(G4int i=0;i<10;i++) {
        physiTargetArray[i]=0;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXUserDetectorConstruction::~NXUserDetectorConstruction()
{
    delete fpMagField;
    delete stepLimit;
    delete chamberParam;
    delete detectorMessenger;             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* NXUserDetectorConstruction::Construct()
{
    //--------- Material definition ---------

    G4double a, z;
    G4double density, temperature, pressure;
    G4int nel;

    //Air
    G4Element* N = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
    G4Element* O = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole);

    G4Material* Air = new G4Material("Air", density= 1.29*mg/cm3, nel=2);
    Air->AddElement(N, 70*perCent);
    Air->AddElement(O, 30*perCent);

    //Lead
    G4Material* Pb = new G4Material("Lead", z=82., a= 207.19*g/mole, density= 11.35*g/cm3);

    //Xenon gas
    G4Material* Xenon = new G4Material("XenonGas", z=54., a=131.29*g/mole, density= 5.458*mg/cm3, kStateGas, temperature= 293.15*kelvin, pressure= 1*atmosphere);

    //Use Nist material Database instead of build material by myself.
    G4NistManager* man=G4NistManager::Instance();
    G4Material* PMMANist=man->FindOrBuildMaterial("G4_PLEXIGLASS");
    G4Material* Al=man->FindOrBuildMaterial("G4_Al"); //13

    //G4Material* Ti=man->FindOrBuildMaterial("G4_Ti"); //22
    G4Material* V=man->FindOrBuildMaterial("G4_V"); //23
    //G4Material* Cr=man->FindOrBuildMaterial("G4_Cr"); //24
    //G4Material* Mn=man->FindOrBuildMaterial("G4_Mn"); //25
    G4Material* Fe=man->FindOrBuildMaterial("G4_Fe"); //26
    //G4Material* Co=man->FindOrBuildMaterial("G4_Co"); //27
    //G4Material* Ni=man->FindOrBuildMaterial("G4_Ni"); //28
    G4Material* Cu=man->FindOrBuildMaterial("G4_Cu"); //29

    G4Material* Mo=man->FindOrBuildMaterial("G4_Mo"); //42
    G4Material* Ag=man->FindOrBuildMaterial("G4_Ag"); //47

    G4Material* Ta=man->FindOrBuildMaterial("G4_Ta");//73
    G4Material* W=man->FindOrBuildMaterial("G4_W");//74
    G4Material* Au=man->FindOrBuildMaterial("G4_Au");//79

    // build material by myself.
    //vacuum
    G4Material* Vacuum=new G4Material("Vacuum",1.0,1.01*g/mole,1.0E-25*g/cm3,kStateGas,2.73*kelvin,3.0E-18*pascal);
    //Ta
    G4Material* Ta_byme = new G4Material( "Ta", 73., 180.95*g/mole, 16.65* g/cm3 );

    // Print all the materials defined.
    //
    G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;


    //--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------

    //------------------------------ 
    // World
    //------------------------------ 

    fWorldLength= 2*m;
    G4double HalfWorldLength = 0.5*fWorldLength;

    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(fWorldLength);
    G4cout << "Computed tolerance = "
        << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
        << " mm" << G4endl;

    solidWorld= new G4Box("world",HalfWorldLength,HalfWorldLength,HalfWorldLength);
    logicWorld= new G4LogicalVolume( solidWorld, Vacuum, "World", 0, 0, 0);

    //  Must place the World Physical volume unrotated at (0,0,0).
    // 
    physiWorld = new G4PVPlacement(0,               // no rotation
            G4ThreeVector(), // at (0,0,0)
            logicWorld,      // its logical volume
            "World",         // its name
            0,               // its mother  volume
            false,           // no boolean operations
            0);              // copy number

    //------------------------------ 
    // Target
    //------------------------------

    TargetMater  = Ta;
    G4ThreeVector positionTarget = G4ThreeVector(0,0,-70*cm);
    fTargetLength=1*mm;
    G4double fHalfTargetLength=0.5*fTargetLength;

    solidTarget = new G4Box("target", 2*cm, 2*cm, fHalfTargetLength);
    logicTarget = new G4LogicalVolume(solidTarget,TargetMater,"Target",0,0,0);
    for(G4int i=0;i<24;i++) {
        G4double z=-70*cm+i*(GapinTarget+2*(solidTarget->GetZHalfLength()));
        positionTarget=G4ThreeVector(0,0,z);
        physiTargetArray[i] = new G4PVPlacement(0,               // no rotation
                positionTarget,  // at (x,y,z)
                logicTarget,     // its logical volume				  
                "Target",        // its name
                logicWorld,      // its mother  volume
                false,           // no boolean operations
                0);              // copy number 
    }

    //------------------------------ 
    // OneSD 
    //------------------------------
    G4ThreeVector positiononeSD= G4ThreeVector(0,0,-50*cm);

    solidoneSD= new G4Tubs("oneSD", 0*cm, 1.5*cm, 5*mm, 0*deg, 360*deg);
    logiconeSD= new G4LogicalVolume(solidoneSD, Vacuum, "OneSD",0,0,0);  
    physioneSD= new G4PVPlacement(0,              // no rotation
            positiononeSD, // at (x,y,z)
            logiconeSD,    // its logical volume				  
            "OneSD",       // its name
            logicWorld,      // its mother  volume
            false,           // no boolean operations
            0);              // copy number 


    //------------------------------ 
    // OneFe 
    //------------------------------
    G4ThreeVector positiononeFe= G4ThreeVector(0,0,0);

    solidoneFe= new G4Box("oneFe", 5*cm, 5*cm, 5*mm);
    logiconeFe= new G4LogicalVolume(solidoneFe, Fe, "OneFe",0,0,0);  
    physioneFe= new G4PVPlacement(0,              // no rotation
            positiononeFe, // at (x,y,z)
            logiconeFe,    // its logical volume				  
            "OneFe",       // its name
            logicWorld,      // its mother  volume
            false,           // no boolean operations
            0);              // copy number 


    //------------------------------ 
    // Tracker
    //------------------------------

    G4ThreeVector positionTracker = G4ThreeVector(0,0,20*cm);

    solidTracker = new G4Box("tracker", 5*cm, 5*cm, 5*cm);
    logicTracker = new G4LogicalVolume(solidTracker , Vacuum, "Tracker",0,0,0);  
    physiTracker = new G4PVPlacement(0,              // no rotation
            positionTracker, // at (x,y,z)
            logicTracker,    // its logical volume				  
            "Tracker",       // its name
            logicWorld,      // its mother  volume
            false,           // no boolean operations
            0);              // copy number 

    //------------------------------ 
    // Tracker segments
    //------------------------------
    // 
    // An example of Parameterised volumes
    // dummy values for G4Box -- modified by parameterised volume

    NbOfChambers = 1;
    ChamberMater = Vacuum;

    solidChamber = new G4Tubs("chamber", 0*cm, 1.5*cm, 0.5*cm, 0*deg, 360*deg); 
    logicChamber = new G4LogicalVolume(solidChamber,ChamberMater,"Chamber",0,0,0);

    G4double firstPosition = 0;

    chamberParam = new NXChamberParameterisation(  firstPosition);

    // dummy value : kZAxis -- modified by parameterised volume
    //
    physiChamber = new G4PVParameterised(
            "Chamber",       // their name
            logicChamber,    // their logical volume
            logicTracker,    // Mother logical volume
            kZAxis,          // Are placed along this axis 
            NbOfChambers,    // Number of chambers
            chamberParam);   // The parametrisation

    G4cout << "There are " << NbOfChambers << " chambers in the tracker region. "
        << ChamberMater->GetName() << "\n The distance between chamber is "
        << " cm" << G4endl;

    G4cout<<"The world is G4Box, fWorldLength is "<<fWorldLength/cm<<" cm"<<G4endl;
    G4cout<<"The Target is G4Box, x&y length is 1cm, fTargetLength is "<<fTargetLength/mm<<" mm"<<G4endl;

    //------------------------------------------------ 
    // Sensitive detectors
    //------------------------------------------------ 

    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    G4String trackerChamberSDname = "nipXray/NXSensitiveDetector";
    NXSensitiveDetector* aTrackerSD = new NXSensitiveDetector( trackerChamberSDname );
    SDman->AddNewDetector( aTrackerSD );
    logicChamber->SetSensitiveDetector( aTrackerSD );
    logiconeSD->SetSensitiveDetector( aTrackerSD );


    //--------- Visualization attributes -------------------------------
    //G4Colour  white   ()                // white    
    //G4Colour  white   (1.0, 1.0, 1.0)   // white      
    //G4Colour  gray    (0.5, 0.5, 0.5)   // gray      
    //G4Colour  black   (0.0, 0.0, 0.0)   // black     
    //G4Colour  red     (1.0, 0.0, 0.0)   // red      
    //G4Colour  green   (0.0, 1.0, 0.0)   // green     
    //G4Colour  blue    (0.0, 0.0, 1.0)   // blue     
    //G4Colour  cyan    (0.0, 1.0, 1.0)   // cyan     
    //G4Colour  magenta (1.0, 0.0, 1.0)   // magenta   
    //G4Colour  yellow  (1.0, 1.0, 0.0)   // yellow

    G4VisAttributes* BoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    logicWorld  ->SetVisAttributes(BoxVisAtt);  //white

    G4VisAttributes* TargetVisAtt= new G4VisAttributes(G4Colour(0,0,1.0));
    logicTarget ->SetVisAttributes(TargetVisAtt); //blue

    G4VisAttributes* TrackerVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
    logicTracker->SetVisAttributes(TrackerVisAtt);  //yellow

    G4VisAttributes* ChamberVisAtt = new G4VisAttributes(G4Colour(0,1.0,0.0));
    logicChamber->SetVisAttributes(ChamberVisAtt);  //green

    //--------- example of User Limits -------------------------------

    // below is an example of how to set tracking constraints in a given
    // logical volume(see also in NXPhysicsList how to setup the processes
    // G4StepLimiter or G4UserSpecialCuts).

    // Sets a max Step length in the tracker region, with G4StepLimiter
    //
    G4double maxStep = 0.5*cm;
    stepLimit = new G4UserLimits(maxStep);
    logicTracker->SetUserLimits(stepLimit);

    return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXUserDetectorConstruction::setTargetMaterial(G4String materialName)
{
    // search the material by its name 
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
    if (pttoMaterial)
    {TargetMater = pttoMaterial;
        logicTarget->SetMaterial(pttoMaterial); 
        G4cout << "\n----> The target is " << materialName << G4endl;
    }             
}

void NXUserDetectorConstruction::setTargetLengthZ(G4double z)
{
    solidTarget->SetZHalfLength(z/2);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXUserDetectorConstruction::setGapinTarget(G4double gap)
{
    GapinTarget=gap;
    G4ThreeVector positionTarget = G4ThreeVector(0,0,-70*cm);
    for(G4int i=0;i<10;i++) {
        G4double z=-70*cm+i*(GapinTarget+2*(solidTarget->GetZHalfLength()));
        positionTarget=G4ThreeVector(0,0,z);
        delete physiTargetArray[i];
        physiTargetArray[i]= new G4PVPlacement(0,               // no rotation
                positionTarget,  // at (x,y,z)
                logicTarget,     // its logical volume				  
                "Target",        // its name
                logicWorld,      // its mother  volume
                false,           // no boolean operations
                0);              // copy number 
    }
}

void NXUserDetectorConstruction::setChamberMaterial(G4String materialName)
{
    // search the material by its name 
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
    if (pttoMaterial)
    {ChamberMater = pttoMaterial;
        logicChamber->SetMaterial(pttoMaterial); 
        G4cout << "\n----> The chambers are " << materialName << G4endl;
    }             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXUserDetectorConstruction::SetMagField(G4double fieldValue)
{
    fpMagField->SetFieldValue(fieldValue);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXUserDetectorConstruction::SetMaxStep(G4double maxStep)
{
    if ((stepLimit)&&(maxStep>0.)) stepLimit->SetMaxAllowedStep(maxStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void NXUserDetectorConstruction::setOneFeLengthZ(G4double z)
{
    // search the material by its name 
    solidoneFe->SetZHalfLength(z/2);
}

void NXUserDetectorConstruction::setOneFeMaterial(G4String materialName)
{
    // search the material by its name 
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
    if (pttoMaterial)
    {TargetMater = pttoMaterial;
        logiconeFe->SetMaterial(pttoMaterial); 
        G4cout << "\n----> The OneFe's material is " << materialName << G4endl;
    }             
}


