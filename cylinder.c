#include "framebuffer.h"

float intersection_cylinder(sfVector3f eye_pos, sfVector3f dir_vector,
			    float radius)
{
  double a;
  double b;
  double c;
  float s;

  a = pow(dir_vector.x, 2) + pow(dir_vector.y, 2);
  b = 2 * ((eye_pos.x * dir_vector.x) + (eye_pos.y * dir_vector.y));
  c = pow(eye_pos.x, 2) + pow(eye_pos.y, 2) - pow(radius, 2);
  s = pow(b, 2) - (4 * a * c);
  if (s < 0)
    return (-1);
  else if (s == 0)
    return (one_sol(a, b));
  else
    return (two_sol(a, b, s));
}

sfVector3f get_normal_cylinder(sfVector3f intersection_point)
{
  intersection_point.z = 0;
  return (intersection_point);
}
