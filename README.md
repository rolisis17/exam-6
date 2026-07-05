# Exam 06 Practice

Practice repository for 42 Exam Rank 06 style C exercises. The files capture repeated attempts, variations, and speed practice around low-level C problem solving.

The purpose is not to present one polished application. It is a training log for getting faster and more confident with exam constraints.

## What it demonstrates

- C programming under time pressure
- Small-program structure without external dependencies
- Repeated implementation practice
- Debugging through many variations of the same idea
- Comfort with sockets, file descriptors, and process-oriented C patterns

## Repository structure

```text
exam.c
main.c
pract0.c ... pract23.c
```

The `pract*.c` files are individual practice attempts.

## Build

Compile the file you want to test:

```bash
cc -Wall -Wextra -Werror main.c -o exam_practice
./exam_practice
```

Or target a practice file directly:

```bash
cc -Wall -Wextra -Werror pract12.c -o pract12
./pract12
```

## Technical highlights

- Keeps practice attempts separate instead of hiding the learning process
- Uses direct compiler commands so each file can be tested quickly
- Reflects the real rhythm of exam preparation: repeat, compare, simplify, and remember

## Skills demonstrated

- C fundamentals
- Fast debugging
- Exam preparation discipline
- Low-level problem decomposition
- Writing small programs from memory

## Notes

This repo is useful as evidence of practice and persistence. It shows the repetitions behind becoming comfortable with constrained C exams.
