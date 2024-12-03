use std::io;

fn check(v: &Vec<i32>) -> bool {
    let mut os = Vec::new();
    let mut ok = true;
    for i in 1..v.len() {
        let del = (v[i] - v[i-1]).abs();
        ok &= 1 <= del && del <= 3;
        let ord : i32;
        if v[i] > v[i-1] {
            ord = 1;
        }
        else if v[i] < v[i-1] {
            ord = -1;
        }
        else {
            ord = 0;
        }
        os.push(ord);
    }
    os.iter().all(|&x| x == os[0]) && ok
}

fn task1 (input: &Vec<Vec<i32>>) -> i32 {
    input.iter().filter(|x| check(x)).count() as i32
}

fn dampener(v: &Vec<i32>) -> Vec<Vec<i32>> {
    let mut res = Vec::new();
    for i in 0..v.len() {
        let mut a = Vec::new();
        for j in 0..v.len() {
            if i != j {
                a.push(v[j]);
            }
        }
        res.push(a);
    }
    res
}

fn task2 (input: &Vec<Vec<i32>>) -> i32 {
    input.iter().filter(|x| check(x) || dampener(x).iter().any(|y| check(y))).count() as i32
}

fn main () {
    let mut input: Vec<Vec<i32>> = Vec::new();
    let mut line = String::new();
    while io::stdin().read_line(&mut line).unwrap() > 0 {
        let iter = line.trim().split_whitespace();
        let a = iter.map(|x| x.parse::<i32>().unwrap()).collect::<Vec<i32>>();
        input.push(a);
        line.clear();
    }

    println!("Task 1: {:?}", task1(&input));
    println!("Task 2: {:?}", task2(&input));
}
