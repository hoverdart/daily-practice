# Attempt — Minimum Boot Stations for a One-Way Network

Complete **before** reading `reference/`.

- Started / finished / total minutes:
- Outcome (independent / hint / reference / unfinished):
- Confidence (1–5):

## Recognize the graph
- What do vertices and directed edges represent?
- Give a counterexample to "boot every indegree-zero vertex".
- Can a directed cycle require zero boots? Why or why not?

## My approach
- How do I compute strongly connected components (SCCs)?
- Why do SCCs form a DAG when contracted?
- Why does each indegree-zero SCC need its own boot?
- Why does one boot per source SCC activate every station?
- How did I choose the smallest station ID per SCC?

## Complexity / Java / CS61B
- Brute-force time:
- Optimal time and space, using n vertices and m edges:
- What is the purpose of finishing order in Kosaraju?
- Why use explicit stacks for deep graphs?
- Bugs / hints / cases that failed:
- One recognition signal to remember: