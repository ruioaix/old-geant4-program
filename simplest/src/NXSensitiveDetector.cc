#include "NXSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4RunManager.hh"
//#include "NXRunAction.hh"

NXSensitiveDetector::NXSensitiveDetector(G4String name) :
    G4VSensitiveDetector(name)
{
}

NXSensitiveDetector::~NXSensitiveDetector(){ }

void NXSensitiveDetector::Initialize(G4HCofThisEvent* HCE)
{
}

G4bool NXSensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
    G4StepPoint* pointPre=aStep->GetPreStepPoint();
    G4StepPoint* pointPost=aStep->GetPostStepPoint(); 
    G4TouchableHandle touchCur=pointPre->GetTouchableHandle();
    G4VPhysicalVolume* volumeCur=touchCur->GetVolume();
    G4String volumeCurName=volumeCur->GetName();
    G4int copyNumofChamber=touchCur->GetCopyNumber();
    G4Track* trackCur=aStep->GetTrack();
    G4ParticleDefinition* particleCur = trackCur->GetDefinition();
    G4String particleCurName = particleCur->GetParticleName();
    G4double kineticEnergyCur = trackCur->GetKineticEnergy();
    G4RunManager* runManager= G4RunManager::GetRunManager();
    //NXRunAction* runActionCur=(NXRunAction *)runManager->GetUserRunAction();
    
    G4cout << "Detector hit! " << pointPre->GetPosition() << " --> " << pointPost->GetPosition() << 
	" by " << particleCurName << 
	" with E=" << kineticEnergyCur / keV << "keV inside " << volumeCurName << G4endl;
    
    
    return true;
}

void NXSensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    G4cout << "Event end!" << G4endl;

}
