#include <stdio.h>
#include "mathlib.h"
#include <math.h>

#define EPSILON 1e-10

double absolute(double x)
{
return x < 0 ? -x : x;
}

double Sqrt(double x) {
    double value = 1.0;
    for (double guess = 0.0; absolute(value - guess) > EPSILON; value = (value + x / value) / 2.0) {
        guess = value;
    }
    return value;
}

static double Exp(double x) {
double t = 1.0;
double y = 1.0;
for (double k = 1.0; t > EPSILON; k += 1.0) {
t *= x / k;
y += t;
}
return y;
}


double my_sin(double x)
{
	double previous = x;
	double new = x;
	
	for (double starting = 1.0; absolute(previous) >= EPSILON; starting += 1.0) {

        		previous = -1 * previous * (x * x);
        		previous = previous / ( 2 * starting ) / ( 2 * starting + 1 ) ;
		
		new += previous;
		
	}
	return new;
}

double my_cos(double x)
{
	double previous = 1;
	double new = 1;
	
	for (double starting = 1.0; absolute(previous) >= EPSILON; starting += 1.0) {

        		previous = -1 * previous * (x * x);
        		previous = previous / ( 2 * starting ) / ( 2 * starting - 1 ) ;
		
		new += previous;
	
	}
	return new;
}

double my_arcsin(double x)
{
	double previous = x;
	double new = x + 1;
	double sin_value = x;
	
	do
	{
	new = previous;
	sin_value = my_sin(previous) - x; 
        previous = previous - sin_value / my_cos(previous);
        }		
	while (absolute(new - previous) >= EPSILON);
			
			
	return previous;
}

double my_arccos(double x)
{	
	double new = x;
	
	new = M_PI / 2 - my_arcsin(x);
	
	return new;
}

double my_arctan(double x)
{
	double previous = x;
	double square_value = x;
	double square = x;
	
	square = x * x + 1;
	square_value = Sqrt(square);
	previous = my_arccos(1 / square_value);
	
	return previous;
}

double my_log(double x)
{
	double previous = 1.0;
	double before = x;
	double after = x;
	double new = x;
	
	do
	{
	before = x - Exp(previous);
	after = before / Exp(previous);
	new = previous + after;
	previous = new;
	}
	while ((Exp(new) - x) >= EPSILON);
	
	
	return previous;
}
