#include "include.h"
#include "Display.h"
#include "GameView.h"

int main (int argc, char** argv)
{
	Display disp;
	disp.setFramerate(60);
	disp.setView(new GameView());

	while (disp.show())
		;

	return 0;
}
