use std::io;

// Splits the string s before each occurrence of the characters in cs
fn split_before(s: &str, cs: String) -> Vec<&str> {
    let mut v = Vec::new();
    let mut start = 0;
    for (i, ch) in s.char_indices() {
        for c in cs.chars() {
            if ch == c {
                if start < i {
                    v.push(&s[start..i]);
                }
                start = i;
            }
        }
    }
    v.push(&s[start..]);
    v
}

fn parse_mul(s: &str) -> i32 {
    let comma_pos = s.find(',');
    let close_paren_pos = s.find(')');

    if comma_pos.is_none() || close_paren_pos.is_none() {
        return 0;
    }
    let x = comma_pos.unwrap();
    let y = close_paren_pos.unwrap();
    if x < y && s.len() > 4 && s[0..4].eq("mul(") {
        let a = s[4..x].parse::<i32>();
        let b = s[x + 1..y].parse::<i32>();
        if a.is_ok() && b.is_ok() {
            return a.unwrap() * b.unwrap();
        }
    }
    0
}

fn task1(input: &str) -> i32 {
    let ss = split_before(input, "m".to_string());
    ss.iter().map(|s| parse_mul(s)).fold(0, |acc, x| acc + x)
}

fn task2(input: &str) -> i32 {
    let ss = split_before(input, "dm".to_string());
    let mut ok = true;
    ss.iter().map(|s| {
        if s.len() > 0 && s.chars().next().unwrap() == 'm' {
            return if ok { parse_mul(s) } else { 0 };
        }
        if s.starts_with("do()") {
            ok = true;
        }
        else if s.starts_with("don't()") {
            ok = false;
        }
        return 0;
    }).fold(0, |acc, x| acc + x)
}

fn main() {
    let mut input = String::new();
    let mut line = String::new();
    while io::stdin().read_line(&mut line).unwrap() > 0 {
        input.push_str(&line.trim());
        line.clear();
    }
    println!("Task 1: {}", task1(&input));
    println!("Task 2: {}", task2(&input));
}
