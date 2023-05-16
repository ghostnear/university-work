module numbers

// Used for printing the numbers independently of base.
const digits_as_runes = "0123456789ABCDEF-"

pub const error_invalid_base = "An invalid base has been selected for the number!"
pub const error_none_number_in_base = "The input provided could not be decoded to a number!"
pub const error_invalid_digit_in_base = "An invalid digit in the specified base has been provided!"
pub const error_invalid_number_in_base = "An invalid number in the specified base has been provided!"

pub struct NumberInABase
{
mut:
    negative bool
    base u8
    digits []byte
}

pub const none_number = NumberInABase {
    negative: false
    base: 2
    digits: []
}

// Returns the number of digits of the number.
pub fn (self NumberInABase) digit_count() int
{
    return self.digits.len
}

// Get digit at a position.
pub fn (self NumberInABase) get_digit(position int) byte
{
    if self.digits.len <= position
    {
        return 0
    }
    return self.digits[position]
}

// Converts the number to a string value.
pub fn (self NumberInABase) str() string
{
    mut result := ""
    if self.negative == true
    {
        result += "-"
    }

    for index := self.digits.len - 1; index >= 0; index--
    {
        result += digits_as_runes[self.digits[index]].ascii_str()
    }
    
    // Empty number
    if result == ""
    {
        return "None"
    }

    return result
}

// Adds a digit to the front of the number. Returns true if the operation was valid, otherwise an error.
pub fn (mut self NumberInABase) push_digit_front(digit byte) ?bool
{
    // Check digit validity
    if digit >= self.base
    {
        return error(error_invalid_digit_in_base)
    }
    self.digits << digit
    return true
}

// Removes empty 0's from the front of the number.
pub fn (mut self NumberInABase) clean_zeros()
{
    for self.digits.len > 1 && self.digits[self.digits.len - 1] == 0
    {
        self.digits = self.digits[..self.digits.len - 1]
    }
}

// Gets the position of a character in the digits_as_runes string.
fn get_digit_position(digit byte) u8
{
    for index := 0; index < digits_as_runes.len; index++
    {
        if digit == digits_as_runes[index]
        {
            return u8(index)
        }
    }
    return u8(digits_as_runes.len)
}

// Adds two number in the same base. Assumes the bases are identical.
fn (first NumberInABase) + (second NumberInABase) NumberInABase
{
    // Build result here.
    mut result := NumberInABase{
        base: first.base
        digits: []
    }

    mut t := 0
    mut index := 0
    for
    {
        sum := first.get_digit(index) + second.get_digit(index) + t
        result.push_digit_front(sum % result.base) or { return none_number }
        t = sum / result.base

        index++
        if index >= first.digit_count() && index >= second.digit_count() && t == 0
        {
            break
        } 
    }

    return result
}

// Subtracts two number in the same base. Assumes the bases are identical.
fn (first NumberInABase) - (second NumberInABase) NumberInABase
{
    // Build result here.
    mut result := NumberInABase{
        base: first.base
        digits: []
    }

    mut t := 0
    mut index := 0
    for
    {
        mut sum := first.get_digit(index) - second.get_digit(index) + t
        t = 0
        for sum < 0 {
            t -= 1
            sum += result.base
        }
        result.push_digit_front(sum % result.base) or { return none_number }

        index++
        if index >= first.digit_count() && index >= second.digit_count()
        {
            if t == 0
            {
                break
            }
            else
            {
                // Invert all digits
                for mut digit in result.digits
                {
                    digit = byte(result.base) - digit - 1
                }
                
                // Mark number as negative and add one.
                result += NumberInABase{
                    base: result.base
                    digits: [byte(1)]
                }
                result.negative = true
                break
            }
        } 
    }

    // Clean any trailing 0's
    result.clean_zeros()

    return result
}

// Create a number in a specified base from a string.
// Returns an error if the base is not in the valid interval required for the task or if the string is not a valid number in the base.
pub fn create_number_from_string_in_base(base u8, number_string string) ?NumberInABase
{
    // Create the number and propagate any errors.
    mut number := create_number_in_base(base) or {
        return error(err.str())
    }

    for index := number_string.len - 1; index >= 0; index--
    {
        // Get the correspondent position and return an error if invalid.
        pos := get_digit_position(number_string[index])
        number.push_digit_front(pos) or {
            return error(error_invalid_number_in_base)
        }
    }

    // None number, should not exist.
    if number.digit_count() == 0
    {
        return error(error_none_number_in_base)
    }

    return number
}

// Create a number in a specified base.
// Returns an error if the base is not in the valid interval required for the task.
pub fn create_number_in_base(base u8) ?NumberInABase
{
    if base < 2 || base > 16
    {
        return error(error_invalid_base)
    }

    // Return None.
    return NumberInABase {
        base: base
        digits: []
    }
}