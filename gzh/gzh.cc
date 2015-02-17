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
#include "G4Timer.hh"
#include "time.h"
#include "stdio.h"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif


int main(int argc,char** argv)
{
	G4Timer myTimer;
	myTimer.Start(); 	//和后面的end（）结合，输出程序运行时间。
	time_t lt;
	lt = time(NULL);
	printf("开始时间：");
	printf(ctime(&lt));	//输出程序开始的本地时间。

	G4VSteppingVerbose* verbosity = new ExN02SteppingVerbose;
	G4VSteppingVerbose::SetInstance(verbosity);
  	
	G4RunManager * runManager = new G4RunManager;

	#ifdef G4VIS_USE
      	G4VisManager* visManager = new G4VisExecutive;
      	visManager->Initialize();
	#endif
 
  	ExN02DetectorConstruction* detector = new ExN02DetectorConstruction;
  	runManager->SetUserInitialization(detector);
  
	G4VUserPhysicsList* physics = new ExN02PhysicsList;
  	runManager->SetUserInitialization(physics);
   
  	ExN02PrimaryGeneratorAction* gen_action = new ExN02PrimaryGeneratorAction(detector);
  	runManager->SetUserAction(gen_action);
  
	G4UserRunAction* run_action = new ExN02RunAction;
  	runManager->SetUserAction(run_action);
  	
	G4UserEventAction* event_action = new ExN02EventAction;
  	runManager->SetUserAction(event_action);
  	
	G4UserSteppingAction* stepping_action = new ExN02SteppingAction;
  	runManager->SetUserAction(stepping_action);

  	runManager->Initialize();
      
  	G4UImanager * UI = G4UImanager::GetUIpointer();  

  	if (argc!=1)     
    	{
     		G4String command = "/control/execute ";
     		G4String fileName = argv[1];
     		UI->ApplyCommand(command+fileName);
	
    	}  
  	else          
    	{ 
      		G4UIsession * session = 0;
		#ifdef G4UI_USE_TCSH
      			session = new G4UIterminal(new G4UItcsh);      
		#else
      		session = new G4UIterminal();
		#endif
      		
		session->SessionStart();
      		delete session;
   	}  
	
	#ifdef G4VIS_USE
      	delete visManager;
	#endif     


  	delete runManager;
  	delete verbosity;

	printf("结束时间：");
	lt = time(NULL);
	printf(ctime(&lt));
	myTimer.Stop();
	G4cout<<"总耗时:"<<myTimer<<G4endl;
  	return 0;
}

