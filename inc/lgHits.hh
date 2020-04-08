#ifndef lgHits_h
#define lgHits_h

//POSSIBE TODO: 1.add some functionality other than hit detection 

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class lgHit: public G4VHit
{
    public:
    lgHit();
    virtual ~lgHit();

    inline void* operator new(size_t);
    inline void operator delete(void*);
};

typedef G4THitsCollection<lgHit> lg_hits_collection;
extern G4ThreadLocal G4Allocator<lgHit>* lg_hit_allocator;

inline void* lgHit::operator new(size_t)
{
    if(!lg_hit_allocator) lg_hit_allocator = new G4Allocator<lgHit>;

    return (void*) lg_hit_allocator->MallocSingle();
}

inline void lgHit::operator delete(void* hit)
{
    lg_hit_allocator->FreeSingle((lgHit*) hit);
}

#endif