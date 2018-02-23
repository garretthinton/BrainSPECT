//
//  BSTrackingAction.hh
//  BrainSPECT
//
//  Created by Matthew Kupinski on 8/28/17.
//  Copyright © 2017 BRP Partnership. All rights reserved.
//

#ifndef BSTrackingAction_h
#define BSTrackingAction_h

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"

class BSTrackingAction : public G4UserTrackingAction
{
public:
  BSTrackingAction();
  virtual ~BSTrackingAction();
  
  
 // virtual void SetTrackingManagerPointer(G4TrackingManager* pValue);
  virtual void PreUserTrackingAction(const G4Track*);
  virtual void PostUserTrackingAction(const G4Track*);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif /* BSTrackingAction_h */
