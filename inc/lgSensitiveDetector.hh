#ifndef lgSensitiveDetector_h
#define lgSensitiveDetector_h

#include "../inc/lgHits.hh"

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"

#include <vector>

class lgSensitiveDetector: public G4VSensitiveDetector
{
    public:
    lgSensitiveDetector(const G4String& name, const G4String& hits_collection_name);
    ~lgSensitiveDetector();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void Initialize(G4HCofThisEvent* hce);
    virtual void EndOfEvent(G4HCofThisEvent* hce);

    private:
    lg_hits_collection* hits_collection;
    G4String sd_name;
};

#endif