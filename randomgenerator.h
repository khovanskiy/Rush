#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

class RandomGenerator
{
    static std::uniform_real_distribution<double> unif;
    static std::default_random_engine rand_engine;

    RandomGenerator(){};
    RandomGenerator(RandomGenerator const &);
    void operator=(RandomGenerator const&);
    ~RandomGenerator();

public:
    static RandomGenerator& gi()
    {
        static RandomGenerator instance;
        return instance;
    }

    static double getRandom(double lower_bound, double upper_bound)
    {
        return lower_bound + (upper_bound - lower_bound) * unif(rand_engine);
    }
};

#endif // RANDOMGENERATOR_H
