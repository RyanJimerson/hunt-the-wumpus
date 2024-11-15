#ifndef GOLD_HPP
#define GOLD_HPP
#include "event.hpp"

// TODO Gold interface (define the gold class and declare its member functions
// below)
class Gold : public event {
	void encounter(player& p);
	void print();
	void is_wumpus(player& p);
	void percept();
};


#endif
