use std::io;

fn isdigit(c: char) -> bool {
    c >= '0' && c <= '9'
}

fn task1(input: &Vec<String>) -> i32 {
    let mut ans = 0;
    let h = input.len() as i32;
    let w = input[0].len() as i32;
    let mut val = 0;
    let mut part = false;
    for i in 0..h {
        for j in 0..w {
            let c = input[i as usize].chars().nth(j as usize).unwrap();
            if !isdigit(c) {
                if part {
                    ans += val;
                }
                val = 0;
                part = false;
            }
            else {
                val *= 10;
                val += c as i32 - '0' as i32;
                for di in -1..=1 {
                    for dj in -1..=1 {
                        if di == 0 && dj == 0 {
                            continue;
                        }
                        let ni = i + di;
                        let nj = j + dj;
                        if ni < 0 || ni >= h || nj < 0 || nj >= w {
                            continue;
                        }
                        let c2 = input[ni as usize].chars().nth(nj as usize).unwrap();
                        if !isdigit(c2) && c2 != '.' && val > 0 {
                            part = true;
                        }
                    }
                }
            }
        }
    }
    ans
}

fn task2(input: &Vec<String>) -> i32 {
    let mut ans = 0;
    let h = input.len() as i32;
    let w = input[0].len() as i32;
    let mut ids = vec![vec![-1; w as usize]; h as usize];
    let mut vals = Vec::new();
    let mut next = 0;
    let mut val = 0;
    for i in 0..h {
        for j in 0..w {
            let c = input[i as usize].chars().nth(j as usize).unwrap();
            if !isdigit(c) {
                for k in (0..j).rev() {
                    if !isdigit(input[i as usize].chars().nth(k as usize).unwrap()) {
                        break;
                    }
                    ids[i as usize][k as usize] = next;
                }
                next += 1;
                vals.push(val);
                val = 0;
            }
            else {
                val *= 10;
                val += c as i32 - '0' as i32;
            }
        }
    }
    for i in 0..h {
        for j in 0..w {
            if input[i as usize].chars().nth(j as usize).unwrap() != '*' {
                continue;
            }
            let mut adj = std::collections::HashSet::<i32>::new();
            for di in -1..=1 {
                for dj in -1..=1 {
                    if di == 0 && dj == 0 {
                        continue;
                    }
                    let ni = i + di;
                    let nj = j + dj;
                    if ni < 0 || ni >= h || nj < 0 || nj >= w {
                        continue;
                    }
                    let x = ids[ni as usize][nj as usize];
                    if x >= 0 {
                        adj.insert(x);
                    }
                }
            }
            if adj.len() == 2 {
                let mut p = 1;
                for x in adj {
                    p *= vals[x as usize];
                }
                ans += p;
            }
        }
    }
    ans
}

fn main() {
    let mut input = Vec::<String>::new();
    let mut line = String::new();
    while io::stdin().read_line(&mut line).unwrap() > 0 {
        line.pop();
        line += ".";
        input.push(line.clone());
        line.clear();
    }
    println!("Task 1: {}", task1(&input));
    println!("Task 2: {}", task2(&input));
}
