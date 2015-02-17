#include "NXPrimaryGeneratorAction.hh"
#include "NXUserDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

#include "Randomize.hh"

NXPrimaryGeneratorAction::NXPrimaryGeneratorAction( NXUserDetectorConstruction* myDC) :
    myDetector(myDC)
{
    G4cout<<"NXPrimaryGeneratorAction: creating photon "<<G4endl;
    G4int n_particle = 1000;
    particleGun = new G4ParticleGun(n_particle);

    // default particle
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    //G4ParticleDefinition* particle = particleTable->FindParticle("e-");
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma"); 
    //G4ParticleDefinition* particle = particleTable->FindParticle("neutron");
    //G4ParticleDefinition* particle = particleTable->FindParticle("alpha");
    //G4ParticleDefinition* particle = particleTable->FindParticle("proton");

    particleGun->SetParticleDefinition(particle);

    G4cout<<"NXPrimaryGeneratorAction: setting position "<<G4endl;
    particleGun->SetParticlePosition(G4ThreeVector(0,0,0));
}

NXPrimaryGeneratorAction::~NXPrimaryGeneratorAction()
{
    delete particleGun;
}

void NXPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
    G4cout<<"NXPrimaryGeneratorAction: shooting "<<G4endl;
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    particleGun->SetParticleEnergy(2*keV);
    particleGun->GeneratePrimaryVertex(anEvent);
}

