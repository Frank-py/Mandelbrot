#include <SDL2/SDL_mouse.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <vector>
#include <iostream>

#include "RenderWindow.hpp"
#include "Math.hpp"


SDL_DisplayMode DM;
Math math;


int iterations = 75;
double zoomFactor = 0.5;
double centerx;
double centery;
double leftBoundary;
double rightBoundary;
double topBoundary;
double bottomBoundary;



int mousex, mousey;


void renderMandelbrot(bool isZooming, int mousex, int mousey, RenderWindow window) {
    if (isZooming) {
        centerx = (float)mousex/DM.w * (rightBoundary - leftBoundary) + leftBoundary; 
        centery = (float)mousey/DM.h * (bottomBoundary - topBoundary) + topBoundary; 
    } else {
        centerx = 0;
        centery = 0;
    }

    leftBoundary = centerx - 1/zoomFactor;
    rightBoundary = centerx + 1/zoomFactor;
    topBoundary = centery - 1/zoomFactor;
    bottomBoundary = centery + 1/zoomFactor;
    for (double j = 0; j <= DM.h; j+=1) {
        for (double i = 0; i <= DM.w; i += 1) {
            double x = leftBoundary + (rightBoundary - leftBoundary) * i / DM.w;
            double y = topBoundary + (bottomBoundary - topBoundary) * j / DM.h;

            // Check if the point is in the Mandelbrot set
            std::complex<double> eingabe(x, y);
            std::complex<double> value = math.checkifinmandel(eingabe, eingabe, 75);

            if (std::real(value) == 1.0) {
                // Draw the point on the screen
                window.draw(i, j);
            }
        }
    }
    window.display();
    window.clear();
}
typedef struct Vector2d 
{
    float x;
    float y;
}vectorf;

typedef struct Vector2di
{
    int x;
    int y;
}vectori;
int count = 10;


int main (int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cerr << "Couldn't initialize SDL2" << std::endl;
        return 1;
    } 

    SDL_GetCurrentDisplayMode(0, &DM);
    RenderWindow window("Mandelbrot", DM.w, DM.h);
    bool gameRunning = true;

    SDL_Event event;
    //std::cout << nullstelle.x << " " << nullstelle.y << std::endl;
    bool shown = false;

    window.display();
    while (gameRunning) {
        if (!shown) {
            renderMandelbrot(false, 0, 0, window);
            shown = true;
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_QUIT:
                    gameRunning = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        zoomFactor *= 4;
                        iterations *= 2;
                        SDL_GetMouseState(&mousex, &mousey);
                        renderMandelbrot(true, mousex, mousey, window);

                    }
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_f:  window.ToggleFullscreen(); break;
                        case SDLK_q: gameRunning = false; break;
                        case SDLK_PLUS: iterations*=2; renderMandelbrot(true, mousex, mousey, window); break;
                    }
            }
            //window.display();
        }

    }
    window.cleanUp();
    // TTF_CloseFont(font32);
    // TTF_CloseFont(font24);
    //	TTF_Quit();

    SDL_Quit();

    return 0;
}
