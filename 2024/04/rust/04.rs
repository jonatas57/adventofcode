use std::io;

fn check(input: &Vec<String>, x: i32, y: i32, dx: i32, dy: i32) -> i32 {
    let xmas = "XMAS";
    let mut at = 0;
    let n = input.len() as i32;
    let m = input[0].len() as i32;
    let mut ans = 0;
    // start at input[x][y] and sum iterate using dx, dy
    let mut i = x;
    let mut j = y;
    while i >= 0 && i < n && j >= 0 && j < m {
        let c = input[i as usize].chars().nth(j as usize).unwrap();
        let c2 = xmas.chars().nth(at as usize).unwrap();
        if c == c2 {
            at += 1;
            if at == xmas.len() as i32 {
                ans += 1;
                at = 0;
            }
        } else if c == 'X' {
            at = 1;
        } else {
            at = 0;
        }
        i += dx;
        j += dy;
    }
    ans
}

fn task1(input: Vec<String>) -> i32 {
    let mut ans = 0;
    let n = input.len() as i32;
    let m = input[0].len() as i32;

    for i in 0..n { ans += check(&input, i, 0, 0, 1); }
    for i in 0..n { ans += check(&input, i, m - 1, 0, -1); }
    for i in 0..m { ans += check(&input, 0, i, 1, 0); }
    for i in 0..m { ans += check(&input, n - 1, i, -1, 0); }
    for i in 0..n { ans += check(&input, i, 0, 1, 1); }
    for i in 1..m { ans += check(&input, 0, i, 1, 1); }
    for i in 0..n { ans += check(&input, i, m - 1, -1, -1); }
    for i in 1..m { ans += check(&input, n - 1, m - 1 - i, -1, -1); }
    for i in 0..n { ans += check(&input, i, m - 1, 1, -1); }
    for i in 1..m { ans += check(&input, 0, m - i - 1, 1, -1); }
    for i in 0..n { ans += check(&input, i, 0, -1, 1); }
    for i in 1..m { ans += check(&input, n - 1, i, -1, 1); }
    ans
}

fn sort(s: String) -> String {
    let mut v: Vec<char> = s.chars().collect();
    v.sort();
    v.into_iter().collect()
}

fn task2(input: Vec<String>) -> i32 {
    let mut ans = 0;
    let n = input.len() as i32;
    let m = input[0].len() as i32;
    for i in 1..n-1 {
        for j in 1..m-1 {
            if input[i as usize].chars().nth(j as usize).unwrap() != 'A' { continue; }
            // get adjacent chars in NW and SE directions
            let mut s1 = String::new();
            s1.push(input[(i - 1) as usize].chars().nth((j - 1) as usize).unwrap());
            s1.push(input[(i + 1) as usize].chars().nth((j + 1) as usize).unwrap());
            let mut s2 = String::new();
            s2.push(input[(i - 1) as usize].chars().nth((j + 1) as usize).unwrap());
            s2.push(input[(i + 1) as usize].chars().nth((j - 1) as usize).unwrap());
            s1 = sort(s1);
            s2 = sort(s2);
            if s1.eq("MS") && s2.eq("MS") {
                ans += 1;
            }
        }
    }
    ans
}

fn main() {
    let mut line = String::new();
    let mut input = Vec::new();
    while io::stdin().read_line(&mut line).unwrap() > 0 {
        input.push(line.clone());
        line.clear();
    }
    println!("Task 1: {}", task1(input.clone()));
    println!("Task 2: {}", task2(input.clone()));
}
