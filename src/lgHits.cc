#include "lgHits.hh"

G4ThreadLocal G4Allocator<lgHit>* lg_hit_allocator = 0;

lgHit::lgHit(): G4VHit()
{}

lgHit::~lgHit()
{}