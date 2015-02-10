#include "globals.hh"
#include "NXPhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

NXPhysicsList::NXPhysicsList():  G4VUserPhysicsList()
{
    //defaultCutValue = 1.0*cm;
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

#include "G4EmProcessOptions.hh"

#include "G4ionIonisation.hh"
#include "G4VAtomDeexcitation.hh"
#include "G4UAtomicDeexcitation.hh"

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
    G4cout<<"setting EM options"<<G4endl;
    G4VAtomDeexcitation * de = new G4UAtomicDeexcitation();
    G4LossTableManager::Instance()->SetAtomDeexcitation(de);
    
    //emOptions.SetDeexcitationActive(true);
    //emOptions.SetAugerActive(true);
    //emOptions.SetMinEnergy(0.1 * keV);
    de->SetFluo(true); // To activate deexcitation processes and fluorescence
    de->SetAuger(true); // To activate Auger effect if deexcitation is activated
    de->SetPIXE(true); // To activate Particle Induced X-Ray Emission (PIXE) 
    //ad->SetFluo(true);
    //ad->SetAuger(true);
    G4cout << "deexcitation: " << de->IsFluoActive() << G4endl;

    
}

void NXPhysicsList::SetCuts()
{
    G4cout<<"setting default cuts "<<G4endl;
    SetCutsWithDefault();
    DumpCutValuesTable();
    G4cout<<"setting default cuts done"<<G4endl;
}
