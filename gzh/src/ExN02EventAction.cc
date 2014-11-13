#include "ExN02EventAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "time.h"
#include "stdio.h"

G4int numofevent =0;

ExN02EventAction::ExN02EventAction()
{}

ExN02EventAction::~ExN02EventAction()
{}

void ExN02EventAction::BeginOfEventAction(const G4Event*)
{
	numofevent++;
	if(numofevent%5000000==0)
	{
		time_t lt;
		lt = time(NULL);
		printf("在time：");
		printf(ctime(&lt));
		G4cout<<"模拟完成了："<<(numofevent/5000000)<<"%"<<G4endl;
		G4cout<<" "<<G4endl;
	}
}

void ExN02EventAction::EndOfEventAction(const G4Event*)
{}

