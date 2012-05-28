//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NXPrimaryGeneratorAction.hh"
#include "NXUserDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

#include "Randomize.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXPrimaryGeneratorAction::NXPrimaryGeneratorAction( NXUserDetectorConstruction* myDC) :
    myDetector(myDC)
{
    G4int n_particle = 1;
    particleGun = new G4ParticleGun(n_particle);

    // default particle

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("e-");
    //G4ParticleDefinition* particle = particleTable->FindParticle("gamma"); 
    //G4ParticleDefinition* particle = particleTable->FindParticle("neutron");
    //G4ParticleDefinition* particle = particleTable->FindParticle("alpha");
    //G4ParticleDefinition* particle = particleTable->FindParticle("proton");

    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleEnergy(20.0*MeV);

    G4double position = -699.5*mm;
    particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,position));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXPrimaryGeneratorAction::~NXPrimaryGeneratorAction()
{
    delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 

    G4double x2y2_2 = 10*G4UniformRand();
    G4double phi=twopi*G4UniformRand();
    G4double x=x2y2_2*std::sin(phi);
    G4double y=x2y2_2*std::cos(phi);
    G4double z=232;
    
    particleGun->SetParticleMomentumDirection(G4ThreeVector(x,y,z));

    particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

