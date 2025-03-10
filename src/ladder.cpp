#include "ladder.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <stdexcept>
#include <cctype>

using namespace std;

void error(string word1, string word2, string msg) {cerr << "Error at " << "(" << word1 << ", " << word2 << "): " << msg << endl;}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int len1 = (int)str1.size();
    int len2 = (int)str2.size();
    if (abs(len1 - len2) > d) {return false;}
    if (len1 == len2) {
        int diffCount = 0;
        for (int i = 0; i < len1; i++) {
            if (str1[i] != str2[i]) {
                diffCount++;
                if (diffCount > d) {return false;}
            }
        }
        return true;
    }
    const string& shorter = (len1 < len2) ? str1 : str2;
    const string& longer  = (len1 < len2) ? str2 : str1;
    int i = 0, j = 0;
    int mismatchCount = 0;
    while ((i < (int)shorter.size()) && (j < (int)longer.size())) {
        if (shorter[i] == longer[j]) {
            i++;
            j++;
        } else {
            mismatchCount++;
            if (mismatchCount > d) {return false;}
            j++;
        }
    }
    if (j < (int)longer.size()) {mismatchCount += (longer.size() - j);}
    return (mismatchCount <= d);
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) {return {};}
    queue<vector<string>> ladder_queue;
    set<string> visited;
    ladder_queue.push({begin_word});
    if (word_list.find(begin_word) != word_list.end()) {visited.insert(begin_word);}
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        const string &last_word = ladder.back();
        for (auto &word: word_list) {
            if (abs((int)word.size() - (int)last_word.size()) > 1) {continue;}
            if (word == last_word) {continue;}
            if (visited.find(word) == visited.end()) {
                if (is_adjacent(last_word, word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {return new_ladder;}
                    ladder_queue.push(new_ladder);
                    visited.insert(word);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream infile(file_name);
    if (!infile.is_open()) {cerr << "Cannot open file" << endl;}
    string word;
    while (infile >> word) {
        for (auto &ch: word) {ch = tolower(ch);}
        word_list.insert(word);
    }
    infile.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {cout << "No word ladder found." << endl;} 
    else {
        cout << "Word ladder found: ";
        for (const auto &word: ladder) {cout << word << " ";}
        cout << endl;
    }
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}


