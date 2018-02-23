
#ifndef BSRun_h
#define BSRun_h 1

#include "G4Run.hh"
#include "globals.hh"

/// Run class
///
/// In RecordEvent() there is collected information event per event 
/// from Hits Collections, and accumulated statistic for the run 

class BSRun : public G4Run
{
  public:
    BSRun();
    virtual ~BSRun(); 

    virtual void RecordEvent(const G4Event*);
    virtual void Merge(const G4Run*);
  private:
    G4int fPrintModulo;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
