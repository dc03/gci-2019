use std::io;

fn main() -> std::io::Result<()> {
    println!("Enter the string to be converted: ");
    let mut user_input = String::new();
    io::stdin().read_line(&mut user_input).expect("Could not read input");
    user_input.make_ascii_uppercase();
    let mut result = String::new();
    for elem in user_input.chars() {
        match elem {
            'A' => result.push_str(".-"),
            'B' => result.push_str("-..."),            
            'C' => result.push_str("-.-."),
            'D' => result.push_str("-.."),
            'E' => result.push_str("."),
            'F' => result.push_str("..-."),
            'G' => result.push_str("--."),
            'H' => result.push_str("...."),
            'I' => result.push_str(".."),
            'J' => result.push_str(".---"),
            'K' => result.push_str("-.-"),
            'L' => result.push_str(".-.."),
            'M' => result.push_str("--"),
            'N' => result.push_str("-."),
            'O' => result.push_str("---"),
            'P' => result.push_str(".--."),
            'Q' => result.push_str("--.-"),
            'R' => result.push_str(".-."),
            'S' => result.push_str("..."),
            'T' => result.push_str("-"),
            'U' => result.push_str("..-"),
            'V' => result.push_str("...-"),
            'W' => result.push_str(".--"),
            'X' => result.push_str("-..-"),
            'Y' => result.push_str("-.--"),
            'Z' => result.push_str("--.."),
            '1' => result.push_str(".----"),
            '2' => result.push_str("..---"),
            '3' => result.push_str("...--"),
            '4' => result.push_str("....-"),
            '5' => result.push_str("....."),
            '6' => result.push_str("-...."),
            '7' => result.push_str("--..."),
            '8' => result.push_str("---.."),
            '9' => result.push_str("----."),
            '0' => result.push_str("-----"),
            other => result.push(other)
        }
    }
    println!("Morse code is:\n{}", result);
    Ok(())
}
