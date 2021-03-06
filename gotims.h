#ifndef __GOTIMS_H__
#define __GOTIMS_H__
#include <string>
#include "block.h"
#include "player.h"

class Block;
class Player;

class Gotims : public Block {
   public:
	Gotims();
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
