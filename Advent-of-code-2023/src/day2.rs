use std::{collections::HashMap, fs};

pub fn part1() {
    println!("part1");
    let input = fs::read_to_string("./src/day2.in").expect("Read day2.in");

    //red, green, blue
    let mut colors = HashMap::new();
    colors.insert("red", 12);
    colors.insert("green", 13);
    colors.insert("blue", 14);

    let mut ans = 0;

    'games: for game in input.lines() {
        let array: Vec<&str> = game.split(':').collect();

        //Game<space>
        let game_num = &array[0][5..].parse::<i32>().unwrap();

        for attempt in array[1].split(';') {
            for cube_with_spaces in attempt.split(',') {
                let num_and_color: Vec<&str> = cube_with_spaces.trim().split(' ').collect();
                let num = num_and_color[0]
                    .parse::<i32>()
                    .expect("Failed to parse number");
                let color = num_and_color[1];

                if let Some(&color_value) = colors.get(color) {
                    if num > color_value {
                        continue 'games;
                    }
                }
            }
        }

        ans += game_num;
    }

    println!("{ans}");
}

pub fn part2() {
    println!("part2");
    let input = fs::read_to_string("./src/day2.in").expect("Read day2.in");

    let mut ans = 0;

    for game in input.lines() {
        let array: Vec<&str> = game.split(':').collect();

        let mut max = [0, 0, 0];
        for attempt in array[1].split(';') {
            for cube_with_spaces in attempt.split(',') {
                let num_and_color: Vec<&str> = cube_with_spaces.trim().split(' ').collect();
                let num = num_and_color[0].parse::<i32>().unwrap();
                let color = num_and_color[1];

                let color_index = match color {
                    "red" => 0,
                    "green" => 1,
                    "blue" => 2,
                    _ => 99,
                };

                if num > max[color_index] {
                    max[color_index] = num;
                }
            }
        }
        ans += max[0] * max[1] * max[2];
    }

    println!("{ans}");
}
