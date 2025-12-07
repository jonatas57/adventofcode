use std::io;

fn task1(ss: &Vec<Vec<char>>) -> i32 {
  let n = ss.len();
  let m = ss[0].len();
  let mut input = ss.clone();
  // find 'S'
  let spos = input[0].iter().position(|&c| c == 'S').unwrap();
  input[0][spos] = '|';
  let mut ans = 0;
  for i in 1..n {
    for j in 0..m {
      if input[i - 1][j] != '|' {
        continue;
      }
      match input[i][j] {
        '.' => input[i][j] = '|',
        '^' => {
          ans += 1;
          input[i][j - 1] = '|';
          input[i][j + 1] = '|';
        },
        _ => {}
      }
    }
  }
  ans
}

fn task2(ss: &Vec<Vec<char>>) -> i64 {
  let n = ss.len();
  let m = ss[0].len();
  let mut input: Vec<Vec<i64>> = ss.iter().map(|row| {
    row.iter().map(|&c| {
      match c {
        'S' => 1,
        _ => 0,
      }
    }).collect()
  }).collect();
  for i in 1..n {
    for j in 0..m {
      if input[i - 1][j] == 0 {
        continue;
      }
      match ss[i][j] {
        '.' => input[i][j] += input[i - 1][j],
        '^' => {
          input[i][j - 1] += input[i - 1][j];
          input[i][j + 1] += input[i - 1][j];
        },
        _ => {}
      }
    }
  }
  input[n - 1].iter().sum()
}

fn main() {
  let mut line = String::new();
  let mut input = vec![];
  while io::stdin().read_line(&mut line).unwrap() > 0 {
    input.push(line.trim().chars().collect());
    line.clear();
  }
  println!("Task 1: {}", task1(&input));
  println!("Task 2: {}", task2(&input));
}
