#include "TargetChamberParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
	//Vacuum
class G4LogicalVolume;

TargetChamberParameterisation::TargetChamberParameterisation(  G4int    NoChambers, G4double startZ)
{
   fNoChambers =  NoChambers; 
   fStartZ     =  startZ; 
   //这个要说下，我开始的时候将这两个作为局部变量放在了最下的函数（也就是使用这个fe和w的函数）里面，然后return fe。
   //导致的结果就是编译通过，但是运行的时候出现段错误，原因就是返回了一个局部指针变量。
  //Fe
  Fe = new G4Material( "Fe", 26., 55.847*g/mole, 7.87* g/cm3 );

  //W
  W = new G4Material( "W",74.,183.84*g/mole,19.3* g/cm3 );

  //pmmanist
  PMMANist=G4NistManager::Instance()->FindOrBuildMaterial("G4_PLEXIGLASS",false);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TargetChamberParameterisation::~TargetChamberParameterisation()
{
  delete Fe;
  delete W;
  delete PMMANist;  
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TargetChamberParameterisation::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
 //记住这里的位置想相对与母体target的，不是world，不注意就会放错地方。 
  	G4double      Zposition= fStartZ;
	if(copyNo<24)
	{
		Zposition=copyNo*0.1*cm+fStartZ;
		physVol->SetTranslation(G4ThreeVector(0,0,Zposition));
		physVol->SetRotation(0);
	}
	else if(copyNo==24)
	{
		Zposition=fStartZ-100*cm;
		physVol->SetTranslation(G4ThreeVector(0,0,Zposition));
		physVol->SetRotation(0);
	}
	else if(copyNo==25)
	{
		Zposition=fStartZ+21*cm;
		physVol->SetTranslation(G4ThreeVector(0,0,Zposition));
		physVol->SetRotation(0);
	}

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TargetChamberParameterisation::ComputeDimensions
(G4Tubs& trackerChamber, const G4int copyNo, const G4VPhysicalVolume*) const
{
	if(copyNo<24)
	{
  		trackerChamber.SetZHalfLength(0.025*cm);
		trackerChamber.SetOuterRadius(1*cm);
		trackerChamber.SetInnerRadius(0);
	}
	else if(copyNo==24)
	{
		trackerChamber.SetInnerRadius(11*cm);
		trackerChamber.SetOuterRadius(15*cm);
		trackerChamber.SetZHalfLength(120*cm);
	}
	else if(copyNo==25)
	{
		trackerChamber.SetInnerRadius(0);
		trackerChamber.SetOuterRadius(120*cm);
		trackerChamber.SetZHalfLength(0.8*cm);
	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material*  TargetChamberParameterisation::ComputeMaterial
(const G4int copyNo,G4VPhysicalVolume * physVol,const G4VTouchable*)
{
	if(copyNo<24)
	{
		physVol->GetLogicalVolume()->SetMaterial(W);
		return W;
		//physVol->GetLogicalVolume()->SetMaterial(PMMANist);
		//return PMMANist;
	}
	else if(copyNo==24)
	{
		physVol->GetLogicalVolume()->SetMaterial(Fe);
		return Fe;
	}
	else if(copyNo==25)
	{
		physVol->GetLogicalVolume()->SetMaterial(PMMANist);
		return PMMANist;
	}
  return 0;
}

