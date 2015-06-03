# include <stdio.h>
# include <stdlib.h> /* needed for error function */
# include <math.h>
double f(double theta, double omega, double t); /* function prototype */

int main()
{
	int i, n;
	double h, k1a, k1b, k2a, k2b, theta, omega, t;
	
	h = 0.1; /* set time step */
	n = 100; /* set number of steps */
	theta = 0; /* set initial angle */
	omega = 1; /* set initial angular velocity */
	t = 0; /* set initial time */
	/* Enter datafile name, and open it for writing */
	
	/* Implement the algorithm: */
	for (i = 1; i <= n; i++){
		k1a = h*omega;
		k1b = h*f(theta, omega, t);
		k2a = h*(omega + k1b);
		k2b = h*f(theta + k1a, omega + k1b, t + h);
		theta = theta + (k1a + k2a) / 2;
		omega = omega + (k1b + k2b) / 2;
		t = t + h;
		printf("%lf\t%lf\t%lf\n", t, theta, omega);
		printf( "%lf\t%lf\t%lf\n", t, theta, omega);
	}	
	return 0;
}

double f(double theta, double omega, double t) /* function header */
{
	double deriv;
	deriv = -theta;

	return deriv;
}
