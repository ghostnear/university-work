#include "lang/lexer.hpp"

#include <fstream>

Lexer::Lexer(const std::string& input_file)
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

bool Lexer::check(const std::string& input) const
{
    int currentState = startState;
    for (char symbol : input) {
        if (transitions.find({currentState, symbol}) == transitions.end())
            return false;  // Invalid transition
        currentState = transitions.at({currentState, symbol});
    }
    return acceptStates.contains(currentState);
}

bool Lexer::is_deterministic() const
{
    // Check for duplicate transitions
    std::set<std::pair<uint32_t, char>> seen_transitions;
    for (const auto& transition : transitions)
    {
        if (seen_transitions.count(transition.first) > 0)
            return false;
        seen_transitions.insert(transition.first);
    }
    return true;
}

std::stringstream Lexer::to_stream()
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
