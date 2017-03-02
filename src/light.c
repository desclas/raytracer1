#include "../framebuffer.h"

float get_light_coef(sfVector3f light_vector, sfVector3f normal_vector)
{
  float coef;

  coef = (light_vector.x * normal_vector.x) +
    (light_vector.y * normal_vector.y) +
    (light_vector.z * normal_vector.z);
  if (coef < 0)
    return (0);
  else
    return (coef);
}
