#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "RES_PATH.h"
//#include "CLEAN_UP.h"

#ifndef __APP_WINDOW_H__
#define __APP_WINDOW_H__

const int SCREEN_X_TOP = 0;
const int SCREEN_Y_TOP = 0;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;
const char WINDOW_NAME [] = "blockStuck";

struct Image
{
  SDL_Texture* CTexture;
  int XCoor;
  int YCoor;
  int CWidth;
  int CHeight;
  Image(SDL_Texture* iTexture, int iX, int iY);
  Image(SDL_Texture* iTexture, int iX, int iY, int iW, int iH);
  ~Image();
  void render(SDL_Renderer* iRen);
};

class AppWindow
{
 private:
  bool CRunning;
  SDL_Window* CWindow;
  SDL_Renderer* CRenderer;
  std::vector<Image> CImageList;
  std::string CResPath;
 public:
  AppWindow();
  ~AppWindow();
  int init();
  void run();
  void quit();
  bool isRunning();
 private:
  bool loadImages();
  void render();
  void handleEvents();
};

void logSDLError(std::ostream &os, const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* iRen);
void renderTexture(SDL_Texture* iTexture, SDL_Renderer* iRen, int iX, int iY);
void renderTexture(SDL_Texture* iTexture, SDL_Renderer* iRen, int iX, int iY, int iW, int iH);
void tileTexture(SDL_Texture* iTexture, SDL_Renderer* iRen, int iX, int iY);
void centreImage(Image &iImage);

#endif
