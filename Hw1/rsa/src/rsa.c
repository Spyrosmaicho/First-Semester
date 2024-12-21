/*Αρχείο rsa.c
Το πρόγραμμα αυτό δέχεται πέντε τιμές από την γραμμή εντολών και με βάση αυτές
κρυπτογραφεί ή αποκρυπτογραφεί μηνύματα αντίστοιχα, χρησιμοποιώντας τον αλγόριθμο RSA.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int enc(long long int m,long long int e,long long int N);
long long int dec(long long int c,long long int d,long long int N);
long long int mypow(long long int base,long long int exp,long long int num); 
int isprime(long long int n);
long long int phi(long long int p,long long int q);
long long int gcd(long long int a,long long int b);

int main(int argc,char *argv[])
{
    long long int m,e,d,p,q,N,f;
    char *op;
    //Έλεγχος αν δίνεται το σωστό πλήθος ορισμάτων στην γραμμή εντολών.
    if(argc!=6)
    {
        printf("Usage: %s enc|dec <exp_exp> <priv_exp> <prime1> <prime2>\n",argv[0]);
        exit(1);
    }

    op=argv[1];
    e=atoll(argv[2]); 
    d=atoll(argv[3]);
    p=atoll(argv[4]);
    q=atoll(argv[5]);

    //Έλεγχος περιορισμών της εκφώνησης.
    if(strcmp(op,"enc")!=0 && strcmp(op,"dec")!=0)
    {
        printf("First argument must be 'enc' or 'dec'\n");
        exit(1);
    }

    if(e==0 || d==0 || p==0 || q==0 || p==q)
        return 1;
    if(e<0 || d<0 || p<0 || q<0)
    {
        printf("Negative numbers are not allowed\n");
        exit(1);
    }

    if(isprime(p)!=1 || isprime(q)!=1)
    {
        printf("p and q must be prime\n");
        exit(1);
    }

    if(p==q) // οι δύο πρώτοι αριθμοί δεν πρέπει να είναι ίσοι για να λειτουργήσει σωστά ο αλγόριθμος rsa.
        return 1;
    N=p*q;

    //Υπολογίζεται το phi(N) το οποίο βάσει εκφώνησης 
    //θα χρειαστεί για τον έλεγχο αν ο αριθμός e είναι coprime με το phi(N).
    //Ακόμα είναι απαραίτητο για τον έλεγχο αν e και d είναι αντίστροφοι.
    f=phi(p,q);

    //Έλεγχος αν το e είναι coprime με το phi(N).
    if(gcd(e,f)!=1)
    {
        printf("e is not coprime with phi(N)\n");
        exit(1);
    }

    //Έλεγχος αν e και d είναι αντίστροφοι, χρησιμοποιώντας τον τύπο της εκφώνησης. 
    if((e*d)%f!=1)
    {
        printf("e * d mod phi(N) is not 1\n");
        exit(1);
    }

    //Έλεγχος αν δεν δοθεί έγκυρη τιμή στην scanf.
    if(scanf("%lld",&m)!=1)
    {
        exit(1);
    }
    //Βάσει προδιαγραφών το μήνυμα πρέπει να είναι θετικός αριθμός.
    if(m<0)
        printf("Negative numbers are not allowed\n");
    if(m==0)
        return 1;
    
    //Έλεγχος αν το μήνυμα m είναι μικρότερο από το N.
    if(m>=N)
    {
        printf("Message is larger than N\n");
        exit(1);
    }

    //Κρυπτογράφηση ή αποκρυπτογράφηση ανάλογα με την επιλογή του χρήστη.
    if(strcmp(argv[1],"enc")==0)
        printf("%lld\n",enc(m,e,N));  // Κρυπτογράφηση
    else if(strcmp(argv[1],"dec")==0)
    {
        printf("%lld\n",dec(m,d,N));  // Αποκρυπτογράφηση
    }
    
    return 0;
}

// Συνάρτηση που ελέγχει αν ένας αριθμός είναι πρώτος
int isprime(long long int n)
{
    int i;

    if(n==1)
        return 0; //Το ένα δεν είναι πρώτος.
    if(n<=3)
        return 1; // 2 και 3 είναι πρώτοι.
    if(n%2==0 || n%3==0)
        return 0; //τα πολλαπλάσια του 2 και του 3 δεν είναι πρώτος.

    // Έλεγχος για άλλους διαιρέτες
    for(i=5;i*i<=n;i+=6)
    {
        if(n%i==0 || n%(i+2)==0) 
            return 0; //Αν βρεθεί διαιρέτης, δεν είναι πρώτος.
    }
        
    return 1; //Είναι πρώτος ο αριθμός.
}

//Συνάρτηση που υπολογίζει τον ΜΚΔ δύο αριθμών με αναδρομή.
long long int gcd(long long int a,long long int b)
{
    if(a<0)
        a*=-1; //Μετατροπή στην περίπτωση αρνητικού αριθμού σε θετικό για ορθό αποτέλεσμα του ΜΚΔ.

    //Η αναδρομή συνεχίζεται μέχρι το b να μηδενιστεί, οπότε επιστρέφεται το a που περιέχει τον ΜΚΔ.
    return (b==0) ? a : gcd(b, a%b);
}

//Συνάρτηση που υπολογίζει το φ(N) για δύο πρώτους αριθμούς p και q.
long long int phi(long long int p, long long int q) 
{
    return (p - 1) * (q - 1);  
}

//Η συνάρτηση mypow υπολογίζει το (base^exp) mod num και χρησιμεύει στους τύπους κρυπτογράφησης και αποκρυπτογράφησης. 
long long int mypow(long long int base, long long int exp,long long int num) 
{
    long long int result=1;

    //Μειώνουμε τη βάση στο υπόλοιπό της για μικρότερες τιμές.
    base=base%num;
    while (exp>0) 
    {
        if (exp%2==1) 
        {
            result = (result*base)%num; 
        }
        base=(base*base)%num;  //Ύψωνω στο τετράγωνο τη βάση, καθώς αυτό αντιστοιχεί σε διπλασιασμό του εκθέτη. 
        exp=exp/2;   //Διαιρούμε τον εκθέτη με το 2, καθώς έχουμε διαχειριστεί τη μισή του δύναμη.
    }
    
    return result;
} 

//Συνάρτηση κρυπτογράφησης αξιοποιώντας τον τύπο της εκφώνησης
long long int enc(long long int m,long long int e,long long int N)
{
    return mypow(m,e,N); //Υπολογίζεται το encrypt με βάση τον τύπο κρυπτογράφησης((m^e) mod N).
}

// Συνάρτηση αποκρυπτογράφησης αξιοποιώντας τον τύπο της εκφώνησης.
long long int dec(long long int c,long long int d,long long int N)
{
    return mypow(c,d,N); //Υπολογίζεται το decrypt με βάση τον τύπο αποκρυπτογράφησης((c^d) mod N).
}