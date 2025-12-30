# C++ Generic Data Structures Library

![Language](https://img.shields.io/badge/language-C++-00599C.svg)
![Type](https://img.shields.io/badge/type-University%20Project-orange)

This repository contains a C++ library implementing fundamental data structures,
developed as a final project for the course **Laboratory of Algorithms & Data Structures**
(B.Sc. in Computer Science) at the **University of Naples Federico II**.

Final evaluation: **28/30**.

## Overview

The project focuses on the implementation of generic dynamic data structures using
template programming and interface-based design.  
All components strictly follow the class hierarchy, interfaces, and directory
structure provided by the official course template.

The objective of the project is to deliver correct, reusable, and well-structured
implementations of common abstract data types.

## Implemented Data Structures

- **Vector**: dynamic array with automatic resizing
- **List**: linked list
- **Ordered Set**:
  - vector-based implementation
  - list-based implementation
- **Heap**: implicit binary heap using vector representation
- **Priority Queue**: heap-based priority queue

All data structures support traversal, mapping, and folding operations as required
by the specifications.

## Design and Architecture

The library is organized around a hierarchy of abstract base classes defining
shared container behavior, including:

- size and emptiness checks
- traversal and accumulation (`Traverse` / `Fold`)
- functional-style transformations (`Map`)
- dictionary and ordered-dictionary operations

Multiple concrete implementations are provided for the same abstract data types
to highlight different design trade-offs.

## Project Structure

- `container/`: abstract interfaces (`Container`, `Traversable`, `Mappable`, `Dictionary`, ...)
- `vector/`, `list/`: linear data structures
- `set/`: ordered set implementations
- `heap/`, `pq/`: heap and priority queue
- `zlasdtest/`: official test suite provided by the course author
- `zmytest/`: additional custom tests

## Build and Execution

The project can be compiled using the provided Makefile:

```bash
make
./main
```

## Testing

Correctness has been verified using:

- the official test suite provided with the course
- additional custom tests covering edge cases such as:
  - empty containers
  - single-element structures
  - boundary insertion and removal scenarios

## Academic Context

- Course: Laboratory of Algorithms & Data Structures
- Language: C++
- Institution: University of Naples Federico II
- Project type: group assignment

This repository contains the source code submitted for the final course evaluation.