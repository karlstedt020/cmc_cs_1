#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>

extern double f(double x);
extern double g(double x);
extern double t(double x);

double test1(double x) {
    return x - 5.;
}

double test2(double x) {
    return 1. / x;
}

double test3(double x) {
    return x * 4.;
}

double F(double (*function1)(double), double (*function2)(double), double x) {
    return function1(x) - function2(x);
}

double trapeze(double (*function)(double), double a, double b, int n, double* arr_x, double* arr_y) {
    double ans = 0.;
    //printf("===============\n");
    for (int i = 0; i < n - 1; ++i) {
        ans += ((arr_x[i + 1] - arr_x[i]) * fabs(arr_y[i + 1] + arr_y[i]) / 2.);
    }
    //printf("%lf\n", ans);
    return ans;
}

double integral(double (*function)(double), double a, double b, double eps) {
    if (b < a) {
        double c = b;
        b = a;
        a = c;
    }
    int n = 2;
    double *arr_x = malloc(2 * sizeof(double));
    double *arr_y = malloc(2 * sizeof(double));
    arr_x[0] = a;
    arr_y[0] = function(a);
    arr_x[1] = b;
    arr_y[1] = function(b);
    double sq1 = trapeze(function, a, b, n, arr_x, arr_y);
    double *help_x = malloc((n * 2 - 1) * sizeof(double));
    double *help_y = malloc((n * 2 - 1) * sizeof(double));
    int j = 0;
    for (int i = 0; i < n - 1; ++i) {
        help_x[j] = arr_x[i];
        help_y[j] = arr_y[i];
        ++j;
        help_x[j] = (arr_x[i] + arr_x[i + 1]) / 2.;
        help_y[j] = function(help_x[j]);
        ++j;
    }
    help_x[j] = b;
    help_y[j] = arr_y[n - 1];
    free(arr_x);
    free(arr_y);
    arr_x = help_x;
    arr_y = help_y;
    double sq2 = trapeze(function, a, b, n * 2 - 1, arr_x, arr_y);
    while (fabs(sq1 - sq2) > eps) {
        sq1 = sq2;
        n = n * 2 - 1;
        help_x = malloc((n * 2 - 1) * sizeof(double));
        help_y = malloc((n * 2 - 1) * sizeof(double));
        j = 0;
        for (int i = 0; i < n - 1; ++i) {
            help_x[j] = arr_x[i];
            help_y[j] = arr_y[i];
            ++j;
            help_x[j] = (arr_x[i] + arr_x[i + 1]) / 2.;
            help_y[j] = function(help_x[j]);
            ++j;
        }
        help_x[j] = b;
        help_y[j] = arr_y[n - 1];
        free(arr_x);
        free(arr_y);
        arr_x = help_x;
        arr_y = help_y;
        sq2 = trapeze(function, a, b, n * 2 - 1, arr_x, arr_y);

    }
    free(arr_x);
    free(arr_y);
    return sq2;
}

int count = 0;

double root(double (*function1)(double), double (*function2)(double), double a, double b, double eps) {
    double c;
    while (1) {
        double k = (F(function1, function2, b) - F(function1, function2, a)) / (b - a);
        double l = F(function1, function2, b) - b * k;
        c = -l / k;
        if (F(function1, function2, a) < 0) {
            if (F(function1, function2, c) < 0) {
                a = c;
                ++count;
                if (F(function1, function2, c + eps) > 0)
                    break;
            }
            else {
                b = c;
                ++count;
                if (F(function1, function2, c - eps) < 0)
                    break;
            }
        }
        else {
            if (F(function1, function2, c) < 0) {
                b = c;
                ++count;
                if (F(function1, function2, c - eps) > 0)
                    break;
            }
            else {
                a = c;
                ++count;
                if (F(function1, function2, c + eps) < 0)
                    break;
            }
        }
    }
    return c;
}
// help - flags
// count
//roots
// tests
const double EPS = 1e-6;

int main(int argc, char** argv) {
    int i;
    int TESTFLAG = 0;
    int COUNTFLAG = 0;
    int ROOTFLAG = 0;
    int HELPFLAG = 0;
    for (i=1; i<argc; i++) {
        if (strcmp(argv[i], "-help") == 0) {
            HELPFLAG = 1;
        }
        if (strcmp(argv[i], "-root") == 0) {
            ROOTFLAG = 1;
        }
        if (strcmp(argv[i], "-test") == 0) {
            TESTFLAG = 1;
        }
        if (strcmp(argv[i], "-count") == 0) {
            COUNTFLAG = 1;
        }
        if (HELPFLAG) {
            printf("-help\n");
            printf("-root\n");
            printf("-count\n");
            printf("-test\n");
        }
        if (COUNTFLAG) {
            double x = root(g, t, -5., -0.001, EPS);
            printf("count: %d\n", count);
        }
        if (ROOTFLAG) {
            printf("f and g: %lf\n", root(f, g, 0., 5., EPS));
            printf("f and t: %lf\n", root(f, t, -5, -0.001, EPS));
            printf("g and t: %lf\n", root(g, t, -5., -0.001, EPS));
        }
        if (TESTFLAG) {
            double x = root(test2, test3, 0.001, 2, EPS);
            double y = root(test1, test2, 1, 10, EPS);
            double z = root(test1, test3, -100, 100, EPS);
            printf("f and g: %lf\n", y);
            printf("f and t: %lf\n", z);
            printf("g and t: %lf\n", x);
            printf("integral f: %lf\n", integral(test1, 1, 2, EPS));
            printf("integral g: %lf\n", integral(test2, 1, 2, EPS));
            printf("integral t: %lf\n", integral(test3, -1, 1, EPS));
        }
        TESTFLAG = 0;
        COUNTFLAG = 0;
        HELPFLAG = 0;
        ROOTFLAG = 0;
    }
    double x = root(g, t, -5., -0.001, EPS);
    double y = root(f, g, 0., 5., EPS);
    double z = root(f, t, -5, -0.001, EPS);
    printf("%lf\n", integral(g, x, y, EPS) + integral(t, z, x, EPS) - integral(f, z, y, EPS));
    return 0;
}
