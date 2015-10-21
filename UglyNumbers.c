/*
 https://www.codeeval.com/open_challenges/42/
 
 
UglyNumbers.c : Defines the entry point for the console application.
 
 
 
 Once upon a time in a strange situation, people called a number ugly if it was divisible by any of the one-digit primes (2, 3, 5 or 7). Thus, 14 is ugly, but 13 is fine. 39 is ugly, but 121 is not. Note that 0 is ugly. Also note that negative numbers can also be ugly: -14 and -39 are examples of such numbers.
 
 One day on your free time, you are gazing at a string of digits, something like:
 
 123456
 
 You are amused by how many possibilities there are if you are allowed to insert plus or minus signs between the digits. For example you can make:
 
 1 + 234 - 5 + 6 = 236
 
 which is ugly. Or
 
 123 + 4 - 56 = 71
 
 which is not ugly.
 
 It is easy to count the number of different ways you can play with the digits: Between each two adjacent digits you may choose put a plus sign, a minus sign, or nothing. Therefore, if you start with D digits there are 3^(D-1) expressions you can make. Note that it is fine to have leading zeros for a number. If the string is '01023', then '01023', '0+1-02+3' and '01-023' are legal expressions.
 
 Your task is simple: Among the 3^(D-1) expressions, count how many of them evaluate to an ugly number.
 Input sample:
 
 Your program should accept as its first argument a path to a filename. Each line in this file is one test case. Each test case will be a single line containing a non-empty string of decimal digits. The string in each test case will be non-empty and will contain only characters '0' through '9'. Each string is no more than 13 characters long. E.g.
 
 1
 9
 011
 12345
 
 Output sample:
 
 Print out the number of expressions that evaluate to an ugly number for each test case, each one on a new line. E.g.
 
 0
 1
 6
 64
 
 */

#include <stdio.h>
//#include <string.h>

static long long uglycount;
//static long long unuc;




// Simple workhorse function uses recursion to create the expressions that are possible with 3^^(n-1) possibilities
void recSearch(long long * presult, long long * pstack, char * digStr, char negflag)
{
//    printf("pr = %p, *pr = %lld, ps = %p, *ps = %lld, nf = %d str = %s\n",
//           presult, *presult, pstack, *pstack, negflag, digStr);
//    printf("res = %lld, stk = %lld, nf = %d str = %s",
//            *presult, *pstack, negflag, digStr);
    
    // if we're done building the string -- check ugly
    if(*digStr == '\n'){
        long long result = *presult + (negflag ? -(*pstack) : *pstack);
        if(
            //  == % 2 ?
            ((result & 0x01) == 0) ||
            (result % 3 == 0) ||
            (result % 5 == 0) ||
            (result % 7 == 0)
          ) {
            
            uglycount++;
        }
    }
    // otherwise continue building the string with insertions of -, + or nothing (which means x10)
    else {
        // stack = stack * 10 + ((long long) (*digStr - '0'));
        long long stack = (*pstack << 1);
        stack += (stack << 2) + ((long long)(*digStr & 0x0f) );
        recSearch(presult, &stack, digStr+1, negflag);
        
        long long resultx = *presult + (negflag ? -*pstack : *pstack);
        long long stackx = (long long) (digStr[0] & 0x0f);
//        printf("%c %lld\n", negflag ? '-' : '+', resultx);
        recSearch(&resultx, &stackx, digStr+1, 1);
        recSearch(&resultx, &stackx, digStr+1, 0);
    }
}


int main(int argc, const char * argv[])
{
    
    FILE *file = fopen(argv[1], "r");
    char digitsStr[1024];
    long long stack;
    long long result;

    
    while(fgets(digitsStr, 1024, file)) {
        // if desired ... insert check that the input string length <= 13 and is only number chars
        // set ugly count to zero
        uglycount = 0;
        result = 0;
        stack = (long long) (digitsStr[0] & 0x0f);
//       printf("INPUT: %s", digitsStr);
        recSearch( &result, &stack, &digitsStr[1], 0);
//        digitsStr[strlen(digitsStr) - 1] = '\0';
//        printf ("Input Value (%s) is %lld time(s) ugly.\n",digitsStr, uglycount);
        printf("%lld\n", uglycount);
    }
    
    return 0;
}

    
