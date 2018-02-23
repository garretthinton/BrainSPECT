
#ifndef BSDetectorConstruction_h
#define BSDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "BSPhantom.hh"
#include "BSPhantomParameterisationColour.hh"
#include "G4PVParameterised.hh"
#include "G4NistManager.hh"
#include "G4TessellatedSolid.hh"
#include "G4Box.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.
///
/// Crystals are positioned in Ring, with an appropriate rotation matrix. 
/// Several copies of Ring are placed in the full detector.

class BSPhantom;

class BSDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  G4LogicalVolume *logicalDetector;
  BSDetectorConstruction();
  virtual ~BSDetectorConstruction();
  
public:
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();
  
private:
  void DefineMaterials();
    
  G4NistManager* nist;
  
  G4LogicalVolume* bodyLogical;
  
  G4TessellatedSolid* body;
  G4String FacetType;
  
public:
  
  void ConstructPhantom();
  
  void ReadTessellatedPhantom(G4String fileName, G4TessellatedSolid* solid);
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

