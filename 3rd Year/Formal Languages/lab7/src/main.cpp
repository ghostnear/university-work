#include "lang/scanner.hpp"
#include "gr-showcase.hpp"
#include "fa-showcase.hpp"
#include <cstdlib>
#include <fstream>
#include <cstring>

int main(int argc, char* argv[])
{
    if(argc < 3)
        throw std::runtime_error("Tokens and input file not specified.");

    if(strcmp(argv[1], "fa-showcase") == 0)
        return fa_showcase();

    if(strcmp(argv[1], "gr-showcase") == 0)
        return gr_showcase();

    Lexer number_fa("./inputs/FA-number.in");
    Lexer symbol_fa("./inputs/FA-symbol.in");
    Scanner scanner = Scanner(std::string(argv[1]), number_fa, symbol_fa);
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
