#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include "block.h"


class Controller;
class Block;
class Academic;
class Player;
class Collect;
class SLC;
class Gym;
class Residence;

class Board{
	int availCup;
	Block * building [40];
	Controller * controller;

	public:
	Board();
	~Board();
	Block * get_pos_ptr(int);
	std::string get_pos_name(int);
	void init(Controller * );
	int get_availCup();
	void incr_availCup();
	void decr_availCup();
	void auction(Block * b, Player * p);
	void printboard();

};

#endif
