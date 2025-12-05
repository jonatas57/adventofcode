use std::io;

fn task1(input: &Vec<String>) -> i32 {
  let mut ans = 0;
  let n = input.len() as isize;
  let m = input[0].len() as isize;
  for i in 0..n {
    for j in 0..m {
      let mut cnt = 0;
      if input[i as usize].chars().nth(j as usize).unwrap() == '.' {
        continue;
      }
      for i2 in i-1..=i+1 {
        for j2 in j-1..=j+1 {
          if i2 < 0 || i2 >= n as isize || j2 < 0 || j2 >= m as isize || (i2 == i as isize && j2 == j as isize) {
            continue;
          }
          if input[i2 as usize].chars().nth(j2 as usize).unwrap() == '@' {
            cnt += 1;
          }
        }
      }
      if cnt < 4 {
        ans += 1;
      }
    }
  }
  ans
}

fn task2(input_base: &Vec<String>) -> i32 {
  let mut input = input_base.clone();
  let mut ans = 0;
  let n = input.len() as isize;
  let m = input[0].len() as isize;
  loop {
    let mut to_rem = vec![];
    for i in 0..n {
      for j in 0..m {
        let mut cnt = 0;
        if input[i as usize].chars().nth(j as usize).unwrap() == '.' {
          continue;
        }
        for i2 in i-1..=i+1 {
          for j2 in j-1..=j+1 {
            if i2 < 0 || i2 >= n as isize || j2 < 0 || j2 >= m as isize || (i2 == i as isize && j2 == j as isize) {
              continue;
            }
            if input[i2 as usize].chars().nth(j2 as usize).unwrap() == '@' {
              cnt += 1;
            }
          }
        }
        if cnt < 4 {
          to_rem.push((i as usize, j as usize));
        }
      }
    }
    if to_rem.is_empty() {
      break;
    }
    for (r, c) in to_rem.iter() {
      let row = unsafe { input.get_mut(*r).unwrap().as_bytes_mut() };
      row[*c] = b'.';
    }
    ans += to_rem.len() as i32;
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
