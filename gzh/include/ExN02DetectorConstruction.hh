#ifndef ExN02DetectorConstruction_h
#define ExN02DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "ExN02MagneticField.hh"
class G4Tubs;
class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;
class ExN02DetectorMessenger;
class G4Sphere;

class ExN02DetectorConstruction : public G4VUserDetectorConstruction
{
  	public:
     		ExN02DetectorConstruction();
    		~ExN02DetectorConstruction();

  	public:
     		G4VPhysicalVolume* Construct();     
     		const 
     		G4double GetWorldFullLength()   {return fWorldLength;}; 
     		void setTargetMaterial (G4String);
     		void SetMagField(G4double);
     		void SetMaxStep (G4double);     
     
  	private:
     		G4Box*             	solidWorld;    
     		G4LogicalVolume*   	logicWorld;   
     		G4VPhysicalVolume* 	physiWorld;  
     
     		G4Tubs*             orige_sol; 
     		G4LogicalVolume*   	orige_log; 
     		G4VPhysicalVolume* 	orige_phy; 

     		G4Box*            	w24c_sol;  
     		G4LogicalVolume*   	w24c_log; 
     		G4VPhysicalVolume* 	w24c_phy; 
     
     		G4Tubs*            	core_sol; 
     		G4LogicalVolume*   	core_log;
     		G4VPhysicalVolume* 	core_phy; 

     		G4VPVParameterisation* 	chamberParam;

     		G4Tubs*            	core_s_sol; 
     		G4LogicalVolume*   	core_s_log; 
     		G4VPhysicalVolume* 	core_s_phy; 
               
			G4Sphere*           guan_sol; 
     		G4LogicalVolume*   	guan_log; 
     		G4VPhysicalVolume* 	guan_phy; 
     

     		G4Material*         TargetMater; 
     		G4UserLimits* 		stepLimit;   
     		ExN02MagneticField* 	fpMagField; 
     
     		ExN02DetectorMessenger* detectorMessenger; 
       
     		G4double 		fWorldLength;            
     		G4double 		fTargetLength;          
     		G4double 		fTrackerLength;        
};

#endif
