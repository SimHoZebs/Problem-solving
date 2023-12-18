use std::fs;

pub fn part1() {
    println!("part1");
    let input = fs::read_to_string("./src/day2.in").expect("Read day2.in");

    //red, green, blue
    let colors = [12, 13, 14];

    let mut ans = 0;

    for game in input.lines() {
        let array: Vec<&str> = game.split(':').collect();

        //Game<space>
        let game_num = &array[0][5..].parse::<i32>().unwrap();

        let mut is_allowed = true;

        for attempt in array[1].split(';') {
            for cube_with_spaces in attempt.split(',') {
                let num_and_cube: Vec<&str> = cube_with_spaces.trim().split(' ').collect();
                let num = num_and_cube[0].parse::<i32>().unwrap();
                let cube = num_and_cube[1];

                let color_index = match cube {
                    "red" => 0,
                    "green" => 1,
                    "blue" => 2,
                    _ => 99,
                };

                if num > colors[color_index] {
                    is_allowed = false;
                    break;
                }
            }

            if !is_allowed {
                break;
            }
        }

        if is_allowed {
            ans += game_num;
        }
    }

    println!("{ans}");
}

pub fn part2() {
    println!("part2");
    let input = fs::read_to_string("./src/day2.in").expect("Read day2.in");
}
