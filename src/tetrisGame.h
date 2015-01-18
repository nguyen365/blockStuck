#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <utility>

#ifndef __TETRIS_GAME_H__
#define __TETRIS_GAME_H__

const int CGridHeight = 22;
const int CGridLength = 10;
const int CRotationAmount = 90;
enum colour {CYAN, YELLOW, PURPLE, GREEN, RED, BLUE, ORANGE, DEBUG};
enum status {ERROR, RUNNING, PAUSED};
const int CTetrominoCentre [] = {2, 0, 1, 1, 3, 1, 1};
std::random_device CRANDOMDEVICE;
std::mt19937 CGENERATOR(CRANDOMDEVICE());
std::uniform_int_distribution<int> CDISTRIBUTION(CYAN,ORANGE);

class Block
{
 private:
  float XCoor;
  float YCoor;
  colour cColour;
 public:
  Block(int,int); //to make a point
  Block(int,int,colour);
  Block(float,float,colour);
  ~Block();
  bool move(int,int);
  float getX();
  float getY();
  colour getColour();
  bool moveTo(int,int);
  bool isEqual(Block iBlock);
};

class BlockCollection
{
 private:
  unsigned cRotation;
  std::vector<Block> cBlockList;
 public:
  BlockCollection();
  ~BlockCollection();
  virtual bool addBlock(Block);
  virtual bool eraseBlockAt(int,int);
  bool eraseSelf();
  virtual bool eraseLine(int); //will also make above blocks fall
  virtual bool mergeCollection(BlockCollection&);
  bool move(int,int);
  int getSize();
  int getBottomY();
  virtual bool rotate();
  std::vector<Block> getBlockList();
  virtual Block* findBlock(int iX, int iY);
  bool blockExist(Block);
 private:
  Block getCentre();
  Block getCyanCentre();
  int getXOffset();
  int getCyanXOffset();
  int getGreenXOffset();
  int getYOffset();
  int getCyanYOffset();
  int getGreenYOffset();
};

class StaticBlockCollection : public BlockCollection
{
  private:
    std::map<int, Block*> cBlockTable;
  public:
    StaticBlockCollection();
    bool addBlock(Block);
    bool eraseBlockAt(int,int);
    bool eraseLine(int);
    bool mergeCollection(BlockCollection&);
    Block* findBlock(int iX, int iY);
};

class TetrisGame
{
 private:
  int cSeed;
  int cLevel;
  status cStatus;
  int cTick;
  int cGrid [CGridHeight][CGridLength];
  bool cMergeFlag;
  BlockCollection playerTetromino;
  StaticBlockCollection tetrominoStack;
 public:
  TetrisGame(int iLevel = 1, int iSeed = 0);
  ~TetrisGame();
  bool moveBlock();
  bool moveBlock(int iX, int iY);
  bool rotateBlock();
  bool iterateLevel(int iMilliseconds);
  std::vector<Block> getBlockList();
 private:
  void addBlock();
  bool eraseLine(int iY);
  bool checkCollision();
  bool checkCollision(BlockCollection iBlockCollection);
  bool isLineFull(int iY);
  bool eraseFullLines();
};

colour randomColour();
BlockCollection makeBlock(colour iBlockColour);

#endif
