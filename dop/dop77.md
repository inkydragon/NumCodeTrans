# Rewrite DOP F77 Code

```c
// SPDX-License-Identifier: BSD-3-Clause
```

- [ENH:MAINT:integrate: Rewrite DOP F77 code in C #21683](https://github.com/scipy/scipy/pull/21683)


## Test

```sh
gfortran -std=legacy -g -o dop853.exe dr_dop853.f  && ./dop853.exe 
gfortran -std=legacy -g -o dopri5.exe dr_dopri5.f  && ./dopri5.exe

cd cprog/
gcc -g -o dop853.exe dop853.c vanderp.c -I. -lm && ./dop853.exe 
gcc -g -o dopri5.exe dopri5.c aren.c -I. -lm && ./dopri5.exe 
gcc -g -o retard.exe retard.c ret.c -I. -lm && ./retard.exe 
```

## Ref

- [Fortran and Matlab Codes/Nonstiff Differential Equations](http://www.unige.ch/~hairer/software.html)

repo:
- Fortran@BSD-3 [jacobwilliams/dop853: Modern Fortran Edition of Hairer's DOP853 ODE Solver. An explicit Runge-Kutta method of order 8(5,3) for problems y'=f(x,y); with dense output of order 7](https://github.com/jacobwilliams/dop853)
- Rust@BSD-3 [srenevey/ode-solvers: Numerical methods to solve ordinary differential equations in Rust.](https://github.com/srenevey/ode-solvers)
