#ifndef lgPrimaryGeneratorAction_h
#define lgPrimaryGeneratorAction_h

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"
#include "G4SystemOfUnits.hh"

class G4ParticleGun;
class G4Event;

class lgPrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
    public:
    lgPrimaryGeneratorAction();
    ~lgPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* event);

    G4ParticleGun* get_particle_gun() {return particle_gun;}

    private:
    G4ParticleGun* particle_gun;
};

#endif