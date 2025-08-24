use std::io;
use std::collections::HashMap;
use std::collections::HashSet;

fn task1(input: &Vec<String>) -> usize {
    let n = input.len();
    let m = input[0].len();
    let mut ants: HashMap<char, Vec<(usize, usize)>> = HashMap::new();
    
    for i in 0..n {
        for j in 0..m {
            if input[i].chars().nth(j).unwrap() != '.' {
                ants.entry(input[i].chars().nth(j).unwrap()).or_default().push((i, j));
            }
        }
    }
    let check = |x: isize, y: isize| x >= 0 && x < n as isize && y >= 0 && y < m as isize;
    let mut s = HashSet::new();
    for v in ants.values() {
        for &(a, b) in v {
            for &(c, d) in v {
                if a == c && b == d { break; }
                let dx = c as isize - a as isize;
                let dy = d as isize - b as isize;
                if check(a as isize - dx, b as isize - dy) { s.insert((a as isize - dx, b as isize - dy)); }
                if check(c as isize + dx, d as isize + dy) { s.insert((c as isize + dx, d as isize + dy)); }
            }
        }
    }

    s.len()
}

fn task2(input: &Vec<String>) -> usize {
    let n = input.len();
    let m = input[0].len();
    let mut ants: HashMap<char, Vec<(isize, isize)>> = HashMap::new();
    
    for i in 0..n {
        for j in 0..m {
            if input[i].chars().nth(j).unwrap() != '.' {
                ants.entry(input[i].chars().nth(j).unwrap()).or_default().push((i as isize, j as isize));
            }
        }
    }
    let check = |x: isize, y: isize| x >= 0 && x < n as isize && y >= 0 && y < m as isize;
    let mut s = HashSet::new();
    for v in ants.values() {
        for &(a, b) in v {
            s.insert((a, b));
            for &(c, d) in v {
                if a == c && b == d { break; }
                let dx = c - a;
                let dy = d - b;
                for i in 1.. {
                    if check(a - i * dx, b - i * dy) { s.insert((a - i * dx, b - i * dy)); }
                    else { break; }
                }
                for i in 1.. {
                    if check(c + i * dx, d + i * dy) { s.insert((c + i * dx, d + i * dy)); }
                    else { break; }
                }
            }
        }
    }
    s.len()
}

fn main() {
    let mut s = String::new();
    let mut input = Vec::new();
    while io::stdin().read_line(&mut s).unwrap() > 0 {
        input.push(s.trim().to_string());
        s.clear();
    }
    println!("Task 1: {}", task1(&input));
    println!("Task 2: {}", task2(&input));
}
