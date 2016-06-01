#ifndef __NEEDLES_H__
#define __NEEDLES_H__
#include "block.h"
#include "player.h"
#include <string>

class Block;
class Player;

class Needles : public Block {
   public:
	Needles(int);
	void land(Player *);
    std::string* print();
    Player * get_owner();
    void set_owner(Player *);
    int getcost();
    void set_mortgage(bool);
    bool get_mortgage();
    int calculate_charge();
    int get_imp_cost();
    int get_imp();
    void incr_imp();
    void decr_imp();
	int get_street_no();
};

#endif
