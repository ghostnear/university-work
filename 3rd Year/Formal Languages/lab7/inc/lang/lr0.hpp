#pragma once

#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>

class LR0Parser {
public:
    using Production = std::pair<std::string, std::vector<std::string>>;
    using State = std::set<Production>;

    explicit LR0Parser(const std::map<std::string, std::vector<std::vector<std::string>>>& productions)
        : productions(productions) {
        canonicalCollection();
    }

    // Closure function
    State closure(State state) {
        bool added;
        do {
            added = false;
            State newState = state;
            for (const auto& item : state) {
                auto pos = std::find(item.second.begin(), item.second.end(), ".");
                if (pos != item.second.end() && ++pos != item.second.end() && isNonterminal(*pos)) {
                    for (const auto& prod : productions.at(*pos)) {
                        Production newItem = {*pos, {"."}};
                        newItem.second.insert(newItem.second.end(), prod.begin(), prod.end());
                        if (newState.insert(newItem).second) {
                            added = true;
                        }
                    }
                }
            }
            state = newState;
        } while (added);
        return state;
    }

    // Goto function
    State goTo(const State& state, const std::string& symbol) {
        State newState;
        for (const auto& item : state) {
            auto pos = std::find(item.second.begin(), item.second.end(), ".");
            if (pos != item.second.end() && ++pos != item.second.end() && *pos == symbol) {
                Production newItem = {item.first, item.second};
                std::swap(newItem.second[std::distance(item.second.begin(), pos - 1)],
                          newItem.second[std::distance(item.second.begin(), pos)]);
                newState.insert(newItem);
            }
        }
        return closure(newState);
    }

    // Canonical collection of sets of LR(0) items
    void canonicalCollection() {
        State startState = closure({{"S'", {".", "S"}}});
        C.push_back(startState);
        bool added;
        do {
            added = false;
            std::vector<State> newC = C;
            for (const auto& state : C) {
                for (const auto& symbol : allSymbols()) {
                    State newState = goTo(state, symbol);
                    if (!newState.empty() && std::find(C.begin(), C.end(), newState) == C.end()) {
                        newC.push_back(newState);
                        added = true;
                    }
                }
            }
            C = newC;
        } while (added);
    }

    // Generate parsing table for a specific input
    void generateParsingTable(const std::string& input) {
        parsingTable.clear();
        std::stack<int> stateStack;
        stateStack.push(0);

        for (char ch : input) {
            std::string symbol(1, ch);
            int currentState = stateStack.top();
            for (const auto& item : C[currentState]) {
                auto pos = std::find(item.second.begin(), item.second.end(), ".");
                if (pos != item.second.end() && ++pos == item.second.end()) {
                    if (item.first != "S'") {
                        parsingTable[{currentState, ""}] = {"reduce", item.first};
                    } else {
                        parsingTable[{currentState, ""}] = {"accept", ""};
                    }
                } else if (pos != item.second.end() && *pos != "." && isNonterminal(*pos)) {
                    for (const auto& state : C) {
                        if (goTo(C[currentState], *pos) == state) {
                            parsingTable[{currentState, *pos}] = {"shift", std::to_string(std::distance(C.begin(), std::find(C.begin(), C.end(), state)))};
                            stateStack.push(std::distance(C.begin(), std::find(C.begin(), C.end(), state)));
                        }
                    }
                } else if (pos != item.second.end() && *pos != "." && !isNonterminal(*pos)) {
                    for (const auto& state : C) {
                        if (goTo(C[currentState], *pos) == state) {
                            parsingTable[{currentState, *pos}] = {"shift", std::to_string(std::distance(C.begin(), std::find(C.begin(), C.end(), state)))};
                            stateStack.push(std::distance(C.begin(), std::find(C.begin(), C.end(), state)));
                        }
                    }
                }
            }
        }
    }

    // Check for conflicts in the parsing table
    void checkForConflicts() {
        for (const auto& entry : parsingTable) {
            if (entry.second.size() > 1) {
                std::cerr << "Conflict at row " << entry.first.first << " and column " << entry.first.second << "\n";
            }
        }
    }

    // Utility function to print the states
    void printStates() const {
        for (size_t i = 0; i < C.size(); ++i) {
            std::cout << "State " << i << ":\n";
            for (const auto& item : C[i]) {
                std::cout << item.first << " -> ";
                for (const auto& symbol : item.second) {
                    std::cout << symbol << " ";
                }
                std::cout << "\n";
            }
            std::cout << std::endl;
        }
    }

    bool isNonterminal(const std::string& symbol) const {
        return productions.find(symbol) != productions.end();
    }

    friend class ParserOutput;

private:
    std::map<std::string, std::vector<std::vector<std::string>>> productions;
    std::vector<State> C;
    std::map<std::pair<int, std::string>, std::vector<std::string>> parsingTable;

    std::set<std::string> allSymbols() const {
        std::set<std::string> symbols;
        for (const auto& [lhs, rhsList] : productions) {
            symbols.insert(lhs);
            for (const auto& rhs : rhsList) {
                for (const auto& symbol : rhs) {
                    symbols.insert(symbol);
                }
            }
        }
        return symbols;
    }
};
