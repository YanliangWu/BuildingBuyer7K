#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include "block.h"
#include "academic.h"
#include "controller.h"

class Block;
class Academic;
class Controller;

class Player{
	protected:
		int idx;
		Block *owned[40];
		Controller *c;
		std::string real_name;
		char name;
		int pos;
		Block * pos_ptr;
		bool stuck;
		int money;
		int owned_residence;
		int owned_gym;
		int owned_street[8];
		int DC;
		int Cup;
		int asst;



	public:
		int get_index();
		void set_block(int , Block *);
		void init(Controller *);
		Player(char, std::string, int, int, Block *, int,int,bool,int);
		int roll();
		char getname();
		Block *getown(int);
		int getpos();
		std::string getpos_name();
		bool getstuck();
		void setstuck(bool);
		int getDC();
		void incrDC();
		void setDCzero();
		int getCup();
		void incrCup();
		void decrCup();
		void deposit(int);
		bool withdraw(int, Player *, bool);
		void move(int new_pos, Block * new_pos_ptr);
		void mortgage(Block *);
		void unmortgage(Block *);
		void improve(std::string, std::string);
		int get_gym();
		int get_residence();
		void purchase_gym(Block *);
		void sell_gym(Block *);
		void purchase_residence(Block *);
		void sell_residence(Block *);
		int get_money();
		void purchase_academic(int n, Block *);
		void sell_academic(int n, Block *);
		int get_academic(int n);
		std::string get_real_name();
		int asset();
		void printasset();
		void incr_asst(int);
		void decr_asst(int);
		Block * get_pos_ptr();
};

#endif
