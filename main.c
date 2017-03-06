#include "framebuffer.h"

#define	FRAMEBUFFER_WIDTH 600
#define FRAMEBUFFER_HEIGHT 400

/*
** This main function is provided for the bootstrap of the Raytracer1.
** YOU MUST NOT SUBMIT IT !
**
** Some functions are required for this code to work :
** - All functions of the c_graph_prog library
** - my_framebuffer_create
** - raytrace_scene
** - my_framebuffer_destroy
**
** //// my_framebuffer_create(int width, int height)
** Creates a framebuffer from the width and the height of the frame.
** 
** //// raytrace_scene(t_my_framebuffer *framebuffer)
** Launches rays and fills the framebuffer with the proper color for 
** every pixels.
** The frame is static so the function only needs to be called once at
** the beginning of the program (as it currently is).
**
** //// my_framebuffer_destroy(t_my_framebuffer *framebuffer)
** Frees the space allocated to the framebuffer.
*/

int	main()
{
  sfVideoMode		mode = {FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, 32};
  sfRenderWindow*	window;
  sfTexture*		texture;
  sfSprite*		sprite;

  t_my_framebuffer	*framebuffer;

  /* Create the main window */
  window = sfRenderWindow_create(mode, "Bootstrap Raytracer 1",
				 sfResize | sfClose, NULL);
  if (!window)
    return EXIT_FAILURE;
  /* Load a sprite to display */
  texture = sfTexture_create(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
  if (!texture)
    return EXIT_FAILURE;
  sprite = sfSprite_create();
  sfSprite_setTexture(sprite, texture, sfTrue);

  /* Create a framebuffer to store pixels in */
  framebuffer = my_framebuffer_create(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);

  /* Raytrace the scene and start game loop */
  raytrace_scene(framebuffer);
  sfTexture_updateFromPixels(texture, framebuffer->pixels,
			     framebuffer->width, framebuffer->height,
			     0,0);
  process_game_loop(window, sprite);

  /* Destroy resources */
  my_framebuffer_destroy(framebuffer);
  sfSprite_destroy(sprite);
  sfTexture_destroy(texture);
  sfRenderWindow_destroy(window);
  return EXIT_SUCCESS;
}

int		process_game_loop(sfRenderWindow *window, sfSprite *sprite)
{
  sfEvent	event;

  /* Start the game loop */
  while (sfRenderWindow_isOpen(window))
    {
      /* Process events */
      while (sfRenderWindow_pollEvent(window, &event))
        {
	  /* Close window : exit */
	  if (event.type == sfEvtClosed)
	    sfRenderWindow_close(window);
        }
      /* Clear the screen */
      sfRenderWindow_clear(window, sfBlack);
      /* Draw the sprite */
      sfRenderWindow_drawSprite(window, sprite, NULL);
      /* Update the window */
      sfRenderWindow_display(window);
    }
}
