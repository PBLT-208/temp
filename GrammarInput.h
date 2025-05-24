// GrammarInput.h
#include<bits/stdc++.h>
using namespace std;

class GrammarInput {
public:
    void readGrammar();
    void displayGrammar(ostream& os) const;
    map<string, vector<vector<string>>> getProductions() const;
    string getStartSymbol() const;

private:
    map<string, vector<vector<string>>> productions;
    string startSymbol;
};
