#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
    return exp(x) + 2.;
}

double g(double x) {
    return 2. * (-x) + 8.;
}

double t(double x) {
    return -5. / x;
}

double F(double (*function1)(double), double (*function2)(double), double x) {
    return function1(x) - function2(x);
}

double trapeze(double (*function)(double), double a, double b, int n, double* arr_x, double* arr_y) {
    double ans = 0.;
    //printf("===============\n");
    for (int i = 0; i < n - 1; ++i) {
        //printf("%lf %lf: %lf\n", arr_y[i], arr_y[i + 1], (arr_x[i + 1] - arr_x[i]) * fabs(arr_y[i + 1] + arr_y[i]) / 2.);
        ans += ((arr_x[i + 1] - arr_x[i]) * fabs(arr_y[i + 1] + arr_y[i]) / 2.);
    }
    //printf("%lf\n", ans);
    return ans;
}

double integral(double (*function)(double), double a, double b, double eps) {
    int n = 2;
    double *arr_x = malloc(2 * sizeof(double));
    double *arr_y = malloc(2 * sizeof(double));
    arr_x[0] = a;
    arr_y[0] = function(a);
    arr_x[1] = b;
    arr_y[1] = function(b);
    double x = trapeze(function, a, b, n, arr_x, arr_y);
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
    double y = trapeze(function, a, b, n * 2 - 1, arr_x, arr_y);
    while (abs(x - y) > eps) {
        x = y;
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
        y = trapeze(function, a, b, n * 2 - 1, arr_x, arr_y);
    }
    return y;
}

double root(double (*function1)(double), double (*function2)(double), double a, double b, double eps) {
    double c;

    while (1) {
        double k = (F(function1, function2, b) - F(function1, function2, a)) / (b - a);
        double l = F(function1, function2, b) - b * k;
        c = -l / k;
        if (F(function1, function2, a) < 0) {
            //c = b - abs(b - a) / (F(function1, function2, b) - F(function1, function2, a)) * abs(F(function1, function2, b));
            if (F(function1, function2, c) < 0) {
                a = c;
                if (F(function1, function2, c + eps) > 0)
                    break;
            }
            else {
                b = c;
                if (F(function1, function2, c - eps) < 0)
                    break;
            }
        }
        else {
            //c = b - abs(b - a) / (F(function1, function2, a) - F(function1, function2, b)) * abs(F(function1, function2, b));
            //printf("%lf\n", function2(c));
            if (F(function1, function2, c) < 0) {
                b = c;
                if (F(function1, function2, c - eps) > 0)
                    break;
            }
            else {
                a = c;
                if (F(function1, function2, c + eps) < 0)
                    break;
            }
        }
    }
    return c;
}

int main(void) {
    double x = root(g, t, -5., -0.001, 0.001);
    double y = root(f, g, 0., 5., 0.001);
    double z = root(f, t, -5, -0.001, 0.001);
    printf("%lf", integral(g, x, y, 0.001) + integral(t, z, x, 0.001) - integral(f, z, y, 0.001));
    return 0;
}
