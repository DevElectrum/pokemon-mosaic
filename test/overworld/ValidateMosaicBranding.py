#!/usr/bin/env python3
from pathlib import Path
import subprocess
root = Path(__file__).resolve().parents[2]
subprocess.run(["python3", "tools/mosaic_rebrand_pass2.py", "--check"], cwd=root, check=True)
assert (root / "docs/SAVE_FILENAME_MIGRATION.md").is_file()
assert (root / "docs/MOSAIC_FIELD_GUIDE.md").is_file()
print("PASS: Mosaic naming and safe save-copy guide")
