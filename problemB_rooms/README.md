# Problem B — Minimum Meeting Rooms

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
m
s1 e1
s2 e2
...
sm em

Output:
rooms   (minimum number of rooms needed)
```

Note: a meeting ending at time t and another starting at time t do NOT
overlap (the room can be reused).

## Example
```
$ ./main
3
0 30
5 10
15 20
2
```

## Tests
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

- `test1`: example from the statement → 2
- `test2`: back-to-back meetings, no overlap → 1
- `test3`: all meetings overlap → 4


## Approach
Greedy sweep-line over sorted start/end events. See `main.cpp` header
comment and `report.md` for pseudocode, greedy-choice-property argument
and complexity analysis (O(m log m) time, O(m) space).
