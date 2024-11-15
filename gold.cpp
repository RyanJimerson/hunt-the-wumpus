#include "gold.hpp"
#include <iostream>

// TODO Gold implementation (define gold member functions below)
void Gold::encounter(player& p){
	p.has_gold = true;
}

void Gold::print(){
	std::cout<<"G";
}

void Gold::is_wumpus(player& p){
	p.is_wumpus = false;
}

void Gold::percept(){
	std::cout<<"you see something shimmer nearby"<<std::endl;
} 
