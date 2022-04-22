
# EmiROOT: Evolutionary minimizer for ROOT <img src="extra/EmiROOTLogo.png" align="right" width="200" />

Classical minimization methods, like *gradient descent* or *quasi-Newton techniques*,have been proved to struggle in dealing with optimization problems with a high-dimensional search space or subject to complex nonlinear constraints. In last decade, the interest on metaheuristic nature inspired algorithms has been growing steadily, due to their flexibility and effectiveness. EmiROOT implements several methauristic algorithms for optimization problems:

* *Artificial Bee Colony Algorithm*;
* *Bat Algorithm*;
* *Cuckoo Search*;
* *Genetic Algorithm*;
* *Gravitationl Search Algorithm*;
* *Grey Wolf Optimization*;
* *Harmony Search*;
* *Improved Harmony Search*;
* *Moth-flame Optimization*;
* *Particle Swarm Optimization*;
* *Simulated Annealing*;
* *Whale Optimization Algorithm*. 

EmiROOT can be used not only for unconstrained problems, but also for problems subjected to inequality constraints and for integer or mixed-integer problems. EmiROOT is based on EmiR, a package for R deveoped by the same authors.


## How to cite

If you use EmiROOT or EmiR, please cite the following work:

```
Pagano, Davide, e Lorenzo Sostero. «EmiR: Evolutionary Minimization for R». SoftwareX 18, 101083 (2022). 
https://doi.org/10.1016/j.softx.2022.101083.
```


## Installation

```
git clone https://github.com/dr4kan/EmiROOT.git
cd EmiROOT 
mkdir build
cd build
cmake ..
make
make install
```


## Example of usage

```

```
