#include <stdio.h>
#include <stdlib.h>

int main()
{
    /*  equality          ==
  less than         <
  Greater than      >
  <=                <=
  >=                >=int a [5];
int i;

for (i=0; i<5; i++)
    a[i] = i;
for (i= 0; i<5; i++)
    printf("a[%d] = %d\n" , i, a[i]);
  inequality        !=
  and               &&
  or                ||
  not               !
  */
    int age;
    int x;
    int y = 0;
    int a =0;  Initialize variables first
    int b;
    int c;
    c = 0;
    int temp;

    printf("Enter your age: ");
    scanf("%d", &age); /* %d means int type, stored in age with & */
    if(age < 100) {
    printf("Your age is %d", age, "You're pretty young!\n"); /* "\n" means new line */
    }
    else {
        printf("Youre old!");
    }
    for (x=0; x < 10; x++){
        printf("%d\n", x);
    }
    while(a< 10) {
        printf("%d\n", a);    /* both for/else and while statments are legit the same as java */
        a++;
    }
    do {
            printf("This is a while loop!\n");
       }while( y != 0);

       printf("Enter a value:");
       scanf("%d", &b);
       if (b < 0) {
        printf("The number is negative.\n");
       } else {
           printf("The number is positive\n");

       }

       printf("Enter a temperature:");
       scanf("%d", &temp);

       while (temp <= 100){
        printf("%4d degrees F = %4d degrees C\n",
            temp, (temp - 32) * 5 / 9);
            temp = temp + 10;
       }

       int d [5];
int i;

for (i=0; i<5; i++)
    d[i] = i;
for (i= 0; i<5; i++)
    printf("d[%d] = %d\n" , i, d[i]);



    getchar(); /* makes it so you have to press enter to finish program, can see what is done */
    return 0;
}
