#ifndef __CONTROLLER__
#define __CONTROLLER__
#include "board.h"
#include "player.h"

class Board;
class Player;

class Controller{

	protected:
		Board * game;
		//GraphicDisplay * gd;
		//Textdisplay * td;
		Player **player;
		std::string playername;
		std::string s_name;
		int numPlayer;
		int index;
		bool testing;

	public:
		~Controller();
		void set_testing();
		Controller();
		void init(Board *);
		Board *getgb();
		void addplayer();
		int roll();
		void play(bool);
		void save(std::string);
		void trade(Player * a, Player * b, int give, Block * receive);
		void trade(Player * a, Player * b, Block * give, int receive);
		void trade(Player * a, Player * b, Block * give, Block * receive);
		void bankrupt(Player *, Player *);
		void auction(Block * b, Player * p);
		void load(std::string);
		bool get_testing();
};
#endif
