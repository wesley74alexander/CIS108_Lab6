#pragma once
#include <string>
#include <vector>
#include "song.h"

using namespace std;

void get_menu(vector<char*> menu); // prints menu to the console line by line

music::music_genre str_toenum(string str); //convers user entered string genre to an enum genre

string enum_tostring(music::music_genre genre_index); //converts enum value to a string before writing it to the file

void add_song(music::Song& s); // prompts user for input and saves input to members of Song s

void save_song(music::Song& s, string fname); // writes members of Song s to a file fname

void list_song(); // reads the contents of fname and prints them line by line to the console

int get_global_count();

void load_vector(string fname);

void clear_file(string fname);
