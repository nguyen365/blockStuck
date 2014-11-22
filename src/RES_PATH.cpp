#include "RES_PATH.h"

std::string getResourcePath(const std::string &subDir)
{
  //  #ifndef _WIN32_
  //  const char PATH_SEP = '\\';
  //  #else
  const char PATH_SEP = '/';
  //  #endif

  static std::string baseRes;
  if (baseRes.empty())
    {
      char *basePath = SDL_GetBasePath();
      if (basePath)
	{
	  baseRes = basePath;
	  SDL_free(basePath);
	}
      else
	{
	  std::cerr << "Error getting resourcce path: " << SDL_GetError() << std::endl;
	  return "";
	}
      size_t pos = baseRes.rfind("bin");
      baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
    }
  return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}
