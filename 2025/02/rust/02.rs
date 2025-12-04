use std::io;
use std::collections::HashSet;

fn get_upper_bound(s: &str) -> i32 {
    let len = s.len();
    let h = len / 2;
    if len % 2 == 0 {
        let mut val = s[..h].parse::<i32>().unwrap();
        let r = s[h..].parse::<i32>().unwrap();
        if r > val {
            val += 1;
        }
        return val;
    }
    10_i32.pow(h as u32)
}

fn get_lower_bound(s: &str) -> i32 {
    let len = s.len();
    let h = len / 2;
    if len % 2 == 0 {
        let mut val = s[..h].parse::<i32>().unwrap();
        let r = s[h..].parse::<i32>().unwrap();
        if r < val {
            val -= 1;
        }
        return val;
    }
    10_i32.pow(h as u32) - 1
}

fn task1(input: &Vec<Vec<&str>>) -> i64 {
    let mut ans = 0;
    for pair in input {
        let l = get_upper_bound(pair[0]);
        let r = get_lower_bound(pair[1]);
        for i in l..=r {
            let mut s = i.to_string();
            s.push_str(&i.to_string());
            let val = s.parse::<i64>().unwrap();
            ans += val;
        }
    }
    ans
}

fn task2(input: &Vec<Vec<&str>>) -> i64 {
    let mut ls = input.iter().map(|pair| pair[0].parse::<i64>().unwrap()).collect::<Vec<i64>>();
    let mut rs = input.iter().map(|pair| pair[1].parse::<i64>().unwrap()).collect::<Vec<i64>>();
    ls.sort();
    rs.sort();
    let mut set = HashSet::new();
    for i in 1.. {
        let mut ok = true;
        let mut s = i.to_string();
        for j in 0.. {
            s.push_str(&i.to_string());
            let val = s.parse::<i64>().unwrap();
            if val > rs[rs.len() - 1] && j == 0 {
                ok = false;
            }
            let pos = ls.binary_search_by(|x| match x.cmp(&val) {
                std::cmp::Ordering::Equal => std::cmp::Ordering::Less,
                ord => ord,
            }).unwrap_err();
            if pos > 0 {
                if ls[pos - 1] <= val && val <= rs[pos - 1] {
                    set.insert(val);
                }
                if pos == ls.len() {
                    break;
                }
            }
        }
        if !ok {
            break;
        }
    }
    set.iter().sum()
}

fn main() {
    let mut s = String::new();
    let _ = io::stdin().read_line(&mut s);
    let input = s.trim().split(',').collect::<Vec<&str>>().into_iter().map(|x| x.split('-').collect::<Vec<&str>>()).collect::<Vec<Vec<&str>>>();
    println!("Task 1: {}", task1(&input));
    println!("Task 2: {}", task2(&input));
}
