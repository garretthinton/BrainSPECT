
#include "BSStackingAction.hh"

#include "G4Track.hh"
#include "G4NeutrinoE.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSStackingAction::BSStackingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSStackingAction::~BSStackingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
BSStackingAction::ClassifyNewTrack(const G4Track* track)
{
  //keep primary particle
  //G4cout << "MAK: " << track->GetParticleDefinition()->GetParticleName() << " " << track->GetKineticEnergy()/keV << G4endl;
  if (track->GetParentID() == 0) return fUrgent;
  
  //kill secondary electrons
  if (track->GetDefinition() == G4Electron::Electron()) return fKill;
  else {
    G4cout << "MAK:  Something other than an electron generated as secondary." << G4endl;
    G4cout << "MAK: " << track->GetDefinition()->GetParticleName() << " " << track->GetKineticEnergy()/keV << G4endl;
  }
  
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
