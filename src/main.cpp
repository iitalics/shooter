#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

enum Dim
{
	Width = 960,
	Height = 640
};

static void init ();
static void draw ();
static void update (float);

int main (int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	auto window =
		SDL_CreateWindow("simple game",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			Dim::Width, Dim::Height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	
	if (!window)
		return (std::cerr << "unable to create window!" << std::endl
		                  << " SDL error: " << SDL_GetError() << std::endl),
			-1;
	
	
	auto ctx = SDL_GL_CreateContext(window);
	
	if (!ctx)
		return (std::cerr << "unable to create GL context!" << std::endl
		                  << " SDL error: " << SDL_GetError() << std::endl),
			-1;
	
	if (SDL_GL_SetSwapInterval(1))
		std::cerr << "warning: vsync unavailable" << std::endl;
	
	SDL_Event e;
	
	init();
	
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
		
		draw();
		SDL_GL_SwapWindow(window);
	}
quit:
	
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}

static void init ()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void draw ()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
		glVertex2f(-.5f, .5f);
		glVertex2f(.5f, .5f);
	glEnd();
	
	
}

static void update (float dt)
{
}