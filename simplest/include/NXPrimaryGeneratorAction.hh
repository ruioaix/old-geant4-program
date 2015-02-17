#ifndef NXPrimaryGeneratorAction_h
#define NXPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class NXUserDetectorConstruction;
class G4ParticleGun;
class G4Event;

class NXPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
    public:
        NXPrimaryGeneratorAction(NXUserDetectorConstruction*);    
        ~NXPrimaryGeneratorAction();

    public:
        void GeneratePrimaries(G4Event*);

    private:
        G4ParticleGun* particleGun;
        NXUserDetectorConstruction* myDetector;
};

#endif
