# Documentation

This program takes the first argument recieved from the command line to be the input file and parses it.

The program has the following classes:

- SymbolTable
    - add(key, value)
    - remove(key)
    - get(key)
    - to_stream() - formats the table to a stream for printing to the screen.

- Scanner
    - Scanner(token_path) - initializes the Scanner by reading the tokens from the specified path.
    - read_input(input_path) - reads and parses a file, internally producing its PIF and ST.
    - log_pif(output_path) - logs the PIF to a file.
    - log_st(output_path) - logs the ST to a file.

- Lexer:
    - Lexer(input_path) - initializes the lexer by reading the formatted file.
    - check(sequence) - checks if a sequence respects the rules of the Finite Automata.

    - BNF for the format of the Lexer input files:
    >    \<program>         ::= <start_state> <end_states> <transitions>
    >
    >    \<start_state>     ::= <numeric_value>
    >
    >    \<end_states>      ::= <numeric_value_list>
    >
    >    \<transitions>     ::= <transition> <transitions> | <transition>
    >
    >    \<transition>      ::= <numeric_value> " " <transition_barrier> " " <numeric_value>
    >
    >    \<numeric_value>   ::= <digit> <digits>
    >
    >    \<digits>          ::= <digit> <digits> | ""
    >
    >    \<digit>           ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
    >
    >    \<transition_barrier> ::= <character> <characters>
    >
    >    \<characters>      ::= <character> <characters> | ""
    >
    >    \<character>       ::= a..zA..Z...
    >
    >    \<numeric_value_list> ::= <numeric_value> <numeric_value_list> | <numeric_value>


If reading the input throws an error, it means a scanning error has occured and the following is done:
- The incorrect token is taken from the error message.
- The input is searched for the location of the error.
- An appropriate message is shown.