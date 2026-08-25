# Algebraic Scientific Computing in Modern C++

This repository contains implementations and experiments in **numerical analysis and scientific computing using modern C++**, with an additional focus on understanding the **algebraic structures underlying numerical algorithms**.

The project explores both the practical implementation of classical numerical methods and the abstraction of those methods through **generic programming, abstract algebra, and mathematical concepts**.

The main idea is to study not only *how* an algorithm works, but also:

> **What mathematical structure does the algorithm actually require?**

This perspective is inspired by the tradition of **generic programming**, particularly the work of Alexander Stepanov, where algorithms are expressed in terms of the algebraic and computational properties they require..

## Topics

The repository covers a variety of areas in numerical and scientific computing, including:

- **Linear Algebra** — Algorithms for matrix and vector operations, linear systems, eigenvalue problems, and related structures.
- **Differential Equations** — Numerical techniques for solving ordinary and partial differential equations.
- **Numerical Integration and Differentiation** — Methods for approximating integrals, derivatives, and related analytical operations.
- **Optimization** — Gradient-based methods, Newton-type methods, linear programming, regression, and other optimization techniques.
- **Interpolation and Approximation** — Methods for estimating and approximating functions from discrete data.
- **Numerical Solvers** — Iterative methods for linear and nonlinear equations.
- **Series and Polynomials** — Computational methods involving polynomial representations, infinite series, and approximations.

## Algebraic Perspective

A central direction of the project is to connect these numerical algorithms with the **mathematical structures in which they naturally operate**.

Instead of treating an algorithm as something that operates on a specific type such as `double`, `std::vector`, or a particular matrix implementation, the goal is to identify the algebraic properties that are actually required.

```text
Classical Numerical Algorithm
            ↓
Mathematical Analysis
            ↓
Identify Algebraic Requirements
            ↓
Generic C++ Abstraction
            ↓
Concepts and Constraints
            ↓
Reusable Scientific Algorithm
```
