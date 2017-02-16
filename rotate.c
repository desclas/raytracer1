#include "framebuffer.h"

sfVector3f rotate_xyz(sfVector3f to_rotate, sfVector3f angles)
{
  sfVector3f res;
  sfVector3f save;

  angles.x = (M_PI * angles.x) / 180;
  angles.y = (M_PI * angles.y) / 180;
  angles.z = (M_PI * angles.z) / 180;
  res.x = to_rotate.x;
  res.y = to_rotate.y * cos(angles.x) + (0 - sin(angles.x)) * to_rotate.z;
  res.z = to_rotate.y * sin(angles.x) + to_rotate.z * cos(angles.x);
  save = res;
  res.x = save.x * cos(angles.y) + save.z * sin(angles.y);
  res.z = (0 - sin(angles.y)) * save.x + cos(angles.y) * save.z;
  save = res;
  res.x = cos(angles.z) * save.x + (0 - sin(angles.z)) * save.y;
  res.y = sin(angles.z) * save.x + cos(angles.z) * save.y;
  return (res);
}

sfVector3f rotate_zyx(sfVector3f to_rotate, sfVector3f angles)
{
  sfVector3f res;
  sfVector3f save;

  angles.x = (M_PI * angles.x) / 180;
  angles.y = (M_PI * angles.y) / 180;
  angles.z = (M_PI * angles.z) / 180;
  res.x = cos(angles.z) * to_rotate.x + (0 - sin(angles.z)) * to_rotate.y;
  res.y = sin(angles.z) * to_rotate.x + cos(angles.z) * to_rotate.y;
  res.z = to_rotate.z;
  save = res;
  res.x = cos(angles.y) * save.x + sin(angles.y) * save.z;
  res.z = (0 - sin(angles.y)) * save.x + cos(angles.y) * save.z;
  save = res;
  res.y = cos(angles.x) * save.y + (0 - sin(angles.x)) * save.z;
  res.z = sin(angles.x) * save.y + cos(angles.x) * save.z;
  return (res);
}
