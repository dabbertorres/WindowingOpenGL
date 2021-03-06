#ifndef DBR_ENG_MATH_RANDOM_HPP
#define DBR_ENG_MATH_RANDOM_HPP

#include <random>

namespace dbr
{
    namespace eng
    {
        namespace math
        {
            class Random
            {
            public:
                template<typename Dist>
                static inline auto get(Dist dist)
                {
                    return dist(engine);
                }

            private:
                static std::random_device randDevice;
                static std::seed_seq seed;
                static std::mt19937 engine;
            };
        }
    }
}

#endif
