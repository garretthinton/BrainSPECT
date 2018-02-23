//
//  BSUserSteppingAction.hh
//  BrainSPECT
//
//  Created by Matthew Kupinski on 8/28/17.
//  Copyright © 2017 BRP Partnership. All rights reserved.
//

#ifndef BSUserSteppingAction_h
#define BSUserSteppingAction_h

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

class BSUserSteppingAction : public G4UserSteppingAction
{
public:
  BSUserSteppingAction();
  ~BSUserSteppingAction();
  
  virtual void UserSteppingAction(const G4Step*);

};


#endif /* BSUserSteppingAction_h */
