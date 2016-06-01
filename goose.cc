/************************************************
  goose.cc
  Vesion 1.3
  CS246 - A5 - BB7K
  ************************************************/
#include <iostream>
#include "goose.h"
#include <iomanip>
#include <sstream>
using namespace std;

Goose::Goose(): Block(20, "Goose Nesting") {}

void Goose::land(Player *p) {
    check_in(p,p->get_index());
	cout << "You are attacked by a flock of nesting geese LOL." << endl;
}

std::string* Goose::print() {
	player_str[0] = "|Goose  ";
	player_str[1] = "|Nesting";
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


Player * Goose::get_owner(){
	return NULL;
}
void Goose::set_owner(Player * p){

}
int Goose::getcost(){
	return 0;
}

void Goose::set_mortgage(bool b){}

bool Goose::get_mortgage() {
	return 0;
}

int Goose::calculate_charge(){
	return 0;
}

int Goose::get_imp() {
	return 0;
}

int Goose::get_imp_cost() {
	return 0;
}

void Goose::incr_imp() {}

int Goose::get_street_no(){return -1;}
void Goose::decr_imp() {}
