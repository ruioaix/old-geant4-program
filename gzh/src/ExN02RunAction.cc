#include "ExN02RunAction.hh"
#include "G4Run.hh"
#include "ExN02PrimaryGeneratorAction.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"

G4int core[12][2000];
G4int origin[2000];
G4double core_s[12];

ExN02RunAction::ExN02RunAction()
{}

ExN02RunAction::~ExN02RunAction()
{}

void ExN02RunAction::BeginOfRunAction(const G4Run* aRun)
{ 
	for(G4int i=0;i<2000;i++)
		origin[i]=0;

	for(G4int i=0;i<12;i++)
		for(G4int j=0;j<2000;j++)
			core[i][j] = 0;
}

void ExN02RunAction::EndOfRunAction(const G4Run*)
{
	//origin 初始谱
	G4cout<<"初始能谱"<<G4endl;
	for(G4int j=0;j<2000;j++)
		G4cout<<(j*0.01)<<"\t--"<<((j+1)*0.01)<<"MeV\t"<<origin[j]<<G4endl;

	//12个测量点，铁片之前，测量前面的能谱。
	for(G4int i=0;i<12;i++)
	{
		for(G4int j=0;j<2000;j++)
			G4cout<<(j*0.01)<<"\t--"<<((j+1)*0.01)<<"MeV\t"<<core[i][j]<<G4endl;
		G4cout<<"-----------------------------------------------------------------\t"<<(i+1)<<G4endl;
	}

	//12个测量点，铁片之后，只测量总能量。
	for(G4int i=0;i<12;i++)
		G4cout<<"第"<<(i+1)<<"个铁片后的总能量:\t"<<core_s[i]/MeV<<"MeV"<<G4endl;
}



