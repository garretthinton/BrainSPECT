//
//  BSPhantom.hpp
//  BrainSPECT
//
//  Created by Matthew Kupinski on 8/8/17.
//  Copyright © 2017 BRP Partnership. All rights reserved.
//

#ifndef BSPhantomMessenger_h
#define BSPhantomMessenger_h 1

#include <stdio.h>
#include "G4Types.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "BSDetectorConstruction.hh"
#include "BSPhantom.hh"


class BSPhantom;

class BSPhantomMessenger : public G4UImessenger
{
public:
  BSPhantomMessenger(BSPhantom* ph);
  ~BSPhantomMessenger();
public:
  void SetNewValue(G4UIcommand * command,G4String newValues);
  G4String GetCurrentValue(G4UIcommand * command);
private:
  G4UIdirectory* phantomDirectory;
  G4UIcmdWith3Vector* nVoxCmd;
  G4UIcmdWith3VectorAndUnit* patientSizeCmd;
  G4UIcmdWithAString* materialCmd;
  G4UIcmdWithAString* materialPhantomCmd;
  
  BSPhantom* phantom;
  
};

#endif 
