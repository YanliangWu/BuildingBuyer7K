// player
// version : 1.0.0
#include "player.h"
#include <cstdlib>
using namespace std;

// Default ctor
Player::Player(char n, std::string r_name, int index, int position, Block * pstr, int timcups, int mon, bool stucked, int round){
	idx = index;
	name = n;
	real_name = r_name;
	pos = position;
	pos_ptr = pstr;
	stuck = stucked;
	money = mon;
	asst = mon;
	owned_gym = 0;
	owned_residence = 0;
	for(int i = 0; i < 40; i++) {
		owned[i] = NULL;
	}
	for (int i = 0; i < 8; i++){
		owned_street[i] = 0;
	}
	DC = round;
	Cup = timcups;
}

// return the index of player
int Player::get_index(){
	return idx;
}

void Player::init(Controller *controller) {
	c = controller;
}

int Player::getDC() {
	return DC;
}

void Player::incrDC() {
	++DC;
}

int Player::getCup() {
	return Cup;
}

// mutate the timcups
void Player::incrCup() {
	++Cup;
}

void Player::decrCup() {
	--Cup;
}

// Set the player to the block.
// the difference between set_block and move is that
// set_block will not excecute the land command.
void Player::set_block(int p,Block * ptr){
	pos = p;
	pos_ptr = ptr;
}

char Player::getname() {
	return name;
}

void Player::deposit(int n){
	cout << "Successfully deposit $" << n << " to " << real_name << endl;
	money += n;
}

// If not enough money, will declear bankrupt
bool Player::withdraw(int n, Player *p, bool must){
	int total;
	bool drop;
	bool p_bankrupt = false;
	while(money < n) {
		total = 0;
		cout << "Not enough money, you have to mortgage" << endl;
		for(int i = 0; i < 40; i++) {
			if(owned[i] != NULL) {
				if(owned[i]->get_mortgage() == false) {
					++total;
				}
			}
		}
		if(total == 0) {
			cout << "You don't have enough assets to pay" << endl;
			if(must == true) {
				drop = true;
				cout << "Enter command to bankrupt" << endl;
				string s;
				cin >> s;
				if(s == "bankrupt") {
					cout << real_name << "declared bankruptcy" << endl;
					c->bankrupt(this, p);
					p_bankrupt = true;
				}
			} else {
				cout << "Please choose another command" << endl;
				drop = true;
			}
			break;
		} else {
			cout << "Please enter the property name are you going to mortgage" << endl;
			cout << "The property that you have and is not mortgaged is listed below" << endl;
			for(int i = 0; i < 40; i++) {
				if(owned[i] != NULL) {
					if(owned[i]->get_mortgage() == false) {
						cout << owned[i]->getname() << endl;
					}
				}
			}
			string name;
			cin >> name;
			bool own = false;
			for(int i = 0; i < 40; i++) {
				if(owned[i] != NULL) {
					if(owned[i]->getname() == name) {
						mortgage(owned[i]);
						own = true;
					}
				}
			}
			if(own == false) {
				cout << "Not such property, mortgage failed" << endl;
			}
		}
	}
	if(p_bankrupt == false) {
		if(money >= n) {
			cout << "Successfully withdraw $" << n << " from " << real_name << endl;
			money -= n;
			drop = false;
		}
	}
	return drop;
}

void Player::move(int new_pos, Block * new_pos_ptr){
	pos_ptr->check_out(idx);
	pos = new_pos;
	pos_ptr = new_pos_ptr;
	new_pos_ptr->land(this);
}

int Player::getpos(){
	return pos;
}

bool Player::getstuck(){
	return stuck;
}

int Player::roll(){

	int one;
	if (c->get_testing() == false){
		one = rand() % 6 + 1;
	}
	else{
		cin>>one;
	}

	return one;
}


Block *Player::getown(int i) {
	return owned[i];
}

void Player::mortgage(Block * b){
	if(b->get_owner() != NULL) {
		if (b->get_owner()->getname() == name){
			if(b->get_mortgage() == false) {
				if(b->get_imp() == 0) {
					b->set_mortgage(true);
					int cost = b->getcost();
					money += cost * .5;
					asst -= cost * .5;
					cout << "Successfully mortgaged " << b->getname() << endl;
					cout << "You received $" << cost * .5 << endl;
				} else {
					cout << "The improvement level of this building is " << b->get_imp() << endl;
					cout << "You have to sell all of the improvements before mortgaging" << endl;
				}
			} else {
				cout << "This property has already been mortgaged, you cannot mortgage it twice" << endl;
			}
		} else {
			cout << "This property does not belong to you" << endl;
		}
	} else {
		cout << "This property does not belong to you" << endl;
	}
}

void Player::unmortgage(Block *b){
	if(b->get_owner() != NULL) {
		if (b->get_owner()->getname() == name){
			if(b->get_mortgage() == true) {
				b->set_mortgage(false);
				int cost = b->getcost();
				int total_cost = cost * .5 + cost * .5 * .1;
				bool none = withdraw(total_cost, NULL, false);
				asst -= cost * .5 * .1;
				cout << "Successfully unmortgaged " << b->getname() << endl;
			} else {
				cout << "This property is unmortgaged, you cannot unmortgage it twice" << endl;
			}
		} else {
			cout << "This property does not belong to you" << endl;
		}
	} else {
		cout << "This property does not belong to you" << endl;
	}
}
void Player::setstuck(bool i){
	stuck = i;
}
std::string Player::getpos_name(){
	return pos_ptr->getname();
}

void Player::purchase_gym(Block *b){
	owned_gym ++;
	owned[b->get_pos()] = b;
}


void Player::sell_gym(Block *b){
	owned_gym --;
	owned[b->get_pos()] = NULL;
}


void Player::purchase_residence(Block *b){
	owned_residence ++;
	owned[b->get_pos()] = b;
}


void Player::sell_residence(Block *b){
	owned_residence --;
	owned[b->get_pos()] = NULL;
}
int Player::get_gym(){
	return owned_gym;
}
int Player::get_residence(){
	return owned_residence;
}
int Player::get_money(){
	return money;
}
void Player::purchase_academic(int n, Block *b){
	owned_street[n] ++;
	owned[b->get_pos()] = b;
}
void Player::sell_academic(int n, Block *b){
	owned_street[n] --;
	owned[b->get_pos()] = NULL;
}
int Player::get_academic(int n){
	return owned_street[n];
}
std::string Player::get_real_name(){
	return real_name;
}

int Player::asset() {
	return asst;
}

void Player::printasset(){
	cout << real_name << "owns:" << endl;
	cout << "$" << money << endl;
	for(int i = 0; i < 40; i++) {
		if(owned[i] != NULL) {
			cout << owned[i]->getname() << " Improvement Level: " << owned[i]->get_imp() << endl;
		}
	}
}

void Player::improve(string n, string decision) {
	bool own = false;
	bool imp = true;
	for(int i = 0; i < 40; i++) {
		Board * b = c->getgb();
		if(c->getgb()->get_pos_name(i) == n) {
			if(b->get_pos_ptr(i)->get_imp_cost() != 0) {
				if(c->getgb()->get_pos_ptr(i)->get_owner() != NULL) {
					if(c->getgb()->get_pos_ptr(i)->get_owner()->getname() == name) {
						int co = owned[i]->get_imp_cost();
						own = true;
						if(decision == "buy") {
							if(c->getgb()->get_pos_ptr(i)->get_imp() == 5) {
								cout << "Already built 5 improvements" << endl;
							} else {
								int max_owned[8] = {2,3,3,3,3,3,3,2};
								if(b->get_pos_ptr(i)->get_imp() == 4) {
									int no_street = b->get_pos_ptr(i)->get_street_no();
									if(owned_street[no_street] == max_owned[no_street]) {
										imp = true;
									} else {
										imp = false;
										cout << "Cannot improve to level 5 since you do not own the monopoly block" << endl;
									}
								} else {
									imp = true;
								}
								if(imp == true) {
									while(co > money) {
										cout << "Not enough money, are you gonna mortgage(y/n)" << endl;
										string s;
										cin >> s;
										if(s == "y") {
											bool own_mort = false;
											cout << "The property that you have and is mortgaged is listed below" << endl;
											for(int j = 0; j < 40; j++) {
												if(owned[j] != NULL) {
													if(owned[j]->get_mortgage() == false) {
														cout << owned[j]->getname() << endl;
													}
												}
											}
											cout << "Please enter the name of the property you want to mortgage" << endl;
											string n1;
											cin >> n1;
											for(int j = 0; j < 40; j++) {
												if(owned[j] != NULL) {
													if(owned[j]->getname() == n1) {
														own_mort = true;
														mortgage(owned[j]);
													}
												}
											}
											if(own_mort == false) {
												cout << "Not such property, mortgage failed" << endl;
											}
										} else if(s == "n") {
											cout << "You choose not to mortgage, improving failed" << endl;
											break;
										}
									}
									if(co <= money) {
										money -= co;
										owned[i]->incr_imp();
										cout << "Successfully improved" << endl;
										cout << "Improvement level: " << owned[i]->get_imp() << endl;
									}
								}
							}
						} else if(decision == "sell") {
							if(owned[i]->get_imp() != 0) {
								owned[i]->decr_imp();
								cout << "Successfully sold improvement" << endl;
								cout << "Improvement level: " << owned[i]->get_imp() << endl;
								money += co * .5;
								asst -= co * .5;
							} else {
								cout << "You cannot sell improvement on a property with 0 improvement" << endl;
							}
						}
					}
				}
			} else {
				imp = false;
				cout << "This place cannot be improved since it is not academic building" << endl;
				break;
			}
		}
	}
	if(own == false and imp == true) {
		cout << "You cannot improve this property since you do not own it" << endl;
	}
}

void Player::setDCzero() {
	DC = 0;
}

void Player::incr_asst(int i) {
	asst += i;
}

void Player::decr_asst(int i) {
	asst -= i;
}
Block * Player::get_pos_ptr(){
	return c->getgb()->get_pos_ptr(pos);
}
