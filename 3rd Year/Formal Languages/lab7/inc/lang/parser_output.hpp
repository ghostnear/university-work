#pragma once

#include "lang/lr0.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>
#include <map>
#include <iomanip>

class ParserOutput {
public:
    struct Node {
        std::string value;
        std::vector<Node> children;
    };

    explicit ParserOutput(LR0Parser& parser)
        : parser(parser), rootNode({"root", {}}) {}

    // Generate and print the parsing table with parent and sibling relationships
    void generateAndPrintParsingTable(const std::string& input) {
        // Clear previous tree
        rootNode.children.clear();

        std::stack<int> stateStack;
        stateStack.push(0);

        std::map<std::pair<int, std::string>, std::pair<std::string, int>> parsingTable;

        std::cout << "Parsing Table:\n";
        std::cout << "State  | Symbol | Action    | Next State\n";
        std::cout << "----------------------------------------\n";

        for (char ch : input) {
            std::string symbol(1, ch);
            int currentState = stateStack.top();
            for (const auto& item : parser.C[currentState]) {
                auto pos = std::find(item.second.begin(), item.second.end(), ".");
                if (pos != item.second.end() && ++pos == item.second.end()) {
                    if (item.first != "S'") {
                        parsingTable[{currentState, ""}] = {"reduce", currentState};
                        printRow(currentState, symbol, "reduce", currentState);
                    } else {
                        parsingTable[{currentState, ""}] = {"accept", currentState};
                        printRow(currentState, symbol, "accept", currentState);
                    }
                } else if (pos != item.second.end() && *pos != "." && parser.isNonterminal(*pos)) {
                    for (const auto& state : parser.C) {
                        if (parser.goTo(parser.C[currentState], *pos) == state) {
                            int nextState = std::distance(parser.C.begin(), std::find(parser.C.begin(), parser.C.end(), state));
                            parsingTable[{currentState, *pos}] = {"shift", nextState};
                            stateStack.push(nextState);
                            printRow(currentState, symbol, "shift", nextState);
                        }
                    }
                } else if (pos != item.second.end() && *pos != "." && !parser.isNonterminal(*pos)) {
                    for (const auto& state : parser.C) {
                        if (parser.goTo(parser.C[currentState], *pos) == state) {
                            int nextState = std::distance(parser.C.begin(), std::find(parser.C.begin(), parser.C.end(), state));
                            parsingTable[{currentState, *pos}] = {"shift", nextState};
                            stateStack.push(nextState);
                            printRow(currentState, symbol, "shift", nextState);
                        }
                    }
                }
            }
        }

        // Check for conflicts in the parsing table
        bool hasConflicts = false;
        for (const auto& entry : parsingTable) {
            // Check if there's a shift action in the current state and current input
            if (parsingTable.count({entry.first.first, entry.first.second}) && parsingTable.at({entry.first.first, entry.first.second}).first == "shift") {
                // Check for reduce action in the same state for the same or empty input
                if (parsingTable.count({entry.first.first, ""}) && parsingTable.at({entry.first.first, ""}).first == "reduce") {
                    std::cerr << "Shift/Reduce conflict at row " << entry.first.first << " and column " << entry.first.second << "\n";
                    hasConflicts = true;
                }
            }
            
            // Check for multiple reduce actions in the same state
            if (parsingTable.count({entry.first.first, ""}) && parsingTable.at({entry.first.first, ""}).first == "reduce") {
                for (const auto& innerEntry : parsingTable) {
                    if (innerEntry.first.first == entry.first.first && innerEntry.first.second != "" && parsingTable.at({innerEntry.first.first, innerEntry.first.second}).first == "reduce") {
                        std::cerr << "Reduce/Reduce conflict at row " << entry.first.first << "\n";
                        hasConflicts = true;
                    }
                }
            }
        }

        // Check if there is an accept, if not a conflict occured.
        bool hasAccept = false;
        for (const auto& entry : parsingTable) {
            if (entry.second.first == "accept") {
                hasAccept = true;
                break;
            }
        }

        if(!hasAccept) {
            std::cerr << "Conflict: No accept action in the parsing table.\n";
            // Show what state we ended in and what symbol was used.

            // Find the last parsed state and the character that got us there.
            int lastState = stateStack.top();

            // Find the last symbol that was used to get to the last state.
            std::string lastSymbol;

            for (char ch : input) {
                std::string symbol(1, ch);
                int currentState = stateStack.top();
                for (const auto& item : parser.C[currentState]) {
                    auto pos = std::find(item.second.begin(), item.second.end(), ".");
                    if (pos != item.second.end() && ++pos == item.second.end()) {
                        lastSymbol = symbol;
                    }
                }
            }

            // Show them.
            std::cerr << "Last state: " << lastState << "\n";
            std::cerr << "Last symbol: " << lastSymbol << "\n";

            hasConflicts = true;
        }

        if (!hasConflicts)
            std::cout << "No conflicts detected in the parsing table." << "\n";
    }

    // Print data structure to the screen
    void printToScreen() const {
        printNode(rootNode, 0);
    }

    // Print data structure to a file
    void printToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            printNodeToFile(outFile, rootNode, 0);
            outFile.close();
        }
    }

private:
    LR0Parser& parser;
    Node rootNode;

    void printRow(int state, const std::string& symbol, const std::string& action, int nextState) {
        std::cout << std::setw(6) << state << " | "
                  << std::setw(6) << symbol << " | "
                  << std::setw(8) << action << " | "
                  << std::setw(11) << nextState << "\n";
    }

    void constructParseTree(const std::string& input, const std::map<std::pair<int, std::string>, std::pair<std::string, int>>& parsingTable) {
        std::stack<Node*> nodeStack;
        Node* currentNode = &rootNode;

        for (char ch : input) {
            std::string symbol(1, ch);
            int currentState = nodeStack.empty() ? 0 : std::stoi(nodeStack.top()->value);
            auto action = parsingTable.at({currentState, symbol});

            if (action.first == "shift") {
                Node* newNode = new Node{symbol, {}};
                currentNode->children.push_back(*newNode);
                nodeStack.push(newNode);
                currentNode = newNode;
            } else if (action.first == "reduce") {
                Node* newNode = new Node{symbol, {}};
                if (!nodeStack.empty()) {
                    nodeStack.top()->children.push_back(*newNode);
                    nodeStack.pop();
                }
                currentNode = nodeStack.empty() ? &rootNode : nodeStack.top();
            }
        }
    }

    void printNode(const Node& node, int indent) const {
        for (int i = 0; i < indent; ++i) std::cout << "  ";
        std::cout << node.value << "\n";
        for (const auto& child : node.children) {
            printNode(child, indent + 1);
        }
    }

    void printNodeToFile(std::ofstream& outFile, const Node& node, int indent) const {
        for (int i = 0; i < indent; ++i) outFile << "  ";
        outFile << node.value << "\n";
        for (const auto& child : node.children) {
            printNodeToFile(outFile, child, indent + 1);
        }
    }
};
