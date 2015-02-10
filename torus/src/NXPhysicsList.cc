#include "globals.hh"
#include "NXPhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VPhysicsConstructor.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4PhysicsListHelper.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4RayleighScattering.hh"
#include "G4KleinNishinaModel.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4NuclearStopping.hh"

#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"

#include "G4SystemOfUnits.hh"

NXPhysicsList::NXPhysicsList():  G4VUserPhysicsList()
{
    //defaultCutValue = 1.0*cm;
    SetVerboseLevel(1);
}

NXPhysicsList::~NXPhysicsList()
{
}

void NXPhysicsList::ConstructParticle()
{
    // In this method, static member functions should be called
    // for all particles which you want to use.
    // This ensures that objects of these particle types will be
    // created in the program. 
    G4cout<<"NXPhysicsList::ConstructParticle"<<G4endl;

    ConstructBosons();
    ConstructLeptons();
    ConstructBaryons();
    G4cout<<"NXPhysicsList::ConstructParticle done"<<G4endl;
}

void NXPhysicsList::ConstructBosons()
{
    G4cout<<"constructing bosons"<<G4endl;
    // pseudo-particles
    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();

    // gamma
    G4Gamma::GammaDefinition();

    // optical photon
    G4OpticalPhoton::OpticalPhotonDefinition();
}

#include "G4LeptonConstructor.hh"
void NXPhysicsList::ConstructLeptons()
{
    G4cout<<"constructing leptons"<<G4endl;
    G4LeptonConstructor pConstructor;
    pConstructor.ConstructParticle();
}

#include "G4BaryonConstructor.hh"
void NXPhysicsList::ConstructBaryons()
{
    G4cout<<"constructing baryons"<<G4endl;
    G4BaryonConstructor  pConstructor;
    pConstructor.ConstructParticle();  
}

void NXPhysicsList::ConstructProcess()
{
    G4cout<<"NXPhysicsList::ConstructProcess"<<G4endl;
    AddTransportation();
    ConstructEM();
    G4cout<<"NXPhysicsList::ConstructProcess done"<<G4endl;
}

void NXPhysicsList::ConstructEM()
{
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  
  // Add standard EM Processes
  //
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4String particleName = particle->GetParticleName();
     
    if (particleName == "gamma") {

      ////ph->RegisterProcess(new G4RayleighScattering, particle);      
      ph->RegisterProcess(new G4PhotoElectricEffect, particle);      
      G4ComptonScattering* cs   = new G4ComptonScattering;
      cs->SetEmModel(new G4KleinNishinaModel());
      ph->RegisterProcess(cs, particle);
      ph->RegisterProcess(new G4GammaConversion, particle);
     
    } else if (particleName == "e-") {

      G4eIonisation* eIoni = new G4eIonisation();
      eIoni->SetStepFunction(0.1, 100*um);      
      ph->RegisterProcess(eIoni,                   particle);
      ph->RegisterProcess(new G4eBremsstrahlung(), particle);      
            
    }
  }
    
  // Deexcitation
  //
  G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
  de->SetFluo(true);
  de->SetAuger(true);   
  de->SetPIXE(true);  
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);
}


void NXPhysicsList::SetCuts()
{
    G4cout<<"setting default cuts "<<G4endl;
    SetCutsWithDefault();
    DumpCutValuesTable();
    G4cout<<"setting default cuts done"<<G4endl;
}
