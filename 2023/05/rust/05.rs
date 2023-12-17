use std::io;
use std::cmp;

type Map = Vec<i64>;
type Mapper = Vec<Map>;

fn task1(seeds: &Vec<i64>, mappers: &Vec<Mapper>) -> i64 {
  let mut seeds = seeds.clone();
  for mapper in mappers {
    for seed in &mut seeds {
      for map in mapper {
        if map[1] <= *seed && *seed < map[1] + map[2] {
          *seed += map[0] - map[1];
          break;
        }
      }
    }
  }
  *seeds.iter().min().unwrap()
}

fn task2(seeds: &Vec<i64>, mappers: &Vec<Mapper>) -> i64 {
  let mut pairs = Vec::new();
  for i in (0..seeds.len()).step_by(2) {
    pairs.push((seeds[i], seeds[i] + seeds[i + 1] - 1));
  }
  pairs.sort();
  for mapper in mappers {
    pairs = pairs.iter().map(|pair| {
      let mut new_pairs = Vec::new();
      let mut current = pair.clone();
      for map in mapper {
        if current.0 < map[1] {
          new_pairs.push((current.0, cmp::min(current.1, map[1] - 1)));
          current.0 = map[1];
          if current.0 > current.1 {
            break;
          }
        }
        if current.0 < map[1] + map[2] {
          new_pairs.push((cmp::max(current.0, map[1]) + map[0] - map[1], cmp::min(current.1, map[1] + map[2] - 1) + map[0] - map[1]));
          current.0 = map[1] + map[2];
          if current.0 > current.1 {
            break;
          }
        }
      }
      if current.0 <= current.1 {
        new_pairs.push((current.0, current.1));
      }
      new_pairs
    }).flatten().collect::<Vec<(i64, i64)>>();
    pairs.sort();
  }
  pairs.iter().fold(i64::MAX, |acc, pair| cmp::min(acc, pair.0))
}

fn main() {
  let mut line = String::new();

  io::stdin().read_line(&mut line).unwrap();
  let mut seed_split = line.trim().split(" ");
  seed_split.next();
  let seeds = seed_split.map(|x| x.parse::<i64>().unwrap()).collect::<Vec<i64>>();
  line.clear();
  io::stdin().read_line(&mut line).unwrap();
  line.clear();

  let mut mappers = Vec::new();
  let mut mapper = Vec::new();
  while io::stdin().read_line(&mut line).unwrap() > 0 {
    if line.trim() == "" {
      mapper.sort_by(|a: &Map, b: &Map| a[1].cmp(&b[1]));
      mappers.push(mapper);
      mapper = Vec::new();
    }
    else if (line.as_bytes()[0] as char).is_digit(10) {
      let map = line.trim().split(" ").map(|x| x.parse::<i64>().unwrap()).collect::<Vec<i64>>();
      mapper.push(map);
    }
    line.clear();
  }
  mapper.sort_by(|a: &Map, b: &Map| a[1].cmp(&b[1]));
  mappers.push(mapper);
  println!("Task 1: {}", task1(&seeds, &mappers));
  println!("Task 2: {}", task2(&seeds, &mappers));
}
