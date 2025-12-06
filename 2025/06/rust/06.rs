use std::io;

fn task1(input: &Vec<Vec<char>>, ops: &Vec<fn(i64, i64) -> i64>) -> i64 {
  let numbers = input.iter().map(|line| {
    line.split(|c| *c == ' ').filter(|s| !s.is_empty()).collect::<Vec<_>>().iter().map(|s| s.iter().collect::<String>().parse::<i64>().unwrap()).collect::<Vec<_>>()
  }).collect::<Vec<_>>();
  let n = numbers.len();
  let m = numbers[0].len();
  let mut ans = 0;
  for i in 0..m {
    let mut acc = numbers[0][i];
    for j in 1..n {
      acc = ops[i](acc, numbers[j][i]);
    }
    ans += acc;
  }
  ans
}

fn task2(input: &Vec<Vec<char>>, ops: &Vec<fn(i64, i64) -> i64>) -> i64 {
  let transposed_input = (0..input[0].len())
    .map(|i| input.iter().map(|row| row[i]).collect::<Vec<char>>())
    .collect::<Vec<Vec<char>>>();
  let mut numbers = transposed_input.iter().map(|line| {
    line.iter().filter(|c| **c != ' ').collect::<String>()
  }).collect::<Vec<String>>();
  numbers.push(String::from(""));
  let mut ans = 0;
  let mut i = 0;
  let mut acc = 0;
  for s in numbers {
    if s.is_empty() {
      ans += acc;
      acc = 0;
      i += 1;
    }
    else {
      let num = s.parse::<i64>().unwrap();
      if acc == 0 {
        acc = num;
      }
      else {
        acc = ops[i](acc, num);
      }
    }
  }
  ans
}

fn main() {
  let mut line = String::new();
  let mut input: Vec<Vec<char>> = vec![];
  while io::stdin().read_line(&mut line).unwrap() > 0 {
    input.push(line[0..line.len() - 1].chars().collect());
    line.clear();
  }
  let ops = input[input.len() - 1].clone().into_iter().filter(|s| *s != ' ').map(|s| if s == '+' { |a, b| a + b } else { |a, b| a * b }).collect::<Vec<fn(i64, i64) -> i64>>();
  input.pop();
  println!("Task 1: {}", task1(&input, &ops));
  println!("Task 2: {}", task2(&input, &ops));
}
