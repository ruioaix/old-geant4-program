#ifndef ExN02TrackerHit_h
#define ExN02TrackerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ExN02TrackerHit : public G4VHit
{
  public:

      ExN02TrackerHit();
     ~ExN02TrackerHit();
      ExN02TrackerHit(const ExN02TrackerHit&);
      const ExN02TrackerHit& operator=(const ExN02TrackerHit&);
      G4int operator==(const ExN02TrackerHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
  
      void SetTrackID  (G4int track)      { trackID = track; };
      void SetChamberNb(G4int chamb)      { chamberNb = chamb; };  
      void SetEdep     (G4double de)      { edep = de; };
      void SetPos      (G4ThreeVector xyz){ pos = xyz; };
      void SetPname    (G4String xyz)      { particletnm = xyz;}
      
      G4int GetTrackID()    { return trackID; };
      G4int GetChamberNb()  { return chamberNb; };
      G4double GetEdep()    { return edep; };      
      G4ThreeVector GetPos(){ return pos; };
      G4String GetPname() {return particletnm;};
      
  private:
  
      G4int         trackID;
      G4int         chamberNb;
      G4double      edep;
      G4ThreeVector pos;
      G4String particletnm;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<ExN02TrackerHit> ExN02TrackerHitsCollection;

extern G4Allocator<ExN02TrackerHit> ExN02TrackerHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* ExN02TrackerHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) ExN02TrackerHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void ExN02TrackerHit::operator delete(void *aHit)
{
  ExN02TrackerHitAllocator.FreeSingle((ExN02TrackerHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
