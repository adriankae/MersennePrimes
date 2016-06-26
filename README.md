# Mersenne Primes


## Description 

The Arduino calculates [Mersenne Primes](https://en.wikipedia.org/wiki/Mersenne_prime) and displays the largest prime found and the number of primes already found on a 2x16 LCD Display.

The Arduino checks in the range of 1 to infinity wether the number is a prime or not and counts the primes found until the current iteration.

The output will be of the form:

first line: "c: count ... i:iterator"  

second line: "largest prime"

Where "count" is the number of primes already found, "iterator" is the exponent and  "largest prime", well, is the largest prime found.

Of course, after a couple of days you'd find ten Mersenne Primes or so due to the Arduino's limited computing power.

## Diffiuclty

Very easy. A fun way to implement the Mersenne Prime search algorithm.

Requires moderate soldering skills.

## Parts list

I used the following parts:

* Arduino uno
* LCD 2x16
* pin headers to solder to the LCD
* 10k Poti
* 220 Ohm Resistor
* Jumper wires
* Breadboard

see also <https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay>

## Schematic

The schematic for hooking up the LCD to your Arduino can be found at <https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay>.

Or here (used from the website above, licensed by CC SA 3.0):  

![licensed by CC SA 3.0](/Users/adrian/Documents/Arduino/naivePrimalityTest/LCD_Base_bb_Fritz.png "Circuit")

## Implementation

I altered the code from my [previous project (Naive Primality Test)](https://github.com/adriankae/NaivePrimalityTest) so that it uses the [BigNumber library](https://github.com/nickgammon/BigNumber).

It uses the naive primality test to check if the numbers are Mersenne primes, too.

## Code

#include <LiquidCrystal.h>

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

## Pictures


## License

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.