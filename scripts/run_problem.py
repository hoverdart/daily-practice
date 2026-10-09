#!/usr/bin/env python3
"""Compile/run the tests for one generated practice problem."""

from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path


def run(cmd: list[str], cwd: Path) -> int:
    print("$", " ".join(cmd), flush=True)
    return subprocess.run(cmd, cwd=cwd).returncode


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("problem_dir", type=Path)
    args = parser.parse_args()

    p = args.problem_dir.resolve()
    if not p.is_dir():
        print(f"Not a directory: {p}", file=sys.stderr)
        return 2

    if (p / "tests.py").exists():
        return run([sys.executable, "tests.py"], p)

    for test in ("Tests.java", "TestSolution.java"):
        if (p / test).exists():
            rc = run(["javac", "Solution.java", test], p)
            return rc or run(["java", Path(test).stem], p)

    for test in ("tests.cpp", "test.cpp"):
        if (p / test).exists():
            source = (p / test).read_text()
            sources = [test]
            if 'include "solution.cpp"' not in source:
                sources.append("solution.cpp")
            rc = run(["g++", "-std=c++17", "-O2", "-Wall", "-Wextra",
                      *sources, "-o", ".practice_tests"], p)
            return rc or run([str(p / ".practice_tests")], p)

    if (p / "tests.c").exists():
        rc = run(["cc", "-std=c11", "-O2", "-Wall", "-Wextra",
                  "tests.c", "-o", ".practice_tests"], p)
        return rc or run([str(p / ".practice_tests")], p)

    if (p / "tests.js").exists():
        return run(["node", "tests.js"], p)

    print("Could not detect a supported test harness.", file=sys.stderr)
    return 2


if __name__ == "__main__":
    raise SystemExit(main())
