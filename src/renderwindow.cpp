#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <string>

#include "RenderWindow.hpp"

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;

static hsv   rgb2hsv(rgb in);
static rgb   hsv2rgb(hsv in);
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h, bool fullscreen)
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

    if (fullscreen) {
	    ToggleFullscreen();
    }
	SDL_ShowCursor(1);

	}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::draw(int x, int y, int hue, int valuehue) {
    hsv hsv;
    hsv.h = hue;
    hsv.s = 1;
    hsv.v = valuehue;
    rgb rgb = hsv2rgb(hsv);
    if (valuehue == 0) {
        rgb.r = 0;
        rgb.g = 0;
        rgb.b = 0;
    } 
    SDL_SetRenderDrawColor(renderer, 0,rgb.b*255,rgb.g*255, 255);
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



hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0              
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = NAN;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}


rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}
