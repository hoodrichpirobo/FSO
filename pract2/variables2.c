#include <stdio.h> 

int a = 0; /* global variable */ 
// This means each method has it's copy

// This function increases the value of global variable a by 1
void inc_a(void) {
    // int a;  This makes 'a' refer to local and not global, variable shadowing
    a++;
}

// This function returns the previous value 
// and saves the new value v
int former_value(int v) {
      int temp;     // This the same as temp = 0                                          --> temp = 0
      static int s; // Declare here static variable s, this is the same as s = 0          --> s = v

      temp = s;     // This won't do shit the first iteration, this is the same as 0 = 0  --> temp = v
      s = v;  ;     // s = v                                                              --> s = v
      return temp;  // return 0                                                           --> return v
}
// static gives memory to the variable, in Java it can only be static when it's global

int main()
{
	int b = 2; /* local variable */
	inc_a();
    former_value(b);	
    printf("a= %d, b= %d\n", a, b);       // a = 1, b = 2
	a++;
	b++;
	inc_a();
    b = former_value(b);
    printf("a= %d, b= %d \n", a, b);    // a = 3, b = 2 
}


