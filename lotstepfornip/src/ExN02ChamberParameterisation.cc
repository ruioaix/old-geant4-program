#include "ExN02ChamberParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
//这个tubs的头文件好像是加上的,否则41行的trackerchamber识别不了。
//在第一行的头文件中，没有包含这个文件，使用的是class 进行声明，这里其实也可以的，不测试了。
#include "G4Tubs.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//因为我使用不到那么多的参数，所以，我就将用不到的参数删除了。
//其实现在这两个也不一定非要使用的，可以写成魔数。
ExN02ChamberParameterisation::ExN02ChamberParameterisation(G4int nbofc,G4double startZ)
{
   Nbofchamber =  nbofc;
   fStartZ     =  startZ; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02ChamberParameterisation::~ExN02ChamberParameterisation()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//这个函数是用来设定位置的，这个位置是相对与母体的，在这个程序里面，母体就是tracker。
//子体和母体，以及母体和母体的母体之间都是中心点。
void ExN02ChamberParameterisation::ComputeTransformation
(const G4int /*copyNo*/, G4VPhysicalVolume* physVol) const
{
  G4double      Zposition= fStartZ;
  physVol->SetTranslation(G4ThreeVector(0,0,Zposition));
  physVol->SetRotation(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//用来设置形状的。
void ExN02ChamberParameterisation::ComputeDimensions
(G4Tubs& trackerChamber, const G4int /*copyNo*/, const G4VPhysicalVolume*) const
{
		trackerChamber.SetZHalfLength(1*cm);
		trackerChamber.SetInnerRadius(0);
		trackerChamber.SetOuterRadius(200*cm);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
