use std::io;

fn task1(input: &Vec<i32>) -> i32 {
    let mut sum = 50;
    let mut ans = 0;
    for x in input {
        sum += x;
        sum = (sum % 100 + 100) % 100;
        if sum == 0 {
            ans += 1;
        }
    }
    ans
}

fn task2(input: &Vec<i32>) -> i32 {
    let mut sum = 50;
    let mut ans = 0;
    for x in input {
        let z;
        if *x < 0 {
            z = (100 - sum) % 100 - x;
        }
        else {
            z = sum + x;
        }
        ans += z / 100;
        sum += x;
        sum = (sum % 100 + 100) % 100;
    }
    ans
}

fn main() {
    let mut line = String::new();
    let mut input = Vec::new();
    while io::stdin().read_line(&mut line).unwrap() > 0 {
        if line.starts_with('L') {
            line.replace_range(0..1, "-");
        }
        else {
            line.remove(0);
        }
        input.push(line.trim().to_string().parse::<i32>().unwrap());
        line.clear();
    }
    println!("Task 1: {}", task1(&input));
    println!("Task 2: {}", task2(&input));
}
