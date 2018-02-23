
#include "BSRunAction.hh"
#include "BSRun.hh"
#include "BSPrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RootAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSRunAction::BSRunAction()
 : G4UserRunAction()
{  
  auto analysisManager = G4RootAnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);
  analysisManager->SetNtupleMerging(true);

  
  analysisManager->CreateNtuple("MAK", "Photon properties");
  analysisManager->CreateNtupleDColumn("Energy");
  analysisManager->CreateNtupleDColumn("XPos");
  analysisManager->CreateNtupleDColumn("YPos");
  analysisManager->CreateNtupleDColumn("ZPos");
  analysisManager->CreateNtupleDColumn("XDir");
  analysisManager->CreateNtupleDColumn("YDir");
  analysisManager->CreateNtupleDColumn("ZDir");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSRunAction::~BSRunAction()
{
  delete G4RootAnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* BSRunAction::GenerateRun()
{ return new BSRun; }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BSRunAction::BeginOfRunAction(const G4Run* run)
{ 
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;
  
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  
  // Get analysis manager
  auto analysisManager = G4RootAnalysisManager::Instance();
  // Open an output file
  analysisManager->OpenFile("MAKTest");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BSRunAction::EndOfRunAction(const G4Run*)
{
  
  auto analysisManager = G4RootAnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
