
#include "BSPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ChargedGeantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSPrimaryGeneratorAction::BSPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
  fParticleGun->SetParticleEnergy(140.5*keV);
  
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSPrimaryGeneratorAction::~BSPrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  
  // fixed position
  //
  G4double x0  = 0*cm, y0  = 0*cm, z0  = 75.0*cm;
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  
  //isotropic: flat in cosTheta and phi
  //Randomize it
  G4double cosTheta = 2.0*G4UniformRand()-1.0; //cosTheta in [0,1] --> theta in [0,pi/2]
  G4double phi = G4UniformRand()*360*deg; //flat in [0,2pi]
  G4double sinTheta = std::sqrt(1.-cosTheta*cosTheta);
  
  G4ThreeVector dir(sinTheta*std::cos(phi),sinTheta*std::sin(phi),cosTheta);
  
  fParticleGun->SetParticleMomentumDirection(dir);
  
  
  //create vertex
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

