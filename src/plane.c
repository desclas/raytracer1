#include "framebuffer.h"

float intersect_plane(sfVector3f eye_pos, sfVector3f dir_vector)
{
  float s;
  
  if (dir_vector.x == 0)
    return (-1);
  s = (-(eye_pos.z) / dir_vector.z);
  if (s < 0)
    return (-1);
  else
    return (s);
}

sfVector3f get_normal_plane(int upward)
{
  sfVector3f res;

  res.x = 0;
  res.y = 0;
  res.z = upward;
  return (res);
}
