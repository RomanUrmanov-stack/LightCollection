#include "../inc/lgPrimaryGeneratorAction.hh"
#include "../inc/distribution_algorithms.hh"


lgPrimaryGeneratorAction::lgPrimaryGeneratorAction():G4VUserPrimaryGeneratorAction()
{
    G4int n_of_particles = 1;
    particle_gun = new G4ParticleGun(n_of_particles);

    G4double particle_energy = 2.034*eV;

    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("opticalphoton");

    particle_gun->SetParticleDefinition(particle);
    particle_gun->SetParticleEnergy(particle_energy);
}

lgPrimaryGeneratorAction::~lgPrimaryGeneratorAction()
{
    delete particle_gun;
}

void lgPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{   
    distributor dist;

    dist.position_distribution();
    particle_gun->SetParticlePosition(dist.pos_dist);

    dist.momentum_distribution();
    particle_gun->SetParticleMomentumDirection(dist.mom_dist);

    dist.polarization_distribution();
    particle_gun->SetParticlePolarization(dist.pol_dist);

    particle_gun->GeneratePrimaryVertex(event);
}