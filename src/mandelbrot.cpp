#include <SDL2/SDL_mouse.h>
#include <complex>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <vector>
#include <iostream>

#include "RenderWindow.hpp"
#include "Math.hpp"

#ifdef Fullscreen

SDL_DisplayMode DM;
int width = DM.w;
int height = height;

#else
int width = 800;
int height = 800;
#endif


Math math;


int iterations = 75;
long double zoomFactor = 0.5;
long double centerx;
long double centery;
long double leftBoundary;
long double rightBoundary;
long double topBoundary;
long double bottomBoundary;



int mousex, mousey;
std::complex<long double> startPoint(-1.99977406013629035931268075596, -0.00000000329004032147943505349697);


void renderMandelbrot(bool isZooming, int mousex, int mousey, RenderWindow window) {
    if (isZooming) {
        centerx = (float)mousex/width * (rightBoundary - leftBoundary) + leftBoundary; 
        centery = (float)mousey/height * (bottomBoundary - topBoundary) + topBoundary; 
    } else {
        centerx = 0;
        centery = 0;
    }

    // leftBoundary = centerx - 1/zoomFactor;
    // rightBoundary = centerx + 1/zoomFactor;
    // topBoundary = centery - 1/zoomFactor;
    // bottomBoundary = centery + 1/zoomFactor;

    leftBoundary = std::real(startPoint) - 1/zoomFactor;
    rightBoundary = std::real(startPoint) + 1/zoomFactor;
    topBoundary = std::imag(startPoint) - 1/zoomFactor;
    bottomBoundary = std::imag(startPoint) + 1/zoomFactor;
    for (int j = 0; j <= height; j+=1) {
        for (int i = 0; i <= width; i += 1) {
            long double x = leftBoundary + (rightBoundary - leftBoundary) * i / width;
            long double y = topBoundary + (bottomBoundary - topBoundary) * j / height;

            // Check if the point is in the Mandelbrot set
            std::complex<double> eingabe(x, y);
            std::complex<double> value = math.checkifinmandel(eingabe, eingabe, iterations, iterations);

                // Draw the point on the screen
                int hue = (int)(360*std::imag(value)/iterations);

                
                int valuehue = 1;
                 
                window.draw(i, j, hue, valuehue);
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
    #ifdef Fullscreen
    SDL_GetCurrentDisplayMode(0, &DM);
    RenderWindow window("Mandelbrot", width, height, true);
    #else
    RenderWindow window("Mandelbrot", width, height, false);
    #endif

    bool gameRunning = true;

    SDL_Event event;
    //std::cout << nullstelle.x << " " << nullstelle.y << std::endl;
    bool shown = false;

    window.display();
    while (gameRunning) {
        zoomFactor += 2;
        if ((int)((zoomFactor - 0.5)/2) % 100 == 0){
            iterations += 1;
        }
        renderMandelbrot(true, 0, 0, window);
        
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
                        //iterations *= 2;
                        SDL_GetMouseState(&mousex, &mousey);
                        renderMandelbrot(true, mousex, mousey, window);

                    }
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_f:  window.ToggleFullscreen(); break;
                        case SDLK_q: gameRunning = false; break;
                        case SDLK_m: iterations*=2; renderMandelbrot(true, mousex, mousey, window); break;
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
