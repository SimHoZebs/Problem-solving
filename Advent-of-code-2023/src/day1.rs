use std::fs;

pub fn part1() {
    println!("part1");
    let input = fs::read_to_string("./src/day1.in").expect("Read day1.in");

    let mut total = 0;
    for line in input.lines() {
        let mut number = 0;

        for char in line.chars() {
            if let Some(digit) = char.to_digit(10) {
                if number > 0 {
                    number = number - number % 10 + digit;
                } else if digit > 0 {
                    number = digit * 10 + digit;
                }
            };
        }
        total += number;
    }

    println!("{total}");
}

pub fn part2() {
    println!("part 2");
    let input = fs::read_to_string("./src/day1.in").expect("Read day1.in");

    fn convert_string_to_num(line: &str, index: usize) -> u32 {
        let substring = &line[index..];
        let numbers: [(&str, u32); 9] = [
            ("one", 1),
            ("two", 2),
            ("three", 3),
            ("four", 4),
            ("five", 5),
            ("six", 6),
            ("seven", 7),
            ("eight", 8),
            ("nine", 9),
        ];

        for (word, number) in numbers.iter() {
            if substring.starts_with(word) {
                return *number;
            }
        }
        return 0;
    }

    let mut total = 0;
    for line in input.lines() {
        let mut number = 0;

        for (index, char) in line.chars().enumerate() {
            let digit = if let Some(digit) = char.to_digit(10) {
                digit
            } else {
                convert_string_to_num(line, index)
            };

            if digit > 0 && number > 0 {
                number = number - number % 10 + digit;
            } else if digit > 0 {
                number = digit * 10 + digit;
            }
        }
        total += number;
    }

    println!("{total}");
}
