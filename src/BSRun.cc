//

#include "BSRun.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSRun::BSRun()
 : G4Run(), 
   fPrintModulo(10000)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSRun::~BSRun()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BSRun::RecordEvent(const G4Event* event)
{
  G4int evtNb = event->GetEventID();
  
  if (evtNb%fPrintModulo == 0) { 
    G4cout << G4endl << "---> end of event: " << evtNb << G4endl;
  }      
  
  G4Run::RecordEvent(event);      
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BSRun::Merge(const G4Run* aRun)
{
  G4Run::Merge(aRun); 
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
