#include "../inc/lgSensitiveDetector.hh"

lgSensitiveDetector::lgSensitiveDetector(const G4String& name, const G4String& hits_collection_name): G4VSensitiveDetector(name)
{
    this->sd_name = name;
    collectionName.insert(hits_collection_name);
}

lgSensitiveDetector::~lgSensitiveDetector()
{}

G4bool lgSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
    //G4cout << "Hit was detected" << G4endl;
    
    lgHit* hit = new lgHit();
    hits_collection->insert(hit);

    return true;
}

void lgSensitiveDetector::Initialize(G4HCofThisEvent* hc_of_this_event)
{
    hits_collection = new lg_hits_collection(sd_name, collectionName[0]);
    G4int lg_hc_id = GetCollectionID(0);

    hc_of_this_event->AddHitsCollection(lg_hc_id, hits_collection);
}

void lgSensitiveDetector::EndOfEvent(G4HCofThisEvent* hc_of_this_event)
{
    //G4int no_of_hits = hits_collection->entries(); 
    //G4cout << "We detected " << no_of_hits << " photons" << G4endl;
}