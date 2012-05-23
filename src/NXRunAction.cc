//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "NXRunAction.hh"

#include "G4Run.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXRunAction::NXRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

NXRunAction::~NXRunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    for(G4int i=0;i<2000;i++) {
        CenterESofGamma[i]=0;
        CenterESofPositron[i]=0;
        CenterESofNegatron[i]=0;
    }
    NumofPrePointNotBoundary=0;
    NumofPrePointIsBoundary=0;
    OtherParticle=0;
    EnergyofGammaContrb=0;
    EnergyofNegatronContrb=0;
    EnergyofPositronContrb=0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void NXRunAction::EndOfRunAction(const G4Run*)
{ 
    G4int AllNumofGamma=0;
    G4int AllNumofPositron=0;
    G4int AllNumofNegatron=0;
    for(G4int i=0;i<2000;i++) {
        AllNumofGamma+=CenterESofGamma[i];
        AllNumofPositron+=CenterESofPositron[i];
        AllNumofNegatron+=CenterESofNegatron[i];
    }

    G4double CenterESofGammaPerC[2000];
    G4double CenterESofPositronPerC[2000];
    G4double CenterESofNegatronPerC[2000];
    for (G4int i=0;i<2000;i++) {
        CenterESofGammaPerC[i]=1.0*CenterESofGamma[i]/AllNumofGamma;
        CenterESofPositronPerC[i]=1.0*CenterESofPositron[i]/AllNumofPositron;
        CenterESofNegatronPerC[i]=1.0*CenterESofNegatron[i]/AllNumofNegatron;
    }

    G4cout<<G4endl;

    G4cout<<"All Num of gamma is "<<AllNumofGamma<<G4endl;
    G4cout<<"All Num of Positron is "<<AllNumofPositron<<G4endl;
    G4cout<<"All Num of Negatron is "<<AllNumofNegatron<<G4endl;
    G4cout<<"All Num of Other particle is "<<OtherParticle<<G4endl;
    G4cout<<"the Num of particle Not bound is  "<<NumofPrePointNotBoundary<<G4endl;
    G4cout<<"the Num of particle bound is  "<<NumofPrePointIsBoundary<<G4endl;
    G4cout<<"the Contribution of Energy by Gamma is "<<EnergyofGammaContrb/MeV<<" MeV"<<G4endl;
    G4cout<<"the Contribution of Energy by Positron is "<<EnergyofPositronContrb/MeV<<" MeV"<<G4endl;
    G4cout<<"the Contribution of Energy by Negatron is "<<EnergyofNegatronContrb/MeV<<" MeV"<<G4endl;
    G4cout<<"the Contribution of Energy by Other particles is "<<EnergyofOtherParticleContrb/MeV<<" MeV"<<G4endl;
    
    G4cout<<G4endl;

    G4cout<<"Energy/MeV\t Gamma\t Positron\t Negatron"<<G4endl;
    for(G4int i=0;i<2000;i++) {
        G4double i_20MeV=(i/100.0)*MeV;
        G4cout<<i_20MeV/MeV<<"\t "<<CenterESofGammaPerC[i]
            <<"\t "<<CenterESofPositronPerC[i]
            <<"\t "<<CenterESofNegatronPerC[i]<<G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



