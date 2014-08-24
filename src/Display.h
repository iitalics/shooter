#pragma once
#include <sstream>
#include <list>
#include <chrono>

class View;

enum class Button
{
	Left, Right, Middle
};

class Display
{
public:
	enum
	{
		MinFPS = 10,
		MaxFPS = 200,
		DefaultFPS = 60
	};
	
	Display ();
	~Display ();

	// fields
	inline int width () const { return _width; }
	inline int height () const { return _height; }
	inline void setFramerate (int fps) { _fps = fps; }

	// properties
	std::string title () const;
	std::string setTitle (const std::string&);
	void setView (std::unique_ptr<View> view);
	inline void setView (View* view)
	{
		setView(std::unique_ptr<View>(view));
	}
	vec2f mouse () const;
	bool mouseButton (Button b = Button::Left) const;

	bool keyDown (SDL_Keycode k);
	bool keyPressed (SDL_Keycode k); // just pressed this frame
	
	// actions
	inline void quit () { _quit = true; }
	void setOptions (int w, int h, bool fs);
	std::ostream& die ();
	bool show ();

private:
	// SDL context
	std::string _title;
	SDL_Window* _window;
	SDL_GLContext _ctx;

	// timing
	using interval_t = std::chrono::milliseconds;
	using clock = std::chrono::high_resolution_clock;
	using tick_t = interval_t::rep;
	static tick_t constexpr tick_s =
		interval_t::period::den;

	tick_t _time,
		   _accumulate,
		   _fps;

	static tick_t _now ();

	// views
	std::unique_ptr<View> _view, _oldView;

	// window information
	int _width, _height;
	bool _quit;
	bool _died;

	// error catching
	std::ostringstream _diemsg;
	void _dump ();

	// keys
	struct key_state
	{
		inline key_state (SDL_Keycode k)
			: first(true), key(k) {}
		
		void expire ();

		bool first;
		SDL_Keycode key;
	};
	std::list<key_state> _keys;
	void _pressed (SDL_Keycode key);
	void _released (SDL_Keycode key);
};


class View
{
public:
	virtual ~View ();

	virtual void update (Display*, float dt);
	virtual void draw (Display*) = 0;
};
