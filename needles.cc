/************************************************
  needles.cc
  Vesion 1.3
  CS246 - A5 - BB7K
************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "needles.h"
#include <sstream>
#include <iomanip>

using namespace std;

Needles::Needles(int pos): Block(pos, "NEEDLES HALL") {}

void Needles::land(Player *p) {
	cout << "You are in Needles Hall!" << std::endl;
	check_in(p,p->get_index());
	bool winCup;
	srand(time(NULL));
	int num = rand() % 18 + 1;
	int a = get_board()->get_availCup();
	bool none;
	if(a != 0) {
		int i = rand() % 100 + 1;
		if(i == 1) {
			cout << "Congrats, you receive a winning Roll Up the Rim cup" << endl;
			p->incrCup();
			get_board()->decr_availCup();
			winCup = true;
		}else {
			winCup = false;
		}
	} else {
		winCup = false;

	}
	if(winCup == false) {
		if(num == 1) {
			cout << "You lost $200" << endl;
			none = p->withdraw(200, NULL, true);
			if(none == false) {
				p->decr_asst(200);
			}
		} else if(num >= 2 and num <= 3) {
			cout << "You lost $100" << endl;
			none = p->withdraw(100, NULL, true);
			if(none == false) {    
				p->decr_asst(100);
			}
		} else if(num >= 4 and num <= 6) {
			cout << "You lost $50" << endl;
			none = p->withdraw(50, NULL, true);
			if(none == false) {
				p->decr_asst(50);
			}
		} else if(num >= 7 and num <= 12) {
			cout << "You earned $25" << endl;
			p->deposit(25);;
			p->incr_asst(25);
		} else if(num >= 13 and num <= 15) {
			cout << "You earned $50" << endl;
			p->deposit(50);
			p->incr_asst(50);
		} else if(num >= 16 and num <= 17) {
			cout << "You earned $100" << endl;
			p->deposit(100);
			p->incr_asst(100);
		} else if(num == 18) {
			cout << "You earned $200" << endl;
			p->deposit(200);
			p->incr_asst(200);
		}

	}
}


std::string* Needles::print() {
	player_str[0] = "|NEEDLES";
	player_str[1] = "|HALL   ";
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

Player * Needles::get_owner(){
	return NULL;
}
void Needles::set_owner(Player * p){

}
int Needles::getcost(){
	return 0;
}
void Needles::set_mortgage(bool b){}

bool Needles::get_mortgage() {
	return 0;
}

int Needles::calculate_charge(){
	return 0;
}

int Needles::get_imp() {
	return 0;
}

int Needles::get_imp_cost() {
	return 0;
}

void Needles::incr_imp() {}
int Needles::get_street_no(){return -1;}
void Needles::decr_imp() {}
