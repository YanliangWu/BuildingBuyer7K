/************************************************
  sla.cc
  Vesion 1.3
  CS246 - A5 - BB7K
************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "slc.h"
#include <sstream>
#include <iomanip>

using namespace std;

SLC::SLC(int pos): Block(pos, "SLC") {}

void SLC::land(Player *p) {
    cout << "You had landed on the SLC!" << endl;
    check_in(p,p->get_index());
	int current_pos = p->getpos();
	int current = current_pos;
	int dis;
    bool winCup;
	srand(time(NULL));
	int i = rand() % 24 + 1;
	int a = get_board()->get_availCup();
	if(a != 0) {
		int num = rand() % 100 + 1;
		if(num == 1) {
			cout << "Congrats, you receive a winning Roll Up the Rim cup" << endl;
			p->incrCup();
			get_board()->decr_availCup();
			winCup = true;
		} else {
			winCup = false;
		}
	} else {
		winCup = false;
	}
	if(winCup == false) {
		if(i >= 1 and i <= 22) {
			if(i >= 1 and i <= 3) {
				cout << "Back 3" << endl;
				current -= 3;
			} else if(i >= 4 and i <= 7) {
				cout << "Back 2" << endl;
				current -= 2;
			} else if(i >= 8 and i <= 11) {
				cout << "Back 1" << endl;
				current -= 1;
			} else if(i >= 12 and i <=14) {
				cout << "Forward 1" << endl;
				current += 1;
			} else if(i >= 15 and i <= 18) {
				cout << "Forward 2" << endl;
				current += 2;
			} else if(i >= 19 and i <= 22) {
				cout << "Forward 3" << endl;
				current += 3;
			}
			string n = get_board()->get_pos_name(current);
			cout << "You are moved to " << n << endl;
		} else {
			if(i == 23) {
				cout << "Go to DC Tims Line" << endl;
				current = 10;
				p->setstuck(true);
			} else if(i == 24) {
				cout << "Advance to Collect OASP" << endl;
				p->deposit(200);
				p->incr_asst(200);
				cout << "Collect $200 OSAP" << endl;
				current = 0;
			}
			dis = current - current_pos;
			if(dis >=  0) {
				cout << "You have forwarded " << dis << endl;
			} else {
				int d = 40 + dis;
				cout << "You have forwarded " << d << endl;
			}
		}
		p->move(current, get_board()->get_pos_ptr(current));
	}
}

std::string* SLC::print() {
	player_str[0] = "|SLC    ";
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
Player * SLC::get_owner(){
	return NULL;
}
void SLC::set_owner(Player * p){

}
int SLC::getcost(){
	return 0;
}
void SLC::set_mortgage(bool b){}

bool SLC::get_mortgage() {
	return 0;
}

int SLC::calculate_charge(){
	return 0;
}

int SLC::get_imp() {
	return 0;
}

int SLC::get_imp_cost() {
	return 0;
}

void SLC::incr_imp() {}
int SLC::get_street_no(){return -1;}
void SLC::decr_imp() {}
