
// residence.h
// version 1.0.0
#ifndef __RESIDENCE__
#define __RESIDENCE__
#include <iostream>
#include "block.h"

class Block;
class Player;
class Residence : public Block{
	protected:
		Player * owner;
		const int cost;
		bool mortgage;
	public:

		Residence(int p, std::string name);
		int calculate_charge();
		void land(Player * p);
		int getcost();
		void set_owner(Player * p);
		Player * get_owner();
		std::string * print();
		void set_mortgage(bool);
		bool get_mortgage();
		int get_imp_cost();
		int get_imp();
		void incr_imp();
		void decr_imp();
		int get_street_no();
};

#endif
