//
//  BSPhantom.cpp
//  BrainSPECT
//
//  Created by Matthew Kupinski on 8/8/17.
//  Copyright © 2017 BRP Partnership. All rights reserved.
//

#include "BSPhantomMessenger.hh"
#include "BSPhantom.hh"
#include "G4UImanager.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4RunManager.hh"


BSPhantomMessenger::BSPhantomMessenger(BSPhantom* ph)
: phantom(ph)
{
  
  phantomDirectory = new G4UIdirectory("/phantom/");
  phantomDirectory->SetGuidance("Phantom definition commands.");
  
  nVoxCmd = new G4UIcmdWith3Vector("/phantom/numVoxels",this);
  nVoxCmd->SetGuidance("Number of x, y, and z voxels.");
  nVoxCmd->SetGuidance("Must be integers.");
  nVoxCmd->SetParameterName("nX","nY","nZ",false, false);
  nVoxCmd->SetRange("nX > 0 && nY > 0 && nZ > 0");
  
  patientSizeCmd = new G4UIcmdWith3VectorAndUnit("/phantom/size",this);
  patientSizeCmd->SetGuidance("Set phantom size.");
  patientSizeCmd->SetParameterName("X","Y","Z",true,true);
  patientSizeCmd->SetDefaultUnit("cm");
  patientSizeCmd->SetUnitCandidates("micron mm cm m km");
  patientSizeCmd->SetRange("X > 0.0 && X <= 50.0 && Y > 0.0 && Y <= 50.0 && Z > 0 && Z <= 180.0");
  
  materialCmd = new G4UIcmdWithAString("/phantom/materials",this);
  materialCmd->SetGuidance("Text file containing the materials");
  
  materialPhantomCmd = new G4UIcmdWithAString("/phantom/materialPhantom",this);
  materialPhantomCmd->SetGuidance("Binary file of size_t's containing the phantom material indices.  This is the absorption phantom.");

}

void BSPhantomMessenger::SetNewValue(G4UIcommand* command,G4String newValues)
{
  if( command==nVoxCmd )
  {
    G4ThreeVector vec = nVoxCmd->GetNew3VectorValue(newValues);
    phantom->SetPhantomVoxels(G4int(vec.getX()),
                                           G4int(vec.getY()),
                                           G4int(vec.getZ()));
  } else if (command == patientSizeCmd)
  {
    G4ThreeVector vec = patientSizeCmd->GetNew3VectorValue(newValues);
    phantom->SetPhantomSize(vec);
  } else if (command == materialCmd)
  {
    phantom->LoadMaterials(newValues);
  } else if (command == materialPhantomCmd)
  {
    phantom->LoadPhantomData(newValues);
  }
}

G4String BSPhantomMessenger::GetCurrentValue(G4UIcommand* command)
{
  G4String cv;
  if( command==nVoxCmd )
  {
    cv = nVoxCmd->ConvertToString(G4ThreeVector());
  }
  return cv;
}


BSPhantomMessenger::~BSPhantomMessenger()
{
  delete nVoxCmd;
  delete patientSizeCmd;
  delete materialCmd;
  delete materialPhantomCmd;
  delete phantomDirectory;
}
