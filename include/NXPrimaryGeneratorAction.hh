//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef NXPrimaryGeneratorAction_h
#define NXPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class ExN02DetectorConstruction;
class G4ParticleGun;
class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NXPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        NXPrimaryGeneratorAction(ExN02DetectorConstruction*);    
        ~NXPrimaryGeneratorAction();

    public:
        void GeneratePrimaries(G4Event*);

    private:
        G4ParticleGun* particleGun;
        ExN02DetectorConstruction* myDetector;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


