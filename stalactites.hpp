#ifndef STALACTITES_HPP
#define STALACTITES_HPP
#include "event.hpp"

// TODO Stalactites interface (define the stalactites class and declare its
// member functions below)
class Stalactites : public event {
private:
	int x = 0;
	int y = 0;
public:
	void encounter(player& p);
	void print();
	void is_wumpus(player& p);
	void event_location(int width, int height);
	void percept();
};

#endif
