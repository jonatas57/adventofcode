use std::io;

fn parse_input(input: &[String]) -> Vec<(i64, Vec<i64>)> {
    input.iter()
        .map(|s| {
            let parts: Vec<&str> = s.split(' ').collect();
            // remove last char
            let target = parts[0]
                .trim_end_matches(':')
                .parse::<i64>()
                .unwrap_or(0);
            let list = parts[1..]
                .iter()
                .filter_map(|&x| x.parse::<i64>().ok())
                .collect::<Vec<i64>>();
            (target, list)
        })
        .collect()
}

fn check(target: &i64, acc: i64, list: Vec<i64>, operations: Vec<fn(i64, i64) -> i64>) -> bool {
    if list.is_empty() {
        return acc == *target
    }
    let first = list[0];
    operations.iter().any(|op| {
        let new_acc = op(acc, first);
        let new_list = list[1..].to_vec();
        check(target, new_acc, new_list, operations.clone())
    })
}

fn task1(input: &[String]) -> i64 {
    let parsed = parse_input(input);
    parsed.iter()
        .filter(|(target, list)| {
            check(target, list[0], list[1..].to_vec(), vec![|x: i64, y: i64| x + y, |x: i64, y: i64| x * y])
        })
        .map(|(target, _)| target)
        .sum::<i64>()
}

fn concat(x: i64, y: i64) -> i64 {
    let mut result = x.to_string();
    result.push_str(&y.to_string());
    result.parse::<i64>().unwrap_or(0)
}

fn task2(input: &[String]) -> i64 {
    let parsed = parse_input(input);
    parsed.iter()
        .filter(|(target, list)| {
            check(target, list[0], list[1..].to_vec(), vec![|x: i64, y: i64| x + y, |x: i64, y: i64| x * y, |x: i64, y: i64| concat(x, y)])
        })
        .map(|(target, _)| target)
        .sum::<i64>()
}

fn main() {
    let mut input = vec![];
    let mut line = String::new();
    while io::stdin().read_line(&mut line).unwrap() > 0 {
        input.push(line.trim().to_string());
        line.clear();
    }
    println!("Task 1: {}", task1(&input));
    println!("Task 2: {}", task2(&input));
}
