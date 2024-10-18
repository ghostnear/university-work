#include <any>
#include <iostream>
#include "lang/symbol_table.hpp"

int main()
{
    SymbolTable sym;
    sym.add("a", int(10));
    sym.add("pi", double(3.14));
    sym.add("das", std::string("test"));
    std::cout << sym.to_stream().str() << "\n";
    sym.remove("a");
    std::cout << sym.to_stream().str() << "\n";
    std::cout << any_to_double(sym.get("pi")) << "\n";
    return EXIT_SUCCESS;
}
