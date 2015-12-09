#include "random.h"

std::uniform_real_distribution<double> Random::unif = std::uniform_real_distribution<double>(0,1);
std::default_random_engine Random::rand_engine;

Random::~Random()
{
}
