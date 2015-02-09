#include "globals.hh"
#include "NXPhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"

NXPhysicsList::NXPhysicsList():  G4VUserPhysicsList()
{
    defaultCutValue = 1.0*cm;
    SetVerboseLevel(1);
}

NXPhysicsList::~NXPhysicsList()
{}

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

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4hMultipleScattering.hh"

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

void NXPhysicsList::ConstructEM()
{
    G4cout<<"NXPhysicsList::ConstructEM"<<G4endl;
    theParticleIterator->reset();
    while( (*theParticleIterator)() ){
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();

        //G4cout<<"for "<<particleName <<G4endl;
        if (particleName == "gamma") {
            // gamma         
            G4cout<<"adding photon processes "<<G4endl;
            pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
            //pmanager->AddDiscreteProcess(new G4ComptonScattering);
            //pmanager->AddDiscreteProcess(new G4GammaConversion);

        } else if (particleName == "e-") {
            //electron
            G4cout<<"adding electron processes "<<G4endl;
            //pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
            //pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
            //pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);      
        }
    }
}

void NXPhysicsList::SetCuts()
{
    G4cout<<"setting default cuts "<<G4endl;
    SetCutsWithDefault();
    G4cout<<"setting default cuts done"<<G4endl;
}
