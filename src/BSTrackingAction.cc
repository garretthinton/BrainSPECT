//
//  BSTrackingAction.cpp
//  BrainSPECT
//
//  Created by Matthew Kupinski on 8/28/17.
//  Copyright © 2017 BRP Partnership. All rights reserved.
//

#include "BSTrackingAction.hh"
#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "G4NeutrinoE.hh"
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"



BSTrackingAction::BSTrackingAction()
{
  
}

BSTrackingAction::~BSTrackingAction()
{

}


void BSTrackingAction::PreUserTrackingAction(const G4Track* track)
{
  //G4cout << "MAK Pre: " << track->GetParticleDefinition()->GetParticleName() << " " << track->GetKineticEnergy()/keV << G4endl;

}

void BSTrackingAction::PostUserTrackingAction(const G4Track* track)
{
  //G4cout << "MAK Post: " << track->GetParticleDefinition()->GetParticleName() << " " << track->GetKineticEnergy()/keV << G4endl;

}
