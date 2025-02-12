#ifndef STD140_SHADOW_BLOCK_H
#define STD140_SHADOW_BLOCK_H

#include "core/math/mat4.h"

namespace std140
{
    struct ShadowBlock
    {
        mat4 iShadowMatrices[4];
    };
}
#endif