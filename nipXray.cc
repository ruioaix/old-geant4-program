//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02DetectorConstruction.hh"
#include "ExN02PhysicsList.hh"
#include "ExN02PrimaryGeneratorAction.hh"
#include "NXRunAction.hh"
#include "NXEventAction.hh"
#include "NXSteppingAction.hh"
#include "ExN02SteppingVerbose.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "G4Timer.hh"
#include "ctime"
#include "cstdio"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
	G4Timer myTimer;
	myTimer.Start(); 	
	time_t lt = time(NULL);
	printf("the beginning time is %s", ctime(&lt));
    
    // User Verbose output class
    //
    G4VSteppingVerbose* verbosity = new ExN02SteppingVerbose;
    G4VSteppingVerbose::SetInstance(verbosity);

    // Run manager
    //
    G4RunManager * runManager = new G4RunManager;

    // User Initialization classes (mandatory)
    //
    ExN02DetectorConstruction* detector = new ExN02DetectorConstruction;
    runManager->SetUserInitialization(detector);
    //
    G4VUserPhysicsList* physics = new ExN02PhysicsList;
    runManager->SetUserInitialization(physics);

    // User Action classes
    //
    G4VUserPrimaryGeneratorAction* gen_action = new ExN02PrimaryGeneratorAction(detector);
    runManager->SetUserAction(gen_action);
    //
    G4UserRunAction* run_action = new NXRunAction;
    runManager->SetUserAction(run_action);
    //
    G4UserEventAction* event_action = new NXEventAction;
    runManager->SetUserAction(event_action);
    //
    G4UserSteppingAction* stepping_action = new NXSteppingAction;
    runManager->SetUserAction(stepping_action);

    // Initialize G4 kernel
    //
    runManager->Initialize();

    // Get the pointer to the User Interface manager
    //
    G4UImanager * UI = G4UImanager::GetUIpointer();  

#ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
#endif    

    if (argc!=1)   // batch mode  
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UI->ApplyCommand(command+fileName);
    }
    else           // interactive mode : define visualization and UI terminal
    { 
        G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
        session = new G4UIterminal(new G4UItcsh);      
#else
        session = new G4UIterminal();
#endif
#ifdef G4VIS_USE
        UI->ApplyCommand("/control/execute macs/vis.mac");     
#endif
        session->SessionStart();
        delete session;
    }

    // Free the store: user actions, physics_list and detector_description are
    //                 owned and deleted by the run manager, so they should not
    //                 be deleted in the main() program !

#ifdef G4VIS_USE
    delete visManager;
#endif     

    delete runManager;
    delete verbosity;

	lt = time(NULL);
	printf( "the end time is %s", ctime(&lt));
	myTimer.Stop();
	G4cout<<"Spend time:"<<myTimer<<G4endl;

    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

