#include "randomgenerator.h"

std::uniform_real_distribution<double> RandomGenerator::unif = std::uniform_real_distribution<double>(0,1);
std::default_random_engine RandomGenerator::rand_engine;

RandomGenerator::~RandomGenerator()
{
}
