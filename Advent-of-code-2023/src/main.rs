pub mod day1;
pub mod day2;
pub mod day3;

fn main() {
    let day: u8 = 3;

    match day {
        1 => {
            day1::part1();
            day1::part2();
        }
        2 => {
            day2::part1();
            day2::part2();
        }
        3 => {
            day3::part1();
        }
        _ => println!("Invalid day"),
    }
}
