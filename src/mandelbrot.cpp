#include <SDL2/SDL_mouse.h>
#include <complex>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <algorithm>
#include <iostream>
#include <vector>

#include "Math.hpp"
#include "RenderWindow.hpp"

#ifdef Fullscreen

SDL_DisplayMode DM;
int width = DM.w;
int height = height;

#else
int width = 800;
int height = 800;
#endif

Math math;

int iterations = 100;
long double zoomFactor = 0.5;
long double centerx;
long double centery;
long double leftBoundary;
long double rightBoundary;
long double topBoundary;
long double bottomBoundary;

int mousex, mousey;
std::complex<long double> startPoint(-1.99977406013629035931268075596,
                                     -0.00000000329004032147943505349697);

void renderMandelbrot(bool isZooming, int mousex, int mousey,
                      RenderWindow window, int fractal) {
  if (isZooming) {
    centerx =
        (float)mousex / width * (rightBoundary - leftBoundary) + leftBoundary;
    centery =
        (float)mousey / height * (bottomBoundary - topBoundary) + topBoundary;
  } else {
    centerx = 0;
    centery = 0;
  }

  leftBoundary = centerx - 1 / zoomFactor;
  rightBoundary = centerx + 1 / zoomFactor;
  topBoundary = centery - 1 / zoomFactor;
  bottomBoundary = centery + 1 / zoomFactor;

  //    leftBoundary = std::real(startPoint) - 1/zoomFactor;
  //    rightBoundary = std::real(startPoint) + 1/zoomFactor;
  //    topBoundary = std::imag(startPoint) - 1/zoomFactor;
  //    bottomBoundary = std::imag(startPoint) + 1/zoomFactor;
  std::vector<int> values = {};
  int value;
  float ratio;
  for (int j = 0; j <= height; j += 1) {
    for (int i = 0; i <= width; i += 1) {
      long double x = leftBoundary + (rightBoundary - leftBoundary) * i / width;
      long double y = topBoundary + (bottomBoundary - topBoundary) * j / height;

      // Check if the point is in the Mandelbrot set
      std::complex<double> eingabe(x, y);
      if (fractal == 0) {
        value = math.checkifinmandel(eingabe, iterations, 30);
        ratio = ((float)value / iterations);
      } else {
        value = math.generalNewtonFractalRecursive(eingabe, fractal - 1, 30);
        ratio = value / ((float)math.roots[0].size());
      }

      int valuehue = 1;
      if (value == 0) {
        valuehue = 0;
      }
      float hue = (180 + (60 * (float)ratio));

      window.draw(i, j, (int)hue, valuehue);
    }
  }
  window.display();
  window.clear();
}
typedef struct Vector2d {
  float x;
  float y;
} vectorf;

typedef struct Vector2di {
  int x;
  int y;
} vectori;
int count = 10;

int main(int argc, char *argv[]) {
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
  // std::cout << nullstelle.x << " " << nullstelle.y << std::endl;
  bool shown = false;
  int fractal = 0;
  if (argc > 1) {
    std::istringstream ss(argv[1]);
    if (!(ss >> fractal)) {
      std::cerr << "Invalid number: " << argv[1] << '\n';
    } else if (!ss.eof()) {
      std::cerr << "Trailing characters after number: " << argv[1] << '\n';
    }
  }

  window.display();
  while (gameRunning) {
    // zoomFactor += 2;
    // if ((int)((zoomFactor - 0.5)/2) % 100 == 0){
    //     iterations += 1;
    // }
    // renderMandelbrot(true, 0, 0, window);

    if (!shown) {
      renderMandelbrot(false, 0, 0, window, fractal);
      shown = true;
    }

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        gameRunning = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
          zoomFactor *= 4;
          // iterations *= 2;
          SDL_GetMouseState(&mousex, &mousey);
          renderMandelbrot(true, mousex, mousey, window, fractal);
        }
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_f:
          window.ToggleFullscreen();
          break;
        case SDLK_q:
          gameRunning = false;
          break;
        case SDLK_m:
          iterations *= 2;
          renderMandelbrot(true, mousex, mousey, window, fractal);
          break;
        }
      }
      // window.display();
    }
  }
  window.cleanUp();
  // TTF_CloseFont(font32);
  // TTF_CloseFont(font24);
  //	TTF_Quit();

  SDL_Quit();

  return 0;
}
