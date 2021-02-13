#include "Vector.hpp"

namespace ImplicitVolumes{
    struct AABB{
        Vector3 min;
        Vector3 max;
    };
    struct Sphere{
        float radius;
        Vector3 position;
    };
};