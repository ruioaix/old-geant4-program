#include "ExN02RunAction.hh"

#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4int largede[100][2000];
G4int jiaodu[4][12][2000];
G4int efu[2000];
G4int ezh[2000];

ExN02RunAction::ExN02RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02RunAction::~ExN02RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  for(G4int i=0;i<2000;i++) 
    efu[i]=ezh[i]=0;
    

	for(G4int i=0;i<4;i++)
    for(G4int j=0;j<12;j++)
      for(G4int k=0;k<2000;k++)
			  jiaodu[i][j][k] = 0;

	for(G4int i=0;i<100;i++)
      for(G4int k=0;k<2000;k++)
			  largede[i][k] = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02RunAction::EndOfRunAction(const G4Run*)
{ 
  for(G4int i=0;i<2000;i++){
    G4cout<<(i+1)<<" ";
    for(G4int j=0;j<100;j++) {
      G4cout<<largede[j][i]<<" ";
    }
    G4cout<<G4endl;
  }
  /*
	for(G4int i=0;i<100;i++)
		for(G4int j=0;j<12;j++)
      for(G4int k=0;k<2000;k++)
			  G4cout<<largede[i][j][k]<<"\t";
  G4cout<<G4endl;
  */
  for(G4int k=0;k<4;k++) {
    G4cout<<"the "<<k<<" cycle:"<<G4endl;
    for(G4int i=0;i<2000;i++) {
      G4cout<<(i+1)<<" ";
      for(G4int j=0;j<12;j++) {
        G4cout<<largede[j][i]<<" ";
      }
      G4cout<<G4endl;
    }
    G4cout<<"====================================================="<<G4endl;
  }

  G4cout<<"======================efu(xia)==============================="<<G4endl;
  for(G4int i=0;i<2000;i++) {
    G4cout<<(i+1)<<"\t"<<efu[i]<<G4endl;
  }
  G4cout<<"=======================ezh(xia)=============================="<<G4endl;
  for(G4int i=0;i<2000;i++) {
    G4cout<<(i+1)<<"\t"<<ezh[i]<<G4endl;
  }
    

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



