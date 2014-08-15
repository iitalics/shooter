#include "include.h"
#include "Display.h"

int main (int argc, char** argv)
{
	Display disp;

	while (disp.show())
		;

	return 0;
}
