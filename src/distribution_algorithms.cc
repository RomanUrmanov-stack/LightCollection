#include "../inc/distribution_algorithms.hh"

//TODO: tweak your dist_z according to geometry and directions of your experimental plant

void distributor::position_distribution()
{   
    G4double mu = 14.47;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::vector<G4double> position(2);

    std::vector<G4double> dim = lgDetectorConstruction::get_crystal_dimensions();
    
    int count = 0;
    int* count_p = &count;

    std::generate(position.begin(), position.end(), [&generator, &dim, &count_p]() { std::uniform_real_distribution<G4double> dist_xy(-dim[*(count_p)], dim[*(count_p)]);
                                                                                   ++*(count_p);
                                                                                   dist_xy.reset();
                                                                                   return dist_xy(generator);});

    
    std::uniform_real_distribution<G4double> dist_z(0,1);
    G4double z;
    do
    {
        z = -5 - mu * log(1 - dist_z(generator));
    } while(z > 5);

    this->pos_dist = G4ThreeVector(position[0]*mm, position[1]*mm, z*mm);
}

void distributor::momentum_distribution()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::uniform_real_distribution<G4double> dist_theta(0, 1.0);
    G4double theta = 2*asin(sqrt(dist_theta(generator)));

    std::uniform_real_distribution<G4double> dist_phi(0, 2 * CLHEP::pi);
    G4double phi = dist_phi(generator);

    std::vector<G4double> momentum(3);
    momentum[0] = sin(theta) * cos(phi);
    momentum[1] = sin(theta) * sin(phi);
    momentum[2] = cos(theta);

    G4double length = sqrt(momentum[0] * momentum[0] + momentum[1] * momentum[1] + momentum[2] * momentum[2]);
   
    try
    {
        this->mom_dist = G4ThreeVector(momentum[0]/length, momentum[1]/length, momentum[2]/length);
    }
    catch(std::exception &ex)
    {
        this->momentum_distribution();
    }
}

void distributor::polarization_distribution() 
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    
    std::uniform_real_distribution<G4double> dist_theta(0, 1.0);
    G4double theta = 2*asin(sqrt(dist_theta(generator)));

    std::uniform_real_distribution<G4double> dist_phi(0, 2 * CLHEP::pi);
    G4double phi = dist_phi(generator);

    std::vector<G4double> temp(3);
    temp[0] = sin(theta) * cos(phi);
    temp[1] = sin(theta) * sin(phi);
    temp[2] = cos(theta);

    G4double pol_x = temp[1] * this->mom_dist.getZ() - this->mom_dist.getY() * temp[2];
    G4double pol_y = temp[2] * this->mom_dist.getX() - this->mom_dist.getZ() * temp[0]; 
    G4double pol_z = temp[0] * this->mom_dist.getY() - this->mom_dist.getX() * temp[1];
    
    G4double length = sqrt(pol_x * pol_x + pol_y * pol_y + pol_z * pol_z);

    try
    {
        this->pol_dist = G4ThreeVector(pol_x/length, pol_y/length, pol_z/length);
    }
    catch(std::exception &ex)
    {
        this->polarization_distribution();
    }
}