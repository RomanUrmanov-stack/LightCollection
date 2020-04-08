#include "../inc/lgEventAction.hh"

lgEventAction::lgEventAction(): G4UserEventAction()
{}

lgEventAction::~lgEventAction()
{}

void lgEventAction::BeginOfEventAction(const G4Event*)
{}

void lgEventAction::EndOfEventAction(const G4Event* event)
{
    G4HCofThisEvent* hc_of_this_event = event->GetHCofThisEvent();
    G4int detected_photons = hc_of_this_event->GetHC(0)->GetSize();

    //G4cout << "Detected in this event " << detected_photons << G4endl;

    lgRunAction::add_photons(detected_photons);
}