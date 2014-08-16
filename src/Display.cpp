#include "include.h"
#include "Display.h"
#include <fstream>
#include <cstdlib>

Display::Display ()
	: _title("simple thing"),
		_window(nullptr),
		_ctx(nullptr),
		_ticks(0), _accumulate(0), _fps(DefaultFPS),
		_quit(false)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	setOptions(1240, 680, false);
}

Display::~Display ()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

std::string Display::title () const
{
	return _title;
}
std::string Display::setTitle (const std::string& t)
{
	if (_window)
		SDL_SetWindowTitle(_window, t.c_str());
	
	return _title = t;
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
		   << "|   " << sdlerr << std::endl;

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
		SDL_CreateWindow(_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_width = w, _height = h,
			SDL_WINDOW_SHOWN |
			SDL_WINDOW_OPENGL |
			(fs ? SDL_WINDOW_FULLSCREEN : 0));

	if (!_window)
	{
		die() << "unable to create SDL window";
		return;
	}

	// vsync
	SDL_GL_SetSwapInterval(1);
	
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

	bool up = true; //false;

	// poll events
	SDL_Event e;
	while (SDL_PollEvent(&e))
		switch (e.type)
		{
		case SDL_QUIT:
			_quit = true;
			return false;

		case SDL_USEREVENT:
			up = true;
			break;

		default:
			break;
		}

	if (!_window)
		return true;
	
	if (up)
	{
		// get delta time
		u32 now = SDL_GetTicks();
		u32 diff = now - _ticks;
		_ticks = now;

		// eliminate unusual errors
		if (diff > (1000 / MinFPS))
			diff = 1000 / MinFPS;
		else if (diff == 0)
		 	diff = 1000 / MaxFPS;


		const u32 desired_diff = 1000 / _fps;
		
		if (_view != nullptr)
		{
			_accumulate += diff;
			while (_accumulate >= desired_diff)
			{
				_view->update(this, 1.f / _fps);
				_accumulate -= desired_diff;
			}
			_view->draw(this);
		}
		else
			color(.5f, .8f, 1.f).glApplyClear();
	}

	SDL_GL_SwapWindow(_window);
	SDL_Delay(2);
	return true;
}


View::~View () {}
void View::update (Display* disp, float dt) {}
