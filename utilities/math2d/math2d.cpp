
#include "math2d.h"

namespace math2d {
    
    CCPoint pointAtCircle(const CCPoint& pt, float radians, float radius)
    {
        CCPoint npt;
        npt.x = pt.x + cosf(radians) * radius;
        npt.y = pt.y - sinf(radians) * radius;
        return npt;
    }
    
    float radians4point(const CCPoint& p1, const CCPoint& p2)
    {
        // atan2f(p2.y - p1.y, p2.x - p1.x);
        return atan2f(-p2.y - (-p1.y), p2.x - p1.x);
    }
    
    float dist(const CCPoint& p1, const CCPoint& p2)
    {
        float dx = p2.x - p1.x;
        float dy = p2.y - p1.y;
        return sqrtf(dx * dx + dy * dy);
    }
    
}
