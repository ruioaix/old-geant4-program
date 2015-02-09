#include "NXPrimaryGeneratorAction.hh"
#include "NXUserDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

#include "Randomize.hh"

NXPrimaryGeneratorAction::NXPrimaryGeneratorAction( NXUserDetectorConstruction* myDC) :
    myDetector(myDC)
{
    G4cout<<"NXPrimaryGeneratorAction: creating photon "<<G4endl;
    G4int n_particle = 1;
    particleSource = new G4GeneralParticleSource();
    particleSource->SetNumberOfParticles(n_particle);

    // default particle
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma"); 
    particleSource->SetParticleDefinition(particle);

    G4cout<<"NXPrimaryGeneratorAction: setting position "<<G4endl;
    particleSource->SetParticlePosition(G4ThreeVector(0,0,0));
}

NXPrimaryGeneratorAction::~NXPrimaryGeneratorAction()
{
    delete particleSource;
}

void NXPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
    //particleSource->SetParticleMomentumDirection(G4ThreeVector(0,0,1*m));
    G4cout<<"NXPrimaryGeneratorAction: shooting " 
	" from "<< particleSource->GetParticlePosition() <<
	" to "<< particleSource->GetParticleMomentumDirection() <<
	" with Energy "<< particleSource->GetParticleEnergy() / keV <<
	" keV" <<G4endl;
    
    //particleSource->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    // random energies
    //G4double energy = (10*G4UniformRand() + 0.1) * keV;
    //particleSource->SetParticleEnergy(energy);
    particleSource->GeneratePrimaryVertex(anEvent);
}

