#include "CWindow.h"

Image::Image(SDL_Texture* iTexture, int iX, int iY)
  : CTexture(iTexture), XCoor(iX), YCoor(iY), CWidth(0), CHeight(0)
{

}

Image::Image(SDL_Texture* iTexture, int iX, int iY, int iW, int iH)
  : CTexture(iTexture), XCoor(iX), YCoor(iY), CWidth(iW), CHeight(iH)
{
  
}

Image::~Image()
{
  /* if (CTexture)
    delete CTexture; */
}

void Image::render(SDL_Renderer* iRen)
{
  if (CWidth > 0 && CHeight > 0)
    renderTexture(CTexture,iRen,XCoor,YCoor,CWidth,CHeight);
  else
    renderTexture(CTexture,iRen,XCoor,YCoor);
}

AppWindow::AppWindow()
{
  CRunning = false;
  CWindow = NULL;
  CRenderer = NULL;  
  CResPath = getResourcePath();
}

AppWindow::~AppWindow()
{
  /*  if (CWindow)
      delete CWindow;
  if (CRenderer)
  delete CRenderer; */
}

int AppWindow::init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
      logSDLError(std::cerr,"SDL_Init");
      return -1;
    }
  if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
      logSDLError(std::cerr,"IMG_Init");
      SDL_Quit();
      return -5;
    }

  CWindow = SDL_CreateWindow(WINDOW_NAME, 100, 100,
			     SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!CWindow)
    {
      logSDLError(std::cerr,"SDL_Window");
      SDL_Quit();
      return -2;
    }
  CRenderer = SDL_CreateRenderer(CWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!CRenderer)
    {
      SDL_DestroyWindow(CWindow);
      logSDLError(std::cerr,"SDL_Render");
      SDL_Quit();
      return -3;
    }
  if (!loadImages())
    {
      SDL_DestroyWindow(CWindow);
      logSDLError(std::cerr,"loadImages");
      SDL_Quit();
      return -6;
    }
  CRunning = true;
  return 0;
}

void AppWindow::run()
{
  while (isRunning())
    {
      render();
      handleEvents();
    }
    quit();
}

void AppWindow::quit()
{
  SDL_DestroyRenderer(CRenderer);
  SDL_DestroyWindow(CWindow);
  SDL_Quit();
}

bool AppWindow::loadImages()
{
  SDL_Texture* background = loadTexture(CResPath + "window_blue_0.png", CRenderer);
  SDL_Texture* image = loadTexture(CResPath + "borderdecoration.png", CRenderer);
  if (!background || !image)
    {
      SDL_DestroyTexture(background);
      SDL_DestroyTexture(image);
      SDL_DestroyWindow(CWindow);
      SDL_DestroyRenderer(CRenderer);
      SDL_Quit();
      return false;
    }
  CImageList.push_back(Image(background,SCREEN_X_TOP,SCREEN_Y_TOP,SCREEN_WIDTH,SCREEN_HEIGHT));
  CImageList.push_back(Image(image,SCREEN_X_TOP,SCREEN_Y_TOP));
  centreImage(CImageList[1]);
  return true;
}

void AppWindow::render()
{
  SDL_RenderClear(CRenderer);
  for (unsigned i = 0; i < CImageList.size(); i++)
    CImageList[i].render(CRenderer);
  SDL_RenderPresent(CRenderer);
}

void AppWindow::handleEvents()
{
  SDL_Event IEvent;
  while (SDL_PollEvent(&IEvent))
    {
      if (IEvent.type == SDL_QUIT)
	CRunning = false;
      else if (IEvent.type == SDL_KEYDOWN)
	{
	  switch( IEvent.key.keysym.sym )
	    {
	    case SDLK_UP:
	      
	      break;

	    case SDLK_DOWN:
	      
	      break;

	    case SDLK_LEFT:
	      
	      break;

	    case SDLK_RIGHT:
	      
	      break;
	      
	    case SDLK_ESCAPE:
	      CRunning = false;
	      break;
	    }
	}
    }
}

bool AppWindow::isRunning()
{
  return CRunning;
}

void logSDLError(std::ostream &os, const std::string &msg)
{
  os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* iRen)
{
  SDL_Texture* ITexture = IMG_LoadTexture(iRen, file.c_str());
  if (!ITexture)
    logSDLError(std::cerr,"IMG_LoadTexture");
  return ITexture;
}

void renderTexture(SDL_Texture* iTexture, SDL_Renderer* iRen, int iX, int iY, int iW, int iH)
{
  SDL_Rect IRect;
  IRect.x = iX;
  IRect.y = iY;
  IRect.w = iW;
  IRect.h = iH;
  SDL_RenderCopy(iRen, iTexture, NULL, &IRect);
}

void renderTexture(SDL_Texture* iTexture, SDL_Renderer* iRen, int iX, int iY)
{
  int width, height;
  SDL_QueryTexture(iTexture, NULL, NULL, &width, &height);
  renderTexture(iTexture, iRen, iX, iY, width, height);
}

void tileTexture(SDL_Texture* iTexture, SDL_Renderer* iRen, int iX, int iY)
{
  int numXTiles = iX / TILE_SIZE;
  int numYTiles = iY / TILE_SIZE;
  for (unsigned i = 0; i < unsigned(numXTiles * numYTiles) ; i++)
    {
      int coorX = (i % numXTiles) * TILE_SIZE;
      int coorY = (i / numXTiles) * TILE_SIZE;
      renderTexture(iTexture, iRen, coorX, coorY, TILE_SIZE, TILE_SIZE);
    }
}

void centreImage(Image &iImage)
{
  if (iImage.CWidth == 0 || iImage.CHeight == 0)
    SDL_QueryTexture(iImage.CTexture, NULL, NULL, &iImage.CWidth, &iImage.CHeight);
  iImage.XCoor = SCREEN_WIDTH / 2 - iImage.CWidth / 2;
  iImage.YCoor = SCREEN_HEIGHT / 2 - iImage.CHeight / 2;
}
