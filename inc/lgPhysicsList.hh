#ifndef lgPhysicsList_h
#define lgPhysicsList_h

#include "G4VUserPhysicsList.hh"

#include "G4RunManager.hh"
#include "G4ProcessManager.hh"

#include "G4OpticalPhoton.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpAbsorption.hh"

#include "G4ParticleDefinition.hh"

class lgPhysicsList: public G4VUserPhysicsList
{
    public:
    lgPhysicsList();
    ~lgPhysicsList();

    protected:
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    virtual void SetCuts();

    void construct_boundary_op();
};

#endif