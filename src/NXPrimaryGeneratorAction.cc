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

    // For discrete Energy Spectrum
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    G4double energyPara;
    G4double rand=G4UniformRand();
         if(rand<0.0025) energyPara=0.25*MeV;
    else if(rand<0.0075) energyPara=0.75*MeV;
    else if(rand<0.0150) energyPara=1.25*MeV;
    else if(rand<0.0250) energyPara=1.75*MeV;
    else if(rand<0.0375) energyPara=2.25*MeV;
    else if(rand<0.0525) energyPara=2.75*MeV;
    else if(rand<0.0700) energyPara=3.25*MeV;
    else if(rand<0.0900) energyPara=3.75*MeV;
    else if(rand<0.1125) energyPara=4.25*MeV;
    else if(rand<0.1375) energyPara=4.75*MeV;
    else if(rand<0.1650) energyPara=5.25*MeV;
    else if(rand<0.1950) energyPara=5.75*MeV;
    else if(rand<0.2275) energyPara=6.25*MeV;
    else if(rand<0.2625) energyPara=6.75*MeV;
    else if(rand<0.3000) energyPara=7.25*MeV;
    else if(rand<0.3400) energyPara=7.75*MeV;
    else if(rand<0.3825) energyPara=8.25*MeV;
    else if(rand<0.4275) energyPara=8.75*MeV;
    else if(rand<0.4750) energyPara=9.25*MeV;
    else if(rand<0.5250) energyPara=9.75*MeV;
    else if(rand<0.5725) energyPara=10.25*MeV;
    else if(rand<0.6175) energyPara=10.75*MeV;
    else if(rand<0.6600) energyPara=11.25*MeV;
    else if(rand<0.7000) energyPara=11.75*MeV;
    else if(rand<0.7375) energyPara=12.25*MeV;
    else if(rand<0.7725) energyPara=12.75*MeV;
    else if(rand<0.8050) energyPara=13.25*MeV;
    else if(rand<0.8350) energyPara=13.75*MeV;
    else if(rand<0.8625) energyPara=14.25*MeV;
    else if(rand<0.8875) energyPara=14.75*MeV;
    else if(rand<0.9100) energyPara=15.25*MeV;
    else if(rand<0.9300) energyPara=15.75*MeV;
    else if(rand<0.9475) energyPara=16.25*MeV;
    else if(rand<0.9625) energyPara=16.75*MeV;
    else if(rand<0.9750) energyPara=17.25*MeV;
    else if(rand<0.9850) energyPara=17.75*MeV;
    else if(rand<0.9925) energyPara=18.25*MeV;
    else if(rand<0.9975) energyPara=18.75*MeV;
    else if(rand<1) energyPara=19.25*MeV;
    particleGun->SetParticleEnergy(energyPara);

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
    //particleGun->SetParticleEnergy(20*MeV);
    particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

