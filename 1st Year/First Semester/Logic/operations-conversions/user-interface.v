module user_interface

import os					// For reading input mostly.
import term					// For work with terminal-related functions.
import v.util.version   	// For showing the version in the app info menu.
import numbers as num		// Our custom number module.
import v.mathutil as math

// Reads an integer from the input (while optionally displaying a message) and returns it. ! Invalid readings return 0 !
fn read_integer(message string) int
{
    a := os.input(message).int()
    return a
}

fn print_app_info()
{
    // Clear the screen
    term.clear()

    // Header
    term.set_cursor_position(x: 2, y: 2)
    println(term.underline(term.bright_green('App Info')) + "\n")

    // Body
    term.set_cursor_position(x: 0, y: 4)
    println('Made for the logic optional assignment.\n')
    println('Written in the V programming language. Compiled using ' + term.italic(term.bold(version.full_v_version(true))) + ".\n")

    wait_for_enter()
}

// Generate the main menu and read an action from it.
fn execute_main_menu() int
{
    // Clear the screen
    term.clear()

    // Header
    term.set_cursor_position(x: 2, y: 2)
    println(term.underline(term.bright_green('Select what operation to do')) + "\n")

    // Body
    term.set_cursor_position(x: 0, y: 4)
    println(term.bold('1. Do an arithmetic operation on positive integers in a base.'))
    println(term.bold('2. Conversion of a number between two bases.'))
    println(term.bold('3. App info.'))
    println(term.bold('4. Exit.') + "\n")

    // Footer
    return read_integer(term.italic("Your action: "))
}

fn show_error_message(message string)
{
    // Clear the screen
    term.clear()

    // Header
    term.set_cursor_position(x: 2, y: 2)
    println(term.underline(term.bright_red('An error has occured!')) + "\n")

    // Body
    term.set_cursor_position(x: 0, y: 4)
    println(term.bold(message + '\n'))

    wait_for_enter()
}

fn print_string_aligned(message string, size int)
{
    for index := 0; index < size - message.len; index++
    {
        print(" ")
    }
    println(message)
}

// Generate the arithmetic operation execution menu.
fn execute_arithmetic_operation()
{
    // Read the base from the terminal.
    term.clear()
    base := u8(read_integer(term.italic("Select the base in which you want the operations to be performed: ")))

    // The task says we can't use those bases, so...
    if (base > 10 && base < 16) || base < 2 || base > 16 {
        show_error_message(num.error_invalid_base)
        return
    }

    // Read the first number.
    first_number := num.create_number_from_string_in_base(
        base,
        os.input(term.italic("\nInput the first number: "))
    ) or {
        show_error_message(err.str())
        return
    }

    // Read the second number.
    second_number := num.create_number_from_string_in_base(
        base,
        os.input(term.italic("\nInput the second number: "))
    ) or {
        show_error_message(err.str())
        return
    }

    // Read the operation.
    operation := read_integer(
        term.bold("\nSelect an operation:\n") + term.italic("1. Addition.\n2. Subtraction.\n3. Multiplication.\n4. Division by one digit.\n\nInput: ")
    )

    // Clear and write the output of the operation.
    term.clear()

    // Do the operations.
    mut result := num.create_number_in_base(base) or { return }	// Dummy number.
    mut operation_str := ""
    match operation
    {
        // Addition
        1
        {
            operation_str = "+"
            result = first_number + second_number
        }

        // Subtraction
        2
        {
            operation_str = "-"
            result = first_number - second_number
        }

        // Multiplication
        3
        {
            operation_str = "*"
            // result = first_number * second_number TODO
        }

        // Division by one digit
        4
        {
            operation_str = "/"
            // Can only have one digit.
            if second_number.digit_count() > 1
            {
                show_error_message("The second number has more than one digit!")
                return
            }
            // result = first_number / second_number TODO
        }

        // Invalid
        else
        {
            show_error_message("Invalid operation selected!")
            return
        }
    }

    // Get results as strings
    first_number_str := first_number.str()
    second_number_str := second_number.str()
    result_str := result.str()

    // Get maximum length of the result
    max_len := math.max(math.max(first_number_str.len + 1, second_number_str.len), result_str.len) + 1

    // Print the operands
    print_string_aligned(first_number_str + operation_str, max_len)
    print_string_aligned(second_number_str, max_len - 1)

    // Print the line
    for index := 0; index < max_len; index++
    {
        print("-")
    }
    println(" (${base})")

    // Print the result and a newline.
    print_string_aligned(result_str, max_len - 1)
    println("")

    wait_for_enter()
}

// Generate the number conversions menu.
fn execute_number_conversions()
{
    
}

// Wait for an enter press and continue.
fn wait_for_enter()
{
    println(term.italic("Press enter to continue."))
    term.hide_cursor()
    os.input("")
    term.show_cursor()
}

// Current app state
enum AppState
{
    stopped
    running
}

// Main app structure
pub struct App
{
mut:
    current_state AppState
}

pub fn (mut self App) start()
{
    // Start the app
    self.current_state = .running

    // Main loop
    for self.current_state != .stopped
    {
        match execute_main_menu()
        {
            1	{	execute_arithmetic_operation()	}
            2	{	execute_number_conversions()	}
            3	{	print_app_info()	}
            4	{	self.current_state = .stopped	} // Mark app as stopped
            else
            {
                // Wrong input
                term.clear()
                term.set_cursor_position(x: 1, y: 2)
                println(term.bold("Unknown input. Please try again.") + "\n")
                
                wait_for_enter()
            }
        }
    }

    // End
    term.clear()
    term.set_cursor_position(x: 2, y: 2)
    println(term.bold(term.green(("Goodbye!"))) + "\n")
}