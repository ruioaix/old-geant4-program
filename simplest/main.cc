#include "NXUserDetectorConstruction.hh"
#include "NXPhysicsList.hh"
#include "NXPrimaryGeneratorAction.hh"
#include "NXRunAction.hh"
//#include "NXEventAction.hh"
//#include "NXSteppingAction.hh"
//#include "NXSteppingVerbose.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "G4Timer.hh"
#include "ctime"
#include "cstdio"

int main(int argc,char** argv)
{
	G4Timer myTimer;
	myTimer.Start(); 	
	time_t lt = time(NULL);
	G4cout<<"main: beginning time is"<<ctime(&lt)<<G4endl;

	// User Verbose output class
	//
	//G4VSteppingVerbose* verbosity = new NXSteppingVerbose;
	//G4VSteppingVerbose::SetInstance(verbosity);

	// Run manager
	//
	G4cout<<"main: init G4RunManager"<<G4endl;
	G4RunManager * runManager = new G4RunManager;

	// User Initialization classes (mandatory)
	//
	G4cout<<"main: detector init "<<G4endl;
	NXUserDetectorConstruction* detector = new NXUserDetectorConstruction;
	G4cout<<"main: detector user init"<<G4endl;
	runManager->SetUserInitialization(detector);
	//
	G4cout<<"main: physics loading"<<G4endl;
	G4VUserPhysicsList* physics = new NXPhysicsList;
	G4cout<<"main: physics user init"<<G4endl;
	runManager->SetUserInitialization(physics);

	// User Action classes
	//
	G4cout<<"main: generator init "<<G4endl;
	G4VUserPrimaryGeneratorAction* gen_action = new NXPrimaryGeneratorAction(detector);
	G4cout<<"main: generator set action "<<G4endl;
	runManager->SetUserAction(gen_action);
	//
	G4cout<<"main: run action init"<<G4endl;
	G4UserRunAction* run_action = new NXRunAction;
	G4cout<<"main: run action user init"<<G4endl;
	runManager->SetUserAction(run_action);
	//
	//G4UserEventAction* event_action = new NXEventAction;
	//runManager->SetUserAction(event_action);
	//
	//G4UserSteppingAction* stepping_action = new NXSteppingAction;
	//runManager->SetUserAction(stepping_action);

	// Initialize G4 kernel
	//
	G4cout<<G4endl;
	G4cout<<"main: runManager init"<<G4endl;
	runManager->Initialize();

	// Get the pointer to the User Interface manager
	//
	G4UImanager * UI = G4UImanager::GetUIpointer();  
	UI->ApplyCommand("/run/beamOn");
	
	/*if (argc!=1) {
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		G4cout<<G4endl;
		G4cout<<"main: executing ..."<<G4endl;
		UI->ApplyCommand(command+fileName);
		G4cout<<"main: executing done"<<G4endl;
	} else {
		G4UIsession * session = 0;
		session = new G4UIterminal();
		session->SessionStart();
		delete session;
	}*/
	
	delete runManager;
	//delete verbosity;

	lt = time(NULL);
	printf( "the end time is %s", ctime(&lt));
	myTimer.Stop();
	G4cout<<"Spend time:"<<myTimer<<G4endl;

	return 0;
}

