# European Option Pricing and Delta Hedging using the Binomial Model

## Overview

This project implements the pricing and hedging of European options using the **Cox–Ross–Rubinstein (CRR) Binomial Model** in C++.

The program allows users to:

* Price European call and put options
* Construct the complete option price tree using backward induction
* Compute replicating portfolios through delta hedging
* Display stock and bond positions at every node of the binomial tree
* Analyse portfolios consisting of multiple options

The implementation demonstrates several fundamental concepts from computational finance and derivative pricing.

---

## Features

* Binomial asset price model
* Risk-neutral valuation
* European call option pricing
* European put option pricing
* Backward induction pricing algorithm
* Replicating portfolio construction
* Delta hedging
* Bond position calculation
* Full lattice (tree) visualization
* Portfolio analysis for multiple options

---

## Project Structure

```
Code1/
│
├── main.cpp               # Program entry point
├── BinModel.h/.cpp        # Binomial stock price model
├── EurOption.h/.cpp       # European option classes and pricing algorithms
├── BinLattice.h           # Binomial tree data structure
├── EurOptionsDeltaHedge.cbp
└── EurOptionsDeltaHedge.layout
```

---

## Mathematical Model

The project is based on the **Cox–Ross–Rubinstein (CRR) Binomial Model**, where:

* Initial stock price: **S₀**
* Up factor: **U**
* Down factor: **D**
* Risk-free growth factor: **R**

The risk-neutral probability is

[
p=\frac{R-D}{U-D}
]

The European option price is computed by

* the closed-form CRR formula, and
* backward induction on the binomial tree.

---

## Implemented Algorithms

### 1. Risk-Neutral Pricing

Computes option prices using the risk-neutral probability.

### 2. Backward Induction

Constructs the entire option price lattice beginning from terminal payoffs and recursively discounting values to time zero.

### 3. Replicating Portfolio

Calculates the portfolio that replicates the option payoff.

For each node, the program computes:

* Stock position (Δ)
* Bond position

using delta hedging principles.

### 4. Portfolio Analysis

The program also allows multiple options to be combined into a single portfolio and computes the aggregate stock and bond positions at a chosen node.

---

## User Input

The program requests:

### Binomial Model Parameters

* Initial stock price (S₀)
* Up factor (U)
* Down factor (D)
* Risk-free growth factor (R)

### Option Parameters

* Number of time steps
* Strike price
* Option type (Call or Put)

### Portfolio Parameters

* Number of options
* Node at which to analyse the portfolio

---

## Program Output

The program displays:

* Option price
* Risk-neutral pricing results
* Complete option price tree
* Replicating stock positions
* Replicating bond positions
* Delta hedging strategy
* Portfolio stock and bond holdings

---

## Compilation

### Code::Blocks

Open

```
EurOptionsDeltaHedge.cbp
```

and build the project.

### Using g++

```bash
g++ *.cpp -o OptionPricing
```

Run with

```bash
./OptionPricing
```

(On Windows)

```bash
OptionPricing.exe
```

---

## Concepts Demonstrated

* Object-Oriented Programming
* Class inheritance
* Dynamic binomial lattices
* Financial derivatives
* Risk-neutral valuation
* Backward induction
* Delta hedging
* Replicating portfolios
* Numerical methods in finance

---

## Possible Improvements

* American option pricing
* Barrier options
* Asian options
* Dividend-paying assets
* Graphical visualization of lattices
* File input/output
* Monte Carlo pricing
* Black–Scholes analytical pricing comparison
* Unit testing

---

## License

This project is intended for educational purposes.


