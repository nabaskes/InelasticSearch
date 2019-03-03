using namespace std;
#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>

class TextCorpus {
  string my_text;
  map<string, unsigned> word_count;
  map<string, vector<unsigned>> index;
  vector<string> my_words;
  string name;

  void build_index() {
    // builds word_count, index, my_words, out of my_text
    my_words.clear();
    word_count.clear();

    unsigned ind = 0;
    int next;
    string temp;
    while (ind < my_text.length()) {

      // get the next word
      next = my_text.find(' ', ind);
      if (next == -1) {
	next = my_text.length();
      }
      temp = my_text.substr(ind, next - ind);
      my_words.push_back(temp);


      // increment the word count
      word_count[temp] = (word_count.find(temp) == word_count.end()) ? 1 : word_count[temp] + 1;

      // track the word in the index
      if (index.find(temp) == index.end()) {
	vector<unsigned> loc_temp;
	loc_temp.push_back(ind);
	index[temp] = loc_temp;
      } else {
	index[temp].push_back(ind);
      }

      // start looking for the next word
      ind = next;
    }

  }

public:
  TextCorpus(string text_data) {
    my_text = text_data;
    build_index();
  }

  TextCorpus(const char* filename, bool is_file) {
    // people may decide to specifically tell you it's not a file
    if (is_file) {
      my_text = filename;
    } else {

      FILE *f;
      f = fopen(filename, "r");
      char line [255];
      my_text = "";

      while(fgets(line, 255, f) != NULL) {
	string temp(line);
	my_text.append(temp);
      }
    }
    build_index();
  }

  string get_text() {
    return my_text;
  }

  vector<string> get_words() {
    return my_words;
  }

  map<string, unsigned> get_word_count() {
    return word_count;
  }

  map<string, vector<unsigned>> get_index() {
    return index;
  }

  void set_name(string title) {
    name = title;
  }

  string get_name() {
    return name;
  }
};
