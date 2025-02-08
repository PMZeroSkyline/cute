#ifndef UNIFORM_SHADOW_BLOCK_H
#define UNIFORM_SHADOW_BLOCK_H

#include "core/math/mat4.h"

namespace std140
{
    struct ShadowBlock
    {
        mat4 iShadowMatrices[4];
    };
}
#endif