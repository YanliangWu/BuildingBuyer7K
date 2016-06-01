/************************************************
  coop.cc
  Vesion 1.3
  CS246 - A5 - BB7K
************************************************/

#include <iostream>
#include "coop.h"
#include <iomanip>
#include <sstream>
using namespace std;

Coop::Coop(): Block(38, "COOP FEE") {}

void Coop::land(Player *p) {
	check_in(p,p->get_index());
	bool none = p->withdraw(150, NULL, true);
	if(none == false) {
		p->decr_asst(150);
		cout << "You have paid $150 coop fee to school." << endl;
	}
}



std::string* Coop::print() {
	player_str[0] = "|COOP   ";
	player_str[1] = "|FEE    ";
	player_str[2] = "|       ";
	player_str[3] = "|";
	for(int i = 0; i < 7 ;++i){
		if(player_on_grid[i] != NULL){
			player_str[3] += player_on_grid[i]->getname();  // push player to the string
		}
	}
	for(int i = player_str[3].length(); i < 8; ++i){
		player_str[3] += " " ;
	}
	player_str[4] = "|_______";
	return player_str;
}


Player * Coop::get_owner(){
	return NULL;
}

// The function below is useless.
void Coop::set_owner(Player * p) {}

bool Coop::get_mortgage() {
	return 0;
}

int Coop::getcost(){
	return 0;
}
void Coop::set_mortgage(bool b){}

int Coop::calculate_charge(){
	return 0;
}

int Coop::get_imp() {
	return 0;
}

int Coop::get_imp_cost() {
	return 0;
}

void Coop::incr_imp() {}

int Coop::get_street_no(){
	return -1;
}
void Coop::decr_imp() {}
