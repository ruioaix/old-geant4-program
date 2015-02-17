#include "ExN02DetectorConstruction.hh"
#include "ExN02DetectorMessenger.hh"
#include "ExN02ChamberParameterisation.hh"
#include "ExN02MagneticField.hh"
#include "ExN02TrackerSD.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4String.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"

//Vacuum
extern	G4Material* Vacuum=new G4Material("Vacuum",1.0,1.01*g/mole,1.0E-25*g/cm3,kStateGas,2.73*kelvin,3.0E-18*pascal);
//Fe
extern	G4Material* Fe=new G4Material("iron",26,55.847*g/mole,7.86*g/cm3);
 
ExN02DetectorConstruction::ExN02DetectorConstruction()
:solidWorld(0),logicWorld(0),physiWorld(0),
 w24c_sol(0),w24c_log(0),w24c_phy(0),
 orige_sol(0),orige_log(0),orige_phy(0), 
 core_s_sol(0),core_s_log(0),core_s_phy(0), 
 core_sol(0),core_log(0),core_phy(0), 
 guan_sol(0),guan_log(0),guan_phy(0),  
 TargetMater(0),chamberParam(0),
 stepLimit(0),fpMagField(0),
 fWorldLength(0.),fTargetLength(0.),fTrackerLength(0.)
{
  	fpMagField = new ExN02MagneticField();
  	detectorMessenger = new ExN02DetectorMessenger(this);
}

 
ExN02DetectorConstruction::~ExN02DetectorConstruction()
{
  	delete fpMagField;
  	delete stepLimit;
  	delete chamberParam;
  	delete detectorMessenger;             
}

 
G4VPhysicalVolume* ExN02DetectorConstruction::Construct()
{
  	G4double a,z,j=0;
  	G4double density;
  	G4int i,nel;
	G4String Tname;

  	//Air
  	G4Element* N = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
  	G4Element* O = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole); 
  	G4Material* Air = new G4Material("Air", density= 1.29*mg/cm3, nel=2);
  	Air->AddElement(N, 70*perCent);
  	Air->AddElement(O, 30*perCent);

	//tungsten
	G4Material* W = new G4Material("tungsten" ,z=74,a=183.85*g/mole, density=19.35*g/cm3);
 
  	//------------------------------ 
  	// World
  	//------------------------------ 
  	fWorldLength= 800*cm;
  	G4double HalfWorldLength = 0.5*fWorldLength;
  	G4GeometryManager::GetInstance()->SetWorldMaximumExtent(fWorldLength);
  	solidWorld= new G4Box("world",HalfWorldLength,HalfWorldLength,HalfWorldLength);
  	logicWorld= new G4LogicalVolume( solidWorld, Vacuum, "World", 0, 0, 0);
  	physiWorld = new G4PVPlacement(	0,               
                                 	G4ThreeVector(0,0,0),
                                 	logicWorld,     
				         			"World",        
                                 	0,           
                                 	false,    
                                 	0);      
				 

  	//------------------------------ 
  	// Target-24CW
  	//------------------------------
  	w24c_sol = new G4Box("target",0.5*cm,0.5*cm,0.025*cm);
  	w24c_log = new G4LogicalVolume(w24c_sol,W,"Target",0,0,0);
	for(i=0;i<24;i++)
	{
		j = (-95+i*0.1)*cm;
  		w24c_phy = new G4PVPlacement(0,               // no rotation
						G4ThreeVector(0,0,j),
				  		w24c_log,     // its lofgical volume		
					  	"Target",        // its name
					  	logicWorld,      // its mother  volume
					  	false,           // no boolean operations
					  	0);              // copy number 
	}


  	//------------------------------ 
  	// 能谱测量面-紧随靶放置
  	//------------------------------
  	G4ThreeVector positiontotalE = G4ThreeVector(0,0,-69*cm);
  	orige_sol = new G4Tubs("st00",0*cm,0.2*cm,0.001*cm,0*deg,360*deg);
  	orige_log = new G4LogicalVolume(orige_sol, Vacuum, "origin",0,0,0);  
  	orige_phy = new G4PVPlacement(	0,              	// no rotation
				  		positiontotalE, 	// at (x,y,z)
				  		orige_log,    	// its logical volume	p
				  		"origin",       	// its name
				  		logicWorld,      	// its mother  volume
				  		false,           	// no boolean operations
				  		0);              	// copy number 


  	//------------------------------ 
  	// 测量环--important
  	//------------------------------
  	core_sol = new G4Tubs("trackerFe",0*cm,15*cm,10*cm,0*deg,360*deg);  //这是圆环的外形，包括内径外经和半厚度。
  	core_log = new G4LogicalVolume(core_sol, Vacuum, "Tracker_Fe",0,0,0);  //圆环设置为真空
  	core_phy = new G4PVPlacement(	0,              	// no rotation
				  		G4ThreeVector(0,0,20*cm),	// at (x,y,z)
				  		core_log,    				// its logical volume	
				  		"Tracker_Fe",       		// its name
				  		logicWorld,      			// its mother  volume
				  		false,           			// no boolean operations
				  		0);              			// copy number 


  	core_s_sol = new G4Tubs("chamber",0*cm,1*cm,0.4*cm,0*deg,360*deg);  //圆环中小片的形状，
  	core_s_log = new G4LogicalVolume(core_s_sol, Vacuum, "chamber",0,0,0); //小片为铁
	chamberParam = new ExN02ChamberParameterisation(  
						   24,          // NoChambers 
						   0*cm,         // Z of center of first 
						   9*cm,        // Z spacing of centers
						   8*cm,          // Width Chamber 
						   2.5*cm,           // lengthInitial 
						   10*cm);           // lengthFinal
  	core_s_phy = new G4PVParameterised(
                           	"Chamber",       // their name
                           	core_s_log,    // their logical volume
                    		core_log,    // Mother logical volume
			    			kZAxis,          // Are placed along this axis 
                            24,    // Number of chambers
                           	chamberParam);   // The parametrisation
	
  	
	//------------------------------ 
  	// 圆罐—— 吸收散射
  	//------------------------------
	guan_sol = new G4Sphere("guan_sd",140*cm,150*cm,0*deg,360*deg,0*deg,170*deg);
	guan_log = new G4LogicalVolume(guan_sol, Vacuum, "guan_sens",0,0,0); 
	guan_phy = new G4PVPlacement(	0,
								G4ThreeVector(0,0,190*cm),
								guan_log,
								"guan_sens",
								logicWorld,
								false,
								0); 

  	//------------------------------------------------ 
  	// Sensitive detectors
  	//------------------------------------------------ 
  	G4SDManager* SDman = G4SDManager::GetSDMpointer();
  	G4String trackerSDname = "MyDetector";
  	ExN02TrackerSD* myTrackerSD = new ExN02TrackerSD( trackerSDname );
  	SDman->AddNewDetector( myTrackerSD );
	core_s_log->SetSensitiveDetector(myTrackerSD);
  	orige_log->SetSensitiveDetector( myTrackerSD);

	//--------- Visualization attributes -------------------------------
  	G4VisAttributes* VisWorld = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  	G4VisAttributes* VisTarget = new G4VisAttributes(G4Colour(0,1.0,1.0));
  	G4VisAttributes* VisFe = new G4VisAttributes(G4Colour(1.0,0,1.0));
  	G4VisAttributes* VisTracker1 = new G4VisAttributes(G4Colour(1.0,1.0,0));
  	G4VisAttributes* VisTracker2 = new G4VisAttributes(G4Colour(1.0,0,0));
  	logicWorld  ->SetVisAttributes(VisWorld);  
 	w24c_log->SetVisAttributes(VisTarget);
	orige_log->SetVisAttributes(VisTracker2);
 	core_log->SetVisAttributes(VisWorld);
  	core_s_log ->SetVisAttributes(VisFe);
  	guan_log->SetVisAttributes(VisTracker1);
	
  
  	return physiWorld;
}

 
void ExN02DetectorConstruction::setTargetMaterial(G4String materialName)
{
  	G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  	if (pttoMaterial)
     	{
			TargetMater = pttoMaterial;
      		core_s_log->SetMaterial(pttoMaterial); 
      		G4cout << "\n----> The target is " << fTargetLength/cm << " cm of "<< materialName << G4endl;
     	}             
}
 
 
void ExN02DetectorConstruction::SetMagField(G4double fieldValue)
{
  	fpMagField->SetFieldValue(fieldValue);
}


void ExN02DetectorConstruction::SetMaxStep(G4double maxStep)
{
  	if ((stepLimit)&&(maxStep>0.)) stepLimit->SetMaxAllowedStep(maxStep);
}

