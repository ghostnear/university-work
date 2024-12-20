#include "gr-showcase.hpp"

int gr_showcase()
{
    while(true)
    {
        std::cout << "\n3. Parse both grammars.";
        std::cout << "\n2. Inspect first grammar.";
        std::cout << "\n1. Inspect second grammar.";
        std::cout << "\n0. Exit app.\n";
        std::cout << "\nCommand > ";
        int command = 0;
        std::string sequence = "";
        Grammar first_grammar("./inputs/g1.txt");
        Grammar second_grammar("./inputs/g2.txt");
        std::cin >> command;
        switch(command)
        {
        case 3:
            {
                std::cout << "\nParsing first grammar...\n";
                LR0Parser parser(first_grammar.getProductions());
                auto states = parser.canonicalCollection();
                parser.printStates(states);

                std::cout << "\nParsing second grammar...\n";
                LR0Parser parser2(second_grammar.getProductions());
                auto states2 = parser2.canonicalCollection();
                parser2.printStates(states2);
                break;
            }
        case 2:
            {
                std::cout << "\nFirst grammar:\n";
                first_grammar.printNonterminals();
                first_grammar.printTerminals();
                first_grammar.printProductions();
                if (first_grammar.isCFG())
                    std::cout << "First grammar is a Context-Free Grammar (CFG).\n";
                else
                    std::cout << "First grammar is not a Context-Free Grammar (CFG).\n";
                std::string nonterminal = "";
                std::cout << "Enter non-terminal to print productions for: ";
                std::cin >> nonterminal;
                first_grammar.printProductionsForNonterminal(nonterminal);
            }
            break;
        case 1:
            {
                std::cout << "\nSecond grammar:\n";
                second_grammar.printNonterminals();
                second_grammar.printTerminals();
                second_grammar.printProductions();
                if (second_grammar.isCFG())
                    std::cout << "Second grammar is a Context-Free Grammar (CFG).\n";
                else
                    std::cout << "Second grammar is not a Context-Free Grammar (CFG).\n";
                std::string nonterminal = "";
                std::cout << "Enter non-terminal to print productions for: ";
                std::cin >> nonterminal;
                second_grammar.printProductionsForNonterminal(nonterminal);
            }
            break;
        case 0:
            std::cout << "\nExiting app...\n\n";
            return EXIT_SUCCESS;
            break;
        default:
            std::cout << "\nUnknown command entered.\n";
            break;
        }
    }

    return EXIT_SUCCESS;
}