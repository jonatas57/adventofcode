use std::io;
use std::iter::zip;
use std::collections::BTreeMap;

fn task1(mut a: Vec<i32>, mut b: Vec<i32>) -> i32 {
    a.sort();
    b.sort();
    zip(a.iter(), b.iter()).map(|(x, y)| (x - y).abs()).sum::<i32>()
}

fn task2(a: Vec<i32>, b: Vec<i32>) -> i32 {
    let mut freq = BTreeMap::new();
    for y in b.iter() {
        *freq.entry(y).or_insert(0) += 1;
    }
    a.iter().map(|x| x * freq.remove(&x).unwrap_or(0)).sum::<i32>()
}

fn main() {
    let mut a = Vec::new();
    let mut b = Vec::new();

    let mut input = String::new();
    while io::stdin().read_line(&mut input).unwrap() > 0 {
        let mut iter = input.split_whitespace();
        let x: i32 = iter.next().unwrap().parse().unwrap();
        let y: i32 = iter.next().unwrap().parse().unwrap();
        a.push(x);
        b.push(y);
        input.clear();
    }

    println!("Task 1: {:?}", task1(a.clone(), b.clone()));
    println!("Task 2: {:?}", task2(a.clone(), b.clone()));
}
