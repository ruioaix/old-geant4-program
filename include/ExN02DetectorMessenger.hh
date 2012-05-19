//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef ExN02DetectorMessenger_h
#define ExN02DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class ExN02DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02DetectorMessenger: public G4UImessenger
{
    public:
        ExN02DetectorMessenger(ExN02DetectorConstruction*);
        ~ExN02DetectorMessenger();

        void SetNewValue(G4UIcommand*, G4String);

    private:
        ExN02DetectorConstruction* myDetector;

        G4UIdirectory*             N02Dir;
        G4UIdirectory*             detDir;
        G4UIcmdWithAString*        TargMatCmd;
        G4UIcmdWithAString*        ChamMatCmd;    
        G4UIcmdWithADoubleAndUnit* FieldCmd;
        G4UIcmdWithADoubleAndUnit* StepMaxCmd;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

