#include<stdio.h>
#include<stdlib.h>

struct Factor{
    float exponent;
    float coefficent;
    struct Factor* next;
};

typedef struct Factor Factor;

struct Polynomial{
    Factor *top;
};

typedef struct Polynomial Polynomial;

Factor* newFactor(){
    Factor* x = (Factor*)malloc(sizeof(Factor));
    x->next = NULL;
    return x;
}

Factor* copyFactor(Factor *main){
    // Copy except next
    Factor *slave = newFactor();
    slave->coefficent = main->coefficent;
    slave->exponent = main->exponent;
    slave->next = NULL;
    return slave;
}

Polynomial* newPolynomial(){
    Polynomial* x = (Polynomial*)malloc(sizeof(Polynomial));
    x->top = NULL;
    return x;
}



void insert(Polynomial* polynomial, Factor* newfactor){
    newfactor->next = NULL;
    Factor *i=polynomial->top, *previous = polynomial->top;
    for(; i != NULL && i->exponent > newfactor->exponent; i=i->next)
        previous = i;
    if(previous == i){
        // Insert begining
        if(i && i->exponent == newfactor->exponent)
            i->coefficent += newfactor->coefficent;
        else{
            newfactor->next = polynomial->top;
            polynomial->top = newfactor;
        }
    }
    else{
        if(i && i->exponent == newfactor->exponent)
            // if exponents are equal add coefficents
            i->coefficent += newfactor->coefficent;
        else{
            previous->next = newfactor;
            newfactor->next = i;
        }
    }

}

Polynomial* sum(Polynomial* A, Polynomial* B){
    Factor* a_pos = A->top;
    Factor* b_pos = B->top;
    Polynomial *C = newPolynomial();

    for (;a_pos != NULL; a_pos=a_pos->next){
        Factor* newfactor = copyFactor(a_pos);
        insert(C, newfactor);
    }

    for(;b_pos != NULL; b_pos=b_pos->next){
        Factor* newfactor = copyFactor(b_pos);
        insert(C, newfactor);
    }
    return C;
}

void display(Polynomial* polynomial){
    printf("\n");
    for(Factor *i=polynomial->top; i != NULL;i=i->next)
        if(i->exponent == 0)
            printf("%0.2f + ", i->coefficent);
        else if(i->coefficent == 1)
            printf("X^%0.2f + ", i->exponent);
        else
            printf("%0.2fX^%0.2f + ", i->coefficent, i->exponent);
    printf("0");
    printf("\n");
}

void readPolynomial(Polynomial* X){
    int n;
    printf("Enter number of terms: ");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        Factor* newfactor = newFactor();
        printf("Enter Exponent and Coefficent: ");
        scanf("%f%f", &newfactor->exponent, &newfactor->coefficent);
        insert(X, newfactor);
        printf("\n");
    }
}

void dispMenu(){
    printf("\n");
    printf("\nEnter 0 for reading Polynomial 0");
    printf("\nEnter 1 for reading Polynomial 1");
    printf("\nEnter 2 for displaying Polynomial 0");
    printf("\nEnter 3 for displaying Polynomial 1");
    printf("\nEnter 4 for addition");
    printf("\nEnter your choice: ");
}

int main(){
    Polynomial *A = newPolynomial(), *B = newPolynomial();
    int choice;
    do{
        dispMenu();
        scanf("%d", &choice);
        switch(choice){
                case 0: readPolynomial(A);break;
                case 1: readPolynomial(B);break;
                case 2: display(A);break;
                case 3: display(B);break;
                case 4: display(sum(A,B));break;
        }
    }while(choice != -1);
    return 0;
}
