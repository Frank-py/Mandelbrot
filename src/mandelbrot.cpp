#include <SDL2/SDL_mouse.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <vector>
#include <iostream>

#include "RenderWindow.hpp"
#include "Math.hpp"

void zoom() {
}

SDL_DisplayMode DM;
Math math;

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
    vectori nullstelle = {DM.w/2, DM.h/2};
    RenderWindow window("Mandelbrot", DM.w, DM.h);
    bool gameRunning = true;

    SDL_Event event;
    //std::cout << nullstelle.x << " " << nullstelle.y << std::endl;
    bool shown = false;

    int zoom = 2;
    window.display();
    while (gameRunning) {
        if (!shown) {
            for (double j = 0; j <= DM.h; j+=1) {
                for (double i = 0; i <= (int)(DM.h*3/2); i += 1) {
                    float x = i/(int)(DM.h*3/2) * 3.0 - 2.0;
                    float y = j/DM.h * 2.0 - 1.0;
                    std::complex<double> eingabe (x, y);
                    std::complex<double> value = math.checkifinmandel(eingabe, eingabe, 75);	
                    if (real(value) == 1.0) {
                        window.draw(i+(int)(DM.w/4), j); 
                    }
                }
            }
            window.display();
            window.clear();
        }
        shown = true;
        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_QUIT:
                    gameRunning = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int mousex, mousey;
                        double pointx, pointy;
                        SDL_GetMouseState(&mousex, &mousey);
                        pointy = float(mousey)/float(DM.h) * 2 - 1;
                        pointx = float((mousex-(float)DM.w/4)/float((float)DM.h*3/2)) * 3 - 2;
                        // I now want to zoom into the points where pointx and pointy are the center of the screen and zoom is the zoom factor.
                        for (double j = 0; j <= DM.h; j+=1) {
                            for (double i = 0; i <= (int)(DM.h*3/2); i += 1) {
                                float x = i/(int)(DM.h*3/2) * 3.0 - 2.0;
                                float y = j/DM.h * 2.0 - 1.0;
                                std::complex<double> eingabe (x, y);
                                std::complex<double> value = math.checkifinmandel(eingabe, eingabe, 75);	
                                if (real(value) == 1.0) {
                                    window.draw(i+(int)(DM.w/4), j); 
                                }
                            }
                        }
                       


                        // window.display();
                        // window.clear();
                        
                    }
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_f:  window.ToggleFullscreen(); break;
                        case SDLK_q: gameRunning = false; break;
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
