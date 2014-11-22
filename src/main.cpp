#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "RES_PATH.h"
#include "CWindow.h"

int main(int argc, char** argv)
{
  AppWindow IWindow;
  IWindow.init();
  IWindow.run();
}

int old_main(int argc, char** argv)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
      std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
      return -1;
    }
  std::cout << "Resource Path: " << getResourcePath() << std::endl;
  SDL_Quit();
  return 0;
}
