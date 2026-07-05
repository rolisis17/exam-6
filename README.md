# Exam 06 Practice

C practice repository for 42 exam-style networking and process exercises.

## What it demonstrates

- Focused C practice under exam constraints
- Socket and process-oriented problem solving
- Iterative implementation through multiple practice files
- Low-level debugging and fast recall of C fundamentals

## Repository layout

```text
exam.c
main.c
pract0.c ... pract23.c
```

The `pract*.c` files capture repeated practice attempts and variations.

## Build

Compile the file you want to test:

```bash
cc -Wall -Wextra -Werror main.c -o exam_practice
./exam_practice
```

Or compile an individual practice file:

```bash
cc -Wall -Wextra -Werror pract12.c -o pract12
./pract12
```

## Skills practiced

- C under time pressure
- Sockets and file descriptors
- Error handling
- Process control
- Minimal, dependency-free programming
