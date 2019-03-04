using namespace std;
#include <map>
#include <stdio.h>
#include "text_corpus.cpp"


class InvertedIndex {
  map<string, vector<TextCorpus*>> index;

public:

  void add_corpus(TextCorpus* text) {
    vector<string> words = text->get_words();

    vector<string>::iterator it;

    for(it = words.begin(); it != words.end(); it++) {
      if(index.find(*it) == index.end()) {
	vector<TextCorpus*> res;
	res.push_back(text);
	index[*it] = res;
      } else {
	if (index[*it].back() == text) {continue;}
	index[*it].push_back(text);
      }
    }
  }

  vector<TextCorpus*> get_matching_corpuses(string word) {
    if (index.find(word) == index.end()) {
      vector<TextCorpus*> res;
      return res;
    }
    return index[word];
  }
};


int main() {

  TextCorpus richard("richard_2.txt", true);
  richard.set_name("Richard II");
  TextCorpus sonnets ("the_sonnets.txt", true);
  sonnets.set_name("The Sonnets");
  TextCorpus merchant ("merchant_of_venice.txt", true);
  merchant.set_name("The Merchant of Venice");
  TextCorpus pericles ("pericles.txt", true);
  pericles.set_name("Pericles, Prince of Tyre");

  InvertedIndex index;
  index.add_corpus(&richard);
  index.add_corpus(&sonnets);
  index.add_corpus(&merchant);
  index.add_corpus(&pericles);

  vector<TextCorpus*> thou = index.get_matching_corpuses("thou");
  vector<TextCorpus*> shylock = index.get_matching_corpuses("Shylock");
  vector<TextCorpus*> scooby = index.get_matching_corpuses("Scooby");

  vector<TextCorpus*>::iterator it;
  cout << "thou:\n";
  unsigned count = 0;
  for(it=thou.begin(); it != thou.end(); it++) {
    printf("%d ", count);
    cout << (*it)->get_name();
    cout << "\n";
    count++;
  }
  cout << "\n";
  cout << "Shylock:\n";
  count = 0;
  for(it=shylock.begin(); it!=shylock.end(); it++) {
    printf("%d ", count);
    cout << (*it)->get_name();
    cout << "\n";
    count++;
  }

  cout << "\n";
  cout << "Scooby:\n";
  count =0;
  for(it=scooby.begin(); it!=scooby.end(); it++) {
    printf("%d ", count);
    cout << (*it)->get_name();
    cout << "\n";
    count++;
  }
}
