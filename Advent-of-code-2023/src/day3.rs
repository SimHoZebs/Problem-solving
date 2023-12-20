use std::collections::VecDeque;
use std::fs;

pub fn part1() {
    //if pos is "right", then recursively all numbers on the right to the end of array.
    //if "left", do the same for numbers on the left to the start of array.
    //otherwise ("mid"), add the number to the array and do both "left" and "right."
    fn gather_digits(
        pos: &str,
        line_iterable: &Vec<char>,
        line_len: usize,
        j: usize,
        digit_array: &mut VecDeque<char>,
    ) {
        if line_iterable[j].is_digit(10) {
            if pos == "left" {
                digit_array.push_front(line_iterable[j]);
            } else {
                digit_array.push_back(line_iterable[j]);
            }
        } else {
            return;
        }

        if pos != "right" && j > 0 {
            gather_digits("left", line_iterable, line_len, j - 1, digit_array);
        }

        if pos != "left" && j < line_len - 1 {
            gather_digits("right", line_iterable, line_len, j + 1, digit_array);
        }
    }

    fn gather_coords(
        adj_cell: &(usize, &str),
        line_array_len: usize,
        j: usize,
        adj_coords: &mut Vec<[usize; 2]>,
    ) {
        let (adj_i, adj_line) = adj_cell;
        let line_iterable: Vec<char> = adj_line.chars().collect();

        //mid
        if line_iterable[j].is_digit(10) {
            adj_coords.push([*adj_i, j]);
        } else {
            //left diagonal
            if j > 0 {
                adj_coords.push([*adj_i, j - 1]);
            }
            //right diagonal
            if j < line_array_len - 1 {
                adj_coords.push([*adj_i, j + 1]);
            }
        }
    }

    let input = fs::read_to_string("./src/day3.in").expect("cound't read day3.in");

    let line_array: Vec<(usize, &str)> = input.lines().enumerate().collect();
    let line_array_len = line_array.len();

    let mut answer: u32 = 0;

    for (i, line) in &line_array {
        for (j, char) in line.char_indices() {
            //skip numbers and '.'
            if char.is_digit(10) || char == '.' {
                continue;
            }

            //now char is a special character; collect coord of adjcent cells.
            //The coords will later be used to find numbers.
            //If non-diagnoal cells have digits, don't care about the diagonal cells on the same line.
            let mut adj_coords: Vec<[usize; 2]> = vec![];

            //top
            if *i > 0 {
                gather_coords(&line_array[*i - 1], line_array_len, j, &mut adj_coords);
            }

            //sides
            gather_coords(&line_array[*i], line_array_len, j, &mut adj_coords);

            //bottom
            if *i < line_array_len - 1 {
                gather_coords(&line_array[*i + 1], line_array_len, j, &mut adj_coords);
            }

            //go through the coords and gather digits in the coords
            for coord in adj_coords {
                let mut digit_array: VecDeque<char> = VecDeque::new();

                let (_, adj_line) = line_array[coord[0]];
                let line_len = adj_line.len();
                let line_iterable: Vec<char> = adj_line.chars().collect();

                let dir = if coord[1] < j {
                    "left"
                } else if coord[1] > j {
                    "right"
                } else {
                    "mid"
                };

                //gather consecutive digits from the coord
                gather_digits(dir, &line_iterable, line_len, coord[1], &mut digit_array);

                //the coord never had a digit
                if digit_array.is_empty() {
                    continue;
                }

                //starting from oneth number, multiply it by 10^(i) and add to the answer.
                //[1,2,3,4] = 1*10^3 + 2*10^2 + 3*10^1 + 4*10^0 =1234
                for (pow, digit) in digit_array.into_iter().rev().enumerate() {
                    answer += (digit.to_digit(10).unwrap()) * (10u32.pow(pow as u32));
                }
            }
        }
    }

    println!("{answer}");
}
