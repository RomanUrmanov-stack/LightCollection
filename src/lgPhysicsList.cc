#include "lgPhysicsList.hh"

lgPhysicsList::lgPhysicsList():G4VUserPhysicsList()
{}

lgPhysicsList::~lgPhysicsList()
{}

void lgPhysicsList::ConstructParticle()
{
    G4OpticalPhoton::Definition();
}

void lgPhysicsList::ConstructProcess()
{
    AddTransportation();
    construct_boundary_op();
}

void lgPhysicsList::SetCuts()
{
    SetCutsWithDefault();
}

void lgPhysicsList::construct_boundary_op()
{
    auto particle_iterator = GetParticleIterator();
    particle_iterator->reset();

    while ((*particle_iterator)())
    {
        G4ParticleDefinition* particle = particle_iterator->value();
        G4ProcessManager* p_manager = particle->GetProcessManager();
        G4String particle_name = particle->GetParticleName();

        if (particle_name == "opticalphoton")
        {
            p_manager->AddDiscreteProcess(new G4OpBoundaryProcess());
            p_manager->AddDiscreteProcess(new G4OpAbsorption());
        }
    }
}