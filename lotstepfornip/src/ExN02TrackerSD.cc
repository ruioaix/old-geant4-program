#include "ExN02TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
extern G4int largede[100][2000];
extern G4int jiaodu[4][12][2000];
extern G4int efu[2000];
extern G4int ezh[2000];

ExN02TrackerSD::ExN02TrackerSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="trackerCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02TrackerSD::~ExN02TrackerSD(){ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02TrackerSD::Initialize(G4HCofThisEvent* HCE)
{
  trackerCollection = new ExN02TrackerHitsCollection
                          (SensitiveDetectorName,collectionName[0]); 
  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection( HCID, trackerCollection ); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool ExN02TrackerSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  //z从的能量沉积
  //G4double edep = aStep->GetTotalEnergyDeposit();
  //if(edep==0.) return false;

  //step开始和结束的点的三维坐标。
	G4ThreeVector pos = aStep->GetPreStepPoint()->GetPosition();	
	G4ThreeVector pospos = aStep->GetPostStepPoint()->GetPosition();	
  //开始和结束点的动量方向。
	G4ThreeVector dirt = aStep->GetPreStepPoint()->GetMomentumDirection();
	G4ThreeVector posdirt = aStep->GetPostStepPoint()->GetMomentumDirection();
	//得到粒子类型粒子名字
	G4ParticleDefinition* particleType = aStep->GetTrack()->GetDefinition();
	G4String particlenamee = particleType->GetParticleName();
  //粒子能量
  G4double Kenergy = aStep->GetTrack()->GetKineticEnergy();
  //trackid
  //G4double id_tracker = aStep->GetTrack()->GetTrackID();

  //粒子发生作用区域属于那个探测器实体
	G4String volumename = aStep->GetTrack()->GetVolume()->GetName();
  //得到chamber的no，用来区分不同的chamber。
	G4int copyNo = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

  G4int signx=0,signy=0;
  G4int z=(pos.z()/cm);
  G4double x=pos.x(),y=pos.y();
  G4double longofxy = sqrt(x*x+y*y);
  //G4double z=pos.z();
	if(volumename == "Chamber") {				
    if(copyNo == 0) {
      if ( z == 19) {   //这里比较如果直接使用G4double类型pos.z()==19*cm，结果是不对的，这可能是精度方面的问题。
        if (particlenamee == "gamma") {
          //G4cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"<<particlenamee<<"\n"<<pos.z()/cm<<"\t"<<G4endl;
          //计算在哪一个圆环上。
          for(G4int i=0;i<100;i++) {
            if(longofxy<=(i+1)*2*cm && longofxy>=i*2*cm) {
              signx=i;
              break;
            }
          }
          //计算在那个角度中。分成12个30度角，依次是 (012)(543)(678)(11109)
          G4int forsigny=0;
          if(y==0 && x>0) {
            signy=0;}
          else if(x==0 && y>0) {
            signy=5;}
          else if(y==0 && x<0) {
            signy=6;}
          else if(x==0 && y<0) {
            signy=11;}
          else {
            if(x>0 && y>0) 
              forsigny=1;
            if(x<0 && y>0)
              forsigny=2;
            if(x<0 && y<0)
              forsigny=3;
            if(x>0 && y<0)
              forsigny=4;
            G4bool abca =fabs(y/x)<(1/sqrt(3)); 
            G4bool abcb =fabs(y/x)<sqrt(3) && fabs(y/x)>=(1/sqrt(3)); 
            G4bool abcc =fabs(y/x)>=sqrt(3); 
            if( abca ) {
              signy=(forsigny-1)*3;
              }
            if( abcb ) {
              signy=(forsigny-1)*3+1;
              }
            if( abcc ) {
              signy=(forsigny-1)*3+2;
              }
          }
          //上面获得了signx和signy。
          //下面获得能谱。
          //这里的jiaodu获取0到3这4个圆环的角度数据。
          //largede是100个圆环的数据，两者都是能普数据。
          for(G4int i=0;i<2000;i++) 
            if(Kenergy<=((i+1)*0.01*MeV) && Kenergy >(i*0.01*MeV)) {
              if(signx<4 && signx>=0)
                jiaodu[signx][signy][i]++;
              largede[signx][i]++;
              break;
            }
        } else if (particlenamee == "e-") {
          for(G4int i=0;i<2000;i++) 
            if(Kenergy<=((i+1)*0.01*MeV) && Kenergy >(i*0.01*MeV)) {
              efu[i]++;
              break;
            }
        } else if (particlenamee == "e+") {
          for(G4int i=0;i<2000;i++) 
            if(Kenergy<=((i+1)*0.01*MeV) && Kenergy >(i*0.01*MeV)) {
              ezh[i]++;
              break;
            }
        } else {
          ExN02TrackerHit* newHit = new ExN02TrackerHit();
          //newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
          //newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
          //newHit->SetEdep     (edep);
          //newHit->SetPos      (aStep->GetPostStepPoint()->GetPosition());
          newHit->SetPname (particlenamee);
          trackerCollection->insert( newHit );
          newHit->Print();
          //newHit->Draw();
        }
      }
    }
  }
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02TrackerSD::EndOfEvent(G4HCofThisEvent*)
{
  /*
  if (verboseLevel>0) { 
     G4int NbHits = trackerCollection->entries();
     G4cout << "\n-------->Hits Collection: in this event they are " << NbHits 
            << " hits in the tracker chambers: " << G4endl;
     for (G4int i=0;i<NbHits;i++) (*trackerCollection)[i]->Print();
    } 
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

