use std::io;

fn char2int(c: char) -> i32 {
  c as i32 - '0' as i32
}

fn task1(input: Vec<String>) -> i32 {
  let mut ans = 0;
  for s in &input {
    let mut ds: Vec<i32> = Vec::new();
    for i in 0..s.len() {
      let c = s.chars().nth(i).unwrap();
      if c.is_digit(10) {
        ds.push(char2int(c));
      }
    }
    ans += 10 * ds[0] + ds[ds.len() - 1];
  }
  ans
}

fn task2(input: Vec<String>) -> i32 {
  let nums = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
  let mut pos = [0, 0, 0, 0, 0, 0, 0, 0, 0];
  let mut ans = 0;
  for s in &input {
    let mut ds: Vec<i32> = Vec::new();
    for i in 0..s.len() {
      let c = s.chars().nth(i).unwrap();
      if c.is_digit(10) {
        ds.push(char2int(c));
      }
      else {
        for i in 0..nums.len() {
          if nums[i].chars().nth(pos[i]).unwrap() == c {
            pos[i] += 1;
            if pos[i] == nums[i].len() {
              pos[i] = 0;
              ds.push(i as i32 + 1);
            }
          }
          else if nums[i].chars().nth(0).unwrap() == c {
            pos[i] = 1;
          }
          else {
            pos[i] = 0;
          }
        }
      }
    }
    ans += 10 * ds[0] + ds[ds.len() - 1];
  }
  ans
}

fn main() {
  let mut input: Vec<String> = Vec::new();
  let mut s = String::new();
  while io::stdin().read_line(&mut s).expect("") > 0 {
    input.push(s.trim().to_string());
    s = String::new();
  }
  let t1 = task1(input.clone());
  println!("Task 1: {t1}");
  let t2 = task2(input.clone());
  println!("Task 2: {t2}");
}
