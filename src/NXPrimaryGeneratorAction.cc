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

    G4double position = -799.5*mm;
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
/*
    // For Focus
    G4double x2y2_2 = 10*G4UniformRand();
    G4double phi=twopi*G4UniformRand();
    G4double x=x2y2_2*std::sin(phi);
    G4double y=x2y2_2*std::cos(phi);
    G4double z=232;
    particleGun->SetParticleMomentumDirection(G4ThreeVector(x,y,z));
*/

/*
    // For discrete Energy Spectrum
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    G4double energyPara;
    G4double rand=G4UniformRand();
    if(rand<0.006662231) energyPara=0.2*MeV;
    else if(rand<0.019986694) energyPara=0.4*MeV;
    else if(rand<0.039973387) energyPara=0.6*MeV;
    else if(rand<0.066622312) energyPara=0.8*MeV;
    else if(rand<0.099933468) energyPara=1*MeV;
    else if(rand<0.139906855) energyPara=1.2*MeV;
    else if(rand<0.186542474) energyPara=1.4*MeV;
    else if(rand<0.239840323) energyPara=1.6*MeV;
    else if(rand<0.299800404) energyPara=1.8*MeV;
    else if(rand<0.366422716) energyPara=2*MeV;
    else if(rand<0.429713913) energyPara=2.2*MeV;
    else if(rand<0.489673993) energyPara=2.4*MeV;
    else if(rand<0.546302959) energyPara=2.6*MeV;
    else if(rand<0.599600808) energyPara=2.8*MeV;
    else if(rand<0.649567542) energyPara=3*MeV;
    else if(rand<0.696203161) energyPara=3.2*MeV;
    else if(rand<0.739507663) energyPara=3.4*MeV;
    else if(rand<0.779481051) energyPara=3.6*MeV;
    else if(rand<0.816123322) energyPara=3.8*MeV;
    else if(rand<0.849434478) energyPara=4*MeV;
    else if(rand<0.879414339) energyPara=4.2*MeV;
    else if(rand<0.906063104) energyPara=4.4*MeV;
    else if(rand<0.929380773) energyPara=4.6*MeV;
    else if(rand<0.949367347) energyPara=4.8*MeV;
    else if(rand<0.966022825) energyPara=5*MeV;
    else if(rand<0.979347207) energyPara=6*MeV;
    else if(rand<0.989340494) energyPara=8*MeV;
    else if(rand<0.996002685) energyPara=10*MeV;
    else if(rand<0.999333781) energyPara=15*MeV;
    else if(rand<1) energyPara=20*MeV;
    particleGun->SetParticleEnergy(energyPara);
*/

/*
    G4double mean;
    G4double stddev;
    mean = 0;
    stddev = 0.3*mm/2.35482;
    G4double x2plusy2_2;
    x2plusy2_2 = G4RandGauss::shoot(mean,stddev);
    G4double phi=twopi*G4UniformRand();
    phi=3.1415926*G4UniformRand();
    G4double x=x2plusy2_2*std::sin(phi);
    G4double y=x2plusy2_2*std::cos(phi);
    G4double z = -799.5*mm;
    particleGun->SetParticlePosition(G4ThreeVector(x,y,z));
*/
   
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    particleGun->SetParticleEnergy(20*MeV);
    particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

