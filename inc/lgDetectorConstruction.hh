#ifndef lgDetectorConstruction_h
#define lgDetectorConstruction_h

#include "lgSensitiveDetector.hh"

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"

#include <vector>

class G4LogicalVolume;
class G4PhysicalVolume;

class lgDetectorConstruction: public G4VUserDetectorConstruction
{
    public:
    lgDetectorConstruction();
    virtual ~lgDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    static std::vector<G4double> get_crystal_dimensions();

    static G4double world_x, world_y, world_z;
    static G4double crystal_x, crystal_y, crystal_z;
    static G4double window_x,  window_y, window_z;
    static G4double grease_x, grease_y, grease_z;
    static G4double gap;
    G4bool checkOverlaps;
};

#endif