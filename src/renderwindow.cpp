#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)  
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Clear the entire screen to our selected color.
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);


//	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//	SDL_RenderPresent(renderer);
//	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

	// Todo
	//SDL_Surface* icon = IMG_Load("bin/debug/res/gfx/icon.png");
	//SDL_SetWindowIcon(window, icon);


	ToggleFullscreen();
	SDL_ShowCursor(1);

	}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::draw(int x, int y) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
	SDL_RenderDrawPoint(renderer, x, y);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
}

void RenderWindow::clear()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
}
void RenderWindow::render(int x, int y)
{
	// SDL_Rect src; 
	// src.x = p_entity.getCurrentFrame().x;
	// src.y = p_entity.getCurrentFrame().y;
	// src.w = p_entity.getCurrentFrame().w;
	// src.h = p_entity.getCurrentFrame().h;

	// SDL_Rect dst;
	// dst.x = p_entity.getPos().x - offset.x;
	// dst.y = p_entity.getPos().y - offset.y;
	// dst.w = p_entity.getCurrentFrame().w * 4;
	// dst.h = p_entity.getCurrentFrame().h * 4;

	// SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}


void RenderWindow::ToggleFullscreen() {
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, IsFullscreen ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);
}
