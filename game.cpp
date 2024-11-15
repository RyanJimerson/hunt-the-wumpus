#include <iostream>
#include <vector>

#include <cstdlib>
#include <ctime>
#include "flashlight.hpp"
#include "armor.hpp"
#include "player.hpp"
#include "game.hpp"
#include "gold.hpp"
#include "bats.hpp"
#include "stalactites.hpp"
#include "wumpus.hpp"
#include "escape_rope.hpp"
#include "arrow.hpp"

// game implementation

game::game(int width, int height, bool debug) :
		width(width),
		height(height),
		debug(debug) {
	// TODO Create the game board: 2D vector of room objects
		std::vector < std::vector < event* > > cave (width, std::vector <event*> (height));
		//Stalactites S1;
		//S1.event_location(width, height);
		//Room R;
		std::cout<<"1"<<std::endl;
		for (int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				cave[i][j] = nullptr;
			}
		}
		cave[rand()%height][rand()%width] = new Stalactites;
		cave[rand()%height][rand()%width] = new Stalactites;
		int y;
		int x;
		bool first = true;
		do{
			x = rand()%width;
			y = rand()%height;
			if (cave[y][x] == nullptr){
				this-> escape_x = x;
				this->escape_y = y;
				this->player_x_coord = x;
				this->player_y_coord = y;
				cave[y][x] = new escape_rope;
				first = false;
			}
		}while(first);
		first =true;
		do{
			x = rand()%width;
			y = rand()%height;
			if (cave[y][x] == nullptr){
				this-> gold_x = x;
				this->gold_y = y;
				cave[y][x] = new Gold;
				first = false;
			}
		}while(first);
		first = true;
		do{
			x = rand()%width;
			y = rand()%height;
			if (cave[y][x] == nullptr){
				this-> arrow1_x = x;
				this->arrow1_y = y;
				cave[y][x] = new Arrow;
				first = false;
			}
		}while(first);
		first=true;
		do{
			x = rand()%width;
			y = rand()%height;
			if (cave[y][x] == nullptr){
				this-> arrow2_x = x;
				this->arrow2_y = y;
				cave[y][x] = new Arrow;
				first = false;
			}
		}while(first);
		first=true;
		do{
			x = rand()%width;
			y = rand()%height;
			if (cave[y][x] == nullptr){
				cave[y][x] = new Armor;
				first = false;
			}
		}while(first);
		first=true;
		do{
			x = rand()%width;
			y = rand()%height;
			if (cave[y][x] == nullptr){
				cave[y][x] = new Wumpus;
				first = false;
			}
		}while(first);
		first=true;
		do{
			x = rand()%width;
			y = rand()%height;
			if (cave[y][x] == nullptr){
				this->flashlight_x = x;
				this->flashlight_y = y;
				cave[y][x] = new Flashlight;
				first = false;
			}
		}while(first);

		this->cave = cave;
		std::cout<<"2"<<std::endl;
	// TODO Randomly insert events (2 bats, 2 stalactites, 1 wumpus, 1 gold,
	// 2 arrows, 1 escape rope) into the board
}

void game::display_game() const{
	std::cout << std::endl << std::endl;
	std::cout << "Arrows remaining: " << this->num_arrows << std::endl;

	std::string row_border = "--";
	for (int i = 0; i < this->width; ++i) {
		row_border += "-----";
	}
	
	std::cout << row_border << std::endl;
	for (int i = 0; i < this->height; ++i) {
		std::cout << "||";
		for (int j = 0; j < this->width; ++j) {
			// The first char indicates whether there is a player in the room
			// at row index i, column index j. TODO If the room contains the
			// player, print an asterisk ("*")
			if(this->player_x_coord == j && this->player_y_coord == i){
				std::cout<<"*";
			}else{
				std::cout<<" ";
			}
			// TODO else, print a space (" ")

			// The next char indicates the event in the room.
			
			// TODO If debug mode is disabled OR the room at location <i, j>
			// does not have an event, print a space (" ")
			// For example:
			if(!this->debug && this->cave[i][j]!= nullptr && this->has_flashlight == true){
					//std::cout<<"you have the flashlight"<<std::endl;
					if(this->player_y_coord == i){// || this->player_x_coord == j){
						cave[i][j]->print();
						//std::cout<<"flashlight y"<<std::endl;
					}else if(this->player_x_coord == j){
						cave[i][j]->print();
						//std::cout<<"flashlight x"<<std::endl;
					}else{
						std::cout<<" ";
					}
			 }else if (!this->debug || this->cave[i][j] == nullptr ) {
			 	std::cout << " ";
			 	//if(p.has_flashlight == true){
			/*}else if(!this->debug){// && this->has_flashlight == true){
					std::cout<<"you have the flashlight"<<std::endl;
					if(this->player_y_coord == i){// || this->player_x_coord == j){
						cave[i][j]->print();
						//std::cout<<"flashlight y"<<std::endl;
					}
					if(this->player_x_coord == j){
						cave[i][j]->print();
						//std::cout<<"flashlight x"<<std::endl;
					}
			*/	
			 }else{
				cave[i][j]->print();
				//std::cout<<"e";
			}
			//
			// TODO else, print the room's debug symbol. There are a few ways to
			// do this. You can use polymorphism, or an event could have a
			// char debug_symbol member variable and some sort of
			// get_debug_symbol() member function that you could call here
			// to get the character and print it.


			std::cout << " ||";
		}
		std::cout << std::endl;
		std::cout << row_border << std::endl;
	}

	//example output (when finished): 
	// ----------------------
	// || P || G || P ||   ||
	// ----------------------
	// ||   || W ||   || S ||
	// ----------------------   
	// ||   ||   ||   || S ||
	// ----------------------   
	// ||*  ||   ||   ||   ||
	// ----------------------
}

bool game::check_win(player& p) const{
	// TODO Delete the below placeholder code. Return true if the player
	// has won the game. Return false otherwise.
	if(p.has_gold == true && this->player_x_coord == this->escape_x && this->player_y_coord == this->escape_y){
		std::cout<<std::endl;
		std::cout<<"you escaped with the gold. you win"<<std::endl;
		return true;
	}else if(this->wumpus_is_dead == true){
		std::cout<<"you killed the wumpus"<<std::endl;
		return true;
	}
	//std::cout << "game::check_win() is not implemented..." << std::endl;
	return false;
}

bool game::check_lose(player& p) const{
	// TODO Delete the below placeholder code. Return true if the player
	// has lost the game. Return false otherwise.
	if(p.hp<=0){
		return true;
	}
	//std::cout << "game::check_lose() is not implemented..." << std::endl;
	return false;
}

bool game::is_direction(char c) {
	return c == 'w' ||
		c == 'a' ||
		c == 's' ||
		c == 'd';
}

char game::to_lower(char direction) {
	if (direction >= 'A' && direction <= 'Z') {
		return direction + ('a' - 'A');
	}
	return direction;
}

bool game::can_move_in_direction(char direction) {
	// TODO Delete the below placeholder code. Return true if the player can
	// move in the given direction ('w' for up, 'a' for left, 's' for down,
	// 'd' for right). Return false otherwise. The player can move in the
	// given direction so long as it wouldn't cause them to move off the
	// grid.
	if (direction == 'w'){
		this->player_y_coord -= 1;
		//p.y_coord-=1
		if(this->player_y_coord<0){
			this->player_y_coord+=1;
			//p.y_coord+=1
			return false;
		}else{
			this->player_y_coord+=1;
			//p.y_coord+=1;
		}
	}
	if (direction == 'a'){
		this->player_x_coord -= 1;
		//p.x_coord-=1;
		if(this->player_x_coord<0){
			this->player_x_coord +=1;
			//p.x_coord+=1;
			return false;
		}else{
			this->player_x_coord +=1;
			//p.x_coord+=1
		}
	}
	if (direction == 's'){
		this->player_y_coord += 1;
		//p.y_coord +=1;
		if(this->player_y_coord>this->height-1){
			this->player_y_coord -=1;
			//p.y_coord-=1;
			return false;
		}else{
			this->player_y_coord -=1;
			//p.y_coord-=1;
		}
	}
	if (direction == 'd'){
		this->player_x_coord += 1;
		//p.x_coord+=1;
		if(this->player_x_coord>this->width-1){
			this->player_x_coord -=1;
			//p.x_coord-=1;
			return false;
		}else{
			this->player_x_coord -=1;
			//p.x_coord-=1;
		}
	}

	std::cout << " " <<
		std::endl;
	return true;
}

bool game::is_valid_action(char action) {
	if (this->is_direction(action)) {
		char direction = action;
		return this->can_move_in_direction(direction);
	} else if (action == 'f') {
		return this->num_arrows > 0;
	}
	return false;
}

void game::print_action_error(char action) {
	if (this->is_direction(action)) {
		std::cout << "You can't move in that direction!" << std::endl <<
			std::endl;
	} else if (action == 'f') {
		std::cout << "You're out of arrows!" << std::endl << std::endl;
	} else {
		std::cout << std::endl << "That's an invalid input!" << std::endl
			<< std::endl;
	}
}

char game::get_player_action() {
	char action;
	bool first = true;
	do {
		if (!first) {
			char previous_action = action;
			this->print_action_error(previous_action);
		}
		first = false;

		std::cout << std::endl << std::endl << "What would you like to do?" <<
			std::endl << std::endl;
		std::cout << "w: move up" << std::endl;
		std::cout << "a: move left" << std::endl;
		std::cout << "s: move down" << std::endl;
		std::cout << "d: move right" << std::endl;
		std::cout << "f: fire an arrow" << std::endl;

		std::cin >> action;
		action = this->to_lower(action);
	} while (!this->is_valid_action(action));

	return action;
}

char game::get_arrow_fire_direction() {
	char direction;
	bool first = true;
	do {
		if (!first) {
			std::cout << std::endl << "That's an invalid input!" <<
				std::endl << std::endl;
		}
		first = false;

		std::cout << std::endl << std::endl <<
			"What direction would you like to fire the arrow?" << std::endl <<
			std::endl;
		std::cout << "w: up" << std::endl;
		std::cout << "a: left" << std::endl;
		std::cout << "s: down" << std::endl;
		std::cout << "d: right" << std::endl;

		std::cin >> direction;
		direction = this->to_lower(direction);
	} while (!this->is_direction(direction));

	return direction;
}

void game::move_up() {
	// TODO Delete the below placeholder code. Move the player up one
	// space in the grid, however you choose to do that.
	this->player_y_coord -= 1;
	//p.y_coord-=1;
	std::cout << " " << std::endl;
}

void game::move_down() {
	// TODO Delete the below placeholder code. Move the player down one
	// space in the grid, however you choose to do that.
	this->player_y_coord += 1;
	//p.y_coord +=1;
	std::cout << " " << std::endl;
}

void game::move_left() {
	// TODO Delete the below placeholder code. Move the player left one
	// space in the grid, however you choose to do that.
	this->player_x_coord -= 1;
	//p.x_coord -=1;
	std::cout << " " << std::endl;
}

void game::move_right() {
	// TODO Delete the below placeholder code. Move the player right one
	// space in the grid, however you choose to do that.
	this->player_x_coord +=1;
	//p.x_coord+=1;
	std::cout << " " << std::endl;
}

void game::move(char direction) {
	if (direction == 'w') {
		this->move_up();
	} else if (direction == 'a') {
		this->move_left();
	} else if (direction == 's') {
		this->move_down();
	} else {
		this->move_right();
	}
}

void game::fire_arrow_up() {
	// TODO Delete the below placeholder code. Fire the arrow upward, killing
	// the wumpus if it hits it or making the wumpus "wake up" and move
	// randomly if it misses
	int y = this->player_y_coord;
	int x = this->player_x_coord;
	bool first;
	if(y>0){
		y-=1;
		//std::cout<<"is wumpus"<<std::endl;
		if(this->cave[y][x]!=nullptr){
			cave[y][x]->is_wumpus(p);
			//std::cout<<"check wumpus"<<std::endl;
			if(p.is_wumpus == true){
				this->wumpus_is_dead = true;
		
				//std::cout<<"wumpus is dead 1"<<this->wumpus_is_dead<<std::endl;
			//y-=1;
			}
		}
		y-=1;
		//std::cout<<"if 2"<<std::endl;
		if(y>=0){
			if(this->cave[y][x]!=nullptr){
				//std::cout<<"check wumpus 1.5"<<std::endl;
				cave[y][x]->is_wumpus(p);
				//std::cout<<"check wumpus 2"<<std::endl;
				if(p.is_wumpus == true){
					this->wumpus_is_dead = true;
					//std::cout<<"wumpus is dead 2"<<std::endl;
				}
			}
		}
		y-=1;
		if(y>=0){
			if(this->cave[y][x]!=nullptr){
				//std::cout<<"check wumpus 3"<<std::endl;
				cave[y][x]->is_wumpus(p);
				if(p.is_wumpus == true){
					this->wumpus_is_dead = true;
					//std::cout<<"wumpus is dead 3"<<std::endl;
				}
			}
		}
		//std::cout<<"wumpus"<<std::endl;
		y+=3;
		if(y-=1>=0 && p.is_wumpus == false){
			if(y-=1>=0 && p.is_wumpus == false){
				if (y-=1>=0 && p.is_wumpus == false){
					if(this->cave[y][x] != nullptr){
						//std::cout<<"one"<<std::endl;
						y+=1;
					}
					//std::cout<<"other one"<<std::endl;
				}else if(y-=1<0){
					if(this->cave[y][x] != nullptr){
						y+=1;
						//std::cout<<"two"<<std::endl;
					}else{
						y+=1;
						//std::cout<<"three"<<std::endl;
					}
				}else if(this->cave[y][x]!=nullptr){
					y+=1;
					//std::cout<<"four"<<std::endl;
				}
				if(cave[y][x] != nullptr){
					y+=1;
					//std::cout<<"five"<<std::endl;
				}
			}else if(y-=1<0){
				if(this->cave[y][x]!=nullptr){
					y+=1;
					//std::cout<<"six"<<std::endl;
				}else{
					y+=1;
					//std::cout<<"seven"<<std::endl;
				}
			}else if(this->cave[y][x]!=nullptr){
				y+=1;
				//std::cout<<"eight"<<std::endl;
			}
			if(cave[y][x] != nullptr){
				y+=1;
				//std::cout<<"nine"<<std::endl;
			}
		}else if(y-=1<0){
			if(this->cave[y][x]!=nullptr){
				y+=1;
				//std::cout<<"ten"<<std::endl;
			}else{
				y+=1;
				//std::cout<<"eleven"<<std::endl;
			}
		}else if(this->cave[y][x]!=nullptr){
			y+=1;
			//std::cout<<"twelth"<<std::endl;
		}if(cave[y][x] != nullptr){
			y+=1;
			//std::cout<<"13"<<std::endl;
		}
	}
		

	if(cave[this->arrow1_y][this->arrow1_x] == nullptr){
		if(cave[y][x] == nullptr){
		//std::cout<<"arrow 1"<<std::endl;
			this ->arrow1_y = y;
			this->arrow1_x = x;
			this->cave[y][x] = new Arrow;
		}else{
			first = true;
			do{
				x = rand()%width;
				y = rand()%height;
				if (cave[y][x] == nullptr){
					this-> arrow1_x = x;
					this->arrow1_y = y;
					cave[y][x] = new Arrow;
					first = false;
				}
			}while(first);

		}
	}else if(cave[this->arrow2_y][this->arrow2_x] == nullptr){
		if(cave[y][x] == nullptr){
		//std::cout<<"arrow 2"<<std::endl;
			this->arrow2_y = y;
			this->arrow2_x = x;
			this->cave[y][x] = new Arrow;
		}else{
			first = true;
			do{
				x = rand()%width;
				y = rand()%height;
				if (cave[y][x] == nullptr){
					this-> arrow2_x = x;
					this->arrow2_y = y;
					cave[y][x] = new Arrow;
					first = false;
				}
			}while(first);

		}
	}
	//std::cout << "game::fire_arrow_up is not implemented..." << std::endl;
}

void game::fire_arrow_down() {
	// TODO Delete the below placeholder code. Fire the arrow downward, killing
	// the wumpus if it hits it or making the wumpus "wake up" and move
	// randomly if it misses
	int y = this->player_y_coord;
	bool first;
	int x = this->player_x_coord;
	int h = this->height-1;
	//std::cout<<"y<h"<<std::endl;
	if(y<h){
		y+=1;
		//std::cout<<"is wumpus"<<std::endl;
		if(this->cave[y][x]!=nullptr){
			cave[y][x]->is_wumpus(p);
			//std::cout<<"check wumpus"<<std::endl;
			if(p.is_wumpus == true){
				this->wumpus_is_dead = true;
		
			//	std::cout<<"wumpus is dead 1"<<this->wumpus_is_dead<<std::endl;
			//y-=1;
			}
		}
		//y+=1;
		//std::cout<<"if 2"<<std::endl;
		if(y<h){
			y+=1;
			if(this->cave[y][x]!=nullptr){
				//std::cout<<"check wumpus 1.5"<<std::endl;
				cave[y][x]->is_wumpus(p);
				//std::cout<<"check wumpus 2"<<std::endl;
				if(p.is_wumpus == true){
					this->wumpus_is_dead = true;
					//std::cout<<"wumpus is dead 2"<<std::endl;
				}
			}
		}
		//y+=1;
		if(y<h){
			y+=1;
			if(this->cave[y][x]!=nullptr){
				//std::cout<<"check wumpus 3"<<std::endl;
				cave[y][x]->is_wumpus(p);
				if(p.is_wumpus == true){
					this->wumpus_is_dead = true;
					//std::cout<<"wumpus is dead 3"<<std::endl;
				}
			}
		}
		//std::cout<<"wumpus"<<std::endl;
		y-=3;
		y+=1;
		if(y<h && p.is_wumpus == false){
			//std::cout<<"if 1"<<std::endl;
			y+=1;
			if(y<h && p.is_wumpus == false){
				//std::cout<<"if 2"<<std::endl;
				y+=1;
				if (y<h && p.is_wumpus == false){
					//std::cout<<"if 3"<<std::endl;
					y-=1;
					if(this->cave[y][x] != nullptr){
						//std::cout<<"one"<<std::endl;
					//	y-=1;
					}
					//std::cout<<"other one"<<std::endl;
				}else if(y>h){
					y-=1;
					if(this->cave[y][x] != nullptr){
						//y-=1;
						//std::cout<<"two"<<std::endl;
					}else{
						y-=1;
						//std::cout<<"three"<<std::endl;
					}
				}else if(this->cave[y][x]!=nullptr){
					y-=1;
					//std::cout<<"four"<<std::endl;
				}
				if(cave[y][x] != nullptr){
					y-=1;
					//std::cout<<"five"<<std::endl;
				}
			}else if(y>h){
				//y-=1;
				if(this->cave[y][x]!=nullptr){
					y-=1;
					//std::cout<<"six"<<std::endl;
				}else{
					y-=1;
					//std::cout<<"seven"<<std::endl;
				}
			}else if(this->cave[y][x]!=nullptr){
				y-=1;
				//std::cout<<"eight"<<std::endl;
			}
			if(cave[y][x] != nullptr){
				y-=1;
			}
			if(cave[y][x] != nullptr){
				y-=1;
				//std::cout<<"nine"<<std::endl;
			}
		}else if(y>h){
			//y-=1;
			if(this->cave[y][x]!=nullptr){
				y-=1;
				//std::cout<<"ten"<<std::endl;
			}else{
				y-=1;
				//std::cout<<"eleven"<<std::endl;
			}
		}else if(this->cave[y][x]!=nullptr){
			y-=1;
		//	std::cout<<"twelth"<<std::endl;
		}if(cave[y][x] != nullptr){
			y-=1;
			//std::cout<<"13"<<std::endl;
		}
	}
		

	if(cave[this->arrow1_y][this->arrow1_x] == nullptr){
		if(cave[y][x] == nullptr){
		//std::cout<<"arrow 1"<<std::endl;
			this ->arrow1_y = y;
			this->arrow1_x = x;
			this->cave[y][x] = new Arrow;
		}else{
			first = true;
			do{
				x = rand()%width;
				y = rand()%height;
				if (cave[y][x] == nullptr){
					this-> arrow1_x = x;
					this->arrow1_y = y;
					cave[y][x] = new Arrow;
					first = false;
				}
			}while(first);

		}
	}else if(cave[this->arrow2_y][this->arrow2_x] == nullptr){
		if(cave[y][x] == nullptr){
		//std::cout<<"arrow 2"<<std::endl;
			this->arrow2_y = y;
			this->arrow2_x = x;
			this->cave[y][x] = new Arrow;
		}else{
			first = true;
			do{
				x = rand()%width;
				y = rand()%height;
				if (cave[y][x] == nullptr){
					this-> arrow2_x = x;
					this->arrow2_y = y;
					cave[y][x] = new Arrow;
					first = false;
				}
			}while(first);

		}
	}

	//std::cout << "game::fire_arrow_down is not implemented..." << std::endl;
}

void game::fire_arrow_left() {
	// TODO Delete the below placeholder code. Fire the arrow leftward, killing
	// the wumpus if it hits it or making the wumpus "wake up" and move
	// randomly if it misses
	int y = this->player_y_coord;
	bool first;
	int x = this->player_x_coord;
	int w = this->width;
	//std::cout<<"y<h"<<std::endl;
	if(x>0){
		x-=1;
		//std::cout<<"is wumpus"<<std::endl;
		if(this->cave[y][x]!=nullptr){
			cave[y][x]->is_wumpus(p);
			//std::cout<<"check wumpus"<<std::endl;
			if(p.is_wumpus == true){
				this->wumpus_is_dead = true;
		
				//std::cout<<"wumpus is dead 1"<<this->wumpus_is_dead<<std::endl;
			//y-=1;
			}
		}
		x-=1;
		//std::cout<<"if 2"<<std::endl;
		if(x>=0){
			if(this->cave[y][x]!=nullptr){
				//std::cout<<"check wumpus 1.5"<<std::endl;
				cave[y][x]->is_wumpus(p);
				//std::cout<<"check wumpus 2"<<std::endl;
				if(p.is_wumpus == true){
					this->wumpus_is_dead = true;
					//std::cout<<"wumpus is dead 2"<<std::endl;
				}
			}
		}
		x-=1;
		if(x>=0){
			if(this->cave[y][x]!=nullptr){
				//std::cout<<"check wumpus 3"<<std::endl;
				cave[y][x]->is_wumpus(p);
				if(p.is_wumpus == true){
					this->wumpus_is_dead = true;
					//std::cout<<"wumpus is dead 3"<<std::endl;
				}
			}
		}
		//std::cout<<"wumpus"<<std::endl;
		x+=3;
		if(x-=1>=0 && p.is_wumpus == false){
			if(x-=1>=0 && p.is_wumpus == false){
				if (x-=1>=0 && p.is_wumpus == false){
					if(this->cave[y][x] != nullptr){
						//std::cout<<"one"<<std::endl;
						x+=1;
					}
				//	std::cout<<"other one"<<std::endl;
				}else if(x-=1<0){
					if(this->cave[y][x] != nullptr){
						x+=1;
						//std::cout<<"two"<<std::endl;
					}else{
						x+=1;
						//std::cout<<"three"<<std::endl;
					}
				}else if(this->cave[y][x]!=nullptr){
					x+=1;
					//std::cout<<"four"<<std::endl;
				}
				if(cave[y][x] != nullptr){
					x+=1;
					//std::cout<<"five"<<std::endl;
				}
			}else if(x-=1<0){
				if(this->cave[y][x]!=nullptr){
					x+=1;
					//std::cout<<"six"<<std::endl;
				}else{
					x+=1;
					//std::cout<<"seven"<<std::endl;
				}
			}else if(this->cave[y][x]!=nullptr){
				x+=1;
				//std::cout<<"eight"<<std::endl;
			}
			if(cave[y][x] != nullptr){
				x+=1;
			}
			if(cave[y][x] != nullptr){
				x+=1;
				//std::cout<<"nine"<<std::endl;
			}
		}else if(x-=1<0){
			if(this->cave[y][x]!=nullptr){
				x+=1;
				//std::cout<<"ten"<<std::endl;
			}else{
				x+=1;
				//std::cout<<"eleven"<<std::endl;
			}
		}else if(this->cave[y][x]!=nullptr){
			x+=1;
			//std::cout<<"twelth"<<std::endl;
		}if(cave[y][x] != nullptr){
			x+=1;
			//std::cout<<"13"<<std::endl;
		}
	}
		
	if(cave[this->arrow1_y][this->arrow1_x] == nullptr){
		if(cave[y][x] == nullptr){
		//std::cout<<"arrow 1"<<std::endl;
			this ->arrow1_y = y;
			this->arrow1_x = x;
			this->cave[y][x] = new Arrow;
		}else{
			first = true;
			do{
				x = rand()%width;
				y = rand()%height;
				if (cave[y][x] == nullptr){
					this-> arrow1_x = x;
					this->arrow1_y = y;
					cave[y][x] = new Arrow;
					first = false;
				}
			}while(first);

		}
	}else if(cave[this->arrow2_y][this->arrow2_x] == nullptr){
		if(cave[y][x] == nullptr){
		//std::cout<<"arrow 2"<<std::endl;
			this->arrow2_y = y;
			this->arrow2_x = x;
			this->cave[y][x] = new Arrow;
		}else{
			first = true;
			do{
				x = rand()%width;
				y = rand()%height;
				if (cave[y][x] == nullptr){
					this-> arrow2_x = x;
					this->arrow2_y = y;
					cave[y][x] = new Arrow;
					first = false;
				}
			}while(first);

		}
	}

	//std::cout << "game::fire_arrow_left is not implemented..." << std::endl;
}

void game::fire_arrow_right() {
	// TODO Delete the below placeholder code. Fire the arrow rightward, killing
	// the wumpus if it hits it or making the wumpus "wake up" and move
	// randomly if it misses
	int y = this->player_y_coord;
	bool first;
	int x = this->player_x_coord;
	int h = this->width-1;
	//std::cout<<"y<h"<<std::endl;
	if(x<h){
		x+=1;
		//std::cout<<"is wumpus"<<std::endl;
		if(this->cave[y][x]!=nullptr){
			cave[y][x]->is_wumpus(p);
			//std::cout<<"check wumpus"<<std::endl;
			if(p.is_wumpus == true){
				this->wumpus_is_dead = true;
		
				//std::cout<<"wumpus is dead 1"<<this->wumpus_is_dead<<std::endl;
			//y-=1;
			}
		}
		//y+=1;
		//std::cout<<"if 2"<<std::endl;
		if(x<h){
			x+=1;
			if(this->cave[y][x]!=nullptr){
				//std::cout<<"check wumpus 1.5"<<std::endl;
				cave[y][x]->is_wumpus(p);
				//std::cout<<"check wumpus 2"<<std::endl;
				if(p.is_wumpus == true){
					this->wumpus_is_dead = true;
					//std::cout<<"wumpus is dead 2"<<std::endl;
				}
			}
		}
		//y+=1;
		if(x<h){
			x+=1;
			if(this->cave[y][x]!=nullptr){
			//	std::cout<<"check wumpus 3"<<std::endl;
				cave[y][x]->is_wumpus(p);
				if(p.is_wumpus == true){
					this->wumpus_is_dead = true;
					//std::cout<<"wumpus is dead 3"<<std::endl;
				}
			}
		}
		//std::cout<<"wumpus"<<std::endl;
		x-=3;
		x+=1;
		if(x<h && p.is_wumpus == false){
			//std::cout<<"if 1"<<std::endl;
			x+=1;
			if(x<h && p.is_wumpus == false){
				//std::cout<<"if 2"<<std::endl;
				x+=1;
				if (x+=1<h && p.is_wumpus == false){
					//std::cout<<"if 3"<<std::endl;
					x-=1;
					if(this->cave[y][x] != nullptr){
					//	std::cout<<"one"<<std::endl;
					//	y-=1;
					}
					//std::cout<<"other one"<<std::endl;
				}else if(x>h){
					x-=1;
					if(this->cave[y][x] != nullptr){
						//y-=1;
						//std::cout<<"two"<<std::endl;
					}else{
						x-=1;
						//std::cout<<"three"<<std::endl;
					}
				}else if(this->cave[y][x]!=nullptr){
					x-=1;
					//std::cout<<"four"<<std::endl;
				}
				if(cave[y][x] != nullptr){
					x-=1;
					//std::cout<<"five"<<std::endl;
				}
			}else if(x>h){
				//y-=1;
				if(this->cave[y][x]!=nullptr){
					x-=1;
					//std::cout<<"six"<<std::endl;
				}else{
					x-=1;
					//std::cout<<"seven"<<std::endl;
				}
			}else if(this->cave[y][x]!=nullptr){
				x-=1;
				//std::cout<<"eight"<<std::endl;
			}
			if(cave[y][x] != nullptr){
				x-=1;
			}
			if(cave[y][x] != nullptr){
				x-=1;
				//std::cout<<"nine"<<std::endl;
			}
		}else if(x>h){
			//y-=1;
			if(this->cave[y][x]!=nullptr){
				x-=1;
				//std::cout<<"ten"<<std::endl;
			}else{
				x-=1;
				//std::cout<<"eleven"<<std::endl;
			}
		}else if(this->cave[y][x]!=nullptr){
			x-=1;
			//std::cout<<"twelth"<<std::endl;
		}if(cave[y][x] != nullptr){
			x-=1;
			//std::cout<<"13"<<std::endl;
		}
	}
		

	if(cave[this->arrow1_y][this->arrow1_x] == nullptr){
		if(cave[y][x] == nullptr){
		//std::cout<<"arrow 1"<<std::endl;
			this ->arrow1_y = y;
			this->arrow1_x = x;
			this->cave[y][x] = new Arrow;
		}else{
			first = true;
			do{
				x = rand()%width;
				y = rand()%height;
				if (cave[y][x] == nullptr){
					this-> arrow1_x = x;
					this->arrow1_y = y;
					cave[y][x] = new Arrow;
					first = false;
				}
			}while(first);

		}
	}else if(cave[this->arrow2_y][this->arrow2_x] == nullptr){
		if(cave[y][x] == nullptr){
		//std::cout<<"arrow 2"<<std::endl;
			this->arrow2_y = y;
			this->arrow2_x = x;
			this->cave[y][x] = new Arrow;
		}else{
			first = true;
			do{
				x = rand()%width;
				y = rand()%height;
				if (cave[y][x] == nullptr){
					this-> arrow2_x = x;
					this->arrow2_y = y;
					cave[y][x] = new Arrow;
					first = false;
				}
			}while(first);

		}
	}

	//std::cout << "game::fire_arrow_right is not implemented..." << std::endl;
}

void game::fire_arrow(char direction) {
	if (direction == 'w') {
		this->fire_arrow_up();
	} else if (direction == 'a') {
		this->fire_arrow_left();
	} else if (direction == 's') {
		this->fire_arrow_down();
	} else {
		this->fire_arrow_right();
	}

	this->num_arrows--;
}


void game::respawn_player(){
	int x;
	int y;
	bool first = true;
	this->player_x_coord = this->escape_x;
	this->player_y_coord = this->escape_y;
	if(this->p.has_gold == true){
		do{
			x = rand()%this->width;
			y = rand()%this->height;
			if (this->cave[y][x] == nullptr){
				this-> gold_x = x;
				this->gold_y = y;
				this->cave[y][x] = new Gold;
				first = false;
			}
		}while(first);
	}
	first = true;
	this->p.has_gold = false;
	if(this->p.has_arrow == true){
		this->num_arrows = 0;
		if(cave[this->arrow1_y][this->arrow1_x] == nullptr){
			do{
				x = rand()%width;
				y = rand()%height;
				if (cave[y][x] == nullptr){
					this-> arrow1_x = x;
					this->arrow1_y = y;
					cave[y][x] = new Arrow;
					first = false;
				}
			}while(first);
		}
		first = true;
		if(cave[this->arrow2_y][this->arrow2_x] == nullptr){
			do{
				x = rand()%width;
				y = rand()%height;
				if (cave[y][x] == nullptr){
					this-> arrow2_x = x;
					this->arrow2_y = y;
					cave[y][x] = new Arrow;
					first = false;
				}
			}while(first);

		}
	}
	first = true;
	if(this ->has_flashlight == true){
		do{
			x =rand()%width;
			y =rand()%height;
			if(cave[y][x] == nullptr){
				this->flashlight_x =x;
				this->flashlight_y =y;
				cave[y][x] = new Flashlight;
				first = false;
			}
		}while(first);
	}
	this->has_flashlight = false;
}

void game::play_game(){
	//player p;
	int hp = this->p.hp;
	int armor = this->p.armor;
	int y =this->player_y_coord;
	int x=this->player_x_coord;
	int h = this->height-1;
	bool first = true;
	while (!this->check_win(this->p) && !this->check_lose(this->p)) {
		hp = this->p.hp;
		armor = this->p.armor;
		//if(p.armor = 0){
		//	p.has_armor =false;
		//}
		// Print game board
		this->display_game();

		// TODO Display precepts around player's location

		// Ask player for their action
		char action = this->get_player_action();

		// Process action
		if (this->is_direction(action)) {
			// W/A/S/D = move player
			char direction = action;
			this->move(direction);
		} else {
			// F = prompt for arrow fire direction and fire arrow
			char direction = this->get_arrow_fire_direction();
			this->fire_arrow(direction);
		}

		// TODO If the user is on a space with an event, trigger its encounter
		for (int i = 0; i<this->height; i++){
			for (int j =0; j < this->width;j++){
				if(this->cave[i][j] != nullptr && player_x_coord == j && player_y_coord == i){
					//std::cout<<"event"<<std::endl;
					cave[i][j]->encounter(this->p);
					if(player_x_coord == gold_x && player_y_coord == gold_y && this->p.has_gold == true){
						//delete cave[i][j];
						std::cout<<"you found the gold"<<std::endl;
						cave[i][j] = nullptr;
					}else if(player_x_coord == arrow1_x && player_y_coord == arrow1_y && this->p.has_arrow == true){
						std::cout<<"you found an arrow"<<std::endl;
						this->cave[i][j] = nullptr;
						this->num_arrows+=1;
					}else if(player_x_coord == arrow2_x && player_y_coord == arrow2_y && this->p.has_arrow == true){
						std::cout<<"you fount an arrow"<<std::endl;
						this->cave[i][j] = nullptr;
						this->num_arrows += 1;
					}else if(player_x_coord == flashlight_x && player_y_coord == flashlight_y && this->p.has_flashlight == true){
						std::cout<<"you found the flashlight"<<std::endl;
						this->has_flashlight = true;
						this->cave[i][j] = nullptr;
					}
				}else if(this->cave[i][j] != nullptr && player_x_coord == j && player_y_coord == i-1){
					cave[i][j]->percept();
				}else if(this->cave[i][j] != nullptr && player_x_coord == j && player_y_coord == i+1){
					cave[i][j]->percept();
				}else if(this->cave[i][j] != nullptr && player_x_coord == j-1 && player_y_coord == i){
					cave[i][j]->percept();
				} else if(this->cave[i][j] != nullptr && player_x_coord == j+1 && player_y_coord == i){
					cave[i][j]->percept();

				}

			}
		}
		if(this->p.hp<hp){
			respawn_player();
/*			this->player_x_coord = this->escape_x;
			this->player_y_coord = this->escape_y;
			if(p.has_gold == true){
				do{
					x = rand()%width;
					y = rand()%height;
					if (cave[y][x] == nullptr){
						this-> gold_x = x;
						this->gold_y = y;
						cave[y][x] = new Gold;
						first = false;
					}
				}while(first);

			}
*/		}
		//if(armor <= 0){
		//	p.has_armor = false;
		//}
		std::cout<<std::endl;
		std::cout<<"player health: "<<this->p.hp<<std::endl;
		if (armor > 0){
			std::cout<<"player armor: "<<this->p.armor<<std::endl;
		}else{
			p.has_armor = false;
			std::cout<<"player armor: none"<<std::endl;
		}
		if(check_lose(p) == true){
			std::cout<<std::endl;
			std::cout<<std::endl;
			std::cout<<"game over. you lost"<<std::endl;
		}
	}
//	std::cout<<this->debug<<std::endl;
		this->debug = 1;
	this->display_game();
}
