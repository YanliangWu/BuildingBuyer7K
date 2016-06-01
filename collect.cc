/************************************************
  collect.cc
  Vesion 1.3
  CS246 - A5 - BB7K
************************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include "collect.h"
using namespace std;

Collect::Collect(): Block(0, "COLLECT OSAP") {}

void Collect::land(Player *p) {
    check_in(p,p->get_index());
	cout << "You landed on COLLECT OSAP" << endl;
}

std::string* Collect::print() {
    player_str[0] = "|COLLECT";
    player_str[1] = "|OSAP   ";
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

Player * Collect::get_owner(){
	return NULL;
}

// The function below is USELESS in this module.
// Just because it is virtual function.
void Collect::set_owner(Player * p){

}

int Collect::getcost(){
	return 0;
}
void Collect::set_mortgage(bool b){}

bool Collect::get_mortgage() {
	return 0;
}

int Collect::calculate_charge(){
	return 0;
}

int Collect::get_imp() {
	return 0;
}

int Collect::get_imp_cost() {
	return 0;
}

void Collect::incr_imp() {}

void Collect::decr_imp() {}
int Collect::get_street_no(){return -1;}
