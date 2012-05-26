//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NXUIMessenger.hh"

#include "NXUserDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXUIMessenger::NXUIMessenger(NXUserDetectorConstruction* myDet) :
    myDetector(myDet)
{ 
    N02Dir = new G4UIdirectory("/N02/");
    N02Dir->SetGuidance("UI commands specific to this example.");

    detDir = new G4UIdirectory("/N02/det/");
    detDir->SetGuidance("detector control.");

    TargMatCmd = new G4UIcmdWithAString("/NX/TargetMaterial",this);
    TargMatCmd->SetGuidance("Select Material of the Target.");
    TargMatCmd->SetParameterName("choice",false);
    TargMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    ChamMatCmd = new G4UIcmdWithAString("/N02/det/setChamberMate",this);
    ChamMatCmd->SetGuidance("Select Material of the Target.");
    ChamMatCmd->SetParameterName("choice",false);
    ChamMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

    FieldCmd = new G4UIcmdWithADoubleAndUnit("/N02/det/setField",this);  
    FieldCmd->SetGuidance("Define magnetic field.");
    FieldCmd->SetGuidance("Magnetic field will be in X direction.");
    FieldCmd->SetParameterName("Bx",false);
    FieldCmd->SetUnitCategory("Magnetic flux density");
    FieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    StepMaxCmd = new G4UIcmdWithADoubleAndUnit("/N02/det/stepMax",this);  
    StepMaxCmd->SetGuidance("Define a step max");
    StepMaxCmd->SetParameterName("stepMax",false);
    StepMaxCmd->SetUnitCategory("Length");
    StepMaxCmd->AvailableForStates(G4State_Idle);    

    TargetLengthZCmd = new G4UIcmdWithADoubleAndUnit("/NX/TargetLengthZ",this);  
    TargetLengthZCmd->SetGuidance("redefine the length of target.");
    TargetLengthZCmd->SetParameterName("TargetLengthZ",false);
    TargetLengthZCmd->SetUnitCategory("Length");
    TargetLengthZCmd->AvailableForStates(G4State_Idle);    

    GapinTargetCmd = new G4UIcmdWithADoubleAndUnit("/NX/GapinTarget",this);  
    GapinTargetCmd->SetGuidance("define the gap between target.");
    GapinTargetCmd->SetParameterName("GapinTarget",false);
    GapinTargetCmd->SetUnitCategory("Length");
    GapinTargetCmd->AvailableForStates(G4State_Idle);    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXUIMessenger::~NXUIMessenger()
{
    delete TargMatCmd;
    delete ChamMatCmd;
    delete FieldCmd;
    delete StepMaxCmd;  
    delete TargetLengthZCmd;  
    delete detDir;
    delete N02Dir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXUIMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
    if( command == TargMatCmd )
    { myDetector->setTargetMaterial(newValue);}

    if( command == ChamMatCmd )
    { myDetector->setChamberMaterial(newValue);}  

    if( command == FieldCmd )
    { myDetector->SetMagField(FieldCmd->GetNewDoubleValue(newValue));}

    if( command == StepMaxCmd )
    { myDetector->SetMaxStep(StepMaxCmd->GetNewDoubleValue(newValue));}   

    if( command == TargetLengthZCmd)
    { myDetector->setTargetLengthZ(TargetLengthZCmd->GetNewDoubleValue(newValue));}   

    if( command == GapinTargetCmd)
    { myDetector->setGapinTarget(GapinTargetCmd->GetNewDoubleValue(newValue));}   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
