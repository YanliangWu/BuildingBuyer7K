/************************************************
academic.cc
Vesion 1.3
CS246 - A5 - BB7K
************************************************/

#include "academic.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "player.h"

// Default CTOR
Academic::Academic(int p, std::string name,int s_n, int cst, int i_c,int charge_1,int charge_2,int charge_3,int charge_4,int charge_5,int charge_6) : cost(cst), Block(p,name) {
	this->street_no = s_n;
	this->improvement = 0;
	this->improvement_cost = i_c;
	this->charge[0] = charge_1;
	this->charge[1] = charge_2;
	this->charge[2] = charge_3;
	this->charge[3] = charge_4;
	this->charge[4] = charge_5;
	this->charge[5] = charge_6;
	this->owner = NULL;
	this->mortgage = false;
}

// Return the value of improvement. 
int Academic::get_imp() {
	return improvement;
}

int Academic::get_imp_cost(){
	return improvement_cost;
}

void Academic::set_owner(Player * p){
	owner = p;
}

int Academic::getcost(){
	return cost;
}

// called when moved to this block
void Academic::land(Player * p){
	check_in(p,p->get_index());
	std::cout << "You landed on " << name << std::endl;
	if (mortgage == false){
		if (owner == NULL){		//If there is no owner
			char decision;
			std::cout << "It is empty with the cost of $" << cost << std::endl;
			std::cout << " Would you like to purchase?(y/n)" << std::endl;
			while(true){
				std::cin >> decision;
				if (decision == 'y'){	// If player choose to purchase the building
					
					if (p->get_money() < cost){	//If player has not enough money
						std::cout << "Insufficient fund. Starting auction process" << std::endl;
						decision = 'n';
					}
					
					else{
						std::cout << "Start Purchasing Process...." << std::endl;
						set_owner(p);
						bool none = p->withdraw(cost, NULL, false);
						p->purchase_academic(street_no, this);
						std::cout << "Purchased Successfully" << std::endl;
						break;
					}
				}
				if (decision == 'n'){
					get_board()->auction(this,p);
					break;
				}
				else{
					std::cout << "wrong input" << std::endl;
				}
			}
		}
		else{
			if(owner->getname() == p->getname()) {
				std::cout << "This building belongs to you" << std::endl;
			} else {
				std::cout << "This Place is owned by " << owner->getname() << std::endl;	// Need to pay tuition
				// Check if should double or not
				bool double_price = false;
				int max_owned[8] = {2,3,3,3,3,3,3,2};
				// Check max_owned value.
				if (improvement == 0 && (p->get_academic(street_no) == max_owned[street_no])){
					double_price = true;
				}

				int amount = charge[improvement];

				if (double_price == true){
					amount *= 2;
				}
				// Apply Transaction


				bool none = p->withdraw(amount, owner, true);
				if(none == false) {
					owner->incr_asst(amount);
					p->decr_asst(amount);
					owner->deposit(amount);
				}
			}

		}
	}
	else{
		std::cout << "Mortgaged! Do nothing!" << std::endl;
	}
}

Player * Academic::get_owner(){
	return owner;
}

void Academic::set_mortgage(bool n){
	mortgage = n;
}

bool Academic::get_mortgage() {
	return mortgage;
}

int Academic::calculate_charge(){
	return 0;
}

// return the block information to board.
std::string* Academic::print(){
	
	// Get improvement information
	if(improvement == 0){
		player_str[0] = "|       ";
	}else if(improvement == 1) {
		player_str[0] = "|I      ";
	}else if(improvement == 2){
		player_str[0] = "II      ";
	}else if(improvement == 3){
		player_str[0] = "|III    ";
	}else if(improvement == 4){
		player_str[0] = "|IIII   ";
	}else{
		player_str[0] = "|IIIII  ";
	}

	player_str[1] = "|-------";

	// Get Block and player information
	player_str[2] =  "|" + getname();
	for(int i = player_str[2].length(); i < 8; ++i){
		player_str[2] += " ";
	}
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

void Academic::incr_imp() {
	++improvement;
}
void Academic::decr_imp() {
	--improvement;
}
int Academic::get_street_no(){
	return street_no;
}

