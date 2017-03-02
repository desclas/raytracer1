#include "../framebuffer.h"

float intersection_cone(sfVector3f eye_pos,
			sfVector3f dir_vector, float semiangle)
{
  double a;
  double b;
  double c;
  float s;

  semiangle = (M_PI * semiangle) / 180;
  a = (pow(tan(semiangle), 2) * (pow(dir_vector.x, 2) + pow(dir_vector.y, 2)))
    - pow(dir_vector.z, 2);
  b = (pow(tan(semiangle), 2) *
       ((2 * eye_pos.x * dir_vector.x) + (2 * eye_pos.y * dir_vector.y)))
    - (2 * eye_pos.z * dir_vector.z);
  c = (pow(tan(semiangle), 2) * (pow(eye_pos.x, 2) + pow(eye_pos.y, 2)))
    - pow(eye_pos.z, 2);
  s = pow(b, 2) - (4 * a * c);
  if (s < 0)
    return (-1);
  else if (s == 0)
    return (one_sol(a, b));
  else
    return (two_sol(a, b, s));
}

sfVector3f get_normal_cone(sfVector3f intersection_point, float semiangle)
{
  intersection_point.z *= (0 - pow(tan((M_PI * semiangle) / 180), 2));
  return (intersection_point);
}
