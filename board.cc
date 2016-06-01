/************************************************
  board.cc
  Vesion 1.3
  CS246 - A5 - BB7K
************************************************/

#include "board.h"
#include <iostream>
#include "academic.h"
#include "slc.h"
#include "collect.h"
#include "controller.h"
#include <iomanip>
#include <sstream>
#include "gym.h"
#include "tuition.h"
#include "residence.h"
#include "needles.h"
#include "dctims.h"
#include "slc.h"
#include "goose.h"
#include "coop.h"
#include "gotims.h"

Block * Board::get_pos_ptr(int i){
    return building[i];
}

std::string Board::get_pos_name(int i){
    return building[i]->getname();
}

Board::Board(){
    controller = NULL;
    // Position, block name, street number, cost, improvement cost, charge 1-6
    building[0] = new Collect();
    building[1] = new Academic(1,"AL",0,40,50,2,10,30,90,160,250);
    building[2] = new SLC(2);
    building[3] = new Academic(3,"ML",0,60,50,4,20,60,180,320,450);
    building[4] = new Tuition();
    building[5] = new Residence(5, "MKV");
    building[6] = new Academic(6,"ECH",1,100,50,6,30,90,270,400,550);
    building[7] = new Needles(7);
    building[8] = new Academic(8,"PAS",1,100,50,6,30,90,270,400,550);
    building[9] = new Academic(9,"HH",1,120,50,8,40,100,300,450,600);
    building[10] = new Dctims();
    building[11] = new Academic(11,"RCH",2,140,100,10,50,150,450,600,750);
    building[12] = new Gym(12, "PAC");
    building[13] = new Academic(13,"DWE",2,140,100,10,50,150,450,625,750);
    building[14] = new Academic(14,"CPH",2,160,100,12,60,180,500,700,900);
    building[15] = new Residence(15,"UWP");
    building[16] = new Academic(16,"LHI",3,180,100,14,70,200,550,750,950);
    building[17] = new SLC(17);
    building[18] = new Academic(18,"BMH",3,180,100,14,70,200,550,750,950);
    building[19] = new Academic(19,"OPT",3,200,100,16,80,220,600,800,1000);
    building[20] = new Goose();
    building[21] = new Academic(21,"EV1",4,220,150,18,90,250,700,875,1050);
    building[22] = new Needles(22);
    building[23] = new Academic(23,"EV2",4,220,150,18,90,250,700,875,1050);
    building[24] = new Academic(24,"EV3",4,240,150,20,100,300,750,925,1100);
    building[25] = new Residence(25,"V1");
    building[26] = new Academic(26,"PHYS",5,260,150,22,110,330,800,975,1150);
    building[27] = new Academic(27,"B1",5,260,150,22,110,330,800,975,1150);
    building[28] = new Gym(28, "CIF");
    building[29] = new Academic(28,"B2",5,280,150,24,120,360,850,1025,1200);
    building[30] = new Gotims();
    building[31] = new Academic(31,"EIT",6,300,200,26,130,390,900,1100,1275);
    building[32] = new Academic(32,"ESC",6,300,200,26,130,390,900,1100,1275);
    building[33] = new SLC(33);
    building[34] = new Academic(34,"C2",6,320,200,28,150,450,1000,1200,1400);
    building[35] = new Residence(25,"REV");
    building[36] = new Needles(36);
    building[37] = new Academic(37,"MC",7,350,200,35,175,500,1100,1300,1500);
    building[38] = new Coop();
    building[39] = new Academic(39,"DC",7,400,200,50,200,600,1400,1700,2000);
    availCup = 4;

}

void Board::init(Controller * c){
	controller = c;
	for (int i = 0; i < 40; ++i){
		building[i]->init(this);
	}
}

void Board::auction(Block * b, Player * p){
	controller->auction(b,p);
}

void Board::printboard(){

	// This is the LOGO appear on the middle of the board
	std::string logo[10];
	logo[0] = "------------------------------------------------";
	logo[1] = "|    ###     ###    #####   ###    ###    ###  |";
	logo[2] = "|    #  #    #  #      #   #   #  #   #  #   # |";
	logo[3] = "|    ####    ####     #    #   #  #   #  #   # |";
	logo[4] = "|    #   #   #   #   #     #   #  #   #  #   # |";
	logo[5] = "|    ####    ####   #       ###    ###    ###  |";
	logo[6] = "|                                              |";
	logo[7] = "------------------------------------------------";
	logo[8] = "           By: Andrew Wu & Simon Chen           ";
	logo[9] = "                                                ";

	std::cout<<"_________________________________________________________________________________________" << std::endl;
	for(int i = 0; i < 5; ++i){
		for(int j = 20; j <= 30; ++j){
			std::cout << (building[j]->print())[i];
		}
		std::cout << "|" << std::endl;
	}

	for(int i = 1; i < 5; ++i){
		for(int j = 0; j < 5; ++j){
			std::cout<< (building[20-i]->print())[j] + "|";
			std::cout << "                                                                       ";
			std::cout<< (building[30+i]->print())[j];
			std::cout<< "|" << std::endl;
		}

	}
	for(int j = 0; j < 5; ++j){
		std::cout << (building[15]->print())[j] + "|";
		std::cout << "            " << logo[j] << "           ";
		std::cout << (building[35]->print())[j];
		std::cout << "|" << std::endl;
	}
	for(int j = 0; j < 5; ++j){
		std::cout<< (building[14]->print())[j] + "|";
		std::cout << "            " << logo[j+5] << "           ";
		std::cout<< (building[36]->print())[j];
		std::cout<< "|" << std::endl;
	}
	for(int j = 0; j < 5; ++j){
		std::cout<< (building[13]->print())[j] + "|";
		std::cout << "                                                                       ";
		std::cout<< (building[37]->print())[j];
		std::cout<< "|" << std::endl;
	}

	for(int j = 0; j < 5; ++j){
		std::cout<< (building[12]->print())[j] + "|";
		std::cout << "                                                                       ";
		std::cout<< (building[38]->print())[j];
		std::cout<< "|" << std::endl;
	}

	for(int j = 0 ; j < 5; ++j){
		if(j == 4){
			std::cout << (building[11]->print())[j] + "|" << "_______________________________________________________________________" << (building[11]->print())[j] + "|" << std::endl;
		}else{
			std::cout<< (building[11]->print())[j] + "|";
			std::cout << "                                                                       ";
			std::cout<< (building[39]->print())[j];
			std::cout<< "|" << std::endl;
		}
	}
	for(int i = 0; i < 5; ++i){
		for(int j = 10; j >= 0; --j){
			std::cout << (building[j]->print())[i];
		}
		std::cout << "|" << std::endl;
	}
}
int Board::get_availCup() {
	return availCup;
}

void Board::incr_availCup() {
	++availCup;
}

void Board::decr_availCup() {
	--availCup;
}

Board::~Board(){
	for (int i = 0; i < 40; i++){
		delete building[i];
	}

}
