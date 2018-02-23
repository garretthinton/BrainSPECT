//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: BSPhysicsList.cc 66536 2012-12-19 14:32:36Z ihrivnac $
//
/// \file BSPhysicsList.cc
/// \brief Implementation of the BSPhysicsList class

#include "BSPhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecay.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4PhysListFactory.hh"
#include "G4GenericIon.hh"
#include "G4Gamma.hh"
#include "G4ProcessVector.hh"
#include "G4ProcessManager.hh"
#include "G4NuclideTable.hh"
#include "G4LossTableManager.hh"
#include "G4VAtomDeexcitation.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4NuclearLevelData.hh"
#include "G4EmPenelopePhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSPhysicsList::BSPhysicsList() 
: G4VModularPhysicsList(){
  SetVerboseLevel(1);

  // Penelope physics
  RegisterPhysics(new G4EmPenelopePhysics());
    
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BSPhysicsList::~BSPhysicsList()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BSPhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
  
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(50*keV,1.0*GeV);
}
