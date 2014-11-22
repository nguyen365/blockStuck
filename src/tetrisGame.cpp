#include "tetrisGame.h"

Block::Block(int iX, int iY, colour iColour)
  : XCoor(iX), YCoor(iY), cColour(iColour)
{;}

Block::~Block()
{;}

bool Block::move(int iX, int iY)
{
  XCoor += iX;
  YCoor += iY;
  return true;
}

bool Block::moveTo(int iX, int iY)
{
  XCoor = iX;
  YCoor = iY;
  return true;
}

int Block::getX()
{
  return XCoor;
}

int Block::getY()
{
  return YCoor;
}

bool Block::isEqual(Block iBlock)
{
  if (this->XCoor == iBlock.XCoor &&
      this->YCoor == iBlock.YCoor)
    return true;
  return false;
}

BlockCollection::BlockCollection()
{;}

BlockCollection::~BlockCollection()
{;}

bool BlockCollection::addBlock(Block iBlock)
{
  if (blockExist(iBlock))
    return false;
  else
    cBlockList.push_back(iBlock);
  return true;
}

bool BlockCollection::eraseBlockAt(int iX, int iY)
{
  for (unsigned i = 0; i < cBlockList.size(); i++)
    if (cBlockList[i].getX() == iX &&
	cBlockList[i].getY() == iY)
      {
	cBlockList.erase(cBlockList.begin() + i);
	return true;
      }
  return false;
}

bool BlockCollection::eraseSelf()
{
  cBlockList.clear();
  return true;
}

bool BlockCollection::eraseLine(int iY)
{
  for (unsigned i = 0; i < CGridLength; i++)
    eraseBlockAt(i,iY);
  return true;
}

bool BlockCollection::mergeCollection(BlockCollection iCollection)
{
  for (unsigned i = 0; i < iCollection.cBlockList.size() ; i++)
    {
      this->addBlock(iCollection.cBlockList[i]);
    }
  return iCollection.eraseSelf();
}

bool BlockCollection::move(int iX, int iY)
{
  for (unsigned i = 0; i < cBlockList.size(); i++)
    {
      if (cBlockList[i].getX() + iX > CGridLength ||
	  cBlockList[i].getX() + iX <= 0 ||
	  cBlockList[i].getY() + iY > CGridHeight ||
	  cBlockList[i].getY() + iY <= 0)
	return false;
      cBlockList[i].move(iX,iY);
    }
  return true;
}

bool BlockCollection::rotate()
{
  for (unsigned i = 0; i < cBlockList.size(); i++)
    {
      int newXCoor = cBlockList[i].getY();
      int newYCoor = -1 * cBlockList[i].getX();
      if (newXCoor >= CGridLength || newXCoor < 0 ||
	  newYCoor >= CGridHeight || newYCoor < 0)
	return false;
      cBlockList[i].moveTo(newXCoor,newYCoor);
    }
  return true;
}

bool BlockCollection::blockExist(Block iBlock)
{
  for (unsigned i = 0; i < cBlockList.size(); i++)
    if (cBlockList[i].isEqual(iBlock))
      return true;
  return false;
}

TetrisGame::TetrisGame(int iLevel, int iSeed)
  : cSeed(iSeed) , cLevel(iLevel) , 
    cStatus(RUNNING), cTick(0)
{
  
}

TetrisGame::~TetrisGame()
{

}

bool TetrisGame::rotateBlock()
{
  return playerTetromino.rotate();
}

bool TetrisGame::iterateLevel()
{
  return playerTetromino.move(0,1);
}
