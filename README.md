# Compiler-Design
ReadME for Recursive Descent Parser


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
