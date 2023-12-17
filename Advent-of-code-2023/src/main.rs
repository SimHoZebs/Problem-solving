pub mod day1;
fn main() {
    let day = 1;

    match day {
        1 => {
            day1::part1();
            day1::part2();
        }
        _ => println!("Invalid day"),
    }
}
