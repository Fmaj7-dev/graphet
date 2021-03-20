#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "particlesystem.h"


TEST_CASE("ParticleSystem")
{
  const size_t NUM_PARTICLES = 10000;
  ParticleSystem ps( NUM_PARTICLES );
  
  // test init size
  REQUIRE( ps.getNumParticles() == NUM_PARTICLES );

  // test add
  Particle p;
  p.position_[0] = 10;
  p.position_[1] = 11;
  p.position_[2] = 12;
  p.color_[0] = 127;
  p.color_[1] = 128;
  p.color_[2] = 129;

  ps.addParticle(p);
  REQUIRE(ps.getNumParticles() == NUM_PARTICLES +1);

  // test get
  Particle p2;
  size_t num_p = ps.getNumParticles();
  p2 = ps.getParticles()[ num_p-1 ];

  REQUIRE(p2.position_[0] == p.position_[0]);
  REQUIRE(p2.position_[1] == p.position_[1]);
  REQUIRE(p2.position_[2] == p.position_[2]);

  REQUIRE(p2.color_[0] == p.color_[0]);
  REQUIRE(p2.color_[1] == p.color_[1]);
  REQUIRE(p2.color_[2] == p.color_[2]);
  
}