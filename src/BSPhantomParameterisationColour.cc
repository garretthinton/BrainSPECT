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
//$Id:BSPhantomParameterisationColour.cc 74592 2013-10-15 21:20:11Z jmadsen $
//
/// \file BSPhantomParameterisationColour.cc
/// \brief Implementation of the BSPhantomParameterisationColour class

#include "BSPhantomParameterisationColour.hh"

#include "globals.hh"
#include "G4VisAttributes.hh"
#include "G4Material.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
BSPhantomParameterisationColour::BSPhantomParameterisationColour(std::vector<G4Color> colors)
: G4PhantomParameterisation()
{
  for ( auto i = colors.begin(); i != colors.end(); i++ ) {
    fAttributes.push_back(new G4VisAttributes(G4Color(*i)));
  }
  SetSkipEqualMaterials(false);
}

BSPhantomParameterisationColour::BSPhantomParameterisationColour()
: G4PhantomParameterisation()
{
  fAttributes.push_back(new G4VisAttributes(G4Color(1.0,1.0,1.0,1.0)));
  SetSkipEqualMaterials(false);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
BSPhantomParameterisationColour::~BSPhantomParameterisationColour()
{
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Material* BSPhantomParameterisationColour::
ComputeMaterial(const G4int copyNo, G4VPhysicalVolume * physVol, const G4VTouchable *)
{
  G4Material* mate = G4PhantomParameterisation::ComputeMaterial( copyNo, physVol, 0 );
  
  size_t id = G4PhantomParameterisation::GetMaterialIndex(copyNo);
  G4VisAttributes* hi = fAttributes[id];
  if (hi->GetColor().GetAlpha() == 0.0) {
    physVol->GetLogicalVolume()->SetVisAttributes( G4VisAttributes::Invisible );
  } else {
    //physVol->GetLogicalVolume()->SetVisAttributes( G4VisAttributes::Invisible );
    physVol->GetLogicalVolume()->SetVisAttributes( hi );
  }
  return mate;
}
