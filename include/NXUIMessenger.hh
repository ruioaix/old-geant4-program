//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef NXUIMessenger_h
#define NXUIMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class NXUserDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NXUIMessenger: public G4UImessenger
{
    public:
        NXUIMessenger(NXUserDetectorConstruction*);
        ~NXUIMessenger();

        void SetNewValue(G4UIcommand*, G4String);

    private:
        NXUserDetectorConstruction* myDetector;

        G4UIdirectory*             N02Dir;
        G4UIdirectory*             detDir;
        G4UIcmdWithAString*        TargMatCmd;
        G4UIcmdWithAString*        ChamMatCmd;    
        G4UIcmdWithADoubleAndUnit* FieldCmd;
        G4UIcmdWithADoubleAndUnit* StepMaxCmd;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

