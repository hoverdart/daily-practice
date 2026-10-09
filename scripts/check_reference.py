#!/usr/bin/env python3
"""Check all reference solutions for a generated day, including legacy layouts."""
from __future__ import annotations
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RUNNER = ROOT / 'scripts' / 'run_problem.py'
LANGS = {
    'solution.py': ['optimal.py'],
    'Solution.java': ['Optimal.java', 'Solution.java'],
    'solution.cpp': ['optimal.cpp', 'solution.cpp'],
    'solution.c': ['optimal.c'],
    'solution.js': ['optimal.js'],
}

def check(folder):
    for starter, refs in LANGS.items():
        if not (folder / starter).exists():
            continue
        reference = next((folder / 'reference' / name for name in refs if (folder / 'reference' / name).exists()), None)
        if reference is None:
            return False
        with tempfile.TemporaryDirectory() as tmp:
            dst = Path(tmp) / folder.name
            shutil.copytree(folder, dst)
            shutil.copy2(reference, dst / starter)
            return subprocess.run([sys.executable, str(RUNNER), str(dst)]).returncode == 0
    return False

def main():
    if len(sys.argv) != 2:
        return 2
    day = Path(sys.argv[1]).resolve()
    ok = day.is_dir()
    for difficulty in ('easy', 'medium', 'hard'):
        direct = day / difficulty
        matches = [direct] if direct.is_dir() else list(day.glob(difficulty + '-*'))
        if len(matches) != 1:
            print('Missing or ambiguous difficulty:', difficulty)
            ok = False
            continue
        print('Checking', matches[0], flush=True)
        if not check(matches[0]):
            ok = False
    return 0 if ok else 1

if __name__ == '__main__':
    raise SystemExit(main())
