#include <stdio.h>

#define PI 3.1416

// The function prototype is very important
float areaC(float radius);

int main() {   
   float area, radius;
   radius = 10;   
   area = areaC(radius);   
   printf("Area of circle with radius %f is %f \n", radius, area); 
}

float areaC(float radius)
{
    // If we did "radius = 0;" here, at main it wouldn't change its value
    return (PI *(radius * radius));
}
