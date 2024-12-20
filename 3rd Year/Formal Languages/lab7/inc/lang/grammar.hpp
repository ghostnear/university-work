#pragma once

#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>

class Grammar {
public:
    Grammar(std::string path)
    {
        readFromFile(path);
    }

    // Read a grammar from file
    bool readFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty()) continue;
            std::istringstream iss(line);
            std::string lhs;
            iss >> lhs;
            nonterminals.insert(lhs);
            std::string arrow;
            iss >> arrow;
            std::string rhs;
            std::vector<std::string> production;
            while (iss >> rhs)
            {
                production.push_back(rhs);
                if (isupper(rhs[0]))
                    nonterminals.insert(rhs);
                else
                    terminals.insert(rhs);
            }
            productions[lhs].push_back(production);
        }
        file.close();
        return true;
    }

    // Print set of nonterminals
    void printNonterminals() const
    {
        std::cout << "Nonterminals: ";
        for (const auto& nt : nonterminals)
            std::cout << nt << " ";
        std::cout << std::endl;
    }

    // Print set of terminals
    void printTerminals() const
    {
        std::cout << "Terminals: ";
        for (const auto& t : terminals)
            std::cout << t << " ";
        std::cout << std::endl;
    }

    // Print set of productions
    void printProductions() const
    {
        std::cout << "Productions:\n";
        for (const auto& [lhs, rhs_list] : productions)
            for (const auto& rhs : rhs_list)
            {
                std::cout << lhs << " -> ";
                for (const auto& symbol : rhs)
                    std::cout << symbol << " ";
                std::cout << std::endl;
            }
    }

    // Get productions for a given nonterminal
    void printProductionsForNonterminal(const std::string& nonterminal) const
    {
        auto it = productions.find(nonterminal);
        if (it != productions.end())
            for (const auto& rhs : it->second)
            {
                std::cout << nonterminal << " -> ";
                for (const auto& symbol : rhs)
                    std::cout << symbol << " ";
                std::cout << std::endl;
            }
        else
            std::cout << "No productions for nonterminal: " << nonterminal << std::endl;
    }

    // Check if the grammar is a Context-Free Grammar (CFG)
    bool isCFG() const
    {
        for (const auto& [lhs, rhs_list] : productions)
        {
            if (lhs.empty() || lhs.size() != 1 || !isupper(lhs[0]))
                return false;
            for (const auto& rhs : rhs_list)
                for (const auto& symbol : rhs)
                    if (symbol.empty()) return false;
        }
        return true;
    }

    const std::map<std::string, std::vector<std::vector<std::string>>>& getProductions() const
    {
        return productions;
    }

private:
    std::set<std::string> nonterminals;
    std::set<std::string> terminals;
    std::map<std::string, std::vector<std::vector<std::string>>> productions;
};
