#include <bcconfig.h>
#include <BigNumber.h>
#include <number.h>

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
BigNumber primeCount = 0; // for counting primes found so far
BigNumber i = 1; // iterator for primes

void displayIterator(BigNumber i){
  lcd.setCursor(8,0);
  lcd.print("i:");
  lcd.setCursor(10,0);
  lcd.print(i);
}

void displayResults(BigNumber primeCount, BigNumber i){
  lcd.setCursor(0,0);
  lcd.print("c: ");
  lcd.setCursor(2,0);
  lcd.print(primeCount);
  lcd.setCursor(0,1);
  lcd.print("2^");
  lcd.setCursor(2,1);
  lcd.print(i);
}

char isPrime(BigNumber n){
  BigNumber divisor = 2;
  
  if(n < 1){ // primes are >0 by definition
    return 0;
  }
  else if(n <= 3){ // 1,2,3 are primes
    return 1;
  }
  else if( ( (n % divisor) == 0) || ( (n % (divisor + (BigNumber)(1))) == 0)){ // checking for 2 actually obsolete because of (i + 2)
    return 0;
  }

  divisor = 5;
  while(divisor*divisor <= n){ // check all divisors, 
    if( ( (n % divisor) == 0) || ( (n % (divisor + (BigNumber)(2))) == 0)){
      return 0;
    }
    divisor += 6;
  }
  return 1;
}


void setup() {
  BigNumber::begin ();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Mersenne Primes"); 
  delay(2000); 
  lcd.clear();
}

void loop() {
  BigNumber a = 2;
  BigNumber candidate; // candidate for Mersenne prime;
  candidate = (BigNumber)(0.5) + a.pow(i)-(BigNumber)(1);// + 0.5 so it gets properly truncated
//  //lcd.clear();
  displayIterator(i);
  
  if(isPrime(candidate)){
    displayResults(primeCount, i);
    primeCount++;
    if(i < 17)
    {
      delay(2000); // if i is small, display result longer
    }
  }
  
  i++;  
}
