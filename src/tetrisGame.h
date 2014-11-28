#include <vector>
#include <random>

#ifndef __TETRIS_GAME_H__
#define __TETRIS_GAME_H__

const int CGridHeight = 22;
const int CGridLength = 10;
enum colour {CYAN, YELLOW, PURPLE, GREEN, RED, BLUE, ORANGE};
enum status {ERROR, RUNNING, PAUSED};
const int CTetrominoCentre [] = {2, 0, 2, 1, 3, 1, 1};

struct Dice
{
  std::default_random_engine CGENERATOR;
  std::uniform_int_distribution<int> CDISTRIBUTION;
  Dice()
  {
    CDISTRIBUTION = std::uniform_int_distribution<int>(CYAN,ORANGE);
  }
};

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
  colour getColour();
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
  std::vector<Block> getBlockList();
 private:
  Block* findBlock(int iX, int iY);
  bool blockExist(Block);
  Block getCentre();
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
  Dice cDice;
 public:
  TetrisGame(int iLevel = 0, int iSeed = 0);
  ~TetrisGame();
  bool moveBlock();
  bool moveBlock(int iX, int iY);
  bool rotateBlock();
  bool iterateLevel();
  std::vector<Block> getBlockList();
  void addBlock();
 private:
  bool eraseLine(int iY);
};

colour randomColour(Dice iDice);
BlockCollection makeBlock(colour iBlockColour);

#endif
