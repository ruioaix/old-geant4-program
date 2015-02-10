#include "NXRunAction.hh"
#include "G4Run.hh"

NXRunAction::NXRunAction()
{}

NXRunAction::~NXRunAction()
{}

void NXRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "NXRunAction::BeginOfRunAction: Run #" << aRun->GetRunID() << " start." << G4endl;
}

void NXRunAction::EndOfRunAction(const G4Run*)
{ 
    G4cout<<"NXRunAction::EndOfRunAction: end of run"<<G4endl;

}
