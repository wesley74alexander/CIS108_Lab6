#include "song.h"
#include "MusicDB.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

vector<music::Song> mysongs;

void get_menu(vector<char*> menu){ //Prints menu one line at a time
    for (int i = 0; i < menu.size(); i++){
      cout << menu[i] << endl;
    };
  };//must compile with c++ 11 or later for get_menu to work

music::music_genre str_toenum(string str) { //real function to take in a string and return an enum genre
   if (str == "blues" || str == "Blues") {
     return music::music_genre::Blues;
   }
   else if (str == "country" || str == "Country") {
     return music::music_genre::Country;
   }
   else if (str == "electronic" || str == "Electronic" || str == "edm" || str == "EDM") {
     return music::music_genre::Electronic;
   }
   else if (str == "folk" || str == "Folk") {
     return music::music_genre::Folk;
   }
   else if (str == "hiphop" || str == "HipHop" || str == "Hip Hop" || str == "hip hop" || str == "Hip-Hop" || str == "rap" || str == "Rap") {
     return music::music_genre::HipHop;
   }
   else if (str == "jazz" || str == "Jazz") {
     return music::music_genre::Jazz;
   }
   else if (str == "latin" || str == "Latin") {
     return music::music_genre::Latin;
   }
   else if (str == "pop" || str == "Pop") {
     return music::music_genre::Pop;
   }
   else if (str == "rock" || str == "Rock"){
     return music::music_genre::Rock;
   }
   else {
     return music::music_genre::fail_case;
   };
};

string enum_tostring(music::music_genre genre_index) {
   if (genre_index == 0) {
     return "Other";
   }
   else if (genre_index == 1) {
     return "Blues";
   }
   else if (genre_index == 2) {
     return "Country";
   }
   else if (genre_index == 3) {
     return "Electronic";
   }
   else if (genre_index == 4) {
     return "Folk";
   }
   else if (genre_index == 5) {
     return "Hip-Hop";
   }
   else if (genre_index == 6) {
     return "Jazz";
   }
   else if (genre_index == 7) {
     return "Latin";
   }
   else if (genre_index == 8) {
     return "Pop";
   }
   else if (genre_index == 9) {
     return "Rock";
   };
};

void add_song(music::Song& s){ //reads user input into members of s
    string inputstr;
    cout << "Enter song title: ";
    getline(cin >> ws, inputstr); //**second parameter must be a string, s.title is a character array** **use string copy function**
    if (inputstr.length() > sizeof(s.title))
      throw runtime_error("Song title is too large!"); //used runtime_error rather than exception because string args to exception are a VS extension
    else
      strcpy(s.title, inputstr.c_str());
    cout << "Enter artist: ";
    getline(cin, inputstr);
    if (inputstr.length() > sizeof(s.artist))
      throw runtime_error("Artist name is too large!");
    else
      strcpy(s.artist, inputstr.c_str());
    cout << "Enter album name: ";
    getline(cin, inputstr);
    if (inputstr.length() > sizeof(s.artist))
      throw runtime_error("Album name is too large!");
    else
      strcpy(s.album, inputstr.c_str());
    cout << "Enter genre: ";
    getline(cin, inputstr);
    s.genre = str_toenum(inputstr);
    cout << "Enter track #: ";
    getline(cin , inputstr);
    try
    {
      s.track = stoi(inputstr);
    }
    catch(invalid_argument)
    {
      throw runtime_error("Numeric input required for track field");
    }
    catch(out_of_range)
    {
      throw runtime_error("Input is too large!");
    }
    cout << "Enter year: ";
    getline(cin, inputstr);
    try
    {
      int iyear = stoi(inputstr);
      if (iyear < 2019)
        s.year = iyear;
      else
        throw runtime_error("You can't add songs from the future!");
    }
    catch(invalid_argument)
    {
      throw runtime_error("Numeric input required for year field");
    }
    catch(out_of_range)
    {
      throw runtime_error("Input is too large!");
    }
    mysongs.push_back(s);
};


void save_song(music::Song& s, string fname){ //writes the members of Song s to a file // must declare count before calling func
    ofstream outfile;
    outfile.open(fname, ios::out | ios::binary);
    auto mysongs_itr = mysongs.begin();
    while (mysongs_itr != mysongs.end()){
      music::Song s = *mysongs_itr;
      outfile.write((char*)&s ,sizeof(s));
      mysongs_itr ++;
    }
     //writes entire song to binary file rather than member by member to text file like lab5. This is much simpler. See http://courses.cs.vt.edu/~cs2604/fall00/binio.html
    outfile.close(); //**save from vector rather than most recent s entry. set flag to overwrite rather than append to avoid repeats.**
};

void clear_file(string fname){
    ofstream cfile;
    mysongs.clear();
    cfile.open(fname, ios:: binary | ios::out | ios::trunc);
    cfile.close();
};


void list_song(){
  int count = 0;
  vector<music::Song>::iterator songs_itr;
  music::Song s;

  for (songs_itr = mysongs.begin(); songs_itr < mysongs.end(); songs_itr ++){
    s = *songs_itr; //sets s equal to the element pointed to by songs_itr
    cout << "Song #: " << count + 1 << endl;
    cout << " Title: " << s.title << endl;
    cout << " Artist: " << s.artist << endl;
    cout << " Album: " << s.album << endl;
    cout << " Genre: " << enum_tostring(s.genre) << endl;
    cout << " Track #: " << s.track << endl;
    cout << " Year: " << s.year << endl;
    count ++;
  };
};


int get_global_count(){
  int global_count = 0;
  vector<music::Song>::iterator songs_itr;

  for (songs_itr = mysongs.begin(); songs_itr < mysongs.end(); songs_itr ++){
    global_count ++;
  };
  return global_count;
};


void load_vector(string fname){
  music::Song s;
  ifstream infile;
  mysongs.clear();
  char ch;

	try
	{
		infile.open(fname, ios::in | ios::binary);
		infile.exceptions(ifstream::failbit);

		while (infile.is_open() && infile.peek() != EOF)
		{
			infile.exceptions(ifstream::badbit);
			infile.read((char*)& s, sizeof(s));
			mysongs.push_back(s);
		};
		infile.close();
	}
  catch (const ifstream::failure& e) {
    cout << "Error opening file " << fname << endl;
  }
};
