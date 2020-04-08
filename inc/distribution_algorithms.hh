#ifndef distribution_algorithms_h
#define distribution_algorithms_h

#include <random>
#include <chrono>
#include <vector>
#include <algorithm>
#include "G4SystemOfUnits.hh"

#include "../inc/lgDetectorConstruction.hh"


class distributor
{
    public:
    void position_distribution();
    void momentum_distribution();
    void polarization_distribution();

    G4ThreeVector pos_dist, mom_dist, pol_dist;
};
#endif
