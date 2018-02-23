//
//  BSPhantom.cpp
//  BrainSPECT
//
//  Created by Matthew Kupinski on 8/8/17.
//  Copyright © 2017 BRP Partnership. All rights reserved.
//

#include "BSPhantom.hh"
#include "BSPhantomMessenger.hh"
#include "G4SystemOfUnits.hh"


BSPhantom::BSPhantom(BSDetectorConstruction* detector) :
numVoxX(1),
numVoxY(1),
numVoxZ(2),
phantomDimX(1.0*cm),
phantomDimY(1.0*cm),
phantomDimZ(1.0*cm),
detectorConstruction(detector)
{
  voxelDimX = phantomDimX / (G4double)numVoxX;
  voxelDimY = phantomDimY / (G4double)numVoxY;
  voxelDimZ = phantomDimZ / (G4double)numVoxZ;

  phantomMessenger = new BSPhantomMessenger(this);
  
  nist = G4NistManager::Instance();

  // Create a small blank phantom and materials
  theMaterials.push_back( nist->FindOrBuildMaterial("G4_AIR"));
  materialColors.push_back( G4Color(1.0,1.0,1.0,1.0) );
  
  mateIDs = new size_t[TotalVoxels()];
  for (int i =0;i< TotalVoxels();i++) {
    mateIDs[i] = 0;
  }
}


void BSPhantom::SetDefaultPhantom()
{
  delete mateIDs;
  mateIDs = new size_t[TotalVoxels()];
  for (int i =0;i< TotalVoxels();i++) {
    mateIDs[i] = 0;
  }
}

BSPhantom::~BSPhantom()
{
  delete mateIDs;
  delete phantomMessenger;
}


G4int BSPhantom::TotalVoxels()
{
  return(numVoxX * numVoxY * numVoxZ);
}

void BSPhantom::SetPhantomVoxels(G4int x,G4int y, G4int z)
{
  numVoxX = x;
  numVoxY = y;
  numVoxZ = z;
  
  voxelDimX = phantomDimX / (G4double)numVoxX;
  voxelDimY = phantomDimY / (G4double)numVoxY;
  voxelDimZ = phantomDimZ / (G4double)numVoxZ;
  
  SetDefaultPhantom();
  
  detectorConstruction->ConstructPhantom();
}


void BSPhantom::SetPhantomSize(G4ThreeVector vec)
{
  phantomDimX = vec.getX();
  phantomDimY = vec.getY();
  phantomDimZ = vec.getZ();
  
  voxelDimX = phantomDimX / (G4double)numVoxX;
  voxelDimY = phantomDimY / (G4double)numVoxY;
  voxelDimZ = phantomDimZ / (G4double)numVoxZ;
  
  detectorConstruction->ConstructPhantom();

}

void BSPhantom::LoadPhantomData(G4String file)
{
  std::ifstream myFile (file.c_str(), std::ios::in | std::ios::binary);
  
  delete mateIDs;
  mateIDs = new size_t[TotalVoxels()];
  myFile.read ((char *)mateIDs, TotalVoxels() * sizeof(size_t));
  myFile.close();

  detectorConstruction->ConstructPhantom();
}



void BSPhantom::LoadMaterials(G4String file)
{
  std::ifstream ifs;
  ifs.open( file.c_str() );
  
  G4int numMaterials;
  ifs >> numMaterials;
  
  theMaterials.clear();
  materialColors.clear();
  for (int ii = 0;ii < numMaterials;ii++)
  {
    G4String materialString;
    G4double red,green,blue,alpha;
    ifs >> materialString >> red >> green >> blue>>alpha;
    G4Material* temp = nist->FindOrBuildMaterial(materialString);
    if (temp) {
      theMaterials.push_back( temp );
    } else {
      G4cout <<"MAK:  Warning:  Program may crash: Only NIST databaset materials are currently supported" << G4endl;
      theMaterials.push_back( temp );
    }
    materialColors.push_back( G4Color(red,green,blue,alpha));
  }
  ifs.close();
  
  detectorConstruction->ConstructPhantom();

}


G4int BSPhantom::GetNumVoxX() { return numVoxX;}
G4int BSPhantom::GetNumVoxY() { return numVoxY;}
G4int BSPhantom::GetNumVoxZ() { return numVoxZ;}
G4double BSPhantom::GetVoxelDimX() {return voxelDimX;}
G4double BSPhantom::GetVoxelDimY() {return voxelDimY;}
G4double BSPhantom::GetVoxelDimZ() {return voxelDimZ;}
G4double BSPhantom::GetPhantomDimX() {return phantomDimX;}
G4double BSPhantom::GetPhantomDimY() {return phantomDimY;}
G4double BSPhantom::GetPhantomDimZ() {return phantomDimZ;}
G4double BSPhantom::GetVoxelHalfDimX() {return voxelDimX/2.0;}
G4double BSPhantom::GetVoxelHalfDimY() {return voxelDimY/2.0;}
G4double BSPhantom::GetVoxelHalfDimZ() {return voxelDimZ/2.0;}
G4double BSPhantom::GetPhantomHalfDimX() {return phantomDimX/2.0;}
G4double BSPhantom::GetPhantomHalfDimY() {return phantomDimY/2.0;}
G4double BSPhantom::GetPhantomHalfDimZ() {return phantomDimZ/2.0;}


