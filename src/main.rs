use std::io;
use std::io::Write;

fn main() -> std::io::Result<()> {
    print!("Enter the year: ");
    io::stdout().flush().unwrap();

    let mut user_input = String::new();
    io::stdin().read_line(&mut user_input).expect("Could not read input");

    let year = user_input.trim().parse::<usize>().unwrap();
    if year % 4 == 0 {
        if year % 400 == 0 {
            println!("{} is a leap year", year);
        } else if year % 100 == 0 {
            println!("{} is not a leap year", year);
        } else {
            println!("{} is a leap year", year);
        } 

    } else {
        println!("{} is not a leap year", year);
    } 

    Ok(())
}
