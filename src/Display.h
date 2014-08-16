#pragma once
#include <sstream>

class View;

class Display
{
public:
	enum
	{
		MinFPS = 10,
		MaxFPS = 120,

		DefaultFPS = 60
	};
	Display ();
	~Display ();

	void setOptions (int w, int h, bool fs);
	inline void setFramerate (int fps) { _fps = fps; }

	void setView (std::unique_ptr<View>&& view);
	inline void setView (View* view)
	{
		setView(std::unique_ptr<View>(view));
	}

	bool show ();
	std::ostream& die ();
	inline void quit () { _quit = true; }

	std::string title () const;
	std::string setTitle (const std::string&);
	inline int width () const { return _width; }
	inline int height () const { return _height; }
private:
	std::string _title;
	SDL_Window* _window;
	SDL_GLContext _ctx;

	// timing
	u32 _ticks,
		_accumulate,
		_fps;

	std::unique_ptr<View> _view, _oldView;

	int _width, _height;
	bool _quit;

	bool _died;
	std::ostringstream _diemsg;
	void _dump ();
};


class View
{
public:
	virtual ~View ();

	virtual void update (Display*, float dt);
	virtual void draw (Display*) = 0;
};
