# Problem C — Budgeted Study Plan (0/1 Knapsack)

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
n T
t1 v1
t2 v2
...
tn vn

Output:
best   (maximum total value achievable within time budget T)
```

## Example
```
$ ./main
3 10
3 4
4 5
7 10
14
```

## Tests
```bash
for i in 1 2 3 4; do
  echo "test$i:"; ./main < tests/test${i}_in.txt
  echo "expected:"; cat tests/test${i}_out.txt
done
```
Run all provided tests on Windows PowerShell:

for ($i = 1; $i -le 4; $i++) {
    Write-Host "test$i:"
    Get-Content "tests\test${i}_in.txt" | .\main.exe
    Write-Host "expected:"
    Get-Content "tests\test${i}_out.txt"
}


- `test1`: example from the statement → 14
- `test2`: nothing fits (all times > T) → 0
- `test3`: multiple choices, must pick the best combo → 11
- `test4`: tight budget, everything fits exactly → 100

## Approach
Bottom-up dynamic programming with a 1-D rolling array, iterating the
capacity dimension downward per item to enforce the 0/1 (at most once)
constraint. See `main.cpp` header comment and `report.md` for pseudocode,
DP-invariant correctness argument and complexity analysis
(O(n·T) time, O(T) space).
