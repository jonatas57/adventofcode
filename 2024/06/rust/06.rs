use std::io;

fn task1(input: Vec<Vec<char>>) -> i32 {
    let n = input.len() as i32;
    let m = input[0].len() as i32;
    let mut x = 0;
    let mut y = 0;
    for i in 0..n {
        for j in 0..m {
            if input[i as usize][j as usize] == '^' {
                x = i;
                y = j;
            }
        }
    }
    let mut dir = 0;
    let mut vis = Vec::new();
    loop {
        vis.push((x, y));
        let nx = x + [-1, 0, 1, 0][dir as usize];
        let ny = y + [0, 1, 0, -1][dir as usize];
        if nx < 0 || nx >= n || ny < 0 || ny >= m {
            break;
        }
        if input[nx as usize][ny as usize] == '#' {
            dir = (dir + 1) % 4;
        } else {
            x = nx;
            y = ny;
        }
    }
    // remove duplicates
    vis.sort();
    vis.dedup();
    vis.len() as i32
}

fn task2(mut input: Vec<Vec<char>>) -> i32 {
    let n = input.len() as i32;
    let m = input[0].len() as i32;
    let mut x = 0;
    let mut y = 0;
    for i in 0..n {
        for j in 0..m {
            if input[i as usize][j as usize] == '^' {
                x = i;
                y = j;
            }
        }
    }
    let mut ans = 0;
    for i in 0..n {
        for j in 0..m {
            if input[i as usize][j as usize] == '#' {
                continue;
            }
            input[i as usize][j as usize] = '#';

            let mut vis = vec![vec![0 as i32; m as usize]; n as usize];
            let mut dir = 0;
            let mut a = x;
            let mut b = y;
            loop {
                if vis[a as usize][b as usize] & (1 << dir) != 0 {
                    ans += 1;
                    break;
                }
                vis[a as usize][b as usize] |= 1 << dir;
                let nx = a + [-1, 0, 1, 0][dir];
                let ny = b + [0, 1, 0, -1][dir];
                if nx < 0 || nx >= n || ny < 0 || ny >= m {
                    break;
                }
                if input[nx as usize][ny as usize] == '#' {
                    dir = (dir + 1) % 4;
                }
                else {
                    a = nx;
                    b = ny;
                }
            }

            input[i as usize][j as usize] = '.';
        }
    }
    ans
}

fn main() {
    let mut s = String::new();
    let mut input = Vec::new();
    while io::stdin().read_line(&mut s).unwrap() > 0 {
        input.push(s.trim().chars().collect());
        s.clear();
    }
    println!("Task 1: {}", task1(input.clone()));
    println!("Task 2: {}", task2(input.clone()));
}
