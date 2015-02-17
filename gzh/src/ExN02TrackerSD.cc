#include "ExN02TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"


extern G4double core_s[12];
extern G4int origin[2000];
extern G4int core[12][2000];

ExN02TrackerSD::ExN02TrackerSD(G4String name)
:G4VSensitiveDetector(name)
{
	G4String HCname;
  	collectionName.insert(HCname="trackerCollection");
}

ExN02TrackerSD::~ExN02TrackerSD(){ }

void ExN02TrackerSD::Initialize(G4HCofThisEvent* HCE)
{
  	trackerCollection = new ExN02TrackerHitsCollection(SensitiveDetectorName,collectionName[0]); 
  	static G4int HCID = -1;
  	if(HCID<0)
  	{
 		HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 
	}
  	HCE->AddHitsCollection( HCID, trackerCollection ); 
}

G4bool ExN02TrackerSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
/*
   	G4double edep = aStep->GetTotalEnergyDeposit();
   	G4double id_parent = aStep->GetTrack()->GetParentID();
	ExN02TrackerHit* newHit = new ExN02TrackerHit();
  	newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
  	newHit->SetEdep     (edep);
  	newHit->SetPos      (aStep->GetPostStepPoint()->GetPosition());
  	trackerCollection->insert( newHit );
*/
	G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();	
	G4ThreeVector pospos = aStep->GetPostStepPoint()->GetPosition();	
	G4ThreeVector dirt = aStep->GetPreStepPoint()->GetMomentumDirection();
	G4ThreeVector posdirt = aStep->GetPostStepPoint()->GetMomentumDirection();
	
	G4ParticleDefinition* particleType = aStep->GetTrack()->GetDefinition();
   	G4double Kenergy = aStep->GetTrack()->GetKineticEnergy();
   	G4double id_tracker = aStep->GetTrack()->GetTrackID();
	G4String particlenamee = particleType->GetParticleName();
	G4String volumename = aStep->GetTrack()->GetVolume()->GetName();

	G4int copyNo = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();


	//G4cout<<copyNo<<"---------------------------------"<<G4endl;
	if(particlenamee =="gamma") 
	{	
		if(volumename == "origin")
		{
			for(G4int i=0;i<2000;i++)
			{
				if(Kenergy<=((i+1)*0.01*MeV) && Kenergy >(i*0.01*MeV))
					origin[i]++;
			}
		}
		else if(volumename == "Chamber")
		{				
			if(copyNo>23)
			{
				G4int s=copyNo-24;
				for(G4int i=0;i<2000;i++)
				{
					if(Kenergy<=((i+1)*0.01*MeV) && Kenergy >(i*0.01*MeV))
						core[s][i]++;
				}
			}
			else if(copyNo>11)
			{
				G4int s=copyNo-12;
				core_s[s]+=Kenergy;
			}
		}
	}		

  	return true;
}

void ExN02TrackerSD::EndOfEvent(G4HCofThisEvent*)
{
}

