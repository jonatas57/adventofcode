use std::io;
use std::collections::BTreeMap;
use std::collections::VecDeque;

fn topsort(g: &BTreeMap<i32, Vec<i32>>, page: Vec<i32>) -> Vec<i32> {
    let mut conv = BTreeMap::new();
    for i in 0..page.len() {
        conv.insert(page[i], i);
    }
    let mut deg = vec![0; page.len()];
    for (u, adj) in g.iter() {
        if conv.contains_key(u) {
            adj.iter().for_each(|v| {
                if let Some(id) = conv.get(v) {
                    deg[*id] += 1;
                }
            })
        }
    }
    let mut queue = VecDeque::new();
    for i in 0..page.len() {
        if deg[i] == 0 {
            queue.push_back(page[i]);
        }
    }
    let mut ord = vec![];
    while let Some(u) = queue.pop_front() {
        ord.push(u);
        if !g.contains_key(&u) {
            continue;
        }
        g.get(&u).unwrap().iter().filter(|v| conv.contains_key(v)).for_each(|v| {
            let id = conv.get(v).unwrap();
            deg[*id] -= 1;
            if deg[*id] == 0 {
                queue.push_back(*v);
            }
        })
    }
    ord
}

fn task1(g: BTreeMap<i32, Vec<i32>>, pages: Vec<Vec<i32>>) -> i32 {
    pages.iter().filter(|v| {
        topsort(&g, v.to_vec()).iter().zip(v.iter()).map(|(a, b)| a == b).fold(true, |acc, x| acc && x)
    }).map(|v| v[v.len() / 2]).fold(0, |acc, x| acc + x)
}

fn task2(g: BTreeMap<i32, Vec<i32>>, pages: Vec<Vec<i32>>) -> i32 {
    let ordered = pages.iter().map(|page| topsort(&g, page.to_vec()));
    pages.iter().zip(ordered).filter(|(page, ord)| {
        !ord.iter().zip(page.iter()).map(|(a, b)| a == b).fold(true, |acc, x| acc && x)
    }).map(|(_, ord)| ord).map(|v| v[v.len() / 2]).fold(0, |acc, x| acc + x)
}

fn main() {
    let mut line = String::new();
    let mut pages = Vec::new();

    let mut g = BTreeMap::<i32,Vec<i32>>::new();

    let mut ok = false;
    while io::stdin().read_line(&mut line).unwrap() > 0 {
        if ok {
            pages.push(line.trim().split(",").map(|x| x.parse::<i32>().unwrap()).collect::<Vec<_>>());
        }
        else {
            if line.len() == 1 {
                ok = true;
            }
            else {
                let e = line.trim().split("|").map(|x| x.parse::<i32>().unwrap()).collect::<Vec<_>>();
                if g.contains_key(&e[0]) {
                    g.get_mut(&e[0]).unwrap().push(e[1]);
                }
                else {
                    g.insert(e[0], vec![e[1]]);
                }
            }
        }
        line.clear();
    }
    println!("Task 1: {}", task1(g.clone(), pages.clone()));
    println!("Task 2: {}", task2(g.clone(), pages.clone()));
}
