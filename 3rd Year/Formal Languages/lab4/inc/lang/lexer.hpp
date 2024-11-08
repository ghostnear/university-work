#pragma once

#include <map>
#include <sstream>
#include <string>
#include <fstream>
#include <set>
#include <string>

class Lexer {
public:
    Lexer(const std::string& input_file)
    {
        std::ifstream fin(input_file);

        std::string line;
        std::getline(fin, line);

        std::stringstream inputStream(line);
        inputStream >> startState;

        std::getline(fin, line);
        inputStream = std::stringstream(line);
        for(uint32_t current; inputStream >> current;)
            acceptStates.insert(current);
        
        while(std::getline(fin, line))
        {
            uint32_t source, destination;
            char barrier;

            inputStream = std::stringstream(line);
            inputStream >> source >> barrier >> destination;

            alphabet.insert(barrier);
            transitions[std::make_pair(source, barrier)] = destination;
        }

        fin.close();
    }

    bool check(const std::string& input) const {
        int currentState = startState;
        for (char symbol : input) {
            if (transitions.find({currentState, symbol}) == transitions.end())
                return false;  // Invalid transition
            currentState = transitions.at({currentState, symbol});
        }
        return acceptStates.contains(currentState);
    }

    std::stringstream to_stream()
    {
        std::stringstream result;
        
        result << "Start state: " << startState << "\n";
        result << "End states:\n";
        for(auto element : acceptStates)
            result << element << " ";
        result << "\n";

        result << "Alphabet: ";
        for(auto element : alphabet)
            result << element;
        result << "\n";
        result << "Transitions:\n";
        for(auto element : transitions)
            result << element.first.first << "->" << element.second << " if " << element.first.second << "\n";

        return result;
    }

private:
    std::set<char> alphabet;
    std::map<std::pair<int, char>, int> transitions;
    int startState;
    std::set<int> acceptStates;
};