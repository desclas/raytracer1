#include "framebuffer.h"

float one_sol(double a, double b)
{
  float sol;

  sol = (0 - b) / (2 * a);
  if (sol < 0)
    return (-1);
  else
    return (sol);
}

float two_sol(double a, double b, float s)
{
  float s2;

  s2 = ((0 - b) + sqrt(s)) / (2 * a);
  s = ((0 - b) - sqrt(s)) / (2 * a);
  if (s2 < 0 && s < 0)
    return (-1);
  else if (s2 >= 0 && s < 0)
    return (s2);
  else if (s2 < 0 && s >= 0)
    return (s);
  else
    {
      if (s2 < s)
	return (s2);
      else
	return (s);
    }
}

float intersect_sphere(sfVector3f eye_pos, sfVector3f dir_vector, float radius)
{
  double a;
  double b;
  double c;
  float s;

  a = pow(dir_vector.x, 2) + pow(dir_vector.y, 2) + pow(dir_vector.z, 2);
  b = 2 * ((eye_pos.x * dir_vector.x) + (eye_pos.y * dir_vector.y) + (eye_pos.z * dir_vector.z));
  c = pow(eye_pos.x, 2) + pow(eye_pos.y, 2) + pow(eye_pos.z, 2) - pow(radius, 2);
  s = pow(b, 2) - (4 * a * c);
  if (s < 0)
    return (-1);
  else if (s == 0)
    return (one_sol(a, b));
  else
    return (two_sol(a, b, s));
}

sfVector3f get_normal_sphere(sfVector3f intersection_point)
{
  return (intersection_point);
}
