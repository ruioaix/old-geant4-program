#include "ExN02PrimaryGeneratorAction.hh"
#include "ExN02DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02PrimaryGeneratorAction::ExN02PrimaryGeneratorAction(
                                               ExN02DetectorConstruction* myDC)
:myDetector(myDC)
{
  G4int n_particle = 1;
  //这里设置1个，那么一个event1个粒子入射。n个，就n个入射。
  particleGun = new G4ParticleGun(n_particle);

// default particle

	//设置粒子为电子。
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  //G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
  G4ParticleDefinition* particle = particleTable->FindParticle("e-");
  //G4ParticleDefinition* particle = particleTable->FindParticle("proton");
  particleGun->SetParticleDefinition(particle);


	//设置粒子运动方向。
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));

  //设置粒子能量
  particleGun->SetParticleEnergy(20*MeV);

  //设置粒子的位置
  //G4double position = -0.5*(myDetector->GetWorldFullLength());
  particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,-399*cm));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02PrimaryGeneratorAction::~ExN02PrimaryGeneratorAction()
{
  delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
  particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

