#include <math.h>
#include <stdio.h>
#include "_dop.h"

char out_format[] = "x =%5.2f  y =%18.10e %18.10e  nstep =%4d\n";


dopri_fcn fvpol;
void fvpol(int n, double x, double *y, double *f)
{
    const double eps = 1.0E-3; // rpar

    f[0] = y[1];
    f[1] = ((1.0 - y[0]*y[0]) * y[1] - y[0]) / eps;
}

// SUBROUTINE SOLOUT (NR,XOLD,X,Y,N, CON,ICOMP,ND, RPAR,IPAR,IRTRN)
dopri_solout solout;
int solout(
    int nr, double xold, double x,
    double *y, int n, double *con, int *icomp, int nd)
{
    int irtrn = 1; // good;  < 0 for error
    double xout; 

    if (nr == 1)
    { 
        printf(out_format, x, y[0], y[1], nr-1);
        xout = x + 0.1;
    }
    else 
    {
        while (x >= xout)
        {
            /* double contd8(
                const int ii, double x,
                double* con, int* icomp, int nd, double* xold, double h) */
            // TODO: need `h`
            printf(out_format,
                xout,
                contd8(0, xout, con, icomp, nd, &xold, h),
                contd8(1, xout, con, icomp, nd, &xold, h),
                nr-1);
            xout += 0.1;
        }
    }

    return irtrn;
}

int main()
{
    const int NDGL = 2, NRD = 2;
    const int L_WORK = 11*NDGL + 8*NRD + 21,
        L_IWORK = NRD + 21;

    double y[NDGL], work[L_WORK];
    int iwork[L_IWORK];  // TODO: use long int

    int iout, itoler;
    double x, xend, atoler, rtoler;
    double rpar;
    int ipar=0, ierr=0;

    /* DIMENSION OF THE SYSTEM */
    // NDGL = 2
    rpar = 1e-3;
    /* OUTPUT ROUTINE (AND DENSE OUTPUT) IS USED DURING INTEGRATION */
    iout = 2;
    /* INITIAL VALUES */
    x = 0.0;
    y[0] = 2.0;
    y[1] = 0.0;
    /* ENDPOINT OF INTEGRATION */
    xend = 2.0;
    /* REQUIRED (RELATIVE) TOLERANCE */
    itoler = 0;
    rtoler = 1.0e-9;
    atoler = rtoler;
    /* DEFAULT VALUES FOR PARAMETERS */
    for (int i=0; i < 10; i++)
    {
        iwork[i] = 0;
    }
    iwork[4-1] = 1;
    iwork[5-1] = NDGL;

    /* CALL OF THE SUBROUTINE DOPRI8 */
    /*
    void dopri853(
        const int n, dopri_fcn* fcn, double x, double* y, double* xend, double* rtol,
        double* atol, const int itol, dopri_solout* solout, const int iout,
        double* work, int* iwork, double* rpar, int* ipar, int* ierr);
    */
    dopri853(
        // n, fcn,   x, y[], *xend, *rtol
        NDGL, fvpol, x, y, &xend, &rtoler,
        // *atol, itol,   solout, iout
        &atoler, itoler, solout, iout,
        // work[], iwork[], *rpar, *ipar, *ierr
        work, iwork, &rpar, &ipar, &ierr);

    /* PRINT FINAL SOLUTION */
    printf(out_format, xend, y[0], y[1], -1);
    /* PRINT STATISTICS */
    printf("\trtol=%g   fcn=%d   step=%d   accpt=%d   rejct=%d\r\n",
        rtoler, iwork[17-1], iwork[18-1], iwork[19-1], iwork[20-1]);

    return 0;
}
