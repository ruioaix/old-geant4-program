#ifndef ExN02RunAction_h
#define ExN02RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

class ExN02RunAction : public G4UserRunAction
{
  public:
    ExN02RunAction();
   ~ExN02RunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif





