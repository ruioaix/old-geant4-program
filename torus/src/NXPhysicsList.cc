#include "globals.hh"
#include "NXPhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "StdPhysicsList.hh"
#include "G4VPhysicsConstructor.hh"

NXPhysicsList::NXPhysicsList():  G4VUserPhysicsList()
{
    physics = new PhysListEmStandard();
    //defaultCutValue = 1.0*cm;
    SetVerboseLevel(1);
}

NXPhysicsList::~NXPhysicsList()
{
    delete physics;
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
    physics->ConstructProcess();
    G4cout<<"NXPhysicsList::ConstructProcess done"<<G4endl;
}


void NXPhysicsList::SetCuts()
{
    G4cout<<"setting default cuts "<<G4endl;
    SetCutsWithDefault();
    DumpCutValuesTable();
    G4cout<<"setting default cuts done"<<G4endl;
}
