#include "lang/scanner.hpp"
#include "lang/lexer.hpp"
#include <cstdlib>
#include <fstream>
#include <cstring>

int fa_showcase()
{
    while(true)
    {
        std::cout << "\n1. Inspect digits finite-automata.\n";
        std::cout << "0. Exit app.\n";
        std::cout << "\nCommand > ";
        int command = 0;
        std::string sequence = "";
        Lexer number_lexer("./inputs/FA-number.in");
        std::cin >> command;
        switch(command)
        {
        case 1:
            std::cout << "\n" << number_lexer.to_stream().str() << "\n";
            std::cout << "Reading sequence for testing > ";
            std::cin >> sequence;
            std::cout << ((number_lexer.check(sequence)) ? "\nSequence is valid.\n" : "\nSequence is invalid.\n");
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

int main(int argc, char* argv[])
{
    if(argc < 3)
        throw std::runtime_error("Tokens and input file not specified.");

    if(strcmp(argv[1], "fa-showcase") == 0)
        return fa_showcase();

    Scanner scanner = Scanner(std::string(argv[1]));
    try
    {
        scanner.read_input(std::string(argv[2]));
    }
    catch(std::runtime_error error)
    {
        std::string errorMessage = error.what();
        std::string errorToken = "";
        uint32_t index = errorMessage.size() - 1;
        while(errorMessage[index] != ' ') index--;
        errorToken = errorMessage.substr(index + 1, errorMessage.size() - index);
        std::ifstream fin(argv[2]);
        uint32_t line_index = 0;
        for (std::string line; std::getline(fin, line); )
        {
            line_index++;
            uint32_t startIndex = 0;
            while(startIndex == ' ') startIndex++;
            if(line.size() - startIndex < 2 || line[startIndex] == '-' && line[startIndex + 1] == '-') continue;
            uint32_t found = line.find(errorToken);
            if(found != std::string::npos)
            {
                std::cout << "An error occured while scanning the input file at line " << line_index;
                std::cout << " and column " << found + 1 << ", it is not lexically correct:\n\t" << errorMessage << "\n";
                break;
            }
        }
        fin.close();
        return EXIT_FAILURE;
    }

    std::cout << "File scanned succesfully, it is lexically correct, now dumping...\n";

    scanner.log_pif("./out/PIF.out");
    scanner.log_symbol_table("./out/ST.out");

    std::cout << "Dumped.\n";

    return EXIT_SUCCESS;
}
