//
//  BSUserSteppingAction.cpp
//  BrainSPECT
//
//  Created by Matthew Kupinski on 8/28/17.
//  Copyright © 2017 BRP Partnership. All rights reserved.
//

#include "BSUserSteppingAction.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

BSUserSteppingAction::BSUserSteppingAction()
{
}


BSUserSteppingAction::~BSUserSteppingAction()
{
  
}


void BSUserSteppingAction::UserSteppingAction(const G4Step* step)
{
    //G4cout << "MAK Step: " << step->GetTrack()->GetKineticEnergy()/keV << " " << step->GetTrack()->GetParticleDefinition()->GetParticleName() <<  G4endl;

}


