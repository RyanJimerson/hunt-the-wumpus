#include <iostream>
#include "flashlight.hpp"

void Flashlight::encounter(player& p){
	p.has_flashlight = true;
}

void Flashlight::print(){
	std::cout<<"F";
}

void Flashlight::is_wumpus(player& p){
	p.is_wumpus =false;
}

void Flashlight::percept(){
	std::cout<<"you see a flashlight in an adjacent room"<<std::endl;
}
