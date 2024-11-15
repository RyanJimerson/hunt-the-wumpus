#ifndef WUMPUS_HPP
#define WUMPUS_HPP
#include "event.hpp"

// TODO Wumpus interface (define the wumpus class and declare its member
// functions below)
class Wumpus : public event {
	void encounter(player& p);
	void print();
	void is_wumpus(player& p);
	//void event_location(int width, int height);
	void percept();
};


#endif
