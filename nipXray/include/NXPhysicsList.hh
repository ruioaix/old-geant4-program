//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef NXPhysicsList_h
#define NXPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NXPhysicsList: public G4VUserPhysicsList
{
    public:
        NXPhysicsList();
        ~NXPhysicsList();

    protected:
        // Construct particle and physics
        void ConstructParticle();
        void ConstructProcess();

        void SetCuts();


    protected:
        // these methods Construct particles 
        void ConstructBosons();
        void ConstructLeptons();
        void ConstructMesons();
        void ConstructBaryons();
        void ConstructIons();

    protected:
        // these methods Construct physics processes and register them
        void ConstructGeneral();
        void ConstructEM();
        void AddStepMax();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


