/************************************************
  block.cc
  Vesion 1.3
  CS246 - A5 - BB7K
************************************************/

#include "block.h"
#include <iostream>

Block::Block(int p, std::string n){
	pos = p;
	name = n;
	board = NULL;

	// Need to make change!!!
	player_str = new std::string[5];
	player_on_grid = new Player*[8];
	for(int i = 0; i < 8; ++i){
		player_on_grid[i] = NULL;
	}


}

int Block::get_pos() {
	return pos;
}

void Block::check_in(Player * p,int index){
	player_on_grid[index] =p;
}

void Block::check_out(int index){
	player_on_grid[index] = NULL;
}

void Block::init(Board *b ){
	board = b;
}
std::string Block::getname(){
	return name;
}

Board * Block::get_board(){
	return board;
}

Block::~Block(){
	delete [] player_on_grid;
	delete [] player_str;
}
