//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef ExN02PhysicsList_h
#define ExN02PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02PhysicsList: public G4VUserPhysicsList
{
    public:
        ExN02PhysicsList();
        ~ExN02PhysicsList();

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

    protected:
        // these methods Construct physics processes and register them
        void ConstructGeneral();
        void ConstructEM();
        void AddStepMax();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


