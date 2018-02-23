
#ifndef BSPrimaryGeneratorAction_h
#define BSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

/// The primary generator action class with particle gum.
///
/// It defines an ion (F18), at rest, randomly distribued within a zone 
/// in a patient defined in GeneratePrimaries(). Ion F18 can be changed 
/// with the G4ParticleGun commands (see run2.mac).

class BSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    BSPrimaryGeneratorAction();    
    virtual ~BSPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);         

    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
