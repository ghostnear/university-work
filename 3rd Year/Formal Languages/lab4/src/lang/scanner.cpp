#include "lang/scanner.hpp"
#include "lang/symbol_table.hpp"
#include "utils/base.hpp"
#include <cctype>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>

Scanner::Scanner(std::string token_path)
{
    // Read all tokens.
    std::ifstream fin(token_path);
    if(!fin.good())
        throw std::runtime_error("Token input file could not be opened for reading.");
    for (std::string line; std::getline(fin, line); ) 
        token_list.push_back(line);
    fin.close();
}

void Scanner::read_input(std::string input_path)
{
    // Read all the file.
    std::ifstream fin(input_path);
    if(!fin.good())
        throw std::runtime_error("Input file could not be opened for reading.");

    std::string input = "  ";
    for (std::string line; std::getline(fin, line); )
    {
        // Exclude comments lines.
        uint32_t index = 0;
        while(line[index] == ' ' && index < line.length()) index++;

        if(line[index] != '-' && line[index + 1] != '-')
            input += line;
    }
    
    // Exclude all trivial spaces.
    std::size_t doubleSpace = input.find("  ");
    while (doubleSpace != std::string::npos)
    {
        input.erase(doubleSpace, 1);
        doubleSpace = input.find("  ");
    }
    
    // Parse depending on whitespaces.
    std::stringstream inputStream(input);
    std::string separators = "+-*/^&%!(){}[],/~=#;:";
    std::string carry = "";
    std::vector<std::string> tokens;
    for (std::string element; std::getline(inputStream, element, ' '); )
    {
        if(element == "")
            continue;

        carry = "";
        
        for(uint32_t index = 0; index < element.size(); index++)
        {
            for(auto token : token_list)
            {
                if(index + token.length() > element.size())
                    continue;
                
                if(element.substr(index, token.length()) == token)
                {
                    if(carry != "")
                        tokens.push_back(carry), carry = "";
                    tokens.push_back(token);
                    index += token.length();
                    break;
                }
            }
            if(element[index] != 0x00 && element[index] != 0x0A)
                carry += element[index];
        }
        if(carry != "")
            tokens.push_back(carry);
    }

    PIFType type;
    std::string arg;
    sym_id = 0;
    for(auto token : tokens)
    {
        // Search for token.
        type = PIFType::NONE;
        arg = "";
        for(auto list_token : token_list)
            if(token == list_token)
            {
                type = PIFType::TOKEN;
                arg = token;
                break;
            }
        
        if(type != PIFType::NONE)
        {
            PIF.push_back(std::make_pair(type, arg));
            continue;
        }

        // Check if the symbol respects the specs.
        if(!std::isalpha(token[0]))
        {
            // Might be number.
            uint32_t start = (token[0] == '-') ? 1u : 0u;
            for(auto index = start; index < token.size(); index++)
                if(!isdigit(token[index]))
                    throw std::runtime_error("Number contains non-letter character: " + token);
            
            if(token[start] == '0')
                throw std::runtime_error("Number cannot start with digit 0.");

            // It's a number.
            type = PIFType::CONSTANT;
            arg = token;
            PIF.push_back(std::make_pair(type, arg));
            continue;
        }

        for(auto character : token)
            if(!std::isalnum(character))
                throw std::runtime_error("Symbol contains non-alphanumerical character: " + token);

        type = PIFType::SYMBOL;
        arg = "";
        for(uint32_t index = 0; index < sym_id; index++)
        {
            std::string value = any_to_string(symbols.get(std::to_string(index)));
            if(value == token)
            {
                arg = std::to_string(index);
                break;
            }
        }
        if(arg == "")
        {
            arg = std::to_string(sym_id);
            symbols.add(std::to_string(sym_id), token);
            sym_id++;            
        }
        PIF.push_back(std::make_pair(type, arg));
    }
}

void Scanner::log_pif(std::string output_path)
{
    std::ofstream fout(output_path);
    for(auto element : PIF)
    {
        fout << "(";
        switch(element.first)
        {
        case PIFType::TOKEN:
            fout << "TOKEN '" << element.second << "')\n";
            break;
        case PIFType::SYMBOL:
            fout << "SYMBOL idx " << element.second << ")\n";
            break;
        case PIFType::CONSTANT:
            fout << "CONSTANT " << element.second << ")\n";
            break;
        default:
            throw new std::runtime_error("Invalid PIF type.");
            break;
        }
    }
    fout.close();
}

void Scanner::log_symbol_table(std::string output_path)
{
    std::ofstream fout(output_path);
    for(uint32_t index = 0; index < sym_id; index++)
    {
        std::string value = any_to_string(symbols.get(std::to_string(index)));
        fout << index << " " << value << "\n";
    }
    fout.close();
}