#include "wumpus.hpp"
#include <iostream>

// TODO Wumpus implementation (define wumpus member functions below)
void Wumpus::encounter(player& p){
	std::cout<<"you were attacked by the wumpus"<<std::endl;
	if (p.armor >0){
		p.armor-=1;
	}else{
		p.hp -= 1;
	}
}

void Wumpus::print(){
	std::cout<<"W";
}

void Wumpus::is_wumpus(player& p){
	p.is_wumpus = true;
}

void Wumpus::percept(){
	std::cout<<"you smell a terrible stench"<<std::endl;
}
