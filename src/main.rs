use std::{io, process, io::Write};
use morse::{encode, decode};

fn main() -> std::io::Result<()> {
    let mut type_enc_denc = String::new();
    print!("1) Text -> morse (or)\n2) Morse -> text\n> ");
    io::stdout().flush();
    io::stdin().read_line(&mut type_enc_denc).expect("Could not read input");
    let type_enc_denc = type_enc_denc.trim().parse::<u8>()
        .unwrap_or_else(|err| {
            println!("Error: {}", err);
            process::exit(-1);
        });
    assert!(type_enc_denc == 1 || type_enc_denc == 2);
    println!("Enter the string to be converted: ");
    
    let mut user_input = String::new();
    io::stdin().read_line(&mut user_input).expect("Could not read input");
    user_input.make_ascii_uppercase();
<<<<<<< HEAD
    if type_enc_denc == 1 {
        match encode::encode(user_input.as_str()) {
            Ok(output) => {
                println!("Encoded string: {}", output);
            },
            Err(err) => {
                println!("Error: {:?}", err);
            }
        }
    } else if type_enc_denc == 2 {
        match decode::decode(user_input.as_str()) {
            Ok(output) => {
                println!("Decoded string: {}", output);
            },
            Err(err) => {
                println!("Error: {:?}", err);
            }
        }
    }

/*    let mut result = String::new();
=======
    
    let mut result = String::new();
>>>>>>> 7a66c1a3e5c00ea97d46771f6cfca6316827ea15
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
    println!("Morse code is:\n{}", result);*/
    Ok(())
}
