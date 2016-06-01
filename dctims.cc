/************************************************
  dctims.cc
  Vesion 1.3
  CS246 - A5 - BB7K
************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "dctims.h"
#include <iomanip>
#include <sstream>

using namespace std;

Dctims::Dctims(): Block(10, "DC Tims Line") {}

void Dctims::land(Player *p) {
	check_in(p,p->get_index());
	srand(time(NULL));
	bool stucked = p->getstuck();
	bool none;
	if(stucked == true) {
		int t = p->getDC();
		cout << "You are stucked in DC Tims Line Now" << endl;
		int one = p->roll();
		int two = p->roll();
		int sum = one + two;
		cout << "You rolled " << one << " and " << two << endl;	
		if(t != 2) {		// Before the third round in the DCTIMSLINE
			if(one == two) {
				cout << "You rolled doubles" << endl;
				cout << "You get out of DC Tims Line successfully" << endl;
				p->setstuck(false);
				p->setDCzero();
				p->move(sum + 10, get_board()->get_pos_ptr(sum + 10));
			} else {
				int n2;
				cout << "You didn't roll doubles" << endl;
				bool s;
				while(true) {
					cout << "Are you gonna 1.pay $50 or 2.use a Roll Up the Rim cup to get out of DC Tims Line or 3.stay here?" << endl;
					if(cin >> n2) {
						if(n2 == 1) {
							none = p->withdraw(50, NULL, true);
							if(none == false) { 
								p->decr_asst(50);
								p->move(sum + 10, get_board()->get_pos_ptr(sum + 10));
								cout << "You get out of DC Tims Line successfully" << endl;
								p->setstuck(false);
								p->setDCzero();
							}
							s = true;
						} else if(n2 == 2) {
							int c = p->getCup();
							if(c == 0) {
								cout << "Not enough Roll Up the Rim cup, plase choose again" << endl;
								s = false;
							} else {
								p->decrCup();
								get_board()->incr_availCup();
								cout << "You get out of DC Tims Line successfully" << endl;
								p->move(sum, get_board()->get_pos_ptr(sum + 10));
								p->setstuck(false);
								p->setDCzero();
								s = true;
							}
						} else if(n2 == 3) {
							cout << "Stay in DC Tims Line, waiting for the next round" << endl;
							p->incrDC();
							s = true;
						}
					} else {
						cout << "Invalid input, please choose again" << endl;
						s = false;
					}
					if(s == true) break;
				}
			}
		} else if(t == 2) {		// Third Time
			if(one == two) {
				cout << "You rolled doubles" << endl;
				cout << "You get out of DC Tims Line successfully" << endl;
				p->move(sum, get_board()->get_pos_ptr(sum + 10));
				p->setstuck(false);
				p->setDCzero();
			} else {
				int num;
				cout << "You didn't roll doubles" << endl;
				bool success;
				while(true) {
					cout << "Are you gonna 1.pay $50 or 2.use a Roll Up the Rim cup to get out of DC Tims Line?" << endl;
					if(cin >> num) {
						if(num == 1) {
							none = p->withdraw(50, NULL, true);
							if(none == false) {
								p->decr_asst(50);
								cout << "You get out of DC Tims Line successfully" << endl;
								p->move(sum, get_board()->get_pos_ptr(sum + 10));
								p->setstuck(false);
								p->setDCzero();
							}
							success = true;
						} else if(num == 2) {
							int n = p->getCup();
							if(n == 0) {
								cout << "Not enough Roll Up the Rim cup, please choose agian" << endl;
								success = false;
							} else {
								p->decrCup();
								get_board()->incr_availCup();
								cout << "You get out of DC Tims Line successfully" << endl;
								p->move(sum, get_board()->get_pos_ptr(sum + 10));
								p->setstuck(false);
								p->setDCzero();
								success = true;
							}
						}
					} else {
						cout << "Invalid input, please choose again" << endl;
						success = false;
					}
					if(success == true) break;
				}
			}
		}
	}
}


std::string* Dctims::print() {
	player_str[0] = "|DC Tims";
	player_str[1] = "|Line   ";
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


// Function below are useless.

Player * Dctims::get_owner(){
	return NULL;
}
void Dctims::set_owner(Player * p){

}
int Dctims::getcost(){
	return 0;
}
void Dctims::set_mortgage(bool b){}

bool Dctims::get_mortgage() {
	return 0;
}

int Dctims::calculate_charge(){
	return 0;
}

int Dctims::get_imp() {
	return 0;
}

int Dctims::get_imp_cost() {
	return 0;
}

void Dctims::incr_imp() {}

int Dctims::get_street_no(){return -1;}

void Dctims::decr_imp() {}
