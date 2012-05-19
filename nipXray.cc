//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "ExN02DetectorConstruction.hh"
#include "ExN02PhysicsList.hh"
#include "ExN02PrimaryGeneratorAction.hh"
#include "ExN02RunAction.hh"
#include "ExN02EventAction.hh"
#include "ExN02SteppingAction.hh"
#include "ExN02SteppingVerbose.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
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
    G4UserRunAction* run_action = new ExN02RunAction;
    runManager->SetUserAction(run_action);
    //
    G4UserEventAction* event_action = new ExN02EventAction;
    runManager->SetUserAction(event_action);
    //
    G4UserSteppingAction* stepping_action = new ExN02SteppingAction;
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
        UI->ApplyCommand("/control/execute vis.mac");     
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

    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

