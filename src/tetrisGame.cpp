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

colour Block::getColour()
{
  return cColour;
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
      if (cBlockList[i].getX() + iX >= CGridLength ||
	  cBlockList[i].getX() + iX < 0 ||
	  cBlockList[i].getY() + iY > CGridHeight ||
	  cBlockList[i].getY() + iY < 0)
	return false;
    }
  for (unsigned i = 0; i < cBlockList.size(); i++)
    cBlockList[i].move(iX,iY);
  return true;
}

bool BlockCollection::rotate()
{
  Block centreBlockCopy = getCentre();
  for (unsigned i = 0; i < cBlockList.size(); i++)
    {
      cBlockList[i].moveTo(cBlockList[i].getX() - centreBlockCopy.getX(),
			   cBlockList[i].getY() - centreBlockCopy.getY());
      int newXCoor = cBlockList[i].getY();
      int newYCoor = -1 * cBlockList[i].getX();
      cBlockList[i].moveTo(newXCoor + centreBlockCopy.getX(),
			   newYCoor + centreBlockCopy.getY());
      /*      if (newXCoor >= CGridLength || newXCoor < 0 ||
	      newYCoor >= CGridHeight || newYCoor < 0)
	      return false;
      */
    }
  return true;
}

Block* BlockCollection::findBlock(int iX, int iY)
{
  for (unsigned i = 0; i < cBlockList.size(); i++)
    if (cBlockList[i].getX() == iX && cBlockList[i].getY() == iY)
      return &(cBlockList[i]);
  return NULL;
}

bool BlockCollection::blockExist(Block iBlock)
{
  for (unsigned i = 0; i < cBlockList.size(); i++)
    if (cBlockList[i].isEqual(iBlock))
      return true;
  return false;
}

std::vector<Block> BlockCollection::getBlockList()
{
  return cBlockList;
}

Block BlockCollection::getCentre()
{
  return cBlockList[CTetrominoCentre[cBlockList[0].getColour()]];
}

TetrisGame::TetrisGame(int iLevel, int iSeed)
  : cSeed(iSeed) , cLevel(iLevel) , 
    cStatus(RUNNING), cTick(0)
{
  
}

TetrisGame::~TetrisGame()
{

}

bool TetrisGame::moveBlock()
{
  return playerTetromino.move(0,1);
}

bool TetrisGame::moveBlock(int iX, int iY)
{
  return playerTetromino.move(iX, iY);
}

bool TetrisGame::rotateBlock()
{
  return playerTetromino.rotate();
}

bool TetrisGame::iterateLevel()
{
  if (cStatus != RUNNING)
    return false;
  return playerTetromino.move(0,1);
}

std::vector<Block> TetrisGame::getBlockList()
{
  std::vector<Block> allBlocks;
  std::vector<Block> loadedBlocks = playerTetromino.getBlockList();
  for (unsigned i = 0; i < loadedBlocks.size(); i++)
    allBlocks.push_back(loadedBlocks.at(i));
  loadedBlocks = tetrominoStack.getBlockList();
  for (unsigned i = 0; i < loadedBlocks.size(); i++)
    allBlocks.push_back(loadedBlocks.at(i));
  return allBlocks;
}

void TetrisGame::addBlock()
{
  playerTetromino.mergeCollection(makeBlock(randomColour(cDice)));
}

colour randomColour(Dice iDice)
{
  int retVal = iDice.CDISTRIBUTION(iDice.CGENERATOR);
  return colour(retVal);
}

BlockCollection makeBlock(colour iBlockColour)
{
  BlockCollection Tetromino = BlockCollection();
  switch (iBlockColour)
    {
    case CYAN:
      for (unsigned i = 0; i < 4; i++)
	Tetromino.addBlock(Block(3 + i, 21, iBlockColour));
      break;
    case YELLOW:
      for (unsigned i = 0; i < 2; i++)
	{
	  Tetromino.addBlock(Block(4 + i, 21, iBlockColour));
	  Tetromino.addBlock(Block(4 + i, 22, iBlockColour));
	}
      break;
    case PURPLE:
      for (unsigned i = 0; i < 3; i++)
	Tetromino.addBlock(Block(3 + i, 21, iBlockColour));
      Tetromino.addBlock(Block(4, 22, iBlockColour));
      break;
    case GREEN:
      for (unsigned i = 0; i < 2; i++)
	{
	  Tetromino.addBlock(Block(3 + i, 21, iBlockColour));
	  Tetromino.addBlock(Block(4 + i, 22, iBlockColour));
	}
      break;
    case RED:
      for (unsigned i = 0; i < 2; i++)
	{
	  Tetromino.addBlock(Block(3 + i, 22, iBlockColour));
	  Tetromino.addBlock(Block(4 + i, 21, iBlockColour));
	}
      break;
    case BLUE:
      for (unsigned i = 0; i < 3; i++)
	Tetromino.addBlock(Block(3 + i, 21, iBlockColour));
      Tetromino.addBlock(Block(3, 22, iBlockColour));
      break;
    case ORANGE:
      for (unsigned i = 0; i < 3; i++)
	Tetromino.addBlock(Block(3 + i, 21, iBlockColour));
      Tetromino.addBlock(Block(5, 22, iBlockColour));
      break;
    }
  return Tetromino;
}
