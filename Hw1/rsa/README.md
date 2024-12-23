# ****ΤΙΤΛΟΣ PROJECT : RSA****

***

## Περιγραφή
Το πρόγραμμα RSA χρησιμοποιεί τον αλγόριθμο κρυπτογράφησης RSA για να κρυπτογραφήσει και να αποκρυπτογραφήσει μηνύματα, ανάλογα με τις παραμέτρους που δίνονται στη γραμμή εντολών. Πιο συγκεκριμένα, χρησιμοποιεί δύο πρώτους αριθμούς και δύο κλειδιά (δημόσιο και ιδιωτικό) για την κρυπτογράφηση και την αποκρυπτογράφηση ακολουθώντας τους τύπους που δίνονται

1. encrypt(m) = $m^{e}$ mod N 

2. decrypt(c) = $c^{d}$ mod N 

και εφαρμόζοντας συγκεκριμένους περιορισμούς
1. Έστω οι ακέραιοι e, d, p, q (το μυστικό) και ο ακέραιος m (το μήνυμα)
2. Έστω ο ακέραιος N = p · q.
3. Περιορισμός: όλοι οι ακέραιοι πρέπει να είναι θετικοί.
4. Περιορισμός: το μήνυμα m πρέπει να είναι μικρότερο του N .
5. Περιορισμός: οι ακέραιοι p και q είναι πρώτοι.
6. Περιορισμός: ο ακέραιος e είναι coprime με το ϕ(N ).
7. Περιορισμός: οι ακέραιοι e και d είναι αντίστροφοι, δηλαδή: e · d mod ϕ( N ) = 1.


Η εκφώνηση του συγκεκριμένου πρότζεκτ βρίσκεται [εδώ](https://progintro.github.io/assets/pdf/hw1.pdf) (άσκηση 2).
***
## Περιεχόμενα
- [Εγκατάσταση](#εγκατάσταση)
- [Χρήση](#χρήση)
- [Παραδείγματα](#Παραδείγματα-Εκτέλεσης)
- [Υλοποίηση](#Υλοποίηση)
- [Άδεια](#άδεια)

## Εγκατάσταση
Κατ' αρχάς αν έχετε ήδη ακολουθήσει τα βήματα εγκατάστασης από το πρόγραμμα "gcd calculator" μεταβείτε απευθείας στο τμήμα κατασκευής του προγράμματος και συγκεκριμένα στο στάδιο "μετάβαση στο φάκελο του προγράμματος" και συνεχίστε από εκεί. Διαφορετικά, ακολουθήστε την παρακάτω διαδικασία από την αρχή.

Για να εκτελεστεί επιτυχώς το πρόγραμμα "RSA" θα χρειαστεί να μετατρέψετε τον πηγαίο κώδικα σε εκτελέσιμο αρχείο. Για να το πραγματοποιήσετε αυτό ακολουθήστε τα παρακάτω βήματα:
### **Πρόσθετες οδηγίες για χρήστες Windows** 
Αν χρησιμοποιείτε Windows, μπορείτε να χρησιμοποιήσετε το Windows Subsystem for Linux (WSL) για να εγκαταστήσετε τον gcc και το git με τα ακόλουθα βήματα:
- Εγκατάσταση WSL: Για να εκτελέσετε το πρόγραμμα, θα χρειαστείτε ένα τερματικό περιβάλλον Linux. Αν δεν έχετε ήδη εγκατεστημένο το WSL, μπορείτε να το εγκαταστήσετε ακολουθώντας τις οδηγίες [εδώ](https://learn.microsoft.com/en-us/windows/wsl/install).

- Ubuntu: Όταν εγκαταστήσετε το WSL ανοίξτε το Ubuntu χρησιμοποιώντας WSL.

- Εγκατάσταση git: Αφού εγκαταστήσετε WSL, μπορείτε να εγκαταστήσετε το git γράφοντας την παρακάτω εντολή στο τερματικό Linux:
```sh
sudo apt update
sudo apt install git
```

- Εγκατάσταση `gcc`: Για να μπορέσετε να τρέξετε το πρόγραμμα αυτό θα χρειαστεί να εγκαταστήσετε τον `gcc` μέσω των εντολών παρακάτω:
```sh
sudo apt install gcc
```
### **Κατασκευή προγράμματος**
1.  Αντιγράψτε το repository στον τοπικό σας υπολογιστή:
   ```sh
git clone git@github.com:progintro/hw1-Spyrosmaicho.git
```

2.    Μεταβείτε στον φάκελο του προγράμματος rsa.c:  
```sh
cd rsa/src
```
3.  Μεταγλωττίστε το πρόγραμμα rsa.c με την παρακάτω εντολή:
```sh
gcc -O3 -Wall -Wextra -Werror -pedantic -o rsa rsa.c
```
Πλέον το πρόγραμμα είναι έτοιμο να εκτελεστεί.
***
## Χρήση
Για να λειτουργήσει το πρόγραμμα rsa.c θα πρέπει να το τρέξετε με πέντε ακριβώς ορίσματα στην γραμμή εντολών. Για να το εκτελέσετε, λοιπόν, χρησιμοποιήστε την παρακάτω εντολή:
```sh
./rsa op e d p q
```
όπου op e d p q είναι τα πέντε ορίσματα, τα οποία θα πρέπει να είναι στο διάστημα $[-10^{18}$ , $10^{18}$], εκτός από το πρώτο όρισμα op το οποίο θα πρέπει να είναι κάποιο σύνολο χαρακτήρων και συγκεκριμένα dec ή enc για αποκρυπτογράφηση ή κρυπτογράφηση αντίστοιχα. Ακόμα, το πρόγραμμα δέχεται το μήνυμα m από την πρότυπη είσοδο (standard input). 

Επιπλέον είναι σημαντικό να αναφερθεί ότι για να ελέγξετε τον κωδικό εξόδου του προγράμματος αφότου τερματιστεί, μπορείτε να πληκτρολογήστε την παρακάτω εντολή. 
```sh 
echo$?
``` 

Παράλληλα για να δώσετε μια τιμή στο πρόγραμμα μέσω stdin, αξιοποιήστε την παρακάτω εντολή:
```sh
echo num | ./rsa op e d p q
```
όπου στο num δίνεται ένας αριθμός για το μήνυμα και στα υπόλοιπα ορίσματα όσα αναφέρθηκαν παραπάνω. 

## Παραδείγματα εκτέλεσης
Στην συγκεκριμένη ενότητα θα παρουσιαστούν ορισμένες ενδεικτικές εκτελέσεις του προγράμματος.

Αρχικά αν το πρόγραμμα τρέξει χωρίς ακριβώς πέντε ορίσματα τότε τερματίζεται με κωδικό εξόδου 1, που δηλώνει σφάλμα, και εκτυπώνεται αντίστοιχο μήνυμα για το πώς πρέπει να γίνει η χρήση του.

**Παράδειγμα 1**

```sh
$ ./rsa
Usage: ./rsa enc|dec <exp_exp> <priv_exp> <prime1> <prime2>
$ echo $?
1
```
Ακολουθούν παραδείγματα με την σωστή λειτουργία του προγράμματος.

**Παράδειγμα 2.1**
```sh
$ echo 42 | ./rsa enc 17 26153 131 229
21187
$ echo 27187 | ./rsa dec 17 26153 131 229
42
```

Επίσης είναι δυνατόν να δώσετε ένα μήνυμα και να γίνει κρυπτογράφηση και στην συνέχεια αποκρυπτογράφηση του.

**Παράδειγμα 2.2**
```sh
$ echo 43434343 | ./rsa enc 65537 2278459553 62971 38609 | ./rsa dec 65537 2278459553 62971 38609
43434343
```

Τέλος για να λειτουργήσει σωστά ο αλγόριθμος Rsa θα πρέπει να ακολουθούνται οι περιορισμοί που αναφέρθηκαν στην αρχή. Στην περίπτωση που γίνει παράβλεψη κάποιου περιορισμού το προγραμμα τερματίζεται με κωδικό εξόδου 1 και ταυτόχρονα ενημερώνεται ο χρήστης για τον περιορισμό που δεν ακολούθησε. 

**Παράδειγμα 3**
```sh
$ ./rsa pop 1 2 3 4
First argument must be 'enc' or 'dec'
$ echo $?
1
$ ./rsa enc 1 2 -3 4
Negative numbers are not allowed
$ echo $?
1
$ ./rsa enc 1 2 3 4
p and q must be prime
$ echo $?
1
$ ./rsa enc 3 6 17 19
e is not coprime with phi(N)
$ echo $?
1
$ ./rsa enc 5 6 17 19
e * d mod phi(N) is not 1
$ echo $?
1
$ echo 500 | ./rsa enc 5 173 17 19
Message is larger than N
$ echo $?
1
$ echo -42 | ./rsa enc 5 173 17 19
Negative numbers are not allowed
$ echo $?
1
```

## Υλοποίηση

### <ins>Εισαγωγή Header Files:</ins>

- Οι εντολές #include <stdio.h>, #include <stdlib.h> και #include <string.h> χρησιμοποιήθηκαν για να εντάξω στο πρόγραμμα μου αυτές τις τρεις βιβλιοθήκες της C (stdio.h, stdlib.h, string.h), οι οποίες προσφέρουν την δυνατότητα αξιοποίησης βασικών συναρτήσεων εισόδου/εξόδο (scanf,printf) (stdio.h). Επιπλέον μέσω της stdlib.h  μπορώ να χρησιμοποιήσω τις συναρτήσεις exit( ) και atoll( ) για τερματισμό του προγράμματος και για μετατροπή των ορισμάτων που δίνονται στην γραμμή εντολών σε long long int αντίστοιχα. Τέλος, η βιβλιοθήκη string.h φάνηκε χρήσιμη κάθως ήταν απαραίτητο να χρησιμοποιήσω την strcmp.

### <ins>Argc και Argv</ins>

- Από τη στιγμή που θέλουμε το πρόγραμμα να παίρνει τιμές από την γραμμή εντολών θα πρέπει η main να περιέχει δύο ορίσματα το argc και argv. Επιπρόσθετα, εφόσον το έγκυρο πλήθος τιμών εισόδου είναι 5 είναι απαραίτητο να γίνεται ο έλεγχος  `if(argc!=5)` ούτως ώστε να εξασφαλίσουμε ότι αν ο χρήστης δεν δώσει ακριβώς πέντε τιμές θα τερματίζεται το πρόγραμμα. `if(argc!=5)` το argc διάφορο του 5 καθώς μετράει πάντα πέρα από τα ορίσματα που δίνει ο χρήστης και το όνομα του προγράμματος που εκτελείται. 

### <ins>Μεταβλητές:</ins>

   - Αντιμετώπιση αριθμών από $-10^{18}$ έως $10^{18}$: Το πρόγραμμα για να μπορέσει να δεχθεί ακέραιους αριθμούς του εύρους &plusmn; $10^{18}$ έπρεπε τα τέσσερα από τα πέντε ορίσματα από την γραμμή εντολών (όχι το πρώτο που είναι σύνολο χαρακτήρων) να μετατραπούν σε long long int για να υποστηρίξει τέτοιους μεγάλους αριθμούς, μιας και ο τύπος αυτός είναι δυνατόν να αποθηκεύσει αριθμούς του εύρους $−2^{63}$ έως $2^{63}−1$ που καλύπτει με ευκολία το διάστημα $[-10^{18}$ , $10^{18}$]. Για τον λόγο αυτό η συνάρτηση atoll βοήθησε ούτως ώστε να αλλάξει το κάθε όρισμα σε long long int και εν συνεχεία να αποθηκευτεί σε αντίστοιχου τύπου μεταβλητή(e,d,p,q).

### <ins>Συναρτήσεις και έλεγχοι για τους περιορισμούς του Αλγορίθμου RSA:</ins>

1. Εφόσον όλοι οι ακέραιοι πρέπει να είναι θετικοί χρησιμοποιήθηκαν δύο έλεγχοι ένας για τους αρνητικούς και άλλος ένας για την περίπτωση της μηδενικής εισόδου (`if(e<0 || d<0 || p<0 || q<0)` και `if(e==0 || d==0 || p==0 || q==0 || p==q)`) μιας και το πρόγραμμα όπως αναφέρουν οι προδιαγραφές εμφανίζει μήνυμα λάθους μόνο στην περίπτωση που κάποιος ακέραιος είναι αρνητικός (και φυσικά και στις δύο περιπτώσεις τερματίζεται το πρόγραμμα με κωδικό εξόδου 1), οπότε έπρεπε να αντιμετωπιστεί ξεχωριστά αυτός ο περιορισμός. Το ίδιο ισχύει και για το μήνυμα m, το οποίο πρέπει να είναι θετικό. Γι' αυτό τον λόγο βάσει των προδιαγραφών αντιμετώπισα ξεχωριστά την περίπτωση που είναι μηδέν και όταν είναι αρνητικό, διότι στην περίτπωση που είναι αρνητικό πέρα από τον τερματσιμό με κωδικό εξόδου 1 απαιτούνταν και η εκτύπωση ενός μηνύματος λάθους (ενώ όταν λαμβάνει μηδενική τιμή αρκούσε η έξοδος με κωδικό εξόδου 1).

2. Το μήνυμα m πρέπει να το μήνυμα m πρέπει να είναι μικρότερο του N. Το Ν για αρχή είναι το γινόμενο των δύο πρώτων αριθμών p και q, το οποίο αποθηκεύεται σε αντίστοιχη μεταβλητή. Αν, λοιπον, το m είναι μεγαλύτερο ή και ίσο του Ν τότε πάλι το πρόγραμμα πρέπει να τερματίζεται (`if(m>=N)`).

3. Το πρώτο όρισμα που δίνεται από την γραμμή εντολών πρέπει να είναι ή `dec` ή `enc`. Επόμενως, έχοντας ενσωματώσει την string.h αξιοποίησα την συνάρτηση `strcmp` η οποία συγκρίνει την συμβολοσειρά μας `op` με τις συμβολοσειρές `enc` και `dec` με βάση τις ASCII τιμές των χαρακτήρων τους και επιστρέφει μια ακέραια τιμή. Οπότε, εκμεταλλεύτηκα αυτή την επιστρεφόμενη τιμή μιας και αν αυτή είναι μηδέν (0) τότε οι συμβολοσειρές είναι ίδιες. Άρα μέσω της συνθήκης `if(strcmp(op,"enc")!=0 && strcmp(op,"dec")!=0)` εξασφαλίζεται ότι αν η συμβολοσειρά `op` είναι διαφορετική και από την `enc` και από την `dec` τότε δεν ικανοποιείται ένας περιορισμός του Αλγορίθμου Rsa οπότε και το πρόγραμμα πρέπει να τερματιστεί.

4. Γίνεται έλεγχος της επιστρεφόμενης τιμής τη scanf ούτως ώστε το πρόγραμμα να τερματίζει αν ο χρήστης δώσει μη έγκυρη τιμή στο μήνυμα m(χαρακτήρα ή `EOF`). Επομένως, `if(scanf("%lld",&m)!=1)` εξετάζει αν η επιστρεφόμενη τιμή της scanf είναι διαφορετική του 1, μιας και αυτός ο έλεγχος καλύπτει πλήρως τις περιπτώσεις που δοθεί λανθασμένη τιμή στο μήνυμα κατά την είσοδο του προγράμματος.
 
5. Συνάρτηση isprime:
    Η συγκεκριμένη συνάρτηση ψάχνει να βρει αν ο αριθμός που δίνεται ως όρισμα και συγκεκριμένα το p και q (αφού αυτοί οι δύο θέλουμε να είναι πρώτοι για να ισχύει ο περιορισμός του rsa) είναι πρώτος. Ουσιαστικά, η συγκεκριμένη μέθοδος βασίζεται στο γεγονός ότι όλοι οι πρώτοι αριθμοί μεγαλύτεροι του 3 έχουν τη μορφή 6κ &plusmn; 1 , όπου k είναι οποιοσδήποτε ακέραιος μεγαλύτερος του 0. Αυτό συμβαίνει επειδή όλοι οι ακέραιοι μπορούν να εκφραστούν ως 6κ &plusmn; 1, όπου i=−1,0,1,2,3,4 ([Primality-test](https://en.wikipedia.org/wiki/Primality_test), [6κ &plusmn; 1](https://www.geeksforgeeks.org/introduction-to-primality-test-and-school-method/)).

    Το 2 όμως διαιρεί τους αριθμούς 6k, 6k+2, και 6k+4.

    Το 3 όμως διαιρεί τους αριθμούς 6k+3.

    Επομένως, οι μόνοι αριθμοί για να είναι πρώτοι είναι της μορφής 6k−1 ή 6k+1. Αυτό οδηγεί στο γεγονός ότι όλοι οι πρώτοι αριθμοί μεγαλύτεροι από το 3 είναι της μορφής 6k &plusmn; 1.

- Άρα ποιος ο λόγος που το i+=6 είναι αποδοτικό: Αν κάνουμε έλεγχο διαιρέσεων με τον απλό τρόπο,δηλαδή αυξάνοντας το i κατά ένα, τότε ελέγχουμε κάθε ακέραιο αριθμό μέχρι το n.

      
- Επομένως έχουμε περιττούς ελέγχους, διότι:

    1. Ελέγχονται άρτιοι αριθμοί (που δεν είναι σίγουρα πρώτοι).

    2. Ελέγχονται πολλαπλάσια του 3 (που δεν είναι σίγουρα πρώτοι).

- Άρα το i+=6: Προσπερνά αριθμούς που είναι πολλαπλάσια του 2 και του 3.

    Για παράδειγμα, αντί να ελέγχουμε όλους τους αριθμούς από το 2 έως το n

    π.χ. 2, 3, 4, 5, 6, 7, 8, 9, 10...

    ελέγχουμε μόνο αριθμούς όπως:

    5, 7, 11, 13, 17, 19, 23, 25... (όλοι της μορφής 6k &plusmn; 1).

    - Αλγόριθμος:

     1. Εξαίρεση του 2 και του 3: Αρχικά, ελέγχουμε αν το n διαιρείται από το 2 ή το 3 (αν ισχύει, τότε δεν είναι πρώτος).
         
     2. i+=6: Ξεκινάμε από i=5 και ελέγχουμε τους αριθμούς της μορφής i και i+2 (δηλαδή στην ουσία 6k−1 και 6k+1).
         
     3. Σταματάμε στον πρώτο διαιρέτη ή όταν $i^{2}$ > n. Αν βρεθεί διαιρέτης, το n δεν είναι πρώτος αλλιώς αν σταματήσει η επανάληψη λόγω ότι $i^{2}$ > n τότε αποτελεί έναν πρώτο αριθμό.

    - Παράδειγμα:

     1. Έστω n=97:

     2. Ο n δεν διαιρείται από το 2 ή το 3. Άρα οδηγούμαστε στην επανάληψη.
         
     3. Αρχίζουμε από i=5 και:
         
     4. Αν 97%5==0: Δεν ισχύει.
         
     5. Αν 97%7==0: Δεν ισχύει.
         
     6. Σταματάει η επανάληψη γιατί $i^{2}$ > n, 25>97
         
     7. Άρα ο 97 είναι πρώτος.

6.  Συνάρτηση phi ή φ: 
Γνωρίζουμε από τις προδιαγραφές της άσκησης ότι η συνάρτηση ϕ έχει την ιδιότητα ότι για κάθε δύο φυσικούς a, b με gcd(a, b) = 1 ισχύει ότι ϕ(a · b) = ϕ(a) · ϕ(b). Επιπλέον, αν ο αριθμός a είναι πρώτος, τότε ισχύει πως ϕ(a) = a − 1. Επομένως, είναι πολύ λογικό εφόσον ο αριθμός Ν είναι το γινόμενο p*q, όπου p και q είναι δύο πρώτοι αριθμοί (άρα φ(p)= p-1 και φ(q)= q-1) να ισχύει ότι το φ(Ν) = φ(p · q) = φ(q) · φ(q). Ακόμα, η συνάρτηση αυτή χρησιμεύει ούτως ώστε να εξετάσουμε έναν περιορισμό του αλγορίθμου: ο ακέραιος e να είναι coprime με το ϕ(N). Έχοντας, λοιπόν, υπολογίσει το ϕ(N) και αξιοποιώντας το γεγονός ότι δύο ακέραιοι a και b είναι coprime όταν ο μέγιστος κοινός διαιρέτης τους είναι το 1, δηλαδή gcd(a, b) = 1 έβαλα τον έλεγχο `if(gcd(e,f)!=1)` εξασφαλίζοντας έτσι τον περιορισμόν της εκφώνησης. Τέλος, με την βοήθεια της συνάρτησης αυτής εξετάζω και τον περιορισμό οι αριθμοί e και d να είναι αντίστροφοι πάλι με βάση τον δοθέντα τύπο της εκφώνησης (e · d mod ϕ(N) = 1)

7. Ανάλυση της συνάρτησης gcd

- Αντιμετώπιση αρνητικών αριθμών:
Αν ο αριθμός a είναι αρνητικός, τον κάνει θετικό. Αυτό γίνεται για να είναι το αποτέλεσμα σωστό..

- Η λογική του αλγόριθμου:

Αν b είναι μηδέν, τότε το αποτέλεσμα είναι ο αριθμός a. Αυτό συμβαίνει επειδή κάθε αριθμός διαιρείται τέλεια με τον εαυτό του.
Διαφορετικά, βρίσκει το υπόλοιπο της διαίρεσης a % b και καλεί τη συνάρτηση ξανά, αλλάζοντας τη θέση των αριθμών ως ορίσματα της συνάρτησης.

-  Τι κάνει η αναδρομή:
Κάθε φορά που η συνάρτηση καλείται ξανά, δουλεύει με μικρότερους αριθμούς, επειδή το υπόλοιπο της διαίρεσης a % b είναι πάντα μικρότερο από το b. Αυτό συνεχίζεται μέχρι το υπόλοιπο να γίνει 0. Όταν συμβεί αυτό, ο αριθμός a είναι ο ΜΚΔ.

- Γιατί ισχύει αυτό:
Ο αλγόριθμος του Ευκλείδη βασίζεται στη μαθηματική αρχή ότι ο ΜΚΔ δύο αριθμών δεν αλλάζει αν αντικαταστήσουμε τον μεγαλύτερο από αυτούς με το υπόλοιπο της διαίρεσής του με τον μικρότερο. Έτσι, μειώνοντας σταδιακά τους αριθμούς, βρίσκουμε τον ΜΚΔ. ([ευκλείδιος-αλγόριθμος](https://en.wikipedia.org/wiki/Euclidean_algorithm)).

### Ενδεικτικό παράδειγμα

Για να γίνει πιο κατανοητό θα χρησιμοποιήσουμε δύο αριθμούς και θα βρούμε τον ΜΚΔ τους χρησιμοποιώντας την συνάρτηση gcd
Έστω ότι θέλουμε να υπολογίσουμε τον ΜΚΔ των -36 και 24.
1. Πρώτη κλήση:
    
    a = −36 | b = 24
    
    Το a < 0 , οπότε μετατρέπεται σε θετικό: a = (-36)*(-1)= 36
    
    Υπολογίζεται gcd(24,36%24) → gcd(24,12)
2. Δεύτερη κλήση:

    a = 24 | b = 12
    
    Υπολογίζεται gcd(12,24%12) → gcd(12,0)
3. Τρίτη κλήση:

    a = 12 | b = 0
    
    Επιστρέφεται το a=12 γιατί όταν το b μηδενιστεί, το a είναι ο ΜΚΔ.

Επομένως, Ο ΜΚΔ του -36 και 24 είναι 12 που πράγματι ισχύει.  

8. Συνάρτηση mypow:
Λογική της συνάρτησης mypow

Η συνάρτηση mypow υπολογίζει την τιμή ($base^{exp}$) mod num χρησιμοποιώντας modular exponentiation ( [modular exponentiation](https://en.wikipedia.org/wiki/Modular_exponentiation)) με τρόπο που να αποφεύγει τον υπολογισμό τεράστιων ενδιάμεσων αποτελεσμάτων.
  
#### **Βήματα:**

- **Αρχικοποίηση:** Η τιμή result αρχικοποιείται στο 1, διότι οποιοσδήποτε αριθμός υψωμένος στη μηδενική δύναμη είναι ίσος με 1.Η βάση 
    (base) μειώνεται στο υπόλοιπό της από num (base = base % num) για να αποτρέψουμε αριθμητική υπερχείλιση.
    
- **Επανάληψη:** Όσο exp > 0, η επανάληψη συνεχίζεται, μειώνοντας τον εκθέτη σταδιακά.
    
- **Εξέταση αν ο εκθέτης είναι περιττός:** Αν exp % 2 == 1 , τότε η τρέχουσα τιμή της base πολλαπλασιάζεται στο result:result = (result  • base) mod num
    
- **Ανανέωση της βάσης:** Η base υψώνεται στο τετράγωνο:base=(base • base) mod  num.Αυτό οδηγεί στο διπλασιασμό της δύναμης που έχει η base.
    
- **Μείωση εκθέτη:** Ο εκθέτης διαιρείται διαδοχικά με το 2: exp=exp/2.
    Αυτό υλοποιεί τη μέθοδο δυαδικής αναπαράστασης του εκθέτη ([Exponentiation by squaring](https://en.wikipedia.org/wiki/Exponentiation_by_squaring)).
    
    Αποδοτικότητα: Η συνάρτηση έχει λογαριθμική πολυπλοκότητα (O(log(exp))), καθώς διαιρεί τον εκθέτη με το 2 σε κάθε επανάληψη.
    Αποφυγή υπερχείλισης: Ο υπολογισμός γίνεται σε κάθε βήμα mod num, διατηρώντας τα ενδιάμεσα αποτελέσματα μικρά

- Η παραπάνω ακριβώς συνάρτηση, δηλαδή η `mypow`, δημιουργήθηκε ούτως ώστε να υπολογίσει αποδοτικά ανάλογα με το πρώτο όρισμα που θα δοθεί στην γραμμή εντολών (`enc` ή `dec`) την κρυπτογράφηση ή αποκρυπτογράφηση του μηνύματος m με βάση τους τύπους του αλγόριθμου rsa.

1. encrypt(m) = $m^{e}$ mod N 
2. decrypt(c) = $c^{d}$ mod N

Επόμενως ελέγχοντας αν δόθηκε `enc` ή `dec` καλείται και η αντίστοιχη συνάρτηση.

```c
if(strcmp(argv[1],"enc")==0)
        printf("%lld\n",enc(m,e,N));  // Κρυπτογράφηση
    else if(strcmp(argv[1],"dec")==0)
    {
        printf("%lld\n",dec(m,d,N));  // Αποκρυπτογράφηση
    }
```

## Άδεια(License)

Αυτό το έργο είναι αδειοδοτημένο υπό την **MIT License**. 

### Επιτρέπεται:

- Η χρήση του κώδικα για οποιονδήποτε σκοπό.
- Η τροποποίηση και η προσαρμογή του κώδικα.
- Η διανομή του κώδικα, υπό την προϋπόθεση ότι θα αναφέρεται η αρχική άδεια.

### Δεν επιτρέπεται:

- Η αποκοπή της άδειας από τον κώδικα.

### MIT License

Copyright (c) 2024 Spyros Maichosoglou

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to use the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
***
