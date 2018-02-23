
#include "BSDetectorConstruction.hh"
#include "BSSensitiveDetector.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhantomParameterisation.hh"
#include "G4PVParameterised.hh"
#include "BSPhantomParameterisationColour.hh"
#include "BSPhantomMessenger.hh"
#include "G4RunManager.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4QuadrangularFacet.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"
#define M_PI 3.14159265358979

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSDetectorConstruction::BSDetectorConstruction()
: G4VUserDetectorConstruction()
{
  DefineMaterials();
    
  //phantom = new BSPhantom(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSDetectorConstruction::~BSDetectorConstruction()
{
  //delete phantom;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BSDetectorConstruction::DefineMaterials()
{
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* BSDetectorConstruction::Construct()
{
  //  Air will be the default material
  nist = G4NistManager::Instance();
  G4Material* default_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  //     
  // World
  //
  G4double world_sizeX = 800*mm;
  G4double world_sizeY = 800*mm;
  G4double world_sizeZ = 2000*mm;
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ); //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        default_mat,         //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      true);       // checking overlaps


  

  //
  // Tessellated phantom test
  //
  
  
  G4ThreeVector bodyPosition = G4ThreeVector(0.0,0.0,50.0*cm);
  body = new G4TessellatedSolid("Body");
  ReadTessellatedPhantom("Body.STL",body);
  G4Material* tissue = nist->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");
  bodyLogical =
  new G4LogicalVolume(body,          //its solid
                      tissue,         //its material
                      "Body");            //its name
  G4VisAttributes *vis1 = new G4VisAttributes();
  vis1->SetVisibility(true);
  //vis1->SetForceLineSegmentsPerCircle(20);
  vis1->SetForceWireframe(false);
  vis1->SetForceSolid(true);
  vis1->SetColor(G4Color(1.0,1.0,1.0,0.3));
//  bodyLogical->SetVisAttributes(G4Color(1.0,1.0,1.0,0.2));
  bodyLogical->SetVisAttributes(vis1);
  G4RotationMatrix *rot = new G4RotationMatrix(0.0,0.0,M_PI);
  new G4PVPlacement(rot ,
                    bodyPosition,
                    bodyLogical,
                    "Body",
                    logicWorld,
                    false,
                    1,true);

  
  
  
  G4TessellatedSolid* bones = new G4TessellatedSolid("Bones");
  ReadTessellatedPhantom("Skeleton.STL",bones);
  G4Material* boneType = nist->FindOrBuildMaterial("G4_BONE_CORTICAL_ICRP");
  G4LogicalVolume* boneLogical =
  new G4LogicalVolume(bones,          //its solid
                      boneType,         //its material
                      "Bones");            //its name
  G4VisAttributes *vis2 = new G4VisAttributes();
  vis2->SetVisibility(true);
  vis2->SetForceWireframe(true);
  vis2->SetForceSolid(false);
  vis2->SetColor(G4Color(1.0,1.0,1.0,1.0));
  boneLogical->SetVisAttributes(vis2);
  //  boneLogical->SetVisAttributes(G4Color(1.0,1.0,1.0,1.0));
  new G4PVPlacement(0 ,
                    G4ThreeVector(),
                    boneLogical,
                    "Body",
                    bodyLogical,
                    false,
                    1,true);


  
  G4TessellatedSolid* lungs = new G4TessellatedSolid("Lungs");
  ReadTessellatedPhantom("Lungs.stl",lungs);
  G4Material* lungType = nist->FindOrBuildMaterial("G4_LUNG_ICRP");
  G4LogicalVolume* lungLogical =
  new G4LogicalVolume(lungs,          //its solid
                      lungType,         //its material
                      "Lungs");            //its name
  G4VisAttributes *vis3 = new G4VisAttributes();
  vis3->SetVisibility(true);
  vis3->SetForceWireframe(false);
  vis3->SetForceSolid(true);
  vis3->SetColor(G4Color(1.0,0.0,0.0,1.0));
  lungLogical->SetVisAttributes(vis3);
//  lungLogical->SetVisAttributes(G4Color(1.0,0.0,0.0,1.0));
  new G4PVPlacement(0 ,
                    G4ThreeVector(),
                    lungLogical,
                    "Lungs",
                    bodyLogical,
                    false,
                    1,true);
  

  G4TessellatedSolid* liver = new G4TessellatedSolid("Liver");
  ReadTessellatedPhantom("Liver.stl",liver);
  G4LogicalVolume* liverLogical =
  new G4LogicalVolume(liver,          //its solid
                      tissue,         //its material
                      "Liver");            //its name
  G4VisAttributes *vis4 = new G4VisAttributes();
  vis4->SetVisibility(true);
  vis4->SetForceWireframe(false);
  vis4->SetForceSolid(true);
  vis4->SetColor(G4Color(0.0,1.0,0.0,1.0));
  liverLogical->SetVisAttributes(vis4);
// liverLogical->SetVisAttributes(G4Color(0.0,1.0,0.0,1.0));
  new G4PVPlacement(0 ,
                    G4ThreeVector(),
                    liverLogical,
                    "Liver",
                    bodyLogical,
                    false,
                    1,true);


  G4TessellatedSolid* brain = new G4TessellatedSolid("Brain");
  ReadTessellatedPhantom("brain.stl",brain);
  G4LogicalVolume* brainLogical =
  new G4LogicalVolume(brain,          //its solid
                      tissue,         //its material
                      "Brain");            //its name
  G4VisAttributes *vis5 = new G4VisAttributes();
  vis5->SetVisibility(true);
  vis5->SetForceWireframe(false);
  vis5->SetForceSolid(true);
  vis5->SetColor(G4Color(0.0,0.0,1.0,1.0));
  brainLogical->SetVisAttributes(vis5);
  //brainLogical->SetVisAttributes(G4Color(0.0,0.0,1.0,1.0));
  new G4PVPlacement(0 ,
                    G4ThreeVector(),
                    brainLogical,
                    "Brain",
                    bodyLogical,
                    false,
                    1,true);

  
  //
  //  Spherical detector
  //
  G4ThreeVector spherePosition = G4ThreeVector(0.0,2.2*cm,75.0*cm);
  G4Sphere *detector = new G4Sphere("Detector",13.7*cm,13.71*cm,0.0,2*pi,0.0,pi);
  
  G4SubtractionSolid* det1 = new G4SubtractionSolid(  "Testing",
                     detector ,
                     body ,
                     rot,
                     bodyPosition-spherePosition  ) ;

  
  logicalDetector = new G4LogicalVolume(det1, default_mat,"Detector");
  new G4PVPlacement(0,spherePosition,logicalDetector,"Detector",logicWorld,false,0,true);
  
  //logicalDetector->SetVisAttributes (G4VisAttributes::GetInvisible());
  G4VisAttributes *vis = new G4VisAttributes();
  vis->SetVisibility(true);
  vis->SetForceLineSegmentsPerCircle(20);
  vis->SetForceWireframe(false);
  vis->SetForceSolid(true);
  vis->SetColor(G4Color(1.0,1.0,1.0,0.2));
  
  logicalDetector->SetVisAttributes(vis);
  

  

  
  //always return the physical World
  //
  return physWorld;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BSDetectorConstruction::ConstructSDandField()
{
  logicalDetector->SetSensitiveDetector(new BSSensitiveDetector("Detector",G4ThreeVector(0.0,2.2*cm,75.0*cm)));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




// Keep around temporatily until I can get rid of BSPhanom.cc
void BSDetectorConstruction::ConstructPhantom()
{
//  voxel_solid->SetXHalfLength(phantom->GetVoxelHalfDimX());
//  voxel_solid->SetYHalfLength(phantom->GetVoxelHalfDimY());
//  voxel_solid->SetZHalfLength(phantom->GetVoxelHalfDimZ());
//  cont_solid->SetXHalfLength(phantom->GetPhantomHalfDimX());
//  cont_solid->SetYHalfLength(phantom->GetPhantomHalfDimY());
//  cont_solid->SetZHalfLength(phantom->GetPhantomHalfDimZ());
//  
//  if (param)
//    delete param;
//  
//  param = new BSPhantomParameterisationColour(phantom->materialColors);
////  param = new G4PhantomParameterisation();
//  param->SetVoxelDimensions( phantom->GetVoxelHalfDimX(),phantom->GetVoxelHalfDimY(),phantom->GetVoxelHalfDimZ());
//  param->SetNoVoxel( phantom->GetNumVoxX(), phantom->GetNumVoxY(), phantom->GetNumVoxZ());
//  param->SetMaterials( phantom->theMaterials );
//    
//  
//  param->SetMaterialIndices( phantom->mateIDs );
//  param->BuildContainerSolid(cont_phys);
//  
//  param->CheckVoxelsFillContainer( cont_solid->GetXHalfLength(),
//                                  cont_solid->GetYHalfLength(),
//                                  cont_solid->GetZHalfLength() );
//  
//  if (patient_phys)
//    delete patient_phys;
//  patient_phys =
//  new G4PVParameterised("Patient",
//                        voxel_logic,
//                        cont_logic,
//                        kXAxis,
//                        phantom->TotalVoxels(),
//                        param);                  // parameterisation
//  
//  // Indicate that this physical volume is having a regular structure
//  //
//  patient_phys->SetRegularStructureId(1);
//  
//  G4RunManager::GetRunManager()->GeometryHasBeenModified(true);
}



void BSDetectorConstruction::ReadTessellatedPhantom(G4String fileName, G4TessellatedSolid* solid)
{
  char header[81];
  typedef struct { float n[3], v1[3], v2[3], v3[3]; unsigned int att; } TFacet_t;
  typedef struct { float n[3], v1[3], v2[3], v3[3], v4[3]; unsigned int att; } QFacet_t;
  
  unsigned long nbFacets;

  
  std::ifstream STLFile( fileName, std::ios::in|std::ios::binary );
  
  if( !STLFile )
  {
    G4cerr << "No STL file: " << "Body.STL"<< G4endl;
    exit(1);
  }

  
  STLFile.seekg(0, std::ios::end);
  long fileSize = STLFile.tellg();
  STLFile.seekg(0, std::ios::beg);
  
  STLFile.read(header, 80);
  header[80] = '\0';
  STLFile.read((char *)&nbFacets, 4);
  
  // Check if the facets are correctly defined
  if ( (int)nbFacets == (fileSize-84)/50 )
  {
    FacetType = "Triangular";
  }
  else if ( (int)nbFacets == (fileSize-84)/62 )
  {
    FacetType = "Quadrangular";
  }
  else
  {
    G4cerr << "STL file corrupted: number of facets do not correspond to file size." << G4endl;
  }
  
  // Read and create all the facets
  while ( true )
  {
    if ( FacetType == "Triangular" )
    {
      TFacet_t TFacet;
      STLFile.read((char *)&TFacet, 50);
      if ( STLFile.eof() ) break;
      // Create the new facet
      G4ThreeVector vertice1 = G4ThreeVector(TFacet.v1[0], TFacet.v1[1], TFacet.v1[2]);
      G4ThreeVector vertice2 = G4ThreeVector(TFacet.v2[0], TFacet.v2[1], TFacet.v2[2]);
      G4ThreeVector vertice3 = G4ThreeVector(TFacet.v3[0], TFacet.v3[1], TFacet.v3[2]);
      G4TriangularFacet *facet = new G4TriangularFacet( vertice1*mm, vertice2*mm, vertice3*mm, ABSOLUTE );
      solid->AddFacet( (G4VFacet*)facet );
    }
    else if ( FacetType == "Quadrangular" )
    {
      QFacet_t QFacet;
      STLFile.read((char *)&QFacet, 62);
      if ( STLFile.eof() ) break;
      // Create the new facet
      G4ThreeVector vertice1 = G4ThreeVector(QFacet.v1[0], QFacet.v1[1], QFacet.v1[2]);
      G4ThreeVector vertice2 = G4ThreeVector(QFacet.v2[0], QFacet.v2[1], QFacet.v2[2]);
      G4ThreeVector vertice3 = G4ThreeVector(QFacet.v3[0], QFacet.v3[1], QFacet.v3[2]);
      G4ThreeVector vertice4 = G4ThreeVector(QFacet.v4[0], QFacet.v4[1], QFacet.v4[2]);
      G4QuadrangularFacet *facet = new G4QuadrangularFacet( vertice1*mm, vertice2*mm, vertice3*mm, vertice4*mm, ABSOLUTE );
      solid->AddFacet( (G4VFacet*)facet );
    }
  }
  
  STLFile.close();
  
  solid->SetSolidClosed( true );

}


