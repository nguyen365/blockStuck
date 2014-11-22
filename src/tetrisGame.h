#include <vector>

#ifndef __TETRIS_GAME_H__
#define __TETRIS_GAME_H__

const int CGridHeight = 22;
const int CGridLength = 10;
enum colour {CYAN, YELLOW, PURPLE, GREEN, RED, BLUE, ORANGE};
enum status {ERROR, RUNNING, PAUSED};

class Block
{
 private:
  int XCoor;
  int YCoor;
  colour cColour;
 public:
  Block(int,int,colour);
  ~Block();
  bool move(int,int);
  int getX();
  int getY();
  bool moveTo(int,int);
  bool isEqual(Block iBlock);
};

class BlockCollection
{
 private:
  std::vector<Block> cBlockList;
 public:
  BlockCollection();
  ~BlockCollection();
  bool addBlock(Block);
  bool eraseBlockAt(int,int);
  bool eraseSelf();
  bool eraseLine(int);
  bool mergeCollection(BlockCollection);
  bool move(int,int);
  bool rotate();
 private:
  bool blockExist(Block);
};

class TetrisGame
{
 private:
  int cSeed;
  int cLevel;
  status cStatus;
  int cTick;
  int cGrid [CGridHeight][CGridLength];
  BlockCollection playerTetromino;
  BlockCollection tetrominoStack;
 public:
  TetrisGame(int iLevel = 0, int iSeed = 0);
  ~TetrisGame();
  bool rotateBlock();
  bool iterateLevel();
 private:
  bool eraseLine(int iY);
};

#endif
