
#ifndef BSActionInitialization_h
#define BSActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
///

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class BSActionInitialization : public G4VUserActionInitialization
{
  public: 
    BSActionInitialization();
    virtual ~BSActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
