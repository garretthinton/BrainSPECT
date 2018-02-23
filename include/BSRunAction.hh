
#ifndef BSRunAction_h
#define BSRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4RootAnalysisManager.hh"
#include "globals.hh"

class G4Run;

/// Run action class

class BSRunAction : public G4UserRunAction
{
  public:
    BSRunAction();
    virtual ~BSRunAction();
    
    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
  
    //G4RootAnalysisManager *analysisManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

