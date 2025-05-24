// FirstFollow.h
#include<bits/stdc++.h>
using namespace std;

class FirstFollow {
public:
    FirstFollow(const map<string, vector<vector<string>>>& prod);
    void computeFirst();
    void computeFollow(const string& startSymbol);
    void displayFirstFollow(ostream& os) const;

    map<string, set<string>> getFirst() const;
    map<string, set<string>> getFollow() const;

private:
    map<string, vector<vector<string>>> productions;
    map<string, set<string>> first;
    map<string, set<string>> follow;
    set<string> computeFirstOfString(const vector<string>& str) const;

};