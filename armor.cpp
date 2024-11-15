#include "armor.hpp"
#include <iostream>

// TODO Arrow implementation (define arrow member functions below)
void Armor::encounter(player& p){
	std::cout<<"you found the armor"<<std::endl;
	p.has_armor = true;
	p.armor = 2;
}

void Armor::print(){
	std::cout<<"A";
}

void Armor::is_wumpus(player& p){
	p.is_wumpus = false;
}

void Armor::percept(){
	std::cout<<"you feel the power"<<std::endl;
}
