#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
unsigned long primeCount = 0; // for counting primes found so far
unsigned long i = 1; // iterator for primes

char isPrime(long n){
  if(n <= 1){ // primes are >0 by definition
    return 0;
  }
  else if(n <= 3){ // 1,2,3 are primes
    return 1;
  }
  else if( ( (n % 2) == 0) || ( (n % 3) == 0)){ // checking for 2 actually obsolete because of (i + 2)
    return 0;
  }

  unsigned long divisor = 5;
  while(divisor*divisor <= n){ // check all divisors, 
    if( ( (n % divisor) == 0) || ( (n % (divisor + 2)) == 0)){
      return 0;
    }
    divisor += 6;
  }
  return 1;
}


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Mersenne Primes"); 
  delay(2000); 
}

void loop() {
  unsigned long candidate; // candidate for Mersenne prime;
  candidate = 2^i;
  if(isPrime(candidate)){
    if(candidate <= 4294967295 ){ // prevents loop from counting higher after reaching the limits of unsigned long
      primeCount++;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("c: ");
    lcd.setCursor(2,0);
    lcd.print(primeCount);
    lcd.setCursor(0,1);
    lcd.print("2^");
    lcd.setCursor(2,1);
    lcd.print(i);
  }
  if(candidate <= 4294967295 ){ // keeps loop within the limits of unsigned long
    i += 1;  
  }
}
