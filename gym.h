#ifndef __GYM__
#define __GYM__

#include "block.h"

class Block;
class Player;

class Gym : public Block { 
protected:
    Player * owner;
	const int cost;
    bool mortgage;
	
public:
	int calculate_charge ();
	Gym(int p, std::string name);
	void land(Player * p);
	int getcost();
	void set_owner(Player * p);
    Player * get_owner();
    void set_mortgage(bool);
    bool get_mortgage();
    std::string* print();
    int get_imp_cost();
    int get_imp();
    void incr_imp();
    void decr_imp();
	int get_street_no();
};

#endif
