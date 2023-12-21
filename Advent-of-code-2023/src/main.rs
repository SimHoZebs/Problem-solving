pub mod day1;
pub mod day2;
pub mod day3;
pub mod day4;

fn main() {
    let day: u8 = 4;

    println!("day {day} solution:");
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
            day3::part2();
        }
        4 => {
            day4::part1();
        }
        _ => println!("Invalid day"),
    }
}
