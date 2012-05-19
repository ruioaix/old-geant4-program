//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef ExN02PrimaryGeneratorAction_h
#define ExN02PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class ExN02DetectorConstruction;
class G4ParticleGun;
class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        ExN02PrimaryGeneratorAction(ExN02DetectorConstruction*);    
        ~ExN02PrimaryGeneratorAction();

    public:
        void GeneratePrimaries(G4Event*);

    private:
        G4ParticleGun* particleGun;
        ExN02DetectorConstruction* myDetector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


