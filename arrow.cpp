#include "arrow.hpp"
#include <iostream>

// TODO Arrow implementation (define arrow member functions below)
void Arrow::encounter(player& p){
	p.has_arrow = true;
}

void Arrow::print(){
	std::cout<<">";
}

void Arrow::is_wumpus(player& p){
	p.is_wumpus = false;
}

void Arrow::percept(){
	std::cout<<"you see an arrow on the ground in an adjacent room"<<std::endl;
}
