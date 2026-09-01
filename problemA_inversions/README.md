# Problem A — Inversion Counter

## Build
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o main
```

## Run
```bash
./main < input.txt
```
## Run

On Windows PowerShell:

```powershell
Get-Content tests\test1_in.txt | .\main.exe

## Input / Output format
```
Input:
n
a1 a2 ... an

Output:
inv   (number of inversions, printed as a single 64-bit integer)
```

## Example
```
$ ./main
5
2 4 1 3 5
3
```

## Tests
Run all provided tests:
```bash
for i in 1 2 3 ; do
  echo "test$i:"; ./main < tests/test${i}_in.txt
  echo "expected:"; cat tests/test${i}_out.txt
done
```

Run all provided tests on Windows PowerShell:

for ($i = 1; $i -le 3; $i++) {
    Write-Host "test$i:"
    Get-Content "tests\test${i}_in.txt" | .\main.exe
    Write-Host "expected:"
    Get-Content "tests\test${i}_out.txt"
}

- `test1`: example from the statement (`[2,4,1,3,5]` → 3)
- `test2`: already sorted (`[1,2,3,4,5]` → 0)
- `test3`: reverse sorted (`[4,3,2,1]` → 6)


## Approach
Divide & conquer via a modified merge sort. See `main.cpp` header comment
and `report.md` at the repo root for full details, pseudocode and
complexity analysis (O(n log n) time, O(n) space).
