#include "gr-showcase.hpp"
#include "lang/lr0.hpp"
#include "lang/grammar.hpp"
#include "lang/parser_output.hpp"

int gr_showcase()
{
    while(true)
    {
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
                std::cout << "Parser states:\n";
                LR0Parser parser(first_grammar.getProductions());
                parser.canonicalCollection();
                parser.printStates();
                std::string token;
                std::cout << "Enter input string: ";
                std::cin >> token;
                ParserOutput output(parser);
                output.generateAndPrintParsingTable(token);
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
                LR0Parser parser(second_grammar.getProductions());
                parser.canonicalCollection();
                parser.printStates();
                std::string token;
                std::cout << "Enter input string: ";
                std::cin >> token;
                ParserOutput output(parser);
                output.generateAndPrintParsingTable(token);
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