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
