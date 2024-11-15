#ifndef FLASHLIGHT_HPP
#define FLASHLIGHT_HPP
#include "event.hpp"

// TODO Arrow interface (define the arrow class and declare its member functions
// below)
class Flashlight : public event {
	void encounter(player& p);
	void print();
	void event_location(int width, int height);
	void is_wumpus(player& p);
	void percept();
};


#endif
