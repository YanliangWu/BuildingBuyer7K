//
//  main.cpp
//  A5
//
//  Created by Yanliang Wu on 2015-07-20.
//  Copyright (c) 2015 Yanliang Wu. All rights reserved.
//
#include "block.h"
#include "academic.h"
#include "board.h"
#include "collect.h"
#include "controller.h"
#include "coop.h"
#include "dctims.h"
#include "goose.h"
#include "gotims.h"
#include "gym.h"
#include "needles.h"
#include "residence.h"
#include "slc.h"
#include "tuition.h"
#include <cstring>
#include <fstream>
int main(int argc, char * argv[]){
	Controller *a = new Controller;
	std::cout << "\x1B""[2J" << "\33[1;1f";
	std::cout << "Welcome to Building Buyer 7000" << std::endl;
	
	if(argc == 2 && strcmp("-testing" , argv[1]) == 0) {
		std::cout << "Initializing Testing Mode" << std::endl;
		a->set_testing();
	}
	Board *b = new Board;
	a->init(b);
	b->init(a);
	b->printboard();
	if (argc == 3 && strcmp("-load" , argv[1]) == 0){
		std::cout << "Loading Game file " << argv[2] << std::endl;
		a->load(argv[2]);
		a->play(true);
	}
	if (argc == 4){
		for (int i = 1; i < argc; i++){
			if (strcmp("-testing" , argv[i]) == 0){
				std::cout << "Initializing Testing Mode" << std::endl;
				a->set_testing();
			}
			if (strcmp("-load" , argv[i]) == 0){
				a->load(argv[i+1]);
				a->play(true);
			}
		}
	}
	else{
		a->addplayer();
		a->play(false);
	}
	
	delete a;
	delete b;
}
/*
   int main(){
   Controller *a = new Controller;
   Board *b = new Board;
   a->init(b);
   b->init(a);
   b->printboard();
   }
 */
