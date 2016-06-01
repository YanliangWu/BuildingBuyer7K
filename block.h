#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "board.h"

class Board;
class Player;

class Block{

	int pos;
	Board * board;
	protected:
	std::string name;
	std::string * player_str; 
	Player ** player_on_grid;
	public:
	Block(int p, std::string n);
	~Block();
	void init(Board *b);
	virtual void land(Player *) = 0;
	std::string getname();
	Board * get_board();
	void check_in(Player * p,int index);
	void check_out(int index);
	virtual Player * get_owner() = 0;
	virtual void set_owner(Player * p) = 0;
	virtual std::string* print() = 0;
	virtual int getcost() = 0;
	virtual int calculate_charge() = 0;
	virtual void set_mortgage(bool) = 0;
	virtual int get_imp_cost() = 0;
	virtual int get_imp() = 0;
	virtual void incr_imp() = 0;
	virtual void decr_imp() = 0;
	virtual bool get_mortgage() = 0;
	virtual int get_street_no() = 0;
	int get_pos();
};
#endif


