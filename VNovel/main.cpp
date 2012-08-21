#include "SDL.h"
#include "Scene.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <stdlib.h>

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;
const char* WINDOW_TITLE = "Duncan";

int main(int argc, char **argv)
{
	SDL_Init( SDL_INIT_VIDEO );

	TTF_Init();

    SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, 
      SDL_HWSURFACE | SDL_DOUBLEBUF );
    SDL_WM_SetCaption( WINDOW_TITLE, 0 );
    SDL_Event event;

	Uint8 *oldkeystates = NULL;
	
    bool gameRunning = true;

	Scene scene;

    while (gameRunning)
	{
		if (SDL_PollEvent(&event))
		{ 
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			else  if( event.type == SDL_KEYDOWN )
            {
				switch( event.key.keysym.sym )
                {
					case SDLK_SPACE:
  						scene.Run();
						break;
				}
			}
		}

		oldkeystates = SDL_GetKeyState( NULL );
   
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 150, 150));

		scene.Draw(screen);

		SDL_Flip(screen);
	}

    SDL_Quit();

	return 0;

}