use std::io;

fn count_wins(cards: &mut Vec<i32>, win: &mut Vec<i32>) -> i32 {
    cards.sort();
    win.sort();
    let mut wins = 0;
    let mut i = 0;
    let mut j = 0;
    while i < cards.len() && j < win.len() {
        if cards[i] > win[j] {
            j += 1;
        }
        else if cards[i] < win[j] {
            i += 1;
        }
        else {
            wins += 1;
            i += 1;
            j += 1;
        }
    }
    wins
}

fn parse(input: &Vec<String>) -> Vec<Vec<Vec<i32>>> {
    let split: Vec<String> = input.iter().map(|x| x.split(":").last().unwrap().to_string()).collect();
    let split2: Vec<Vec<String>> = split.iter().map(|x| x.split(" | ").map(|y| y.to_string()).collect()).collect();
    let cards = split2.iter()
                      .map(|x| x.iter()
                                .map(|y| y.split(" ")
                                          .map(|z| z.trim().to_string())
                                          .filter(|z| z != "")
                                          .map(|z| z.parse::<i32>().unwrap())
                                          .collect::<Vec<i32>>())
                                .collect::<Vec<Vec<i32>>>())
                      .collect::<Vec<Vec<Vec<i32>>>>();
    cards
}

fn task1(input: &Vec<String>) -> i32 {
    let cards = parse(input);
    cards.iter()
         .map(|x| count_wins(&mut x[0].clone(), &mut x[1].clone()))
         .map(|x| if x > 0 { 2_i32.pow((x - 1) as u32) } else { 0 })
         .sum::<i32>()
}

fn task2(input: &Vec<String>) -> i32 {
    let cards = parse(input);
    let wins = cards.iter()
                    .map(|x| count_wins(&mut x[0].clone(), &mut x[1].clone()))
                    .collect::<Vec<i32>>();
    let n = wins.len();
    let mut count = vec![0; n];
    count[0] = 1;
    for i in 0..n {
        if i > 0 {
            count[i] += count[i - 1];
        }
        let l = i + 1;
        let r = i + 1 + wins[i] as usize;
        if l < n {
            count[l] += count[i];
        }
        if r < n {
            count[r] -= count[i];
        }
    }
    count.iter().sum()
}

fn main() {
    let mut line = String::new();
    let mut input = Vec::new();
    while let Ok(_) = io::stdin().read_line(&mut line) {
        if line.trim() == "" {
            break;
        }
        input.push(line.trim().to_string());
        line.clear();
    }
    println!("Task 1: {}", task1(&input));
    println!("Task 2: {}", task2(&input));
}
