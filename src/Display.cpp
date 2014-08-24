#include "include.h"
#include "Display.h"
#include <fstream>
#include <algorithm>
#include <cstdlib>

Display::Display ()
	: _title("simple thing"),
		_window(nullptr),
		_ctx(nullptr),
		_time(_now()), _accumulate(0), _fps(DefaultFPS),
		_quit(false)
{
	SDL_Init(SDL_INIT_VIDEO);
	//SDL_CaptureMouse(false);
	
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
vec2f Display::mouse () const
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	return vec2f(x, y);
}
bool Display::mouseButton (Button b) const
{
	u32 state = SDL_GetMouseState(nullptr, nullptr);
	u32 mask =
		(b == Button::Left)   ? SDL_BUTTON(SDL_BUTTON_LEFT) : 
		(b == Button::Right)  ? SDL_BUTTON(SDL_BUTTON_RIGHT) :
		(b == Button::Middle) ? SDL_BUTTON(SDL_BUTTON_MIDDLE) : 0;

	return state & mask;
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

void Display::setView (std::unique_ptr<View> view)
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

	if (!_window)
		return true;

	// poll events
	SDL_Event e;
	while (SDL_PollEvent(&e))
		switch (e.type)
		{
		case SDL_QUIT:
			quit();
			return false;

		case SDL_KEYDOWN:
			_pressed(e.key.keysym.sym);
			break;

		case SDL_KEYUP:
			_released(e.key.keysym.sym);
			break;
		
		default:
			break;
		}

	// get delta time
	tick_t now = _now();
	tick_t diff = now - _time;
	_time = now;

	// eliminate unusual framerate errors (dragging, etc)
	if (diff > (tick_s / MinFPS))
		diff = tick_s / MinFPS;
	else if (diff == 0)
		diff = tick_s / MaxFPS;

	// constant framerate for update()
	const tick_t desired_diff = tick_s / _fps;
	int frames = 0;

	if (_view != nullptr)
	{
		_accumulate += diff;
		while (_accumulate >= desired_diff)
		{
			try
			{
				_view->update(this, 1.f / _fps);
				frames++;
			}
			catch (std::exception& e)
			{
				die() << e.what();
				return false;
			}

			_accumulate -= desired_diff;

			// expire old keys states
			for (key_state& ks : _keys)
				ks.expire();
		}
#ifdef NO_FRAME_SKIP
		if (_accumulate > 0)
		{
			frames++;
			_view->update(this, _accumulate / (float)tick_s);
			_accumulate = 0;
		}
#endif
		_view->draw(this);
	}
	else
		color(.5f, .8f, 1.f).glApplyClear();

	SDL_GL_SwapWindow(_window);

	
	/* const double sleep_s = 1.0 / 100.0;
	const time_t sleep_t = time_t(tick_s * sleep_s);
	auto n = _now();
	while ((_now() - n) < sleep_t)
		; */

	SDL_Delay(6);

	return true;
}

Display::tick_t Display::_now ()
{
	return std::chrono::duration_cast<interval_t>(
			clock::now().time_since_epoch()).count();
}



bool Display::keyDown (SDL_Keycode k)
{
	for (auto& ks : _keys)
		if (ks.key == k)
			return true;
	return false;
}
bool Display::keyPressed (SDL_Keycode k)
{
	for (auto& ks : _keys)
		if (ks.key == k)
			return ks.first;

	return false;
}

void Display::_pressed (SDL_Keycode key)
{
	for (auto& ks : _keys)
		if (ks.key == key)
			return;
	
	_keys.emplace_back(key);
}
void Display::_released (SDL_Keycode key)
{
	_keys.erase(std::find_if(_keys.begin(), _keys.end(),
					[key] (key_state& ks)
					{
						return ks.key == key;
					}));
}
void Display::key_state::expire ()
{
	if (first)
		first = false;
}



View::~View () {}
void View::update (Display* disp, float dt) {}
