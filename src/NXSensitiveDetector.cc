//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NXSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4RunManager.hh"
#include "NXRunAction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXSensitiveDetector::NXSensitiveDetector(G4String name) :
    G4VSensitiveDetector(name)
{
    G4String HCname;
    collectionName.insert(HCname="trackerCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXSensitiveDetector::~NXSensitiveDetector(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXSensitiveDetector::Initialize(G4HCofThisEvent* HCE)
{
    trackerCollection = new NXHitsCollection
        (SensitiveDetectorName,collectionName[0]); 
    static G4int HCID = -1;
    if(HCID<0)
    { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
    HCE->AddHitsCollection( HCID, trackerCollection ); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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
    NXRunAction* runActionCur=(NXRunAction *)runManager->GetUserRunAction();

    if(volumeCurName == "OneSD") {
        if(particleCurName == "gamma") {
            if(kineticEnergyCur == 20*MeV)
                runActionCur->Allgammaof20MeV++;
            for(G4int i=0;i<40;i++) {
                if(kineticEnergyCur<=((i+1)*0.5*MeV) && kineticEnergyCur>(i*0.5*MeV)) {
                    runActionCur->OneSD_ESofGamma[i]++;
                    break;
                }
            }
        } else if(particleCurName == "e+") {
            for(G4int i=0;i<40;i++) {
                if(kineticEnergyCur<=((i+1)*0.5*MeV) && kineticEnergyCur>(i*0.5*MeV)) {
                    runActionCur->OneSD_ESofPositron[i]++;
                    break;
                }
            }
        } else if(particleCurName == "e-") {
            for(G4int i=0;i<40;i++) {
                if(kineticEnergyCur<=(0.5*(i+1.0)*MeV) && kineticEnergyCur>(i*0.5*MeV)) {
                    runActionCur->OneSD_ESofNegatron[i]++;
                    break;
                }
            }
        } else {
            runActionCur->OtherParticle++;
        }
    }
    
    if(volumeCurName == "Chamber") {
        if(copyNumofChamber == 0) {
            if (pointPre->GetStepStatus() != fGeomBoundary) {
                runActionCur->NumofPrePointNotBoundary++;
            } else {
                runActionCur->NumofPrePointIsBoundary++;
            }

            if(particleCurName == "gamma") {
                runActionCur->EnergyofGammaContrb+=kineticEnergyCur;
                for(G4int i=0;i<40;i++) {
                    if(kineticEnergyCur<=((i+1)*0.5*MeV) && kineticEnergyCur>(i*0.5*MeV)) {
                        runActionCur->CenterESofGamma[i]++;
                        break;
                    }
                }
            } else if(particleCurName == "e+") {
                runActionCur->EnergyofPositronContrb+=kineticEnergyCur;
                for(G4int i=0;i<40;i++) {
                    if(kineticEnergyCur<=((i+1)*0.5*MeV) && kineticEnergyCur>(i*0.5*MeV)) {
                        runActionCur->CenterESofPositron[i]++;
                        break;
                    }
                }
            } else if(particleCurName == "e-") {
                runActionCur->EnergyofNegatronContrb+=kineticEnergyCur;
                for(G4int i=0;i<40;i++) {
                    if(kineticEnergyCur<=(0.5*(i+1.0)*MeV) && kineticEnergyCur>(i*0.5*MeV)) {
                        runActionCur->CenterESofNegatron[i]++;
                        break;
                    }
                }
            } else {
                runActionCur->EnergyofOtherParticleContrb+=kineticEnergyCur;
                runActionCur->OtherParticle++;
                G4double edep = aStep->GetTotalEnergyDeposit();

                if(edep==0.) return false;

                NXHit* newHit = new NXHit();
                newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
                newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()
                        ->GetCopyNumber());
                newHit->SetEdep     (edep);
                newHit->SetPos      (aStep->GetPostStepPoint()->GetPosition());
                trackerCollection->insert( newHit );
            }
        }
    }

    //newHit->Print();
    //newHit->Draw();

    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXSensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    if (verboseLevel>0) { 
        G4int NbHits = trackerCollection->entries();
        G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
            << " hits in the tracker chambers: " << G4endl;
        for (G4int i=0;i<NbHits;i++) (*trackerCollection)[i]->Print();
    } 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

