//
//  BSPhantom.hpp
//  BrainSPECT
//
//  Created by Matthew Kupinski on 8/8/17.
//  Copyright © 2017 BRP Partnership. All rights reserved.
//

#ifndef BSPhantom_h
#define BSPhantom_h 1

#include "BSPhantomMessenger.hh"
#include "BSDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Color.hh"
#include "G4NistManager.hh"
#include "G4Types.hh"


class BSPhantomMessenger;
class BSDetectorConstruction;

class BSPhantom
{
public:
  BSPhantom(BSDetectorConstruction* detector);
  ~BSPhantom();
  
  void SetPhantomVoxels(G4int x,G4int y, G4int z);
  void SetPhantomSize(G4ThreeVector vec);
  void LoadMaterials(G4String file);
  void LoadPhantomData(G4String file);
  
  G4int TotalVoxels();
  
  void SetDefaultPhantom();
  
  G4int GetNumVoxX();
  G4int GetNumVoxY();
  G4int GetNumVoxZ();
  G4double GetVoxelDimX();
  G4double GetVoxelDimY();
  G4double GetVoxelDimZ();
  G4double GetPhantomDimX();
  G4double GetPhantomDimY();
  G4double GetPhantomDimZ();
  G4double GetVoxelHalfDimX();
  G4double GetVoxelHalfDimY();
  G4double GetVoxelHalfDimZ();
  G4double GetPhantomHalfDimX();
  G4double GetPhantomHalfDimY();
  G4double GetPhantomHalfDimZ();
  
  std::vector < G4Material* > theMaterials;
  std::vector < G4Color > materialColors;
  size_t* mateIDs;
private:
  G4int numVoxX,numVoxY,numVoxZ;
  G4double voxelDimX,voxelDimY,voxelDimZ;
  G4double phantomDimX,phantomDimY,phantomDimZ;
  
  G4NistManager* nist;
  
  BSPhantomMessenger* phantomMessenger;
  BSDetectorConstruction* detectorConstruction;

};

#endif 
