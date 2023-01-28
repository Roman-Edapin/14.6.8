#include <iostream>
#include <string>
#define underline


bool field_1[10][10];
bool field_2[10][10];
int field_1_atk[10][10];
int field_2_atk[10][10];
int ships[2][5]{ { 0,0,0,0,20 },{ 0,0,0,0,20 } };

void clean_field() {
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			field_1[i][j] = false;
			field_2[i][j] = false;
			field_1_atk[i][j] = 0;
			field_2_atk[i][j] = 0;
		}
	}
}

void converted_add(std::string add, int* coordinates, int max) {
	int f = 0;
	for (int i = 0; i < add.size() && f < max; ++i) {
		if (add[i] >= '0' && add[i] <= '9') {
			coordinates[f] = add[i] - '0';
			f++;
		}
	}
}

bool adding_multi_deck_ships(bool field[][10], int* coordinates) {
	bool check = true;
	for (int i = coordinates[1]; i <= coordinates[3] && check; i++) {
		for (int j = coordinates[0]; j <= coordinates[2] && check; j++) {
			if (field[i][j] == true)
				check = false;
		}
	}
	if (check) {
		for (int i = coordinates[1]; i <= coordinates[3]; i++) {
			for (int j = coordinates[0]; j <= coordinates[2]; j++) {
				field[i][j] = true;
			}
		}
		std::cout << "Ship added." << std::endl;
	}
	else {
		std::cout << "Ships intersect! Installation is not possible!" << std::endl;
		return false;
	}
		return true;
}

void print_field(bool field[][10]) {
	std::cout << underline "\033[4m" << " |0|1|2|3|4|5|6|7|8|9|" << std::endl;
	for (int i = 0; i < 10; ++i) {
		std::cout << i << '|';
		for (int j = 0; j < 10; ++j) {
			std::cout << field[i][j] << '|';
		}
		std::cout << std::endl;
	}
}

void print_field_atk(int field[][10]) {
	std::cout << underline "\033[4m" << " |0|1|2|3|4|5|6|7|8|9|" << std::endl;
	for (int i = 0; i < 10; ++i) {
		std::cout << i << '|';
		for (int j = 0; j < 10; ++j) {
			std::cout << field[i][j] << '|';
		}
		std::cout << std::endl;
	}
	std::cout << underline "\033[0m";
}

void add_ship(bool field[][10], int player_num) {
	std::string add;

	while (ships[player_num][0] != 4 || ships[player_num][1] != 3 || ships[player_num][2] != 2 || ships[player_num][3] != 1) {
		int coordinates[4]{ -1,-1,-1,-1 };
		print_field(field);
		std::cout << underline "\033[0m" << "You just need to add the following ships to the field:" << std::endl;
		std::cout << "Single - deck: " << (4 - ships[player_num][0]) << std::endl;
		std::cout << "Two - deck: " << (3 - ships[player_num][1]) << std::endl;
		std::cout << "Three - deck: " << (2 - ships[player_num][2]) << std::endl;
		std::cout << "Four - deck: " << (1 - ships[player_num][3]) << std::endl;

		std::getline(std::cin, add);
		converted_add(add, coordinates, 4);
		if (coordinates[0] >= 0 && coordinates[1] >= 0
			&& coordinates[2] >= -1 && coordinates[3] >= -1) {
			if (coordinates[2] < 0 && coordinates[3] < 0) {
				if (ships[player_num][0] == 4) {
					std::cout << "All ships of this type are on the field!" << std::endl;
				}
				else {
					if (field[coordinates[1]][coordinates[0]])
						std::cout << "This cell is occupied by another ship!" << std::endl;
					else {
						field[coordinates[1]][coordinates[0]] = true;
						std::cout << "Ship added." << std::endl;
						ships[player_num][0]++;
					}
				}
			}
			else if (coordinates[2] - coordinates[0] < 4 && coordinates[3] - coordinates[1] < 4  
				&& (ships[player_num][1] != 3 || ships[player_num][2] != 2 || ships[player_num][3] != 1) ) {
				if (ships[player_num][1] == 3 && (coordinates[2] - coordinates[0] == 0 && coordinates[3] - coordinates[1] == 1
					|| coordinates[2] - coordinates[0] == 1 && coordinates[3] - coordinates[1] == 0)) {
					std::cout << "All ships of this type are on the field!" << std::endl;
				}
				else if (coordinates[2] - coordinates[0] == 0 && coordinates[3] - coordinates[1] == 1
					|| coordinates[2] - coordinates[0] == 1 && coordinates[3] - coordinates[1] == 0) {
					if (adding_multi_deck_ships(field, coordinates))
						ships[player_num][1]++;
				}
					
				if (ships[player_num][2] == 2 && (coordinates[2] - coordinates[0] == 0 && coordinates[3] - coordinates[1] == 2
					|| coordinates[2] - coordinates[0] == 2 && coordinates[3] - coordinates[1] == 0)) {
					std::cout << "All ships of this type are on the field!" << std::endl;
				}
				else if (coordinates[2] - coordinates[0] == 0 && coordinates[3] - coordinates[1] == 2
					|| coordinates[2] - coordinates[0] == 2 && coordinates[3] - coordinates[1] == 0) {
					if (adding_multi_deck_ships(field, coordinates))
						ships[player_num][2]++;
				}

				if (ships[player_num][3] == 1 && (coordinates[2] - coordinates[0] == 0 && coordinates[3] - coordinates[1] == 3
					|| coordinates[2] - coordinates[0] == 3 && coordinates[3] - coordinates[1] == 0)) {
					std::cout << "All ships of this type are on the field!" << std::endl;
				}
				else if (coordinates[2] - coordinates[0] == 0 && coordinates[3] - coordinates[1] == 3
					|| coordinates[2] - coordinates[0] == 3 && coordinates[3] - coordinates[1] == 0) {
					if (adding_multi_deck_ships(field, coordinates))
						ships[player_num][3]++;
				}
			}
			else 
				std::cout << "The coordinate order is not correct" << std::endl;
		}
		else {
			std::cout << "The range of values is entered incorrectly! Try agagin!" << std::endl;
		}
	}
}

bool game_menu(std::string str) {
	if (str == "Start" || str == "start") {
		std::cout << "Let's go!" << std::endl;

	}
	else if (str == "Rules" || str == "rules") {
		std::cout << "First, the first player adds ships to the field, after the second." << std::endl;
		std::cout << "After that, the game begins. During which the players alternately enter the coordinates of the cell that was hit." << std::endl;
		std::cout << "The game ends when all the ships of one of the players have been destroyed." << std::endl;
	}
	else if (str == "Controlling" || str == "controlling") {
		std::cout << "Entering the coordinates of the new ship strictly in the format x,y or x,y-x,y." << std::endl;
		std::cout << "Entering coordinates when adding multi-deck ships strictly from the smallest coordinate to the largest." << std::endl;
		std::cout << "During training on the battlefield, empty cells are designated 0, occupied 1." << std::endl;
		std::cout << "During the battle, enter the coordinates where the shot was fired only in the format x,y." << std::endl;
		std::cout << "The coordinates count starts from 0 and ends with 9." << std::endl;
	}
	else if (str == "Exit" || str == "exit") {
		std::cout << "Goodbye!" << std::endl;
		return false;
	}
	else {
		std::cout << "Invalid text. Try again!" << std::endl;
	}
	return true;
 }

int atk_check(bool field[][10], int field_atk[][10], int* coordinates_atk, int count_steps) {
	if (field[coordinates_atk[1]][coordinates_atk[0]] && field_atk[coordinates_atk[1]][coordinates_atk[0]] == 0) {
		std::cout << "There is a hit!" << std::endl;
		field_atk[coordinates_atk[1]][coordinates_atk[0]] = 2;
		--ships[count_steps % 2][4];
	}
	else if (field_atk[coordinates_atk[1]][coordinates_atk[0]] == 0) {
		field_atk[coordinates_atk[1]][coordinates_atk[0]] = 1;
		std::cout << "Miss" << std::endl;
	}
	else {
		std::cout << "This cage has already been hit! A second strike is impossible! Try again!" << std::endl;
		return --count_steps;
	}
	return count_steps;
}

int main()
{
	clean_field();
	int step = 0;
	
	std::string str = " ";
	std::cout << "Welcome to the game <<Sea Battle>>." << std::endl;
	std::cout << "To navigate, enter the words marked > Text <" << std::endl;
	do {
		std::cout << "MENU" << std::endl;
		std::cout << "> Start <" << std::endl;
		std::cout << "> Rules <" << std::endl;
		std::cout << "> Controlling <" << std::endl;
		std::cout << "> Exit <" << std::endl;
		std::getline(std::cin, str);
		if (!game_menu(str))
			return 0;
	} while (str != "Start" && str != "start");
	

	std::cout << "Fill in the first field" << std::endl;
	add_ship(field_1, 0);
	print_field(field_1);
	std::cout << "Fill in the second field" << std::endl;
	add_ship(field_2, 1);
	print_field(field_2);
	std::cout << "The battle begins" << std::endl; 
	for (int count_steps = 0; ships[0][4] != 0 && ships[1][4] != 0; ++count_steps) {
		std::string coord_atk;
		int coordinates_atk[2]{ 0,0 };
		std::cout << "Step " << count_steps << std::endl;
		std::cout << "The " << (count_steps % 2 ? "second" : "first") << " player walks" << std::endl;
		print_field_atk(count_steps % 2 ? field_1_atk : field_2_atk);
		std::getline(std::cin, coord_atk);
		if (coord_atk == "Exit" || coord_atk == "exit") {
			std::cout << "Goodbye!" << std::endl;
			return 0;
		}
		converted_add(coord_atk, coordinates_atk, 2);
		if (count_steps % 2) {
			count_steps = atk_check(field_1, field_1_atk, coordinates_atk, count_steps);
		}
		else {
			count_steps = atk_check(field_2, field_2_atk, coordinates_atk, count_steps);
		}
		std::cout << "Hits from the first player: " << 20 - ships[1][4] << std::endl;
		std::cout << "Hits from the second player: " << 20 - ships[0][4] << std::endl;
	}

	if (ships[1][4] == 0)
		std::cout << "Win first player!" << std::endl;
	else
		std::cout << "Win second player!" << std::endl;

	std::cout << "Goodbye!" << std::endl;
}