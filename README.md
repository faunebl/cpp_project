# C++ Project for M2 203 - Faune Blanchard 

To run the project, please use:

```
g++ main.cpp pde.cpp utils.cpp matrix.cpp black_scholes.cpp -o pde_pricer -std=c++17
```

Results are already visible in the results folder, where you can see the convergence data as well as the convergence graph.

Important : if you want to replicate the results, you need gnuplot installed in order to see the graph.

If you want further debugging or checking of the intermediate values, uncomment the lines of code in pde.cpp