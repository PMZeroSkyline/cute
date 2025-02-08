#include "motion.h"

Motion::Motion(const json& j)
{
    mass = j["mass"];
    if (j.contains("linearVelocity"))
    {
        linear_velocity = j["linearVelocity"];
    }
    if (j.contains("isKinematic"))
    {
        is_kinematic = j["isKinematic"];
    }
    if (j.contains("inertiaDiagonal"))
    {
        inertia_diagonal = j["inertiaDiagonal"];
    }
}