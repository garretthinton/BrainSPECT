//
//

#include "BSActionInitialization.hh"
#include "BSRunAction.hh"
#include "BSPrimaryGeneratorAction.hh"
#include "BSStackingAction.hh"
#include "BSTrackingAction.hh"
#include "BSUserSteppingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSActionInitialization::BSActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSActionInitialization::~BSActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BSActionInitialization::BuildForMaster() const
{
  SetUserAction(new BSRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BSActionInitialization::Build() const
{
  SetUserAction(new BSRunAction);
  SetUserAction(new BSPrimaryGeneratorAction);
  SetUserAction(new BSStackingAction);
//  SetUserAction(new BSTrackingAction);
//  SetUserAction(new BSUserSteppingAction);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
