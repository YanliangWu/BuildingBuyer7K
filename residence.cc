/************************************************
  residence.cc
  Vesion 1.3
  CS246 - A5 - BB7K
************************************************/

#include "residence.h"
#include <iomanip>
#include <sstream>
#include "player.h"
using namespace std;


Residence::Residence(int p, std::string name) : cost(200),Block(p,name){
	owner = NULL;
	mortgage = false;
}

int Residence::calculate_charge(){
	int multiplicity = owner->get_residence();
	if (multiplicity == 1){
		return 25;
	}
	else if (multiplicity == 2){
		return 50;
	}
	else if (multiplicity == 3){
		return 100;
	}
	else if (multiplicity == 4){
		return 200;
	}
	else{
		std::cout << "Wrong num of Residence, check the bug!" << std::endl;
		return 0;
	}
}

void Residence::set_owner(Player * p){
	owner = p;
}

int Residence::getcost(){
	return cost;
}

void Residence::land(Player *p){
	check_in(p,p->get_index());
	bool none;
	std::cout << "You landed on " << name << std::endl;
	if (mortgage == false){
		if (owner != NULL){
			if(owner->getname() != p->getname()) {
				int charge = calculate_charge();
				none = p->withdraw(charge, owner, true);
				if(none == false) {
					p->decr_asst(charge);
					owner->deposit(charge);
					owner->incr_asst(charge);
				}
			} else {
				cout << "It belongs to you" << endl;
			}
		}
		else{
			std::cout << "It is empty with the cost of $" << cost << std::endl;
			std::cout << "would you like to purchase (y/n)" << std::endl;
			char decision;
			while (true){
				std::cin >> decision;
				if (decision == 'y'){
					if (p->get_money() < cost){
						std::cout << "Insufficient fund. Starting auction process" << std::endl;
						decision = 'n';
					}
					else{
						set_owner(p);
						none = p->withdraw(cost, NULL, false);
						if(none == false) {
							p->purchase_residence(this);
						}
						break;
					}
				}
				if (decision == 'n'){
					get_board()->auction(this,p);
					break;
				}
				else{
					std::cout << "invalid input, please check again"<< std::endl;
				}
			}
		}
	}
	else{
		std::cout << "Land Mortgaged!" << std::endl;

	}
}

Player * Residence::get_owner(){
	return owner;
}

std::string* Residence::print(){

	player_str[0] = "|" + getname();
	for (int i = player_str[0].length(); i < 8; ++i){
		player_str[0] += " ";
	}
	player_str[1] = "|       ";
	player_str[2] = "|       ";
	player_str[3] = "|";
	for(int i = 0; i < 7 ;++i){
		if(player_on_grid[i] != NULL){
			player_str[3] += player_on_grid[i]->getname();
		}
	}

	for(int i = player_str[3].length(); i < 8; ++i){
		player_str[3] += " " ;
	}
	player_str[4] = "|_______";
	return player_str;

}


void Residence::set_mortgage(bool b){
	mortgage = b;
}

bool Residence::get_mortgage() {
	return mortgage;
}

int Residence::get_imp() {
	return 0;
}

int Residence::get_imp_cost() {
	return 0;
}

void Residence::incr_imp() {}
int Residence::get_street_no(){return -1;}
void Residence::decr_imp() {}
