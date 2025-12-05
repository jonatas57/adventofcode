use std::io;

fn task1(rs: &Vec<(i64, i64)>, is: &Vec<i64>) -> i64 {
  let mut ri = 0;
  let mut ii = 0;
  let mut ans = 0;
  while ri < rs.len() && ii < is.len() {
    let (l, r) = rs[ri];
    let x = is[ii];
    if x < l {
      ii += 1;
    }
    else if x > r {
      ri += 1;
    }
    else {
      ans += 1;
      ii += 1;
    }
  }
  ans
}

fn task2(rs: &Vec<(i64, i64)>) -> i64 {
  let mut ans = 0;
  let mut last = -1;
  for (l, r) in rs {
    if *l > last + 1 {
      ans += r - l + 1;
      last = *r;
    }
    else if *r > last {
      ans += r - last;
      last = *r;
    }
  }
  ans
}

fn main() {
  let mut rs = Vec::new();
  let mut is = Vec::new();
  for line in io::stdin().lines() {
    let line = line.unwrap();
    if line.is_empty() {
      break;
    }
    let (l, r) = line.split_once('-').unwrap();
    rs.push((l.parse::<i64>().unwrap(), r.parse::<i64>().unwrap()));
  }
  for line in io::stdin().lines() {
    let line = line.unwrap();
    is.push(line.parse::<i64>().unwrap());
  }
  rs.sort();
  is.sort();
  println!("Task 1: {}", task1(&rs, &is));
  println!("Task 2: {}", task2(&rs));
}
