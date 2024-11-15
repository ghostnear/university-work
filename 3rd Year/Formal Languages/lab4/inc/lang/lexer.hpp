#pragma once

#include <map>
#include <sstream>
#include <string>
#include <set>
#include <string>

class Lexer {
public:
    Lexer(const std::string& input_file);
    bool check(const std::string& input) const;
    bool is_deterministic() const;
    std::stringstream to_stream();

private:
    std::set<char> alphabet;
    std::map<std::pair<int, char>, int> transitions;
    int startState;
    std::set<int> acceptStates;
};