#pragma once

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>

class LR0Parser {
public:
    using Production = std::pair<std::string, std::vector<std::string>>;
    using State = std::set<Production>;

    explicit LR0Parser(const std::map<std::string, std::vector<std::vector<std::string>>>& productions)
    : productions(productions) {}

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
    std::vector<State> canonicalCollection() {
        std::vector<State> C;
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
        return C;
    }

    // Utility function to print the states
    void printStates(const std::vector<State>& states) const {
        for (size_t i = 0; i < states.size(); ++i) {
            std::cout << "State " << i << ":\n";
            for (const auto& item : states[i]) {
                std::cout << item.first << " -> ";
                for (const auto& symbol : item.second) {
                    std::cout << symbol << " ";
                }
                std::cout << "\n";
            }
            std::cout << std::endl;
        }
    }

private:
    std::map<std::string, std::vector<std::vector<std::string>>> productions;

    bool isNonterminal(const std::string& symbol) const {
        return productions.find(symbol) != productions.end();
    }

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
