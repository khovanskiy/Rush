#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <random>

class Random
{
    static std::uniform_real_distribution<double> unif;
    static std::default_random_engine rand_engine;

    Random()
    {

    };
    Random(Random const &);
    void operator=(Random const&);
    ~Random();

public:
    static Random& gi()
    {
        static Random instance;
        return instance;
    }

    static double getRandom(double lower_bound, double upper_bound)
    {
        return lower_bound + (upper_bound - lower_bound) * unif(rand_engine);
    }
};

#endif // RANDOMGENERATOR_H
