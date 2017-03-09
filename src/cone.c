#include "framebuffer.h"

float intersect_cone(sfVector3f eye_pos,
		     sfVector3f dir_vector, float semiangle)
{
  double a;
  double b;
  double c;
  float s;
  
  semiangle = pow(tan((M_PI * semiangle) / 180), 2);
  a = pow(dir_vector.x, 2) + pow(dir_vector.y, 2)
    - pow(dir_vector.z, 2) * semiangle;
  b = 2 * (eye_pos.x * dir_vector.x + eye_pos.y * dir_vector.y
	   - eye_pos.z * dir_vector.z * semiangle);
  c = (pow(eye_pos.x, 2) + pow(eye_pos.y, 2))
    - (pow(eye_pos.z, 2) * semiangle);
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
