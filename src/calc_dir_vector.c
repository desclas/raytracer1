#include "../framebuffer.h"

sfVector3f calc_dir_vector(float dist_to_plane, sfVector2i screen_size, sfVector2i screen_pos)
{
  sfVector3f res;

  res.x = dist_to_plane;
  res.y = (screen_size.x / 2) - screen_pos.x;
  res.z = (screen_size.y / 2) - screen_pos.y;
  return (res);
}
