#include "include.h"
#include "Display.h"
#include <fstream>
#include <cstdlib>

Display::Display ()
	: _window(nullptr),
		_ctx(nullptr),
		_quit(false)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	setOptions(906, 640, false);
}

Display::~Display ()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

std::string Display::title () const
{
	return "simple shooter";
}

std::ostream& Display::die ()
{
	_died = true;
	_quit = true;
	return _diemsg;
}

void Display::_dump ()
{
	std::ostringstream ss;
	
	std::string sdlerr(SDL_GetError());

	ss << "# An error occured: " << std::endl
	   << "|   " << (_diemsg.str()) << std::endl;

	if (!sdlerr.empty())
		ss << "+ SDL error: " << std::endl
		   << "|   " << SDL_GetError() << std::endl;

	std::cerr << ss.str();
	
	std::ofstream log("log.txt");
	log << ss.str();
	log.close();

	_died = false;
	_diemsg.str("");
}

void Display::setView (std::unique_ptr<View>&& view)
{
	_oldView = std::move(_view);
	_view = std::move(view);
}

void Display::setOptions (int w, int h, bool fs)
{
	if (_window)
	{
		SDL_DestroyWindow(_window);
		SDL_GL_DeleteContext(_ctx);
	}

	_window =
		SDL_CreateWindow(title().c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_width = w, _height = h,
			SDL_WINDOW_SHOWN |
			SDL_WINDOW_OPENGL |
			(fs ? SDL_WINDOW_FULLSCREEN : 0));

	// vsync
	SDL_UpdateWindowSurface(_window);

	if (!_window)
	{
		die() << "unable to create SDL window";
		return;
	}

	// create openGL context
	_ctx = SDL_GL_CreateContext(_window);

	if (!_ctx)
	{
		die() << "unable to create OpenGL context";
		return;
	}

	// initialize GL
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glShadeModel(GL_SMOOTH); 

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);

	glOrtho(0, width(), height(), 0, 0, 1);
}

bool Display::show ()
{
	if (_quit)
	{
		if (_died)
			_dump();
		return false;
	}

	// poll events
	SDL_Event e;
	while (SDL_PollEvent(&e))
		switch (e.type)
		{
		case SDL_QUIT:
			_quit = true;
			return false;

		default:
			break;
		}

	if (!_window)
		return true;

	// update
	
	// draw
	color(.6f, .7f, .9f).glApplyClear();

	color(0, 0, 0).gl();
	glBegin(GL_LINES);
	for (int i = 0; i < 10; i++)
	{
		vec2f(0, math::random(height())).gl();
		vec2f(width(), math::random(height())).gl();
	}
	glEnd();

	SDL_GL_SwapWindow(_window);
	return true;
}
