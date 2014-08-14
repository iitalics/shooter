#include <SDL2/SDL.h>

int main (int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	auto window =
		SDL_CreateWindow("Hello, world",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			960, 640,
			SDL_WINDOW_OPENGL);
	
	SDL_Event e;
	
	for (;;)
	{
		while (SDL_PollEvent(&e))
			switch (e.type)
			{
			case SDL_QUIT:
				goto quit;
			
			default:
				break;
			}
	}
quit:
	
	SDL_Quit();
	
	return 0;
}