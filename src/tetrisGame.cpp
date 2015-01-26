#include "tetrisGame.h" 

std::random_device CRANDOMDEVICE;
std::mt19937 CGENERATOR(CRANDOMDEVICE());
std::uniform_int_distribution<int> CDISTRIBUTION(CYAN,ORANGE);

Block::Block(int iX, int iY)
  : XCoor(iX), YCoor(iY), cColour(DEBUG)
{;}

Block::Block(int iX, int iY, colour iColour)
  : XCoor(iX), YCoor(iY), cColour(iColour)
{;}

Block::Block(float iX, float iY, colour iColour)
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

float Block::getX()
{
  return XCoor;
}

float Block::getY()
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
  : cRotation(0)
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
  for (unsigned i = 0; i < cBlockList.size(); i++)
  {
    if (cBlockList[i].getX() == i &&
	cBlockList[i].getY() == iY)
      {
	cBlockList.erase(cBlockList.begin() + i);
      }
  }
  return true;
}

bool BlockCollection::makeBlocksAboveFall(int iY)
{
  for (unsigned i = 0; i < cBlockList.size(); i++)
    if (cBlockList[i].getY() > iY)
    {
      cBlockList[i].move(0,-1);
    }
  return true;
}

bool BlockCollection::mergeCollection(BlockCollection& iCollection)
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

int BlockCollection::getSize()
{
  return cBlockList.size();
}

int BlockCollection::getBottomY()
{
  int YLocation = CGridHeight;
  for (unsigned i = 0; i < cBlockList.size(); i++)
    if (YLocation > cBlockList[i].getY())
      YLocation = cBlockList[i].getY();
  return YLocation;
}

bool BlockCollection::rotate()
{
  if (cBlockList[0].getColour() == YELLOW)
    return true;
  Block centreBlock = getCentre();
  std::vector<Block> rotatedBlocks = cBlockList;
  for (unsigned i = 0; i < cBlockList.size(); i++)
    {
      rotatedBlocks[i].move(-1 * centreBlock.getX(), -1 * centreBlock.getY());
      rotatedBlocks[i].moveTo(rotatedBlocks[i].getY(), -1 * rotatedBlocks[i].getX());
      rotatedBlocks[i].move(centreBlock.getX() + getXOffset(),
			 centreBlock.getY() + getYOffset());
      if (rotatedBlocks[i].getX() >= CGridLength ||
	  rotatedBlocks[i].getX() < 0 ||
	  rotatedBlocks[i].getY() > CGridHeight ||
	  rotatedBlocks[i].getY() < 0)
	return false;
    }
  cBlockList = rotatedBlocks;
  cRotation = (cRotation + 90)%360;
  return true;
}

std::vector<Block> BlockCollection::getBlockList()
{
  return cBlockList;
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

Block BlockCollection::getCentre()
{
  switch (this->cBlockList[0].getColour())
  {
    case CYAN:
      return getCyanCentre();
    default:
      return cBlockList[cBlockList.size() / 2 - 1];	
  }
}

Block BlockCollection::getCyanCentre()
{
  switch (cRotation)
  {
    case 0:
      return Block(cBlockList[2].getX(),cBlockList[2].getY());
    case 90:
      return Block(cBlockList[1].getX(),cBlockList[1].getY() + 1 );
    case 180:
      return Block(cBlockList[1].getX(),cBlockList[1].getY() + 1 );
    case 270:
      return Block(cBlockList[1].getX(),cBlockList[1].getY() + 1 );
    default:
      return Block(0,0);
  }
}

int BlockCollection::getXOffset()
{
  switch (this->cBlockList[0].getColour())
  {
    case CYAN:
      return getCyanXOffset();
    case GREEN:
      return getGreenXOffset();
    default:
      return 0;
  }
}

int BlockCollection::getYOffset()
{
  switch (this->cBlockList[0].getColour())
  {
    case CYAN:
      return getCyanYOffset();
    case GREEN:
      return getGreenYOffset();
    default:
      return 0;
  }
}

int BlockCollection::getCyanXOffset()
{
  switch (cRotation)
  {
    case 0:
      return 0;
    case 90:
      return 1;
    case 180:
      return 0;
    case 270:
      return 1;
    default:
      return 0;
  }
}

int BlockCollection::getCyanYOffset()
{
  switch (cRotation)
  {
    case 0:
      return -1;
    case 90:
      return -2;
    case 180:
      return -1;
    case 270:
      return 0;
    default:
      return 0;
  }
}

int BlockCollection::getGreenXOffset()
{
  switch (cRotation)
  {
    case 0:
      return 1;
    case 90:
      return -1;
    case 180:
      return 0;
    case 270:
      return 0;
    default:
      return 0;
  }
}

int BlockCollection::getGreenYOffset()
{
  switch (cRotation)
  {
    case 0:
      return -1;
    case 90:
      return -1;
    case 180:
      return 1;
    case 270:
      return 1;
    default:
      return 0;
  }
}

StaticBlockCollection::StaticBlockCollection()
  : BlockCollection() , cBlockTable()
{
    
}

bool StaticBlockCollection::addBlock(Block iBlock)
{
  if (BlockCollection::addBlock(iBlock) == false)
    return false;
  int key = iBlock.getY() * CGridHeight + iBlock.getX();
  cBlockTable.insert(std::pair<int,Block*>(key, &iBlock));
  return true;
}

bool StaticBlockCollection::eraseBlockAt(int iX, int iY)
{
  cBlockTable.erase(iY*CGridHeight + iX);
  return BlockCollection::eraseBlockAt(iX, iY);
}

bool StaticBlockCollection::eraseLine(int iY)
{
  for (unsigned i = 0; i < CGridLength; i++)
//     if (!eraseBlockAt(i,iY))
//       return false;
    eraseBlockAt(i,iY);
  BlockCollection::makeBlocksAboveFall(iY);
  updateBlocks();
  return true;
}

bool StaticBlockCollection::updateBlocks()
{
  cBlockTable.clear();
  std::vector<Block> blockList = BlockCollection::getBlockList();
  for (unsigned i = 0; i < blockList.size(); i++)
       {
	 int key = blockList[i].getY() * CGridHeight + blockList[i].getX();
	 cBlockTable.insert(std::pair<int,Block*>(key, &(blockList[i])));
       }
  return true;
}

bool StaticBlockCollection::mergeCollection(BlockCollection& iCollection)
{
  std::vector<Block> blockList = iCollection.getBlockList();
  for (unsigned i = 0; i < blockList.size() ; i++)
    {
      this->addBlock(blockList[i]);
    }
  return iCollection.eraseSelf();
}

Block* StaticBlockCollection::findBlock(int iX,  int iY)
{
  std::map<int,Block*>::iterator it = cBlockTable.find(iY * CGridHeight + iX);
  if (it == cBlockTable.end())
    return NULL;
  else
    return (*it).second;
}



TetrisGame::TetrisGame(int iLevel, int iSeed)
  : cSeed(iSeed) , cLevel(iLevel) , 
    cStatus(RUNNING), cTick(0), cMergeFlag(false)
{
  
}

TetrisGame::~TetrisGame()
{
  
}

bool TetrisGame::moveBlock()
{
  return moveBlock(0,-1);
}

bool TetrisGame::moveBlock(int iX, int iY)
{
  BlockCollection tempMovedCollection = playerTetromino;
  if (!tempMovedCollection.move(iX,iY))
  {
    return false;
  }
  else if (checkCollision(tempMovedCollection))
  {
    if (iX == 0)
      cMergeFlag = true;
    return false;
  }
  else 
    playerTetromino = tempMovedCollection;
  return true;
}

bool TetrisGame::rotateBlock()
{
  return playerTetromino.rotate();
}

bool TetrisGame::iterateLevel(int iMilliseconds)
{
  if (cStatus != RUNNING)
    return false;
  cTick += iMilliseconds;
  if (cTick >= (CMillisecondsPerLevel/cLevel) )
  {
    moveBlock(0,-1);
    cTick = 0;//(CMillisecondsPerLevel);
  }
  if (cMergeFlag || playerTetromino.getBottomY() == 0 || checkCollision()) 
  {
    tetrominoStack.mergeCollection(playerTetromino);
    eraseFullLines();
    cMergeFlag = false;
  }
  if (playerTetromino.getSize() == 0)
    addBlock();
  return true; 
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
  playerTetromino = (makeBlock(randomColour()));
}

bool TetrisGame::checkCollision()
{
  return checkCollision(playerTetromino);
}

bool TetrisGame::checkCollision(BlockCollection iBlockCollection)
{
  std::vector<Block> BlockList = iBlockCollection.getBlockList();
  for (unsigned i = 0; i < BlockList.size(); i++)
    if (tetrominoStack.findBlock(BlockList[i].getX(),BlockList[i].getY()))
    {
      return true;
    }
  return false;
}

bool TetrisGame::isLineFull(int iY)
{
  for (unsigned i = 0; i < CGridLength; i++)
    if (!tetrominoStack.findBlock(i, iY))
      return false;
  return true;
}

bool TetrisGame::eraseFullLines()
{
  for (int i = CGridHeight - 1; i >= 0; i--)
    if (isLineFull(i))
      tetrominoStack.eraseLine(i);
  return true;
}

colour randomColour()
{
  int retVal = CDISTRIBUTION(CGENERATOR);
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
    case DEBUG:
      Tetromino.addBlock(Block( 4, 21, CYAN));
      Tetromino.addBlock(Block( 5, 21, YELLOW));
      Tetromino.addBlock(Block( 6, 21, RED));
      Tetromino.addBlock(Block( 7, 21, GREEN));
      break;
    }
  return Tetromino;
}
