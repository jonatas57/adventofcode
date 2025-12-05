use std::io;
use std::cmp::max;

fn task1(input: &Vec<String>) -> i64 {
  let mut ans = 0;
  for line in input {
    let mut val = 0;
    let mut m = 0;
    for c in line.chars() {
      let v = c as i64 - '0' as i64;
      val = max(10 * m + v, val);
      m = max(m, v);
    }
    ans += val;
  }
  ans
}

fn task2(input: &Vec<String>) -> i64 {
  let n = input[0].len();
  let mut ans = 0;
  for line in input {
    let mut dp = vec![vec![0; n + 1]; 13];
    for i in 1..=12 {
      for j in 0..n {
        let v = line.chars().nth(j).unwrap() as i64 - '0' as i64;
        dp[i][j + 1] = max(dp[i][j], dp[i - 1][j] * 10 + v);
      }
    }
    ans += dp[12][n];
  }
  ans
}

fn main() {
  let mut input = Vec::new();
  let mut line = String::new();
  while io::stdin().read_line(&mut line).unwrap() > 0 {
    input.push(line.trim().to_string());
    line.clear();
  }
  println!("Task 1: {}", task1(&input));
  println!("Task 2: {}", task2(&input));
}
