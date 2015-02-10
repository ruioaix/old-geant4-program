#ifndef StdPhysicsList_h
#define StdPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

class PhysListEmStandard: public G4VPhysicsConstructor
{
    public:
        PhysListEmStandard();
        ~PhysListEmStandard();

    protected:
        // Construct particle and physics
        void ConstructParticle();
        void ConstructProcess();
        void SetCuts();

    protected:
        // these methods Construct particles 
        void ConstructBosons();
        void ConstructLeptons();
        void ConstructBaryons();

        // these methods Construct physics processes and register them
        void ConstructEM();
};

#endif


