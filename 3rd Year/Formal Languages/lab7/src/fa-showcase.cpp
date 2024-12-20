#include "fa-showcase.hpp"

int fa_showcase()
{
    while(true)
    {
        std::cout << "\n2. Inspect symbol finite-automata.";
        std::cout << "\n1. Inspect digits finite-automata.";
        std::cout << "\n0. Exit app.\n";
        std::cout << "\nCommand > ";
        int command = 0;
        std::string sequence = "";
        Lexer number_lexer("./inputs/FA-number.in");
        Lexer symbol_lexer("./inputs/FA-symbol.in");
        std::cin >> command;
        switch(command)
        {
        case 2:
            std::cout << "\n" << symbol_lexer.to_stream().str() << "\nIs deterministic: " << (symbol_lexer.is_deterministic() ? "true" : "false") << "\n\n";
            std::cout << "Reading sequence for testing > ";
            std::cin >> sequence;
            std::cout << "Checking sequence: " << sequence << "\n" << ((symbol_lexer.check(sequence)) ? "\nSequence is valid.\n" : "\nSequence is invalid.\n");
            break;
        case 1:
            std::cout << "\n" << number_lexer.to_stream().str() << "\nIs deterministic: " << (number_lexer.is_deterministic() ? "true" : "false") << "\n\n";
            std::cout << "Reading sequence for testing > ";
            std::cin >> sequence;
            std::cout << "Checking sequence: " << sequence << "\n" << ((number_lexer.check(sequence)) ? "\nSequence is valid.\n" : "\nSequence is invalid.\n");
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