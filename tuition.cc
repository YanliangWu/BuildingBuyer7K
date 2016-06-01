/************************************************
  tuition.cc
  Vesion 1.3
  CS246 - A5 - BB7K
************************************************/
#include <iostream>
#include "tuition.h"
#include "player.h"
#include <sstream>
#include <iomanip>

using namespace std;


Tuition::Tuition(): Block(4, "TUITION") {}

void Tuition::land(Player *p) {
	bool none;
	cout << "You had landed on the Tuition!" << endl;
	check_in(p,p->get_index());
	cout << "Choose number 1 or 2:" << endl;
	cout << "1 represents paying $300." << endl;
	cout << "2 represents paying 10% of your total worth. Plus, your total worth is $" << p->asset() << endl;
	int num;
	cin >> num;
	while(true) {
		bool valid = true;
		if(num != 1 and num !=2) {
			valid = false;
			cout << "Invalid input. Please choose the number again:" << endl;
			cin >> num;
		}
		if(valid == true) break;
	}
	if(num == 1) {
		none = p->withdraw(300, NULL, true);
		if(none == false) {
			p->decr_asst(300);
		}
	} else if(num == 2) {
		int total = p->asset();
		none = p->withdraw(total * .1, NULL, true);
		if(none == false) {        
			p->decr_asst(total * .1);
		}
	}
}

std::string* Tuition::print() {
	player_str[0] = "|TUITION";
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
Player * Tuition::get_owner(){
	return NULL;
}
void Tuition::set_owner(Player * p){

}
int Tuition::getcost(){
	return 0;
}
void Tuition::set_mortgage(bool b){}

bool Tuition::get_mortgage() {
	return 0;
}

int Tuition::calculate_charge(){
	return 0;
}

int Tuition::get_imp() {
	return 0;
}

int Tuition::get_imp_cost() {
	return 0;
}

void Tuition::incr_imp() {}
int Tuition::get_street_no(){return -1;}
void Tuition::decr_imp() {}
