
#ifndef __MATH2D_H_
#define __MATH2D_H_

#include "cocos2d.h"
#include <math.h>

using namespace cocos2d;

// 确定是否发生碰撞
#define IS_COLLISION(p1, r1, p2, r2) (math2d::dist(p1, p2) - r1 - r2 <= 0)

// 随机返回 true 或 false
#define RANDOM_TRUE_FALSE           (rand() % 2 == 1)

// 创建 1 -> 100 之间的随机数（含 1 和 100）
#define RANDOM_1_100                ((rand() % 100) + 1)
#define RANDOM_1_100_F(s)           (((rand() / (float)RAND_MAX) * 99 + 1) * (s))

// 创建 0 -> n 之间的随机数（含 0 和 n）
#define RANDOM_0_N(n)               (rand() % ((int)(n) + 1))

// 创建 1 -> n 之间的随机数（含 1 和 n）
#define RANDOM_1_N(n)               ((rand() % (int)(n)) + 1)

// 创建 min -> max 之间的随机数（含 min 和 max）
#define RANDOM_MIN_MAX(min, max)    ((rand() % (int)((max) - (min) + 1)) + (int)(min))
#define RANDOM_MIN_MAX_F(min, max)  ((rand() / (float)RAND_MAX) * ((max) - (min)) + (min))

// 帧时间差修订
#define FRAME_TIME_FIX(dt, value)   ((value) * ((dt) / 0.016666667f))


namespace math2d {
    
    // 求圆上一个点的位置
    CCPoint pointAtCircle(const CCPoint& pt, float radians, float radius);
    
    // 求两条线段的夹角弧度
    float radians4point(const CCPoint& p1, const CCPoint& p2);
    
    // 求两个点的距离
    float dist(const CCPoint& p1, const CCPoint& p2);
    
};

#endif // __MATH2D_H_
