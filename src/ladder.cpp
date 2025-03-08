#include "ladder.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <stdexcept>

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
                if (diffCount > 1) {return false;}
            }
        }
        return (diffCount == 1);
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
            if (mismatchCount > 1) {return false;}
            j++;
        }
    }
    if (j < (int)longer.size()) {mismatchCount++;}
    return (mismatchCount == 1);
}
