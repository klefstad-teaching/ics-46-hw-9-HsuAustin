#include "ladder.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    set<string> word_list;
    try {load_words(word_list, "words.txt");} 
    catch (exception& e) {
        cerr << "Error loading words: " << e.what() << endl;
        return 1;
    }
    cout << "Enter start word: ";
    string start;
    cin >> start;
    cout << "Enter end word: ";
    string end;
    cin >> end;
    for (auto &ch : start) {ch = tolower(ch);}
    for (auto &ch : end) {ch = tolower(ch);}
    if (start == end) {
        error(start, end, "Start and end words must differ");
        return 0;
    }
    vector<string> ladder = generate_word_ladder(start, end, word_list);
    if (ladder.empty()) {cout << "No ladder found from '" << start << "' to '" << end << "'." << endl;} 
    else {print_word_ladder(ladder);}
    return 0;
}
