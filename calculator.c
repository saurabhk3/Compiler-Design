#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define SUCCESS 1
#define FAILURE -1

int j = 0;  // global index for array of stack, points to the top of the stack

struct Stack{
    int type;  // 0 -> operator, 1-> int, 2-> precedence
    int val;  // if type=1,it will contain the corresponding value
    char sym;   // if the type=0 or 2, it will contain the operator or precedence symbol respectively
}stack[100];

int getLastSymbol(int pos){  // returns the index of last symbol, to check the next precedence
    for(int k =pos-1;k>=0;k--){
        if(stack[k].type==0){
            return k;
        }
    }
    return FAILURE;
}

int evaluate(int a,int b,char op){  // evaluates an expression and returns the value
    if(op=='+')
        return (a+b);
    if(op=='-')
        return (a-b);
    if(op=='*')
        return (a*b);
    if(op=='/')
        return (a/b);
}

int convertToInt(int * t,int size){  // converts the character array to corresponding integer value
    int k = 0;
    int res = 0;
    for(int i=size-1;i>=0;i--){
        res += t[i]*pow(10,k);
        k++;
    }
    return res;
}
void yields(char current,char c){  // sub-routine for yields precedence over
    stack[j].type = 2;
    stack[j].sym = current;// push the precedence symbol
    j++;
    stack[j].type = 0;   
    stack[j].sym = c;  // push the corresponding operator
    j++;
}
void takes(char c){     // sub-routine for takes precedence over
     // pop until '<' + 1 more entry for operand
     int op1,op2,value;
     char operator;
    j--;
    if(stack[j].type==1){
        op1 = stack[j].val;
        j--;
    }
    if(stack[j].type==0){
        operator = stack[j].sym;
        j--;
    }
    if(stack[j].sym=='<'){
        j--;
    }
    op2 = stack[j].val;
    value = evaluate(op2,op1,operator);

    stack[j].val = value;  
    stack[j].type = 1;
    j++;
    int index = getLastSymbol(j);
    if(c=='$' && stack[index].sym != '$'){  // special case for $ i.e. end of input string
        if(j>1)  // if there is a single value, then it'll not call takes() again
            takes(c);
        
    }else if(c==')' && stack[index].sym=='('){  // special case for handling close parenthesis
        j--;
        while(stack[j].sym!='<'){
            j--;
        }

        // j-=2;
        stack[j].val = value;
        stack[j].type = 1;
        j++;

    }else if(c!='$'){
        stack[j].type =2;
        stack[j].sym = '<';
        j++;
        stack[j].type = 0;
        stack[j].sym = c;
        j++;
    }
}

int main(int argc,char** argv){
    char exp[40],stck[100];
    if(argc!=2){
        perror("Usage error: <a.out> <expression>");
        exit(1);
    }
    // copy the expression to variable and add $ in the end of expression
    int i=0,k=0;
    for(i=0;i<strlen(argv[1]);i++){
        exp[i] = argv[1][i];
    }
    exp[i++] = '$';
    exp[i] = '\0';

    // initialize the stack with $, at 0th index
    stack[j].type = 0;
    stack[j].sym = '$';
    j++;
    i = 0;
    int op1,op2,value=0;
    char c,current;
    int t[20];
    int isValid = 0;
    while(i<strlen(exp)){
        c = exp[i];
        if(isdigit(c)){
            k=0;
            t[k++] = c-'0';
            i++;   // to check whether the it's a single digit num or more
            char d = exp[i]; 
            while(isdigit(d)){
                t[k++] = d-'0';
                i++;
                d = exp[i];
            }
            i--;   // the last character read was non-digit (while loop exit)
            int v = convertToInt(t,k);
            stack[j].type = 1;
            stack[j].val = v;
            j++;
        }else{
            int indexOfLastSymbol = getLastSymbol(j);
            if(c=='+'){
                char y =exp[i+1];  // checking for valid input
                if(!isdigit(y) && y !='(' ){
                    perror("Invalid input\n");
                    exit(1);
                }

                if(stack[indexOfLastSymbol].sym=='$'){
                    current = '<';  // yields precedence
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='+'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='-'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='*'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='/'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym =='('){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym ==')'){
                    current = '>';  // takes precedence
                    takes(c);
                }
            }else if(c=='-'){
                 char y =exp[i+1]; 
                if(!isdigit(y) && y !='(' ){
                    perror("Invalid input\n");
                    exit(1);
                }

                if(stack[indexOfLastSymbol].sym=='$'){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='+'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='-'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='*'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='/'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym =='('){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym ==')'){
                    current = '>';  // takes precedence
                    takes(c);
                }
            }else if(c=='*'){
                 char y =exp[i+1]; 
                if(!isdigit(y) && y !='(' ){
                    perror("Invalid input\n");
                    exit(1);
                }

                if(stack[indexOfLastSymbol].sym=='$'){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='+'){
                    current = '<';
                    yields(current,c);
                    
                }else if(stack[indexOfLastSymbol].sym=='-'){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='*'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='/'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym =='('){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym ==')'){
                    current = '>';  // takes precedence
                    takes(c);
                }
            }else if(c=='/'){
                 char y =exp[i+1]; 
                if(!isdigit(y) && y !='(' ){
                    perror("Invalid input\n");
                    exit(1);
                }

                if(stack[indexOfLastSymbol].sym=='$'){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='+'){
                    current = '<';
                    yields(current,c);
                    
                }else if(stack[indexOfLastSymbol].sym=='-'){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='*'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='/'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym =='('){
                   current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym ==')'){
                    current = '>';  // takes precedence
                    takes(c);
                }   
            }else if(c=='('){
                char y =exp[i+1]; 
                if(!isdigit(y) && y !='(' ){
                    perror("Invalid input\n");
                    exit(1);
                }
                if(stack[indexOfLastSymbol].sym=='$'){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='+'){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='-'){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='*'){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='/'){
                    current = '<';
                    yields(current,c);
                }else if(stack[indexOfLastSymbol].sym=='('){
                    current = '<';
                    yields(current,c); 
                }else if(stack[indexOfLastSymbol].sym==')'){
                    perror("Invalid input");
                    exit(1);
                }

            }else if(c==')'){
                 char y =exp[i+1]; 
                if(isdigit(y) || y =='('  ){
                    perror("Invalid input\n");
                    exit(1);
                }
                if(stack[indexOfLastSymbol].sym=='$'){
                    perror("Invalid input");
                    exit(1);
                }else if(stack[indexOfLastSymbol].sym=='+'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='-'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='*'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='/'){
                    current = '>';  // takes precedence
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='('){
                   current = '<';
                   yields(current,c);
                }else if(stack[indexOfLastSymbol].sym==')'){
                    current = '>';  // takes precedence
                    takes(c);
                }
            }else if(c=='$'){
                if(stack[indexOfLastSymbol].sym=='$'){
                    printf("Input complete\n");
                }else if(stack[indexOfLastSymbol].sym=='+'){
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='-'){
                   takes(c);
                }else if(stack[indexOfLastSymbol].sym=='*'){
                    takes(c);
                }else if(stack[indexOfLastSymbol].sym=='/'){
                   takes(c);
                }else if(stack[indexOfLastSymbol].sym=='('){
                    perror("Error");
                }else if(stack[indexOfLastSymbol].sym==')'){
                   takes(c);
                }
            }
        }
        
        i++;
    }
    printf("Result : %d\n",stack[1].val);
    return 0;
}