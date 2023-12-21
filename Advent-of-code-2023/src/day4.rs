use std::fs;

pub fn part1() {
    // let input = fs::read_to_string("./src/day4_sample.md").expect("couldn't read");
    let input = fs::read_to_string("./src/day4.md").expect("couldn't read");
    let mut ans = 0u32;

    for line in input.lines() {
        let line_split = line.splitn(2, ':').collect::<Vec<&str>>();
        let winning_num_game_num = line_split[1].splitn(2, '|').collect::<Vec<&str>>();

        let mut winning_nums = winning_num_game_num[0]
            .trim()
            .split_whitespace()
            .map(|c| c.parse::<u32>().unwrap())
            .collect::<Vec<u32>>();
        winning_nums.sort();
        let win_num_count = winning_nums.len();

        let mut game_nums = winning_num_game_num[1]
            .trim()
            .split_whitespace()
            .map(|c| c.parse::<u32>().unwrap())
            .collect::<Vec<u32>>();

        game_nums.sort();
        let game_num_count = game_nums.len();

        let mut i = 0usize;
        let mut j = 0usize;
        let mut match_count = 0u32;

        while i < win_num_count && j < game_num_count {
            let winning_num = winning_nums[i];
            let game_num = game_nums[j];

            if winning_num == game_num {
                match_count += 1;
                i += 1;
                j += 1;
            } else if game_num > winning_num {
                i += 1;
            } else if game_num < winning_num {
                j += 1;
            }
        }

        println!("matches {match_count}");
        if match_count > 0 {
            ans += 2u32.pow(match_count - 1);
        }
    }

    println!("{ans}");
}
