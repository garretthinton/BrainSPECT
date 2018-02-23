//
//  BSSensitiveDetector.hpp
//  BrainSPECT
//
//  Created by Matthew Kupinski on 8/1/17.
//  Copyright © 2017 BRP Partnership. All rights reserved.
//

#ifndef BSSensitiveDetector_hpp
#define BSSensitiveDetector_hpp

#include "G4VSensitiveDetector.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"


class BSSensitiveDetector : public G4VSensitiveDetector
{
public:
  BSSensitiveDetector(G4String str);
  BSSensitiveDetector(G4String str,G4ThreeVector pos);
protected: // with description
  G4ThreeVector origin;
  virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
};





#endif /* BSSensitiveDetector_hpp */
