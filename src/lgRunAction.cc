#include "../inc/lgRunAction.hh"

 G4int lgRunAction::detected_photons = 0;

lgRunAction::lgRunAction(): G4UserRunAction()
{}

lgRunAction::~lgRunAction()
{}

void lgRunAction::BeginOfRunAction(const G4Run* run)
{}

void lgRunAction::add_photons(G4int add)
{
    detected_photons += add;
}

void lgRunAction::EndOfRunAction(const G4Run* run)
{
    G4double n_of_events = run->GetNumberOfEvent();

    G4cout << "In this run we detected " << detected_photons/n_of_events * 100 <<"% of all photons" << G4endl;
}