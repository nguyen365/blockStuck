#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "RES_PATH.h"
#include "tetrisGame.h"
//#include "CLEAN_UP.h"

#ifndef __APP_WINDOW_H__
#define __APP_WINDOW_H__

const int SCREEN_X_TOP = 0;
const int SCREEN_Y_TOP = 0;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 15;
const int GameWindowMargin = 6;
const int BlockOffset [] = { 15 , 13 };
const int RenderGridWidth = TILE_SIZE * (CGridLength + 1);
const int RenderGridHeight = TILE_SIZE * (CGridHeight);
const char WINDOW_NAME [] = "blockStuck";
const char BLOCK_FOLDER [] = "colorblocks/";
const std::string IMAGE_NAMES [] = { "window_blue_0.png", "borderdecoration.png", "BlankValentinesPanel.png",
				     std::string(BLOCK_FOLDER) + "lightblue.png",
				     std::string(BLOCK_FOLDER) + "darkgray.png",
				     std::string(BLOCK_FOLDER) + "purple.png",
				     std::string(BLOCK_FOLDER) + "green.png",
				     std::string(BLOCK_FOLDER) + "red2.png",
				     std::string(BLOCK_FOLDER) + "blue.png",
				     std::string(BLOCK_FOLDER) + "orange.png",
				     "NULL"};
const char END_NAME [] = "NULL";
enum TextureName {TBackground, TBorderDecoration, TGameWindow, TBlock, EndTBlock = TBlock + 6};
enum ImageName {IBackground, IGameWindow, ICursor};

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
  bool move(int iX, int iY);
  bool set(int iX, int iY);
};

class AppWindow
{
 private:
  bool CRunning;
  SDL_Window* CWindow;
  SDL_Renderer* CRenderer;
  std::vector<Image> CImageList;
  std::vector<SDL_Texture*> CTextureList;
  std::string CResPath;
  SDL_Rect CGameWindow;
  TetrisGame CGame;
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
