/*Πρόγραμμα: factor.c
Αυτό το πρόγραμμα υλοποιεί τον αλγόριθμο Pollard's Rho για την παραγοντοποίηση
μεγάλων ημιπρώτων αριθμών. Ο αλγόριθμος χρησιμοποιείται για την εύρεση δύο μη
απλών παραγόντων ενός αριθμού (p και q) όταν ο αριθμός είναι ημιπρώτος*/
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Τύπος για την υποστήριξη 128-bit ακέραιων αριθμών
typedef __int128 i128;

//Η συνάρτηση υπολογίζει την απόλυτη τιμή ενός 128-bit αριθμού, καθώς το x - y
//μπορεί να είναι αρνητικό και ο GCD απαιτεί θετικές τιμές. Επίσης απαιτείται
//και για την υλοποίση του Pollard's Rho
i128 abs128(i128 num) { return num < 0 ? -num : num; }

//Χρησιμοποιείται για την παραγωγή τυχαίων αριθμών μέσω Xorshift128+
//και για τη δημιουργία διαφορετικών τιμών c στον Pollard's Rho.
static uint64_t seed[2] = {0x123456789abcdef0ULL, 0xfedcba9876543210ULL};

//Δημιουργία τυχαίων αριθμών με τον Xorshift128+ αλγόριθμο.
uint64_t xorshift128plus() {
  uint64_t s1 = seed[0];
  const uint64_t s0 = seed[1];
  seed[0] = s0;

  // Shift και XOR για τυχαία διάχυση των bits
  s1 ^= s1 << 23;
  seed[1] = s1 ^ s0 ^ (s1 >> 17) ^ (s0 >> 26);
  return seed[1] + s0;
}

//Συνάρτηση που επιστρέφει έναν τυχαίο unsigned long long αριθμό
//Χρησιμευεί για την τυχαιότητα του seed στον Pollard's Rho
unsigned long long better_rand() { return xorshift128plus(); }

// Υπολογίζει το (x * y) % mod αποφεύγοντας υπερχείλιση(Modular Multiplication).
i128 modmul(i128 x, i128 y, i128 mod) {
  i128 result = 0;  // Αθροιστής για το τελικό αποτέλεσμα

  //Μείωση του x και y στο mod για να αποτρέψουμε περιττές μεγάλες πράξεις
  x %= mod;
  y %= mod;

  while (y) {
    //Αν το τελευταίο bit του y είναι 1, προσθέτουμε το x στο αποτέλεσμα
    if (y & 1) {
      result += x;
      if (result >= mod)
        result -= mod;  //Μείωση mod για αποφυγή υπερχείλισης, αν χρειάζεται.
    }

    x += x;  //Διπλασιασμός του x για το επόμενο bit
    if (x >= mod) x -= mod;

    y >>= 1;
  }
  return result;
}

//Ευκλείδειος αλγόριθμος για τον υπολογισμό του Μέγιστου Κοινού Διαιρέτη (GCD).
i128 gcd(i128 x, i128 y) {
  while (y) {
    i128 temp = y;
    y = x % y;
    x = temp;
  }
  return x;
}

//Η συνάρτηση εκτελεί τον Pollard's Rho για παραγοντοποίηση μεγάλων αριθμών.
// c: Η σταθερά για τη συνάρτηση f(x) = (x^2 + c) % semi.
int rho(i128 semi, i128 *p, i128 *q, i128 c) {
  i128 x = 2, y = 2, num = 1;  //Χ,y αρχικοποιούνται στο 2 για να αποφεχθούν
                               //στατικές ακολουθίες.

  while (num == 1) {
    //Υπολογίζουμε τη f(x) και f(y) δύο φορές.
    x = (modmul(x, x, semi) + c) % semi;
    y = (modmul(y, y, semi) + c) % semi;
    // y ενημερώνεται δύο φόρες, για διπλάσια ταχύτητα.
    y = (modmul(y, y, semi) + c) % semi;

    //Υπολογίζουμε τον GCD της απόλυτης τιμής του x - y και του semi
    num = gcd(abs128(x - y), semi);
  }

  //Αν το αποτέλεσμα είναι ίσο με τον ίδιο τον αριθμό τότε έχουμε αποτυχία.
  if (num == semi) return -1;

  *p = num;  //πρώτος παράγοντας που βρέθηκε.
  //Ο άλλος παράγοντας προκύπτει διαιρώντας το semi με τον πρώτο
  *q = semi / num;
  return 0;
}

//Η συνάρτηση εκτυπώνει έναν 128-bit αριθμό χαρακτήρα-χαρακτήρα
void print_int128(i128 n) {
  if (n == 0) {
    putchar('0');
    return;
  }
  if (n < 0) {
    putchar('-');
    n = -n;  //Μετατρέπουμε σε θετικό αριθμό για απλοποίηση
  }

  char buffer[40];  //Αρκετό μέγεθος για 128-bit αριθμό
  int i = 0;
  while (n > 0) {
    buffer[i++] = '0' + (n % 10);  //Αποθηκεύουμε τα ψηφία του αριθμού ανάστροφα
    n /= 10;
  }
  while (i > 0) {
    putchar(buffer[--i]);  //Εκτυπώνουμε τα ψηφία στη σωστή σειρά
  }
}

//Συνάρτηση μετατροπής συμβολοσειράς σε 128-bit αριθμό
i128 atoint128(const char *str) {
  i128 result = 0;
  int sign = 1;  //μεταβλητή για το πρόσημο
  if (*str == '-') {
    sign = -1;  //Ελέγχουμε για αρνητικό αριθμό
    str++;
  }
  while (*str >= '0' && *str <= '9') {  //Αν ο χαρακτήρας είναι ψηφίο
    result = result * 10 + (*str - '0');  //τον προσθέτουμε στο αποτέλεσμα
    str++;
  }
  return result * sign;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <number>\n", argv[0]);
    return 1;
  }

  i128 semi = atoint128(argv[1]);

  //Αν ο ημιπρώτος είναι αρνητικός τερματίζεται το πρόγραμμα.
  if (semi < 0) return 1;

  i128 p = 0, q = 0;

  //Εκτελούμε τον Pollard's Rho για διαφορετικές σταθερές c
  for (int i = 1; i <= 100; i++) {
    i128 c = (better_rand() % (semi - 2)) + 1;
    if (rho(semi, &p, &q, c) == 0) {
      printf("Factors: ");
      print_int128(p);
      printf(" ");
      print_int128(q);
      printf("\n");
      return 0;
    }
  }
}
