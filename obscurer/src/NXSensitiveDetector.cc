#include "NXSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4RunManager.hh"
#define ELOW 0.1
#define EHIGH 10
//#include "NXRunAction.hh"

NXSensitiveDetector::NXSensitiveDetector(G4String name) :
    G4VSensitiveDetector(name)
{
}

void NXSensitiveDetector::writeCounters(){
	for(int i = 0; i < NTHETA; i++) {
		std::ofstream f;
		std::ostringstream filename;
		filename << "detect_" << (i+1) << ".txt";
		G4cout << "writing" << filename.str() << G4endl;
		f.open(filename.str().c_str());
		for(int j = 0; j < NENERGY; j++) {
			f << ELOW + j * (EHIGH - ELOW) * 1. / NENERGY << "\t" << counters[i][j] << "\n";
		}
		f.close();
	}
}
NXSensitiveDetector::~NXSensitiveDetector(){
	writeCounters();
}

void NXSensitiveDetector::Initialize(G4HCofThisEvent* HCE)
{
}

G4bool NXSensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
	G4StepPoint* pointPre=aStep->GetPreStepPoint();
	G4StepPoint* pointPost=aStep->GetPostStepPoint(); 
	G4TouchableHandle touchCur=pointPre->GetTouchableHandle();
	G4Track* trackCur=aStep->GetTrack();
	G4VPhysicalVolume* volumeCur=touchCur->GetVolume();
	G4String volumeCurName=volumeCur->GetName();
	G4int copyNumofChamber=touchCur->GetCopyNumber();
	G4ParticleDefinition* particleCur = trackCur->GetDefinition();
	G4String particleCurName = particleCur->GetParticleName();
	G4double kineticEnergyCur = trackCur->GetKineticEnergy();
	//G4RunManager* runManager= G4RunManager::GetRunManager();
	//NXRunAction* runActionCur=(NXRunAction *)runManager->GetUserRunAction();*/
	
	/*
	G4cerr << "Detector hit! " << pointPre->GetPosition() << " --> " << pointPost->GetPosition() << 
		" at theta angle " << pointPre->GetPosition().theta() * 180 / pi << "deg" <<
		" at phi angle " << pointPre->GetPosition().phi() * 180 / pi << "deg" <<
		" by " << particleCurName << 
		" with E=" << (kineticEnergyCur / keV) << "keV inside " << volumeCurName << G4endl;
	*/
	
	if (kineticEnergyCur / keV < ELOW) {
		return true;
	}
	double e = (kineticEnergyCur / keV - ELOW) / (EHIGH - ELOW) * NENERGY;
	int ebin = (int) e;
	double theta = pointPre->GetPosition().theta() - pi / 2;
	if (theta > pi / 2)
		theta -= pi / 2;
	if (theta < 0)
		theta += pi / 2;
	
	int thetabin = (int)(theta / (pi / 2) * NTHETA);
	//G4cout << "   storing in " << ebin << " | " << 
	//	pointPre->GetPosition().theta() << " -> " << thetabin <<
	//	G4endl;
	if (thetabin < NTHETA && thetabin >= 0 && ebin < NENERGY && ebin >= 0) {
		counters[thetabin][ebin] += 1;
	} else {
		G4cout << "   WARNING: stored at strange index " << kineticEnergyCur / keV << "keV | theta=" << thetabin << G4endl;
	}
	
	return true;
}

void NXSensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
    writeCounters();
    G4cout << "Event end!" << G4endl;
}
