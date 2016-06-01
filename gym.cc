/************************************************
  gym.cc
  Vesion 1.3
  CS246 - A5 - BB7K
  ************************************************/
#include "gym.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "player.h"
Gym::Gym(int p, std::string name) : Block(p,name), cost(150){

	owner = NULL;
	mortgage = false;
}

int Gym::calculate_charge(){

	int multiplicity;
	if (owner->get_gym() == 1){
		multiplicity = 4;
	}
	else {
		multiplicity = 10;
	}
	srand(time(NULL));
	std::cout << "Rooling Dice One "<< std::endl;
	int dice_1 = rand() % 6 + 1;
	std::cout << "Dice One is: " << dice_1 << std::endl;
	int dice_2 = rand() % 6 + 1;
	std::cout << "Rolling Dice Two "<< std::endl;
	std::cout << "Dice Two is: " << dice_2 << std::endl;
	return ((dice_1 + dice_2) * multiplicity);
}

void Gym::set_owner(Player * p){
	owner = p;
}

int Gym::getcost(){
	return cost;
}

void Gym::land(Player *p){
	check_in(p,p->get_index());
	std::cout << "You landed on " << name << std::endl;
	bool none;
	if (mortgage == false){
		if (owner != NULL){
			if(owner->getname() != p->getname()) {
				int charge = calculate_charge();
				// Apply Transaction
				none = p->withdraw(charge, owner, true);
				if(none == false) {
					owner->incr_asst(charge);
					owner->deposit(charge);
					p->decr_asst(charge);
				}
			} else {
				std::cout << "It belongs to you" << std::endl;
			}
		}
		else{
			std::cout << "It is empty with the cost of $" << cost << std::endl;
			std::cout << " Would you like to purchase (y/n)" << std::endl;
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
						p->purchase_residence(this);
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
Player * Gym::get_owner(){
	return owner;
}

void Gym::set_mortgage(bool n){
	mortgage = n;
}

bool Gym::get_mortgage() {
	return mortgage;
}

std::string* Gym::print(){

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

int Gym::get_imp() {
	return 0;
}

int Gym::get_imp_cost() {
	return 0;
}

void Gym::incr_imp() {}

void Gym::decr_imp() {}
int Gym::get_street_no(){return -1;}
