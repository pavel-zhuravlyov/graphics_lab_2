#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void clear(float r, float g, float b, float a);
	void swapBuffers();

	~Display();

private:
	SDL_Window* window;
	SDL_GLContext glContext;
};

#endif
