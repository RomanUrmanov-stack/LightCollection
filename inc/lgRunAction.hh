#ifndef lgRunAction_h
#define lgRunAction_h

#include "G4UserRunAction.hh"
#include "G4Run.hh"

class G4Run;

class lgRunAction: public G4UserRunAction
{
    public:
    lgRunAction();
    virtual ~lgRunAction();

    virtual void BeginOfRunAction(const G4Run* run);
    virtual void EndOfRunAction(const G4Run* run);

    static void add_photons(G4int add);

    protected:
    static G4int detected_photons;
};

#endif