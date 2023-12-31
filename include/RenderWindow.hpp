#pragma once
#include <SDL2/SDL.h>



class RenderWindow 
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h, bool fullscreen);
	void cleanUp();
	void clear();
	void render(int x, int y);
	void ToggleFullscreen();
	void draw(int x, int y, int hue, int valuehue);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
