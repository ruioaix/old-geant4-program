//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef NXHit_h
#define NXHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class NXHit : public G4VHit
{
    public:

        NXHit();
        ~NXHit();
        NXHit(const NXHit&);
        const NXHit& operator=(const NXHit&);
        G4int operator==(const NXHit&) const;

        inline void* operator new(size_t);
        inline void  operator delete(void*);

        void Draw();
        void Print();

    public:

        void SetTrackID  (G4int track)      { trackID = track; };
        void SetChamberNb(G4int chamb)      { chamberNb = chamb; };  
        void SetEdep     (G4double de)      { edep = de; };
        void SetPos      (G4ThreeVector xyz){ pos = xyz; };

        G4int GetTrackID()    { return trackID; };
        G4int GetChamberNb()  { return chamberNb; };
        G4double GetEdep()    { return edep; };      
        G4ThreeVector GetPos(){ return pos; };

    private:

        G4int         trackID;
        G4int         chamberNb;
        G4double      edep;
        G4ThreeVector pos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<NXHit> NXHitsCollection;

extern G4Allocator<NXHit> NXHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* NXHit::operator new(size_t)
{
    void *aHit;
    aHit = (void *) NXHitAllocator.MallocSingle();
    return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void NXHit::operator delete(void *aHit)
{
    NXHitAllocator.FreeSingle((NXHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
