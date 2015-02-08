#ifndef NXRunAction_h
#define NXRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class NXRunAction : public G4UserRunAction
{
    public:
        NXRunAction();
        ~NXRunAction();

    public:
        void BeginOfRunAction(const G4Run*);
        void EndOfRunAction(const G4Run*);
};

#endif





