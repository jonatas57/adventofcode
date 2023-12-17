use std::io;

fn solve(t: &i64, d: &i64) -> i64 {
  let mut l = 0;
  let mut r = t / 2;
  while l < r {
    let m = (l + r) / 2;
    if m * (t - m) <= *d {
      l = m + 1;
    } else {
      r = m;
    }
  }
  t - 2 * l + 1
}

fn task1(input: &Vec<(&i64, &i64)>) -> i64 {
  let mut res = 1;
  for (t, d) in input {
    res *= solve(*t, *d);
  }
  res
}

fn task2(input: &Vec<(&i64, &i64)>) -> i64 {
  let (t2, d2) = input.iter().fold((0, 0), |acc, (t, d)| {
    let (t1, d1) = acc;
    let t2 = (t1.to_string() + &t.to_string()).parse::<i64>().unwrap();
    let d2 = (d1.to_string() + &d.to_string()).parse::<i64>().unwrap();
    (t2, d2)
  });
  solve(&t2, &d2)
}

fn main() {
  let mut line = String::new();

  let _ = io::stdin().read_line(&mut line);
  let ts = line.trim().split(" ").filter(|&x| x != "").skip(1).map(|x| x.parse::<i64>().unwrap()).collect::<Vec<i64>>();
  line.clear();
  let _ = io::stdin().read_line(&mut line);
  let ds = line.trim().split(" ").filter(|&x| x != "").skip(1).map(|x| x.parse::<i64>().unwrap()).collect::<Vec<i64>>();
  let input = ts.iter().zip(ds.iter()).collect::<Vec<(_, _)>>();
  println!("Task 1: {}", task1(&input));
  println!("Task 2: {}", task2(&input));
}
