#include "FirstFollow.h"
#include<bits/stdc++.h>

using namespace std;

FirstFollow::FirstFollow(const map<string, vector<vector<string>>>& prod)
    : productions(prod) {}

void FirstFollow::computeFirst() {
    // Initialize FIRST sets for all non-terminals
    for (const auto& [nonTerminal, _] : productions) {
        first[nonTerminal] = {};
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& [nonTerminal, rules] : productions) {
            for (const auto& rule : rules) {
                set<string> result = computeFirstOfString(rule);
                size_t before = first[nonTerminal].size();
                first[nonTerminal].insert(result.begin(), result.end());
                if (first[nonTerminal].size() > before) {
                    changed = true;
                }
            }
        }
    }
}

set<string> FirstFollow::computeFirstOfString(const vector<string>& str) const {
    set<string> result;
    if (str.empty()) {
        result.insert("ε");
        return result;
    }

    for (size_t i = 0; i < str.size(); ++i) {
        const string& symbol = str[i];
        // Terminal symbol if not in productions
        if (productions.find(symbol) == productions.end()) {
            result.insert(symbol);
            break;
        }

        const auto& firstSet = first.at(symbol);
        result.insert(firstSet.begin(), firstSet.end());

        if (!firstSet.count("ε")) {
            break;
        }

        // If epsilon is in FIRST(symbol), continue to next symbol
        if (i == str.size() - 1) {
            result.insert("ε");
        } else {
            result.erase("ε");
        }
    }
    return result;
}

void FirstFollow::computeFollow(const string& startSymbol) {
    for (const auto& [nonTerminal, _] : productions) {
        follow[nonTerminal] = {};
    }
    follow[startSymbol].insert("$");

    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& [lhs, rules] : productions) {
            for (const auto& rule : rules) {
                for (size_t i = 0; i < rule.size(); ++i) {
                    const string& B = rule[i];
                    if (productions.find(B) == productions.end()) continue;

                    size_t before = follow[B].size();

                    if (i + 1 < rule.size()) {
                        vector<string> beta(rule.begin() + i + 1, rule.end());
                        set<string> firstBeta = computeFirstOfString(beta);
                        for (const string& f : firstBeta) {
                            if (f != "ε") {
                                follow[B].insert(f);
                            }
                        }
                        if (firstBeta.count("ε")) {
                            follow[B].insert(follow[lhs].begin(), follow[lhs].end());
                        }
                    } else {
                        follow[B].insert(follow[lhs].begin(), follow[lhs].end());
                    }

                    if (follow[B].size() > before) {
                        changed = true;
                    }
                }
            }
        }
    }
}

void FirstFollow::displayFirstFollow(ostream& os) const {
    os << "\nFIRST sets:\n";
    for (const auto& [nonTerminal, firstSet] : first) {
        os << "FIRST(" << nonTerminal << ") = { ";
        for (const string& symbol : firstSet) {
            os << symbol << " ";
        }
        os << "}\n";
    }

    os << "\nFOLLOW sets:\n";
    for (const auto& [nonTerminal, followSet] : follow) {
        os << "FOLLOW(" << nonTerminal << ") = { ";
        for (const string& symbol : followSet) {
            os << symbol << " ";
        }
        os << "}\n";
    }
}

map<string, set<string>> FirstFollow::getFirst() const {
    return first;
}

map<string, set<string>> FirstFollow::getFollow() const {
    return follow;
}
