/************************************************
gotims.cc
Vesion 1.3
CS246 - A5 - BB7K
************************************************/
#include <iostream>
#include "gotims.h"
#include <iomanip>
#include <sstream>
using namespace std;

Gotims::Gotims(): Block(30, "GO TO TIMS") {}

void Gotims::land(Player *p) {
    	
	cout << "You are moved to DC Tims Line" << endl;
	p->setstuck(true);
	p->set_block(10, get_board()->get_pos_ptr(10));
	get_board()->get_pos_ptr(10)->check_in(p,p->get_index());

}

std::string* Gotims::print() {
	player_str[0] = "|GO TO  ";
	player_str[1] = "|TIMS   ";
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


Player * Gotims::get_owner(){
	return NULL;
}

void Gotims::set_owner(Player * p){

}
int Gotims::getcost(){
	return 0;
}
void Gotims::set_mortgage(bool b){}

bool Gotims::get_mortgage() {
	return 0;
}

int Gotims::calculate_charge(){
	return 0;
}

int Gotims::get_imp() {
	return 0;
}

int Gotims::get_imp_cost() {
	return 0;
}

void Gotims::incr_imp() {}

int Gotims::get_street_no(){return -1;}
void Gotims::decr_imp() {}
