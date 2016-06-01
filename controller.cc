#include <iostream>
#include "controller.h"
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>
using namespace std;

Controller::Controller(): numPlayer(0), index(0) {
	player = new Player *[8];
	for(int i = 0; i < 8; i++) {
		player[i] = NULL;
	}
	playername = "GBDPS$LT";
	s_name = "00000000";
	testing = false;
}

void Controller::set_testing() {
	testing = true;
}

void Controller::init(Board *b) {
	game = b;
}

bool read_decision(){
	char decision;
	while(true){
		std::cin >> decision;
		if (decision == 'y'){
			return true;
		}
		else if (decision == 'n'){
			return false;
		}
		else{
			std::cout << "Invalid Input, Please check that again" << std::endl;
		}
	}
}

Board *Controller::getgb() {
	return game;
}

void Controller::trade(Player * a, Player * b, int give, Block * receive){
	if (receive->get_imp() == 0){
		std::cout << "Player " << a->get_real_name() << " is starting trading process with " << b->get_real_name() << std::endl;
		// Check if property belongs to b.
		if (receive->get_owner() == NULL|| receive->get_owner()->getname() != b->getname()){
			std::cout << receive->getname() << " is not owned by " << b->get_real_name() << std::endl;
		}
		else if (a->get_money() < give){
			std::cout <<  a->get_real_name() << " has not suffcient fund." << std::endl;
		}
		else{
			std::cout << b->get_real_name()<<" , would you like to trade with Player? (y/n)" << std::endl;
			bool decision = read_decision();
			if (decision == true){
				// starting transaction

				bool success = a->withdraw(give,NULL,false);
				if (success == false){
					b->deposit(give);
					receive->set_owner(a);
					if (receive->get_pos() == 5 || receive->get_pos() == 15 || receive->get_pos() == 25 || receive->get_pos() == 35){
						//It is resident
						a->purchase_residence(receive);
						b->sell_residence(receive);
					}
					else if (receive->get_pos() == 12 || receive->get_pos() == 28){
						//It is= Gym
						a->purchase_gym(receive);
						b->sell_gym(receive);
					}
					else {
						a->purchase_academic(receive->get_street_no(),receive);
						b->sell_academic(receive->get_street_no(),receive);
					}
					cout << "Transaction Complete! " << endl;
				}
				else{
					std::cout << "Insufficient Fund, Transaction Declined" << std::endl;
				}
			}
			else{
				std::cout << "Transaction Declined" << std::endl;
			}

		}
	}
	else {
		std::cout << "You cannot trade a building with improvements" << std::endl;
	}
}

void Controller::trade(Player * a, Player * b, Block * give, Block * receive){
	if (receive->get_imp() == 0 && give->get_imp() == 0){
		std::cout << "Player " << a->get_real_name() << " is starting trading process with " << b->get_real_name() << std::endl;
		// Check if property belongs to b.
		if (give->get_owner() == NULL || give->get_owner()->getname() != a->getname()){
			std::cout << give->getname() << " is not owned by " << a->get_real_name() << std::endl;
		}
		if (receive->get_owner() == NULL || receive->get_owner()->getname() != b->getname()){
			std::cout << receive->getname() << " is not owned by " << b->get_real_name() << std::endl;
		}
		else{
			std::cout << b->get_real_name()<<" , would you like to trade with Player? (y/n)" << std::endl;
			bool decision = read_decision();
			if (decision == true){
				// starting transaction
				give->set_owner(b);
				receive->set_owner(a);

				if (give->get_pos() == 5 || give->get_pos() == 15 || give->get_pos() == 25 || give->get_pos() == 35){
					//It is resident
					b->purchase_residence(give);
					a->sell_residence(give);
				}
				else if (give->get_pos() == 12 || give->get_pos() == 28){
					//It is= Gym
					b->purchase_gym(give);
					a->sell_gym(give);
				}
				else {
					b->purchase_academic(give->get_street_no(),give);
					a->sell_academic(give->get_street_no(),give);
				}

				if (receive->get_pos() == 5 || receive->get_pos() == 15 || receive->get_pos() == 25 || receive->get_pos() == 35){
					//It is resident
					a->purchase_residence(receive);
					b->sell_residence(receive);
				}
				else if (receive->get_pos() == 12 || receive->get_pos() == 28){
					//It is= Gym
					a->purchase_gym(receive);
					b->sell_gym(receive);
				}
				else {
					a->purchase_academic(receive->get_street_no(),receive);
					b->sell_academic(receive->get_street_no(),receive);
				}
				std::cout << "Transaction Completed!" << std::endl;

			}
			else{
				std::cout << "Transaction Declined" << std::endl;
			}
		}
	}
	else {
		std::cout << "You cannot trade a building with improvements" << std::endl;
	}
}

void Controller::trade(Player * a, Player * b, Block * give, int receive){
	if (give->get_imp() == 0){
		std::cout << "Player " << a->get_real_name() << " is starting trading process with " << b->get_real_name() << std::endl;
		// Check if property belongs to b.
		if (give->get_owner() == NULL|| give->get_owner()->getname() != a->getname()){
			std::cout << give->getname() << " is not owned by " << a->get_real_name() << std::endl;
		}
		else if (b->get_money() < receive){
			std::cout <<  b->get_real_name() << " has not suffcient fund." << std::endl;
		}
		else{
			std::cout << b->get_real_name()<<" , would you like to trade with Player? (y/n)" << std::endl;
			bool decision = read_decision();
			if (decision == true){
				// starting transaction
				bool success = b->withdraw(receive,NULL,false);
				if (success == false){
					a->deposit(receive);
					give->set_owner(b);
					if (give->get_pos() == 5 || give->get_pos() == 15 || give->get_pos() == 25 || give->get_pos() == 35){
						//It is resident
						b->purchase_residence(give);
						a->sell_residence(give);
					}
					else if (give->get_pos() == 12 || give->get_pos() == 28){
						//It is= Gym
						b->purchase_gym(give);
						a->sell_gym(give);
					}
					else {
						b->purchase_academic(give->get_street_no(),give);
						a->sell_academic(give->get_street_no(),give);
					}
					cout << "Transaction Complete! " << endl;
				}
				else{
					std::cout << "Insufficient fund, Transaction Declined" << std::endl;
				}
			}
			else{
				std::cout << "Transaction Declined" << std::endl;
			}

		}
	}
	else{
		std::cout << "You cannot trade a building with improvements" << std::endl;
	}
}
void Controller::bankrupt(Player *p1, Player *p2) {
	string s1 = p1->get_real_name();
	string s2;
	if(p2 != NULL) s2 = p2->get_real_name();
	cout << s1 << " declared bankruptcy" << endl;
	int total = 0;
	if(p1 != NULL) {
		for(int i = 0; i < 40; i++) {
			if(p1->getown(i) != NULL) {
				if(p1->getown(i)->get_mortgage() == false) {
					++total;
				}
			}
		}
	}
	if(total != 0) {
		cout << "You still have property that is unmortgaged, so you cannot declare bankruptcy" << endl;
	} else {
		if(p2 != NULL) {
			p2->deposit(p1->get_money());
			cout << "It is " << s2 << "'s turn" << endl;
			for(int i = 0; i < 40; i++) {
				if(p1->getown(i) != NULL) {
					cout << "Are you going to receive " << p1->getown(i)->getname() << "by paying 10% to the Bank(y/n)" << endl;
					string s1;
					cin >> s1;
					bool none;
					if(s1 == "y") {
						int worth = p1->getown(i)->getcost() * .1;
						none = p2->withdraw(worth, NULL, false);
						if(none == false) {
							p2->decr_asst(worth);
							cout << "Are you going to unmortgage it(1) or leave it mortgaged(2)" << endl;
							cout << "You have to pay an additional 10% if you leave it mortgaged" << endl;
							string s2;
							cin >> s2;
							if(s2 == "1") {
								int mort = p1->getown(i)->getcost() * .5;
								none = p2->withdraw(mort, NULL, true);
								if(none == false) {
									cout << "Unmortgaged successfully" << endl;
									p1->getown(i)->set_owner(p2);
									p1->getown(i)->set_mortgage(false);
									int position = p1->getown(i)->get_pos();
									if (position == 5 || position == 15 || position == 25 || position == 35){
										p2->purchase_residence(p1->getown(i));
									}
									else if (position == 12  || position == 28){
										p2->purchase_gym(p1->getown(i));
									}
									else{
										p2->purchase_academic(p1->getown(i)->get_street_no(),p1->getown(i));
									}

									p2->incr_asst(mort);
								} else {
									cout << "Not enough asset, declaring bankruptcy" << endl;
								}
							} else if(s2 == "2") {
								none = p2->withdraw(worth, NULL, true);
								if(none == false) {
									cout << "Leave it mortgaged" << endl;
									int position = p1->getown(i)->get_pos();
									if (position == 5 || position == 15 || position == 25 || position == 35){
										p2->purchase_residence(p1->getown(i));
									}
									else if (position == 12  || position == 28){
										p2->purchase_gym(p1->getown(i));
									}
									else{
										p2->purchase_academic(p1->getown(i)->get_street_no(),p1->getown(i));
									}

								}
							}
						}
					}
				}
			}
		} else if(p2 == NULL) {
			cout << "All of " << s1 << "'s assets are return to the open market, and Auction Starts!" << endl;
			for(int i = 0; i < 40; i++) {
				if(p1->getown(i) != NULL) {
					auction(p1->getown(i), p1);
				}
			}
		}
		int numDC = p1->getDC();
		for(int i = 0; i < numDC; i++) {
			getgb()->incr_availCup();
		}
		int p1_index = p1->get_index();
		p1->get_pos_ptr()->check_out(p1->get_index());
		delete p1;
		player[p1_index] = NULL;
		numPlayer--;
		cout << "Please Manually input 'next' in order to continue the game." << endl;
	}
}

void Controller::addplayer(){
	string n;
	int player_no = 0;
	char name;
	bool available;
	bool max = false;
	int num;
	while(true) {		// To prevent wrong input.
		cout << "Please enter the number of players(2-8)" << endl;
		if(cin >> num) {
			if(num < 2 or num > 8) {
				cout << "Invalid input, please enter again" << endl;
				available = false;
			} else {
				numPlayer = num;
				available = true;
			}
		} else {
			cout << "Invalid input, please enter again" << endl;
			available = false;
		}
		if(available == true) break;
	}
	num = 0;
	while(true) {
		if(num < numPlayer) {
			cout << "Please choose one of the following pieces:" << endl;
			for(int i = 0; i < 8; i++) {
				if(playername[i] != '0') {
					cout << playername[i] << " ";
				}
			}
			cout << endl;
			if(cin >> name) {
				available = true;
			} else {
				cout << "Invalid input, please choose again" << endl;
				available = false;
			}
		} else {
			max = true;
		}
		if(available == true and max == false) {
			for(int i = 0; i < 8; i++) {
				if(player[i] != NULL) {
					if(player[i]->getname() == name) {
						cout << "Already taken. Please choose one of the following pieces agian:" << endl;
						for(int j = 0; j < 8; j++) {
							if(playername[j] != '0') {
								cout << playername[j] << " ";
							}
						}
						available = false;
						cout << endl;
					}
				}
			}
		}
		if(available == true and max == false) {
			if(name != 'G' and name != 'B' and name != 'D' and name != 'P' and name != 'S' and name != '$' and name != 'L' and name != 'T') {
				cout << "Invalid input. Please choose one of the following pieces again:" << endl;
				for(int j = 0; j < 8; j++) {
					if(playername[j] != '0') {
						cout << playername[j] << " ";
					}
				}
				available = false;
				cout << endl;
			}
		}
		if(available == true and max == false) {
			cout << "Please enter your name" << endl;
			cin >> n;
			Player *newp = new Player(name, n, player_no, 0, NULL,0,1500,false,0);
			++player_no;
			newp->init(this);
			player[num] = newp;
			++num;
			for(int i = 0; i < 8; i++) {
				if(playername[i] == name) {
					playername[i] = '0';
				}
			}
			for(int i = 0; i < 8; i++) {
				if(s_name[i] == '0') {
					s_name[i] = name;
				}
			}
			cout << "Successfully create a new piece." << endl;
		}
		if(max == true) {
			cout << "Created the number of players required" << endl;
			break;
		}
	}
}


int Controller::roll(){
	int one = rand() % 6 + 1;
	return one;
}

void Controller::play(bool load){
	if (load == false){
		// Initilize initial condition of player on board
		for(int i = 0; i < numPlayer; i++){
			game->get_pos_ptr(0)->check_in(player[i],player[i]->get_index());
			player[i]->set_block(0,game->get_pos_ptr(0));

		}
	}
	srand(time(NULL));
	int pn = 0; // Player Number
	bool moved = false;
	int doubles = 0;
	std::cout << "Game start!" << std::endl;
	game->printboard();
	cout << player[pn]->get_real_name() << "'s turn " << endl;
	string cmd;
	while (cin >> cmd) {

		if(cmd == "roll") {
			int one;
			int two;
			if(moved == true) {
				cout << "You have already rolled/moved" << endl;
				cout << "Please choose another command" << endl;
			} else {
				moved = true;
				if(player[pn]->getstuck() == true){
					player[pn]->move(10, getgb()->get_pos_ptr(10));
				} else {
					one = player[pn]->roll();
					two = player[pn]->roll();
					int sum = one + two;
					cout << "You rolled " << one << " and " << two << endl;
					int newpos = (player[pn]->getpos() + sum);
					if (newpos >= 40){
						newpos -= 40; // Collect Money
						std::cout << "passed by OSAP! get 200!" << std::endl;
						player[pn]->deposit(200);
						player[pn]->incr_asst(200);
					}
					if(one == two and doubles == 2) {
						cout << "It is your third time rolled doubles, you are moved to DC Tims Line" << endl;
						player[pn]->get_pos_ptr()->check_out(player[pn]->get_index());
						player[pn]->set_block(10, game->get_pos_ptr(10));
						doubles = 0;
						player[pn]->setstuck(true);
						moved = true;
						game->get_pos_ptr(10)->check_in(player[pn], player[pn]->get_index());
					} else if(one == two and doubles != 2){
						player[pn]->move(newpos, getgb()->get_pos_ptr(newpos));
						++doubles;
						cout << "You rolled doubles, you can roll again" << endl;
						moved = false;
					} else if(one != two) {
						player[pn]->move(newpos, getgb()->get_pos_ptr(newpos));
						moved = true;
					}
				}
			}
			game->printboard();
		} else if(cmd == "next"){
			if (moved == false){
				cout << "You haven't rolled yet, please roll!" << endl;
			}
			else{
				doubles = 0;
				moved = false;
				if(numPlayer == 1) {
					for(int i = 0; i < 8; i++) {
						if(player[i] != NULL) {
							pn = i;
							break;
						}
					}
				} else {
					if(pn == 7) {
						for(int i = 0; i < 8; i++) {
							if(player[i] != NULL) {
								pn = i;
								break;
							}
						}
					} else {
						++pn;
						while(1) {
							if(player[pn] != NULL) {
								break;
							}
							if(pn == 7) {
								pn = 0;
							} else {
								pn++;
							}
						}
					}
				}
				if(numPlayer == 1) {
					cout << player[pn]->get_real_name() << " won the game" << endl;
					break;
				}
				else{
					cout << player[pn]->get_real_name() << "'s turn " << endl;
				}
			}
		}
		else if(cmd == "trade") {
			string name;
			string give;
			string receive;

			cin >> name >> give >> receive;
			bool digitg = isdigit(give[0]);
			bool digitr = isdigit(receive[0]);
			int indg = 0;
			int indr = 0;
			int indp = 0;
			bool owng = false;
			bool ownr = false;
			bool pexist = false;

			while(indp < 8) {
				if(player[indp] != NULL) {
					if(player[indp]->get_real_name() == name) {
						pexist = true;
						break;
					}
				}
				++indp;
			}


			if (digitg == false){
				while(indg < 40) {
					if(player[pn]->getown(indg) != NULL && player[pn]->getown(indg)->getname() == give) {
						owng = true;
						break;
					}
					indg++;
				}
			}

			if (digitr == false){
				while(indr < 40) {
					if(player[indp]->getown(indr) != NULL && player[indp]->getown(indr)->getname() == receive) {
						ownr = true;
						break;
					}
					indr++;
				}
			}

			if(pexist == true) {
				while(indr < 40) {
					if(player[indp]->getown(indr) && player[indp]->getown(indr)->getname() == receive) {
						ownr = true;
						break;
					}
					++indr;
				}
			}

			if (digitg == true && digitr == true){
				cout << "Cannot trade money with money" << endl;
			}
			if(pexist == true and digitg == true and ownr == true) {
				int n = atoi(give.c_str());
				trade(player[pn], player[indp], n, player[indp]->getown(indr));
			}
			if(pexist == true and digitr == true and owng == true) {
				int nu = atoi(receive.c_str());
				trade(player[pn], player[indp], player[pn]->getown(indg), nu);
			}
			if(pexist == true and digitg == false and digitr == false) {
				trade(player[pn], player[indp], player[pn]->getown(indg), player[indp]->getown(indr));
			}
		}
		else if(cmd == "mortgage") {
			string pr2;
			cin >> pr2;
			int indx = 0;
			bool exist = false;
			while(indx < 40) {
				if(game->get_pos_name(indx) == pr2) {
					exist = true;
					break;
				}
				++indx;
			}
			if(exist == true) {
				player[pn]->mortgage(game->get_pos_ptr(indx));
			}
		} else if(cmd == "improve") {
			string pr3;
			string dec;
			cin >> pr3 >> dec;
			player[pn]->improve(pr3, dec);
			game->printboard();
		} else if(cmd == "unmortgage") {
			string pr4;
			cin >> pr4;
			int indx2 = 0;
			bool exist = false;
			while(indx2 < 40) {
				if(game->get_pos_name(indx2) == pr4) {
					exist = true;
					break;
				}
				++indx2;
			}
			if(exist == true) {
				player[pn]->unmortgage(game->get_pos_ptr(indx2));
			}
		} else if(cmd == "assets") {
			player[pn]->printasset();
		} else if(cmd == "bankrupt") {
			cout << "This command is not available" << endl;
		}
		else if (cmd == "save"){
			string filename;
			cout << "please input the file name you wish to save" << endl;
			cin >> filename;
			ofstream outputfile(filename.c_str());
			outputfile << numPlayer << endl;
			cout << "Saving Player Data.." << endl;
			for (int i = 0; i < numPlayer; i++){
				Player * p = player[i];
				outputfile << p->get_real_name() << " " << p->getname() << " " << p->getCup() << " " << p->get_money() << " " << p->getpos();
				if (p->getpos() == 10){
					outputfile << " " << p->getstuck();
					if (p->getstuck() == true){
						outputfile << " " << p->getDC();
					}
				}
				outputfile << endl;
			}
			cout << "Saving Grid Data.." << endl;
			for (int i = 0; i < 40; i++){
				Block * b = game->get_pos_ptr(i);
				if (b->get_owner() != NULL){
					outputfile << b->getname() << " " << b->get_owner()->getname() << " " << b->get_imp() << endl;
				}
			}
			cout << "Game saved to " << filename << endl;
		}

		else if(cmd == "exit" || cmd == "quit"){
			cout << "Exiting the game" << endl;
			break;
		}
	}

}

void Controller::auction(Block * b, Player * p){
	bool offer_made = false;
	int maxoffer = b->getcost();
	bool decision[8];
	int on_bid = numPlayer - 1;
	for (int i = 0; i < 8; i++){
		if (player[i] != NULL){
			decision[i] = true;
		}
	}
	decision[p->get_index()] = false;
	while(true){
		if (on_bid == 0 && offer_made == false){
			break;
		}
		for (int i = 0; i < 8; ++i){
			if (on_bid == 1 && offer_made == true){
				break;
			}
			if (player[i] != NULL){
				Player * current = player[i];
				if (decision[i] == true){
					int offer;
					std::cout << player[i]->get_real_name() << " would you like to make an offer to: " << b->getname() << "?" << std::endl;
					std::cout << "If you would like to make an offer, please type the amount you would like to pay for the product (if 0 means skip the round)" << std::endl;

					std::cout << "current highest offer: " << maxoffer << std::endl;
					cin >> offer;
					if (current->get_money() < offer){
						std::cout << "Insufficient Fund, Automatically decline" << std::endl;
						decision[i] = false;
						on_bid --;
					}
					else if (offer == 0){
						std::cout << "Player has declined the offer." << std::endl;
						decision[i] = false;
						on_bid --;
					}
					else if (offer < maxoffer){
						std::cout << "Lower than the highest offer. Skipped the round." << std::endl;
					}
					else {
						std::cout << "You made the bid successfully!" << std::endl;
						maxoffer = offer;
						offer_made = true;
					}
				}
			}
		}
		if (on_bid == 1){
			break;
		}
	}
	if(offer_made == true){
		for (int i = 0; i < 8; i++){
			if (player[i] != NULL){
				if (decision[i] == true){
					std::cout << player[i]->get_real_name() <<", You win the bid!!" << std::endl;
					b->set_owner(player[i]);
					player[i]->withdraw(maxoffer, NULL, false);
					int position = b->get_pos();
					if (position == 5 || position == 15 || position == 25 || position == 35){
						player[i]->purchase_residence(b);
					}
					else if (position == 12  || position == 28){
						player[i]->purchase_gym(b);
					}
					else{
						player[i]->purchase_academic(b->get_street_no(),b);
					}
				}
			}
		}
	}
	else{
		std::cout << "No One has made an offer, stay unchange." << std::endl;
	}
}
Controller::~Controller(){
	for (int i = 0; i < 8; i++){
		delete player[i];
	}
	delete [] player;
}

void Controller::load(std::string filename){
	int totalcup = 0;
	cout << "Reading Saved File..." << endl;
	ifstream f(filename.c_str());	
	std::string line;
	getline(f,line);
	istringstream ss(line);
	ss >> numPlayer;
	cout << "Number of Player: " << numPlayer << endl;
	cout << "Loading Player Profile" << endl;
	for (int i = 0; i < numPlayer; ++i){
		getline(f,line);
		istringstream ss(line);
		char rep;
		int timcups;
		int money;
		int position;
		bool stuck = false;
		int round = 0;
		std::string name;
		ss >> name >> rep >> timcups >> money >> position;
		if (position == 10){
			ss >> stuck;
			if (stuck == true){
				ss >> round;
			}
		}
		totalcup += timcups;
		if (totalcup > 4){
			cout << "Exceed Maximum Tim Cup! Please check if save file is correct" << endl;

		}
		for (int j = 0; j < timcups; j++){
			getgb()->decr_availCup();
		}

		player[i] = new Player(rep,name,i,position,game->get_pos_ptr(position),timcups,money,stuck,round);
		// check in on board.
		player[i]->init(this);
		game->get_pos_ptr(position)->check_in(player[i],i);
	}

	cout << "Loading Map Details" << endl;
	while (getline(f,line)){
		istringstream ss(line);
		std::string building_name;
		char owner;
		int improvements;
		ss >> building_name >> owner >> improvements;
		Player * p;
		Block * b;
		for (int j = 0; j < numPlayer; j++){
			if (player[j]->getname() == owner){
				p = player[j];
				break;
			}
		}
		for (int i = 0; i < 40; ++i){
			if (game->get_pos_ptr(i)->getname() == building_name){
				b = game->get_pos_ptr(i);
				break;
			}
		}
		for (int i = 0; i < improvements; ++i){
			b->incr_imp();
		}
		b->set_owner(p);
		p->incr_asst(b->getcost());
		if (improvements != 0){
			p->incr_asst(b->get_imp_cost() * improvements);
		}
		if (b->get_pos() == 5 || b->get_pos() == 15 || b->get_pos() == 25 || b->get_pos() == 35){
			//It is resident
			p->purchase_residence(b);
		}
		else if (b->get_pos() == 12 || b->get_pos() == 28){
			//It is= Gym
			p->purchase_gym(b);
		}
		else {
			p->purchase_academic(b->get_street_no(),b);
		}

	}
}
bool Controller::get_testing(){
	return testing;
}

