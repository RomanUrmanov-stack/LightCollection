#ifndef lgEventAction_h
#define lgEventAction_h

#include "lgRunAction.hh"

#include "G4UserEventAction.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"

class G4Event;

class lgEventAction: public G4UserEventAction
{
    public:
    lgEventAction();
    virtual ~lgEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event* event);
};

#endif