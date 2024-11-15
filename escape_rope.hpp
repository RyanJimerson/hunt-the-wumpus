#ifndef ESCAPE_ROPE_HPP
#define ESCAPE_ROPE_HPP
#include "event.hpp"

// TODO Escape rope interface (define the escape_rope class and declare its
// member functions below)
class escape_rope : public event {
	void encounter(player& p);
	void print();
	void is_wumpus(player& p);
	void event_location(int width, int height);
	void percept();
};


#endif
