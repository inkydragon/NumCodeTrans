# Rewrite DOP F77 Code

```c
// SPDX-License-Identifier: BSD-3-Clause
```

- [ENH:MAINT:integrate: Rewrite DOP F77 code in C #21683](https://github.com/scipy/scipy/pull/21683)


## Test

```sh
# f77 test driver
cd f77/
gfortran -std=legacy -g -o fdop853.exe dr_dop853.f  && ./fdop853.exe 
gfortran -std=legacy -g -o fdopri5.exe dr_dopri5.f  && ./fdopri5.exe

cd cprog/
gcc -g -o dop853.exe dop853.c vanderp.c -lm && ./dop853.exe 
gcc -g -o dopri5.exe dopri5.c aren.c -lm && ./dopri5.exe 
gcc -g -o retard.exe retard.c ret.c -lm && ./retard.exe

# dop.c
gcc -g -o dop853.exe _dop.c test_dop853.c -lm && ./dop853.exe 
```

## Ref

- [Fortran and Matlab Codes/Nonstiff Differential Equations](http://www.unige.ch/~hairer/software.html)
    - [cprog: C-versions of DOPRI5, DOP853 and RETARD](http://www.unige.ch/~hairer/prog/nonstiff/cprog.tar)

repo:
- Fortran@BSD-3 [jacobwilliams/dop853: Modern Fortran Edition of Hairer's DOP853 ODE Solver. An explicit Runge-Kutta method of order 8(5,3) for problems y'=f(x,y); with dense output of order 7](https://github.com/jacobwilliams/dop853)
- Rust@BSD-3 [srenevey/ode-solvers: Numerical methods to solve ordinary differential equations in Rust.](https://github.com/srenevey/ode-solvers)
