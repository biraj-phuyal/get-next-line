# Get-next-line

Line-by-line file/stream reader for the 42 curriculum. `get-next-line` returns the next line (including the trailing `\n` if present) from a given file descriptor each time it is called.

## Requirements
- **C compiler:** `cc`
- **Flags:** `-Wall -Wextra -Werror`
- **Build:** `make` (Norminette-compliant)
- **Macro:** `BUFFER_SIZE` (controls read chunk size; may be overridden at compile time)

## Usage
```bash
cc -Wall -Wextra -Werror -DBUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c && ./a.out
```

## API
```c
char *get_next_line(int fd);
```
- **Returns:** a heap-allocated string containing the next line (including `\n` if present), or `NULL` on EOF or error.
- The caller **must `free`** the returned pointer when non-`NULL`.

## Behavior & Constraints
- Reads from `fd` in chunks of `BUFFER_SIZE` using `read(2)` and maintains a **static stash** between calls to assemble lines.
- Handles **partial lines**, **long lines**, and **end-of-file** correctly.
- A **single trailing line without `\n`** is returned as-is on the final call.
- On **error** (invalid `fd`, `read` error, allocation failure), returns `NULL` and clears internal storage for that `fd` if implemented.

## Bonus (multi-FD)
- The bonus version supports **multiple file descriptors simultaneously** (e.g., interleaved calls on different `fd`s) by keeping independent stashes (commonly via an array or map keyed by `fd`).

## Project Structure
```
get_next_line/
├─ bonus/
│  ├─ get_next_line_bonus.h
│  ├─ get_next_line_bonus.c
│  └─ get_next_line_utils_bonus.c
├─ mandatory/
│  ├─ get_next_line.h
│  ├─ get_next_line.c
│  └─ get_next_line_utils.c
└─ README.md
```

## Edge Cases to Test
- Empty file; file with only `\n`s
- Very long lines (> `BUFFER_SIZE`); `BUFFER_SIZE` = 1
- Final line without `\n`
- Interleaved reads across multiple `fd`s (bonus)
- Invalid `fd` / `read` error handling

## Notes
- No global state beyond allowed **static** storage inside the function/module.
- Memory allocations are checked; stash is trimmed aggressively to avoid leaks.
- The implementation avoids undefined behavior and follows the 42 Norm.