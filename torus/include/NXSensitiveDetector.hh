#ifndef NXSensitiveDetector_h
#define NXSensitiveDetector_h 1

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class NXSensitiveDetector : public G4VSensitiveDetector
{
    public:
        NXSensitiveDetector(G4String);
        ~NXSensitiveDetector();

        void Initialize(G4HCofThisEvent*);
        G4bool ProcessHits(G4Step*, G4TouchableHistory*);
        void EndOfEvent(G4HCofThisEvent*);

};
#endif

