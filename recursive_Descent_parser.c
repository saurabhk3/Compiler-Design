#include<stdio.h>
#include<string.h>
#include<ctype.h>

/*
    I've used the while loop construct: I've simplified it a little bit to avoid complicacy:
    # Only single letter Variables are considered
    # Only single digit numbers are considered
    # Input should be provided without any SPACE or LINE-BREAK i.e. All input should be in one line
    # Inside the while loop I've considered only one assignment statement
    # Example of one valid input : while(c==4)begina=i*3;end

    While loop construct :
        
        while(condition)
        begin
        statement;
        end

    Grammar used :

    S -> w(C)bAe
    C -> ION | IOI
    I -> a|b|c|d|...|z
    N -> 0|1|2|3...|9
    O -> ==|<=|>=|!=
    A -> L;
    L -> I=E
    E -> T*F
    T -> I
    F -> N



*/
int C();
int I();
int S();
int N();
int O();
int A();
int L();
int E();
int T();
int F();

char lookAhead;  // variable for storing lookahead character
int i =0;
char input[40];   // for taking input
int main(){
    printf("Enter the input:(according to format as written in comment)\n");
    scanf("%s",input);
    // get the first character in lookahead:
    lookAhead = input[i++];

    if(S()==1){
        printf("Accepted!\n");
    }else{
        printf("Rejected!");
    }

}
void match(char ch){  // matches the current char and increments the pointer to next input
    if(lookAhead==ch){
        lookAhead = input[i++];
    }else 
        return;
}

int S(){
    if(lookAhead=='w'){  // match for while
        match('w');
        match('h');
        match('i');
        match('l');
        match('e');
        match('(');
        if(C()){
            match(')');
            match('b');
            match('e');
            match('g');
            match('i');
            match('n');
            if(A()){
                match('e');
                match('n');
                match('d');
                return 1;
            }
        }
    }
    return 0;
}
int C(){
    if(I()==1){
        if(O()==1){
            if(N()==1){
                return 1;
            }else if(I()==1){
                return 1;
            }
        }
    }
}
int I(){
    if(isalpha(lookAhead)){
        match(lookAhead);    // For simplicity I'am considering only varibles of single letters
        return 1;
    }
    return 0;
}
int N(){
    if(isalnum(lookAhead)){
        match(lookAhead);   // For simplicity I'am considering only single digit numbers
        return 1;
    }
    return 0;
}
int O(){
    if(lookAhead=='='){
        match('=');
        match('=');
        return 1;
    }else if(lookAhead=='<'){
        match('<');
        match('=');
        return 1;
    }else if(lookAhead=='>'){
        match('>');
        match('=');
        return 1;
    }else if(lookAhead=='!'){
        match('!');
        match('=');
        return 1;
    }
    return 0;
}
int A(){
    if(L()){
        match(';');
        return 1;
    }
    return 0;
}
int L(){
    if(I()){
        match('=');
        if(E())
            return 1;
        else if(N())
            return 1;
    }
    return 0;
}
int E(){
    if(I())
        match('*');
        if(N())
            return 1;
    return 0;
}
