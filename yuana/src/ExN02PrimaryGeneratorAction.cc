#include "ExN02PrimaryGeneratorAction.hh"
#include "ExN02DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"

ExN02PrimaryGeneratorAction::ExN02PrimaryGeneratorAction(ExN02DetectorConstruction* myDC)
:myDetector(myDC)
{
  	G4int n_particle = 1;
  	particleGun = new G4ParticleGun(n_particle);
  	
	//设置粒子为电子。
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  	G4ParticleDefinition* particle = particleTable->FindParticle("e-");
	particleGun->SetParticleDefinition(particle);

	//设置粒子运动方向。
  	particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  	
	//设置粒子枪的位置。
	particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,-199*cm));
}

ExN02PrimaryGeneratorAction::~ExN02PrimaryGeneratorAction()
{
  	delete particleGun;
}

void ExN02PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
/*  
	//用于产生能量高斯分布的粒子。
	G4double mean;
	G4double stddev;
	mean = 3*MeV;
	stddev = 1*MeV;
  	G4double energyp;
	energyp = G4RandGauss::shoot(mean,stddev);
*/

	//G4cout<<"EVENTenergy IS "<<energyp/keV<<G4endl;   //用于检测。
	
	//设置粒子的初始能量。
	G4double energyp = 20*MeV;
	particleGun->SetParticleEnergy(energyp);
  	particleGun->GeneratePrimaryVertex(anEvent);
}

G4double ExN02PrimaryGeneratorAction::GetParticleEnergy()
{
	G4double energyparticle = particleGun->GetParticleEnergy();
	return energyparticle;
}

