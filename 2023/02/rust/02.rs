use std::io;
use std::cmp::max;

#[derive(Clone)]
struct Game {
  id: i32,
  draws: Vec<[i32; 3]>,
}

fn parse_color(s: String) -> (usize, i32) {
  let mut spl = s.split(" ");
  let cnt = spl.next().unwrap()
               .parse()
               .ok().unwrap();
  let color = match spl.next().unwrap() {
    "red" => 0,
    "green" => 1,
    "blue" => 2,
    _ => 3,
  };
  (color, cnt)
}

fn parse_draw(s: String) -> [i32; 3] {
  let mut cs: [i32; 3] = [0, 0, 0];
  //let colors: Vec<(usize, i32)> = s.split(", ").collect::<Vec<&str>>().iter().map(|&s| parse_color(s.to_string())).collect();
  let v = s.split(", ").collect::<Vec<&str>>();
  let colors: Vec<(usize, i32)> = v.iter().map(|&s| parse_color(s.to_string())).collect();
  for (c, cnt) in colors {
    cs[c] += cnt;
  }
  cs
}

fn parse_game(s: String) -> Game {
  let mut game = s.split(": ");
  let id: i32 = game.next().unwrap().split(" ").nth(1).unwrap().parse().ok().unwrap();
  let draws: Vec<[i32; 3]> = game.next()
                                 .unwrap()
                                 .split("; ")
                                 .collect::<Vec<&str>>()
                                 .iter()
                                 .map(|s| parse_draw(s.to_string()))
                                 .collect();
  Game {
    id: id,
    draws: draws,
  }
}

fn task1(games: Vec<Game>) -> i32 {
  games.iter().map(|game| {
    let mut ms = [0, 0, 0];
    for draw in &game.draws {
      for i in 0..3 {
        ms[i] = max(ms[i], draw[i]);
      }
    }
    (game.id, ms)
  })
  .filter(|(_, ms)| ms.iter().zip([12, 13, 14].iter()).map(|(a, b)| a <= b).all(|x| x))
  .fold(0, |a, (id, _)| a + id)
}

fn task2(games: Vec<Game>) -> i32 {
  games.iter().map(|game| {
    let mut ms = [0, 0, 0];
    for draw in &game.draws {
      for i in 0..3 {
        ms[i] = max(ms[i], draw[i]);
      }
    }
    ms[0] * ms[1] * ms[2]
  }).fold(0, |a, b| a + b)
}

fn main() {
  let mut input: Vec<Game> = Vec::new();
  let mut s = String::new();
  while io::stdin().read_line(&mut s).expect("") > 0 {
    input.push(parse_game(s.trim().to_string()));
    s = String::new();
  }

  let t1 = task1(input.clone());
  println!("Task 1: {t1}");
  let t2 = task2(input.clone());
  println!("Task 2: {t2}");
}
