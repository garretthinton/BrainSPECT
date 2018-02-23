//
//  BSSensitiveDetector.cpp
//  BrainSPECT
//
//  Created by Matthew Kupinski on 8/1/17.
//  Copyright © 2017 BRP Partnership. All rights reserved.
//

#include "BSSensitiveDetector.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4RootAnalysisManager.hh"
#include "G4ThreeVector.hh"


BSSensitiveDetector::BSSensitiveDetector(G4String str)
: G4VSensitiveDetector(str)
{
}


BSSensitiveDetector::BSSensitiveDetector(G4String str,G4ThreeVector pos)
  : G4VSensitiveDetector(str),
  origin(pos)
{
}

G4bool BSSensitiveDetector::ProcessHits(G4Step* aStep,G4TouchableHistory* )
{
  // The sensitive detector is the sphere.  Whenever a photon hits
  // the sphere, we record its information and kill the photon.
  G4Track *aTrack = aStep->GetTrack();
  G4double kineticEnergy = aTrack->GetKineticEnergy();
  G4ThreeVector pos = aTrack->GetPosition();
  G4ThreeVector dir = aTrack->GetMomentumDirection();

  // Make sure photon is exiting sphere.  If entering
  // sphere, just leave it alone.
  if ((pos-origin).dot(dir) >=0.0) {
    
    // Exiting sphere so stop and kill track.
    aTrack->SetTrackStatus(fStopAndKill);

    // Add information to Root manager for output later.
    auto analysisManager = G4RootAnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, kineticEnergy/keV);
    analysisManager->FillNtupleDColumn(1,pos.x());
    analysisManager->FillNtupleDColumn(2,pos.y());
    analysisManager->FillNtupleDColumn(3,pos.z());
    analysisManager->FillNtupleDColumn(4,dir.x());
    analysisManager->FillNtupleDColumn(5,dir.y());
    analysisManager->FillNtupleDColumn(6,dir.z());
    analysisManager->AddNtupleRow();
  }
  return true;
}
