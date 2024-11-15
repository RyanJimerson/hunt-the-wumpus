#ifndef BATS_HPP
#define BATS_HPP
#include "event.hpp"

// TODO Bats interface (define the bats class and declare its member functions
// below)
class Bats : public event {
	void encounter();
	void print();
	void event_location(int width, int height);
};


#endif
