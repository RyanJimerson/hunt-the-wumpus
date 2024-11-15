#include "stalactites.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

// TODO Stalactites implementation (define stalactites member functions below)
//
//
void Stalactites::encounter(player& p){
	int random = rand()%2;
	if(random == 1){
		std::cout<<"a stalactite fell on you"<<std::endl;
	}
	if (p.armor >0){
		p.armor-=random;
	}else{
		p.hp -= random;
	}

}
void Stalactites::event_location(int width, int height) {
//	this -> y = rand()%height;
//	int x = rand()%width;
}

void Stalactites::print(){
	std::cout<<"S";
}

void Stalactites::is_wumpus(player& p){
	p.is_wumpus = false;
}

void Stalactites::percept(){
	std::cout<<"you hear water dripping"<<std::endl;
}
