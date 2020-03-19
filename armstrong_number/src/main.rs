use std::io;
use std::io::Write;
use std::convert::TryInto;

fn main() -> std::io::Result<()> {
    print!("Enter the number: ");
    io::stdout().flush().unwrap();

    let mut user_input = String::new();
    io::stdin().read_line(&mut user_input).expect("Could not read input");

    let num = user_input.trim().parse::<usize>();
    match num {
        Ok(mut num) => {
            let length = user_input.chars().count() - 1;
            let mut sum = 0;
            let temp = num;
            while num > 0 {
                sum += (num % 10).pow(length.try_into().unwrap());
                num /= 10;
            }
            if sum == temp {
                println!("{} is an Armstrong number", temp);
            } else {
                println!("{} is not an Armstrong number", temp);
            }
        },
        Err(err) => {
            println!("Error: {}", err);
        }
    }

    Ok(())
}
