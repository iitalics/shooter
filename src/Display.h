#pragma once
#include <sstream>

class View;

class Display
{
public:
	Display ();
	~Display ();

	void setOptions (int w, int h, bool fs);

	void setView (std::unique_ptr<View>&& view);
	inline void setView (View* view)
	{
		setView(std::unique_ptr<View>(view));
	}

	bool show ();
	std::ostream& die ();
	inline void quit () { _quit = true; }

	std::string title () const;
	inline int width () const { return _width; }
	inline int height () const { return _height; }
private:
	SDL_Window* _window;
	SDL_GLContext _ctx;

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
