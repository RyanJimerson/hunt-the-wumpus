#ifndef EVENT_HPP
#define EVENT_HPP
#include "player.hpp"
// Event interface
class event {
private:
	// TODO private members, if relevant
protected:
	// TODO protected members, if relevant
public:
	// TODO public members
	virtual void encounter(player& p) = 0;
	virtual void print() = 0;
	virtual void is_wumpus(player& p)=0;
	//virtual void event_location(int width, int height)=0;
	virtual ~event() = default;
	virtual void percept ()= 0;
};

#endif
