#ifndef __ACADEMIC__
#define __ACADEMIC__

#include "block.h"

class Player;
class Academic : public Block{

	protected:
		int street_no;
		Player * owner;
		const int cost;
		int improvement;
		int improvement_cost;
		int charge[6];
		bool mortgage;

	public:
		Academic(int p, std::string name,int s_n, int cst, int i_c,int charge_1,int charge_2,int charge_3,int charge_4,int charge_5,int charge_6);
		void set_owner(Player * p);
		void land(Player * p);
		int getcost();
		Player * get_owner();
		void set_mortgage(bool);
		bool get_mortgage();
		int calculate_charge();
		int get_imp();
		int get_imp_cost();
		std::string* print();
		void incr_imp();
		void decr_imp();
		int get_street_no();
};

#endif
