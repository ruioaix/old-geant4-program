#include "ExN02DetectorConstruction.hh"
#include "ExN02DetectorMessenger.hh"
#include "ExN02ChamberParameterisation.hh"
#include "TargetChamberParameterisation.hh"
#include "ExN02MagneticField.hh"
#include "ExN02TrackerSD.hh"

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
 
ExN02DetectorConstruction::ExN02DetectorConstruction()
:solidWorld(0),  logicWorld(0),  physiWorld(0),
 solidTarget(0), logicTarget(0), physiTarget(0), 
 //这里添加了一行，下面还添加了两个，这里的这些叫做直接初始化。
 //这里的都是指针，指针初始化为0，是明智的。
 solidtarch(0),  logictarch(0), physitarch(0),
 solidTracker(0),logicTracker(0),physiTracker(0), 
 solidChamber(0),logicChamber(0),physiChamber(0), 
 TargetMater(0), ChamberMater(0),tarChamberMater(0),
 chamberParam(0), tarchaparam(0),
 stepLimit(0), fpMagField(0),
 fWorldLength(0.),  
 NbOfChambers(0) 
{
  fpMagField = new ExN02MagneticField();
  detectorMessenger = new ExN02DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
ExN02DetectorConstruction::~ExN02DetectorConstruction()
{
  delete fpMagField;
  delete stepLimit;
  delete chamberParam;
  //这里添加了delete，其他的分配了new的指针的删除应该是runmanager执行的。
  delete tarchaparam;
  delete detectorMessenger;             
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* ExN02DetectorConstruction::Construct()
{
//--------- Material definition ---------
//屏蔽掉的这些，是不想编译的时候出现未使用的warning，删了下次要用可惜，所以注释掉。
  //vacuum
  G4Material* Vacuum=new G4Material("Vacuum",1.0,1.01*g/mole,1.0E-25*g/cm3,kStateGas,2.73*kelvin,3.0E-18*pascal);
/*
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
  G4Material* Pb = 
  new G4Material("Lead", z=82., a= 207.19*g/mole, density= 11.35*g/cm3);
    
  //Xenon gas
  G4Material* Xenon = 
  new G4Material("XenonGas", z=54., a=131.29*g/mole, density= 5.458*mg/cm3,
                 kStateGas, temperature= 293.15*kelvin, pressure= 1*atmosphere);
  //Fe
  G4Material* Fe = new G4Material( "Fe", 26., 55.847*g/mole, 7.87* g/cm3 );
*/

  //W
  G4Material* W = new G4Material( "W",74.,183.84*g/mole,19.3* g/cm3 );

  //pmmanist
 // G4Material* PMMANist=G4NistManager::Instance()->FindOrBuildMaterial("G4_PLEXIGLASS",false);
  //
  // Print all the materials defined.
  //
  //G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  //G4cout << *(G4Material::GetMaterialTable()) << G4endl;

      
//--------- Definitions of Solids, Logical Volumes, Physical Volumes ---------
  
  //------------------------------ 
  // World
  //------------------------------ 
  fWorldLength = 800*cm;
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
  
  TargetMater  = Vacuum;
  G4ThreeVector positionTarget = G4ThreeVector(0,0,-200*cm);
  solidTarget = new G4Tubs("target",0*cm,300*cm,190*cm,0*deg,360*deg);
  logicTarget = new G4LogicalVolume(solidTarget,TargetMater,"Target",0,0,0);
  physiTarget = new G4PVPlacement(0,               // no rotation
				  positionTarget,  // at (x,y,z)
				  logicTarget,     // its logical volume				  
				  "Target",        // its name
				  logicWorld,      // its mother  volume
				  false,           // no boolean operations
				  0);              // copy number 

  G4cout << "Target is " << " cm of " 
         << TargetMater->GetName() << G4endl;

  //------------------------------ 
  //Target segment
  //------------------------------ 
  //这里就是添加的chamber了，上面的target是这个的母体，从target的形状就可以看出很大。
  //下面的单元都是新添加的。 
  tarChamberMater = W;     //这个的设置其实不必要，在chamberpara函数里面其实重新设定了。
  NbOftarChambers = 26;
  G4double tarfirstposition = 100*cm;
  solidtarch = new G4Tubs("tarchamber",0*cm,100*cm,0.025*cm,0*deg,360*deg);
  logictarch = new G4LogicalVolume(solidtarch,tarChamberMater,"Tarchamber",0,0,0);
  tarchaparam = new TargetChamberParameterisation(NbOftarChambers,tarfirstposition);
  physitarch = new G4PVParameterised(
                          "Tarchamber",
                          logictarch,
                          logicTarget,
                          kZAxis,
                          NbOftarChambers,
                          tarchaparam);



  //------------------------------ 
  // Tracker
  //------------------------------
  
  G4ThreeVector positionTracker = G4ThreeVector(0,0,200*cm);
  
  solidTracker = new G4Tubs("tracker",0*cm,300*cm,190*cm,0*deg,360*deg);
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

  ChamberMater = Vacuum;
  solidChamber = new G4Tubs("chamber", 0*cm, 100*cm, 1*cm, 0*deg, 360*deg);
  logicChamber = new G4LogicalVolume(solidChamber,ChamberMater,"Chamber",0,0,0);
  
  G4double firstPosition = -180*cm;
  NbOfChambers = 1;
  chamberParam = new ExN02ChamberParameterisation(NbOfChambers,firstPosition);           
			   
  // dummy value : kZAxis -- modified by parameterised volume
  //
  physiChamber = new G4PVParameterised(
                            "Chamber",       // their name
                            logicChamber,    // their logical volume
                            logicTracker,    // Mother logical volume
                  			    kZAxis,          // Are placed along this axis 
                            NbOfChambers,    // Number of chambers
                            chamberParam);   // The parametrisation

  //G4cout << "There are " << NbOfChambers << " chambers in the tracker region. "
  //       << ChamberMater->GetName() << "\n The distance between chamber is "
	// << " cm" << G4endl;
	 
  //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  G4String trackerChamberSDname = "ExN02/TrackerChamberSD";
  ExN02TrackerSD* aTrackerSD = new ExN02TrackerSD( trackerChamberSDname );
  SDman->AddNewDetector( aTrackerSD );
  logicChamber->SetSensitiveDetector( aTrackerSD );

//--------- Visualization attributes -------------------------------

  G4VisAttributes* BoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  logicWorld  ->SetVisAttributes(BoxVisAtt);  
  logicTarget ->SetVisAttributes(BoxVisAtt);
  logicTracker->SetVisAttributes(BoxVisAtt);
  
  G4VisAttributes* ChamberVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
  logicChamber->SetVisAttributes(ChamberVisAtt);
  
//--------- example of User Limits -------------------------------

  // below is an example of how to set tracking constraints in a given
  // logical volume(see also in N02PhysicsList how to setup the processes
  // G4StepLimiter or G4UserSpecialCuts).
    
  // Sets a max Step length in the tracker region, with G4StepLimiter
  //设置最大的step长度，感觉几厘米就差不多了。
  G4double maxStep = 5*cm;
  stepLimit = new G4UserLimits(maxStep);
  logicTracker->SetUserLimits(stepLimit);
  
  // Set additional contraints on the track, with G4UserSpecialCuts
  //
  // G4double maxLength = 2*fTrackerLength, maxTime = 0.1*ns, minEkin = 10*MeV;
  // logicTracker->SetUserLimits(new G4UserLimits(maxStep,maxLength,maxTime,
  //                                               minEkin));
  
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void ExN02DetectorConstruction::setTargetMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {TargetMater = pttoMaterial;
      logicTarget->SetMaterial(pttoMaterial); 
      G4cout << "\n----> The target is " << " cm of "
             << materialName << G4endl;
     }             
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02DetectorConstruction::setChamberMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {ChamberMater = pttoMaterial;
      logicChamber->SetMaterial(pttoMaterial); 
      G4cout << "\n----> The chambers are " <<  " cm of "
             << materialName << G4endl;
     }             
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
void ExN02DetectorConstruction::SetMagField(G4double fieldValue)
{
  fpMagField->SetFieldValue(fieldValue);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((stepLimit)&&(maxStep>0.)) stepLimit->SetMaxAllowedStep(maxStep);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
