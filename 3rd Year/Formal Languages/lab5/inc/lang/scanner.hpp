#pragma once

#include "symbol_table.hpp"
#include "lang/lexer.hpp"

class Scanner
{
private:
    enum PIFType
    {
        SYMBOL = 0,
        TOKEN,
        CONSTANT,
        NONE,
        COUNT
    };

    uint32_t sym_id;
    SymbolTable symbols;
    std::vector<std::string> token_list;
    std::vector<std::pair<PIFType, std::string>> PIF;
    Lexer& number_fa, &symbol_fa;
    
public:
    Scanner(std::string token_path, Lexer& number_fa, Lexer& symbol_fa);
    void read_input(std::string input_path);
    void log_pif(std::string output_path);
    void log_symbol_table(std::string output_path);
};