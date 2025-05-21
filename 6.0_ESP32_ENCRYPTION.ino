//============================
// Encryption Algorithm 6.0
// ESP32 w/ TFT
// Updates as of 4.13.2024:
//        1. Introducing the working Brute Force Calculator!
//        2. Uses all possible characters or a set of characters to determine all possible combinations, and guess your password you enter. 
//        2. Will return: your password (calculated), will print all combinations possible given a password length and set of characters, number of possible combinations,
//        3. It works now! Fixed the newline characters being added to the input of the user. This has been plaguing serial input for a long time, but no more!
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();
// encryption variables
            // navigation through the program
            int menuSelector = 0; 
            int wipeIndex = 0; // used to loop through the arrays and delete the data. 
            //=========== encryption stuff
            int encryptionKey = 8; // used to multiply the data or divide it, which makes data encrypted or decrypted. 
            int dataSize = 10000; // keeps track of the size of data array to make. 
            // encrypted data stored in the array data[10,000]
            int data[10000];
            int decryptedData[10000];
            String EncryptedString = ""; // holds encrypted output
            String DecryptedString = ""; // holds decrypted output
            int x = 0; 
            int y = 0; 
            int height = data[x]; // used to draw pixels that represent the data. 
            int dataIndex = 0; // where the user is at in the data array. 
            int numInputs = 0; // this limits the amount of data the user can input. 
            // simple incrementor
            int i = 0; 
            //int z = 0; // loops through the data array to ensure it's not empty before you decrypt it. 
            // keep track of cursor
            int cursorIndex = 0; 
            // decryption
            int decryptPosition = 0; 
            // used to get input from the user, including navigation and encryption input. 
            char incomingByte; 
            int pageY = 40; // keeps track of the scrolling of the page, used for viewing. 
            // keeps track of the page. 
            int pageNumber = 0; // where the esp32 prints out from the data[] array. 
            int pageSize = 700; // number of characters the screen prints out per page.
            int arraySize = 10000; // IMPORTANT - keeps the loop from going outside bounds of array. 
            bool print = false; // controlls printing so the screen doesn't print the output many times
            bool firstBootup = true;// displays menu only if the device has just been turned on. 
            char input = 'x'; // used to select options from main menu of encryption algorithm. 
// Encryption Program Description:
        // The menu asks if the user wishes to decrypt or encrypt data. The menu is where the user loops back to. 
            // input 
                // a series of characters that the user provides.
            // processing 
                // take the ASCII value of each character and multiply it by the encryption key variable; store it in the data array. 
                // note: limited to 312 terms.  
                // decryption: divide each integer by the encryption key; store it in the data[] array. 
            // output
                // the encrypted data as integers, output char at a time. 
                // decryption: the decrypted data as chars, output 1 char at a time. 
                // a value showing where the computer is at decrypting in the array. 
// Brute Force Program Description
//        1. Uses all possible characters or a set of characters to determine all possible combinations, and guess your password you enter. 
//        2. Will return: your password (calculated), will print all combinations possible given a password length and set of characters, number of possible combinations
// HOW DOES IT WORK?
          // it uses a base 94 system as of 2.24.2024. This is because there are 94 possible characters on the keyboard. The computer starts with choosing entry  0 in every single slot of the password. 
          // it then increases the right most character of the password by 1 index entry, so it would go from 'a' to 'b' (Increase from entry [0] to Entry [1])
          // Each place in the password has one of these counters. 
          // when one of the counters is maxed out - it equals the library size. 
          // When a counter goes above 94, it is set to zero. The counter to its LEFT is increased by 1. 
          // in this way, the computer 'counts' in a base 94 system, which has 94 'numbers', each represented by a symbol aA - zZ, 0 - 9, and all special characters. 
          // Somehow, this generates every single possible combination without repeating. 
          // BENEFITS
                    // starts with a single character, and increases until it reaches the maximum size, that way, it guesses all combinations for a 1 character password and then a 2 character password and so on, until it reaches 8 
// BELOW: BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES 
            float numPossibleCombinations = 0;
            // the library of characters from which the computer chooses. aA - bB, 0 - 9, all special characters, and space. 
            char possibleCharacters[] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 
                                          'h', 'i', 'j', 'k', 'l', 'm', 'n', 
                                          'o', 'p', 'q', 'r', 's', 't', 'u', 
                                          'v', 'w', 'x', 'y', 'z', 'A', 'B', 
                                          'C', 'D', 'E', 'F', 'G', 'H', 'I', 
                                          'J', 'K', 'L', 'M', 'N', 'O', 'P', 
                                          'Q', 'R', 'S', 'T', 'U', 'V', 'W', 
                                          'X', 'Y', 'Z', '0', '1', '2', '3', 
                                          '4', '5', '6', '7', '8', '9', ',', 
                                          '`', '|', '"', '}', '{', '[', ']', 
                                          '(', ')', '!', '#', '.', ';', '?', 
                                          '$', '=', '*', '^', '+', '/', '-', 
                                          ':', '>', '<', '_', '&', '%', '@', 
                                          '~', '\\', '\''
                                        }; 

            // READ: these variables control the entry from 'possibleCharacters' the computer chooses. 
                  int onesPlace = 0; // placeholder for the rightmost character in the password. 
                  int twosPlace = 0; 
                  int threesPlace = 0;  
                  int foursPlace = 0; 
                  int fivesPlace = 0; 
                  int sixthsPlace = 0; 
                  int seventhsPlace = 0; 
                  int eighthsPlace = 0; // placeholder for the leftmost character in the password
            int passwordLength = 0; // the length of the password the computer tries to guess.  
            double librarySize = 95; // the size of the library. This also controlls the overflow from 1 place value to the next highest.
            String passwordToGuess = ""; // the password the computer is trying to guess. 
            String guessedPassword = ""; // the current guess the computer has generated. 
            int BruteMenuSelector = 0; 
            bool showOptions = false; // true = display brute mini menu, otherwise don't. 
            bool stopGuess = false; // controls guessing hte password loop. 
            double numCalculations = 0; 
            double possibleCombinations; 
            double percentComplete = numCalculations / possibleCombinations; 
            String inputString; // used for changing password to guess
            bool twosGuessed = false; 
            bool threesGuessed = false; 
            bool foursGuessed = false; 
            bool fivesGuessed = false; 
            bool sixthsGuessed = false; 
            bool seventhsGuessed = false; 
            bool eighthsGuessed = false; 
            double passwordsGuessed = 0; 
// ABOVE: BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES BRUTE FORCE VARIABLES 

void setup() {
  // accept input through the keyboard
  Serial.begin(115200); 
  tft.init();
  tft.setRotation(1);
  tft.setCursor(0,0);
  tft.setTextSize(2); 
  tft.setTextPadding(2); 
  tft.setTextColor(TFT_WHITE);
  tft.fillScreen(TFT_BLACK); 
}

void loop() {
switch(menuSelector) {
  // the menu
  case 0:
    if(firstBootup == true) {
      firstBootup = false; 
      tft.init(); 
      tft.fillScreen(TFT_BLACK);
      tft.setTextSize(2); 
      tft.setCursor(0,0);
      tft.println("Menu:"); 
      tft.println("a - Encrypt");       // 1
      tft.println("b - Decrypt");       // 2
      tft.println("c - Restart");       // 3
      tft.println("d - Change Key");    // 4
      tft.println("e - See Commands"); // 5
      tft.println("f - Send Cipher to Serial Monitor");
      tft.println("g - Graph CipherText");
      tft.println("h - Brute Force");
      tft.print("Your current key is: ");
      tft.print(encryptionKey);  
    }
        if(Serial.available()) {
          input = Serial.read();
          switch(input) {
            case 'a':
                      tft.init();
                      tft.fillScreen(TFT_BLACK);
                      tft.setCursor(30,0); 
                      tft.setRotation(1);
                      tft.setTextSize(1); 
                      tft.setTextPadding(2); 
                      tft.setTextColor(TFT_WHITE);
                      // encryption instructions. 
                      tft.println("Type characters into the serial monitor.");
                      tft.println("They will be ouput on the TFT as the ASCII value times the encryption key. The $, the #, the *, and the ^ will all be ignored and not placed into the ciphertext."); 
                      tft.print("You have typed ");
                      tft.print(numInputs);
                      tft.print(" of ");
                      tft.print(dataSize); 
                      tft.println("Type a ^ to see number of remaining characters.");  
                      menuSelector = 1;
            break;

            case 'b':
                      // user can return home from here. 
                      if(Serial.available()) {
                            if(Serial.read() == '*') {
                              menuSelector = 0; 
                              tft.init(); 
                              tft.fillScreen(TFT_BLACK);
                              tft.setCursor(0,0);
                              tft.println("Menu:"); 
                              tft.println("a - Encrypt");      // 1
                              tft.println("b - Decrypt");      // 2
                              tft.println("c - Restart");      // 3
                              tft.println("d - Change Key");   // 4
                              tft.println("f - Send Cipher to Serial Monitor");
                              tft.println("g - Graph CipherText");
                              tft.print("Your current key is: ");
                              tft.print(encryptionKey); 
                            }
                      }
                      // data appears to be empty
                      if(data[3] == 1 || data[3] == 0) {
                        tft.init();
                        tft.fillScreen(TFT_BLACK);
                        tft.setCursor(0,0);
                        tft.setRotation(1);
                        tft.setTextSize(2); 
                        tft.setTextPadding(2); 
                        tft.setTextColor(TFT_WHITE);
                        tft.println("NO DATA:"); 
                        int h; 
                        for(h = 0; h < 50; h++) {
                          tft.print(data[h]); 
                          tft.print(" ");
                        } 
                        // give user time to respond. 
                        delay(2000);
                        firstBootup = true;
                        menuSelector = 0;
                        
                      } 
                      // data appears to be in array. 
                      if(data[3] != 1 || data[3] != 0) {
                        tft.init();
                        tft.fillScreen(TFT_BLACK);
                        tft.setCursor(0,pageY);
                        tft.setRotation(1);
                        tft.setTextSize(1); 
                        tft.setTextPadding(2); 
                        tft.setTextColor(TFT_WHITE);
                        for(decryptPosition = 0; decryptPosition < numInputs; decryptPosition++) {
                            // copy the encrypted data to where it will be decrypted
                            // this step also decrypts. 
                            decryptedData[decryptPosition] = data[decryptPosition] / encryptionKey;
                            DecryptedString += char(decryptedData[decryptPosition]);
                        }
                      menuSelector = 2;
                      tft.print(DecryptedString); 
                      tft.println("Use * to go home."); 
                      }
            break;

            case 'c':
                      tft.init();
                      tft.fillScreen(TFT_BLACK);
                      tft.setCursor(0,0);
                      tft.setRotation(1);
                      tft.setTextSize(0.3); 
                      tft.setTextPadding(2); 
                      tft.setTextColor(TFT_WHITE);
                      menuSelector = 3; 
            break;

            case 'd': // user wishes to change the cipher key. 
                      tft.init(); 
                      tft.setCursor(0,0); 
                      tft.fillScreen(TFT_BLACK); 
                      tft.setRotation(1);
                      tft.setTextSize(0.3); 
                      tft.setTextPadding(2); 
                      tft.setTextColor(TFT_WHITE);
                      tft.println("Change Encryption Key"); 
                      tft.println("The current key is: ");
                      tft.print(encryptionKey); 
                      //tft.println("Enter new key:"); 
                      tft.println("Note: must be a number from 1 - 32768. High numbers are risky because the key multiplied by the text could be over this range. This will likely cause errors.");
                      //tft.println("The first number will be ignored. To set the key to 100, you would have to type 1100."); 
                      tft.println("Press 'aaa' to increase the key. Press 'bbb' to decrement the key.");
                      tft.println("Typing something like 'aaaaaaaaaaaaaaaaaaaaaaaa' is allowed too.") ;
                      menuSelector = 4; 
            break;

            case 'e':
                      tft.init(); 
                      tft.setTextSize(2); 
                      tft.setCursor(0,0); 
                      tft.fillScreen(TFT_BLACK); 
                      tft.setRotation(1);
                      tft.setTextPadding(2); 
                      tft.setTextColor(TFT_WHITE);
                      tft.println("Use * at any time to go home.");  
                      tft.println("$ = Scroll Up");
                      tft.println("# = Scroll Down");
                      tft.println("Encryption only: ^ = See remaining characters in the ciphertext");
                      menuSelector = 5; 
            break;

            case 'f': // user wants to send the cipher text into the serial monitor
                      tft.init();
                      tft.fillScreen(TFT_BLACK);
                      tft.setCursor(0,0);
                      tft.setRotation(1);
                      tft.setTextSize(2); 
                      tft.setTextPadding(2); 
                      tft.setTextColor(TFT_WHITE);
                      tft.println("Printing CipherText . . "); 
                      tft.setTextSize(0.3); 
                      for(i = 0; i < numInputs; i++) {
                        // print through the data, put it on the serial monitor. 
                            Serial.println(data[i]); 
                            tft.print(data[i]); 
                            tft.print(" "); 
                      }
                      tft.println("Done!"); 
                      menuSelector = 7;
            break;

            case 'g': // user wishes to print out a visual representation of the ciphertext.
                      // reset screen. 
                      tft.init();
                      tft.fillScreen(TFT_BLACK);
                      tft.setCursor(0,0);
                      tft.setRotation(1);
                      tft.setTextSize(1); 
                      tft.setTextPadding(2); 
                      tft.setTextColor(TFT_BLUE);
                      x = 0; 
                      y = 0; 
                      // height of the line
                        height = encryptionKey / 2; // used to draw pixels that represent the data. 
                      // outer for loop controls the x axis. This also controls spot in the data[]
                      // inner for loop controls the height of the line.
                      for(x = 0; x < 480; x++) {
                        for(y = 0; y < abs(data[x]); y++) {
                          tft.drawPixel(x, abs(y/height), TFT_WHITE); 
                        }
                      } 
                      
                      for(x = 0; x < 480; x++) {
                        for(y = 0; y < abs(data[x]/encryptionKey); y++) {
                          // draw different colored pixels if it's a vowel
                          switch(abs(data[x]/encryptionKey)) {
                              // a
                              case 97:
                                      tft.drawPixel(x, abs(y/height), TFT_RED); 
                                      break;
                              // A
                              case 65: 
                                      tft.drawPixel(x, abs(y/height), TFT_RED); 
                                      break;
                              // e
                              case 101:
                                      tft.drawPixel(x, abs(y/height), TFT_ORANGE); 
                                      break;
                              // E
                              case 69: 
                                      tft.drawPixel(x, abs(y/height), TFT_ORANGE); 
                                      break;
                              // i
                              case 105:
                                      tft.drawPixel(x, abs(y/height), TFT_MAGENTA); 
                                      break;
                              // I
                              case 73:
                                      tft.drawPixel(x, abs(y/height), TFT_MAGENTA); 
                                      break; 
                              // o
                              case 111:
                                      tft.drawPixel(x, abs(y/height), TFT_GREEN); 
                                      break;
                              // O
                              case 79:
                                      tft.drawPixel(x, abs(y/height), TFT_GREEN);
                                      break; 
                              // u
                              case 117:
                                      tft.drawPixel(x, abs(y/height), TFT_BLUE); 
                                      break;
                              // U
                              case 85:
                                      tft.drawPixel(x, abs(y/height), TFT_BLUE); 
                                      break; 
                              // draw a dark cyan pixel if it's not a vowel
                              default: tft.drawPixel(x, abs(y/height), TFT_DARKCYAN); 
                                      break;
                          }
                        }
                      }
                      tft.setCursor(0,240);
                      tft.setTextColor(TFT_WHITE); 
                      tft.println("Cipher Text - White");
                      tft.println("A = red");
                      tft.println("E = orange"); 
                      tft.println("I = Magenta");
                      tft.println("O = Green"); 
                      tft.println("U = Blue");  
                      tft.setTextSize(2); 
                      tft.println("Use '*' to go home.");
                      menuSelector = 8; 
            break;
            
            // user chooses brute force algorithm
            case 'h':
                      tft.println("Redirecting . . . "); 
                      tft.init();
                      tft.fillScreen(TFT_BLACK);
                      tft.setCursor(0,0);
                      tft.setRotation(1);
                      tft.setTextSize(2); 
                      tft.setTextPadding(2); 
                      tft.setTextColor(TFT_WHITE);
                      tft.println("-----BRUTE FORCE CALCULATOR MENU-----"); 
                      // display menu options for brute force calculator
                      tft.println("a - Set Password"); 
                      tft.println("b - Show Library"); 
                      tft.println("c - Calculate Number Combinations"); 
                      tft.println("d - Show Possible Combinations");
                      tft.println("e - Guess my Password"); 
                      tft.println("f - Main Menu"); 
                      tft.println("g - Change Library Size");
                      menuSelector = 9; 
            break;

            default: // the catch all for user input error in the menu. 
            break;
          }
        }
  break;

  case 1: // user wishes to encrypt
          if(Serial.available()) {
                incomingByte = Serial.read();
          } 
          // user cannot go over data size
          if(Serial.available() && incomingByte != 36 && incomingByte != 35 && incomingByte != 94) {
            // the user has started typing, so start encrypting:
            // The $, the #, the *, and the ^ will all be ignored and not placed into the ciphertext.
            if(numInputs < dataSize && dataIndex < dataSize && cursorIndex < dataSize) {   
              int theOutPut = incomingByte * encryptionKey;
              numInputs++; // the amount of types the user has given input, total. 
              dataIndex++; // the place in the array the user is modifying. 
              data[dataIndex] = theOutPut; // assign at the current index the data that has been encrypted. 
            }  else {
              // user has used up all data spots in array. 
              tft.init(); 
              tft.fillScreen(TFT_BLACK);
              tft.setCursor(0,0);
              tft.println("You have used up all your space. See below:");
              tft.println("NumInputs:");
              tft.println(numInputs);
              tft.println("DataIndex:");
              tft.println(dataIndex);
              tft.println("CursorIndex:");
              tft.println(cursorIndex); 
              tft.println("Enter an '*' to go home.");
              tft.println("Choose option 'c' in the menu. This flushes the encryption memory.");
              menuSelector = 6; 
            }
          }
          // user can see how many characters they have left
          if(incomingByte == 94) {
              tft.setCursor(100,0); 
              tft.fillRect(100, 0, 200, 30, TFT_BLACK);
              tft.print("You have typed ");
              tft.print(numInputs);
              tft.print(" of ");
              tft.print(dataSize); 
            }
          // user has chosen to exit
          if(incomingByte == 42) {
            // the user has chosen to exit. 
            menuSelector = 0; 
            firstBootup = true; 
          }   
          if(incomingByte == 36) {
            if(pageNumber <= arraySize-pageSize) {
              pageNumber+=10;  
              Serial.println("Page #: "); 
              Serial.println(int(pageNumber)); 
              print = true;
            } else {
              tft.println("End of file: ");
              tft.println(pageNumber); 
            }
          } 
          if(incomingByte == 35) {
            if(pageNumber > 1 ) {
              pageNumber-=10;  
              Serial.println("Page #: "); 
              Serial.println(int(pageNumber)); 
              print = true;
            } else {
              tft.println("End of file. Page #: ");
              tft.println(pageNumber);
            }
          } 
          // print the enrypted data.
          if(print == true) {	
            tft.setCursor(0,0); 
            tft.fillScreen(TFT_BLACK); 
            for(i = 0; i <= pageSize; i++) {
              // don't print 0's or 1's:
              if(data[pageNumber+i] != 0 && data[pageNumber+i] != 1) {
                  tft.print(data[pageNumber+i]);
                  tft.print(" ");
              } 
            }
            tft.println(""); 
            tft.print("Page #: ");
            tft.print(pageNumber/10); 
            print = false;
          }
  break;

  case 2: // user wishes to decrypt
      incomingByte = Serial.read(); 
                //cursorIndex = 0;
                tft.setCursor(30,pageY);
                      // scrolling through the decrypted text
                                  // user scrolls down by entering a $
                                  if(incomingByte == 36) {
                                    // scroll the page, all the while ensuring that the user knows which way its going
                                    // refreshing the screen so it doesn't smear
                                      pageY+=100;
                                      tft.fillScreen(TFT_BLACK); 
                                          // print out the numbers, and change them using char() into letters. 
                                          for(i = 0; i < numInputs; i++) {
                                              char character = char(decryptedData[i]);
                                              tft.print(character);
                                              // "move" the cursor
                                              cursorIndex++;
                                              }
                                  }
                                  // user scrolls up by entering a #
                                  if(incomingByte == 35) {
                                      // scroll the page, all the while ensuring that the user knows which way its going
                                      // refreshing the screen so it doesn't smear
                                        pageY-=100; 
                                        tft.fillScreen(TFT_BLACK); 
                                          // print out the numbers, and change them using char() into letters. 
                                          for(i = 0; i < numInputs; i++) {
                                              char character = char(decryptedData[i]);
                                              tft.print(character);
                                              // "move" the cursor
                                              cursorIndex++;
                                              }
                                  }
                          // user can return home from here.  
                            if(incomingByte == 42) {  
                              menuSelector = 0;
                              tft.init(); 
                              tft.fillScreen(TFT_BLACK);
                              tft.setCursor(0,0);
                              tft.setTextSize(2); 
                              tft.println("Menu:"); 
                              tft.println("a - Encrypt");      // 1
                              tft.println("b - Decrypt");      // 2
                              tft.println("c - Restart");      // 3
                              tft.println("d - Change Key");   // 4
                              tft.println("f - Send Cipher to Serial Monitor");
                              tft.println("g - Graph CipherText"); 
                              tft.print("Your current key is: ");
                              tft.print(encryptionKey); 
                            }
                          
  break;

  case 3: // user wishes to restart
    pageY = 40; 
    numInputs = 0; 
    dataIndex = 0; 
    cursorIndex = 0; 
    decryptPosition = 0; 
    // wipe the encryption array and decryption array, by assigning all values to be 1's. 
    wipeIndex = 0; // used to loop through the arrays and delete the data. 
      // wipe decrypted array
      for(wipeIndex = 0; wipeIndex < dataSize; wipeIndex++) {
        if(wipeIndex == 0) {
          tft.println("Wiping the decrypted array:");
        }
        decryptedData[wipeIndex] = 1; 
        // rect used as loading bar
        tft.fillRect(wipeIndex / 20, 0, 1, 10, TFT_WHITE); 

      }
      // this x variable makes the loading bar move.
    // wipe encrypted array
      for(wipeIndex = 0; wipeIndex < dataSize; wipeIndex++) {
        // rect used as loading bar
        tft.fillRect(wipeIndex / 20, 20, 1, 10, TFT_WHITE);  
        // wipe the data
        data[wipeIndex] = 1;
      }
    menuSelector = 0;
    firstBootup = true; 
  break;

  case 4: // user wishes to change the encryption key 
              // the user enters letter to increment or decrement the key. 
              if(Serial.available()) {
                  incomingByte = Serial.read();
                char input = char(Serial.read()); 
                // increment
                if(input == 'a') {
                  encryptionKey++;
                  tft.print("   Increased to: "); 
                  tft.print(encryptionKey); 
                }
                // decrement
                  if(input == 'b') {
                    encryptionKey--;
                    tft.print("   Decreased to: "); 
                    tft.print(encryptionKey); 
                }
                // user selects to go home by entering an *
                if(incomingByte == 42) {
                          menuSelector = 0; 
                          tft.init(); 
                          tft.fillScreen(TFT_BLACK);
                          tft.setCursor(0,0);
                          tft.setTextSize(2); 
                          tft.println("Menu:"); 
                          tft.println("a - Encrypt");      // 1
                          tft.println("b - Decrypt");      // 2
                          tft.println("c - Restart");      // 3
                          tft.println("d - Change Key");   // 4
                          tft.println("e - See Commands");   
                          tft.println("f - Send Cipher to Serial Monitor");
                          tft.println("g - Graph CipherText");
                          tft.print("Your current key is: ");
                          tft.print(encryptionKey); 
                      }
              }
  break;

  case 5:// user is looking at the commands they can use. 
    if(Serial.available()) {
      incomingByte = Serial.read(); 
    }
                                  if(incomingByte == 42) {
                                      // the user has chosen to exit. 
                                      menuSelector = 0; 
                                      tft.init(); 
                                      tft.fillScreen(TFT_BLACK);
                                      tft.setCursor(0,0);
                                      tft.println("Menu:"); 
                                      tft.println("a - Encrypt");      // 1
                                      tft.println("b - Decrypt");      // 2
                                      tft.println("c - Restart");      // 3
                                      tft.println("d - Change Key");   // 4
                                      tft.println("e - See Commands");
                                      tft.println("f - Send Cipher to Serial Monitor");
                                      tft.println("g - Graph CipherText");
                                      tft.print("Your current key is: ");
                                      tft.print(encryptionKey); 
                                  }
  break;

  case 6: // the user has run out of space. 
                              if(Serial.available()) {
                                incomingByte = Serial.read(); 
                                  if(incomingByte == 42) {
                                    firstBootup = true; 
                                    menuSelector = 0;
                                  }
                              }
  break;

  case 7: // user wishes to send the ciphertext over the serial monitor
      // user can go home by pressing asterisk. 
      if(Serial.available()) {
        incomingByte = Serial.read(); 
          if(incomingByte == 42) {
            menuSelector = 0; 
            firstBootup = true; 
          }
      }
  break; 

  case 8: // user wishes to map out the ciphertext visually. 
          // this screen will print out different lengths of lines which represent the numerical value of the ciphertext character. 
      // user can go home by pressing asterisk. 
      if(Serial.available()) {
        incomingByte = Serial.read(); 
          if(incomingByte == 42) {
            menuSelector = 0; 
            firstBootup = true; 
          }
      }
  break; 

  // brute force algorithm loop
  case 9: 
          // displays mini menu for Brute Force Algorithm each time the user comes back to it by using an asterisk 
          if(showOptions == true) {
            tft.init();
            tft.fillScreen(TFT_BLACK);
            tft.setCursor(0,0);
            tft.setRotation(1);
            tft.setTextSize(2); 
            tft.setTextPadding(2); 
            tft.setTextColor(TFT_WHITE);
            tft.println("-----BRUTE FORCE CALCULATOR MENU-----"); 
            // display menu options for brute force calculator
            tft.println("a - Set Password"); 
            tft.println("b - Show Library"); 
            tft.println("c - Calculate Number Combinations"); 
            tft.println("d - Show Possible Combinations");
            tft.println("e - Guess my Password"); 
            tft.println("f - Main Menu"); 
            tft.println("g - Change Library Size"); 
            showOptions = false;
          }            

        incomingByte = Serial.read();
        // listen for user's choice in the Brute force menu, display the text 1 time, or perform chosen action 1 time and go to another screen so it doesn't loop. 
        switch (incomingByte) {
            case 'a': // Set Password to Guess, 
                      // sets BruteMenuSelector to 0
                        tft.init();
                        tft.setRotation(1);
                        tft.setCursor(0,0);
                        tft.setTextSize(2); 
                        tft.setTextPadding(2); 
                        tft.setTextColor(TFT_WHITE);
                        tft.fillScreen(TFT_BLACK); 
                        tft.println("Enter the password you wish to crack: "); 
                        tft.println("* = Go Home"); 
                        tft.setTextSize(1); 
                        tft.setTextColor(TFT_ORANGE); 
                        tft.println("Note: Password must be only 8 characters long. Asterisk Will send you home, so don't make a password with an asterisk."); 
                        BruteMenuSelector = 0; 
                        menuSelector = 10; 
            break;

            case 'b': // Print Library
                        tft.init(); 
                        tft.setCursor(0,0); 
                        tft.fillScreen(TFT_BLACK); 
                        tft.setTextSize(2);  
                        tft.println("Printing all characters in library:"); 
                        tft.setTextSize(2); 
                        tft.setTextColor(TFT_MAGENTA); 
                        // print the entire  library for debugging.
                        for(i = 0; i < librarySize; i++) {
                            tft.print(possibleCharacters[i]);
                            tft.print("  ");  
                          }; 
                          tft.println(); 
                          tft.setTextColor(TFT_WHITE);
                          tft.println("Done!"); 
                          tft.println("* = Go Home"); 
                          BruteMenuSelector = 1;
                          menuSelector = 10;
                      // -----
            break;

            case 'c': // Calculate # of possible Combinations
                      tft.init(); 
                      tft.setCursor(0,0); 
                      tft.fillScreen(TFT_BLACK); 
                      tft.setTextSize(2);  
                      tft.setCursor(0,0); 
                      tft.setTextSize(2); 
                      tft.println("* = Go Home"); 
                      tft.println("Number of Possible calculations is "); 
                      tft.print(librarySize);
                      tft.print(" ^ 8"); 
                      tft.println(); 
                      possibleCombinations = pow(librarySize, 8);
                      tft.print(possibleCombinations);
                      BruteMenuSelector = 2; 
                      menuSelector = 10;
            break;

            case 'd': // Show Possible Combinations
                      tft.init(); 
                      tft.setCursor(0,0); 
                      tft.fillScreen(TFT_BLACK); 
                      tft.setTextSize(2);  
                      tft.setCursor(0,0); 
                      tft.setTextSize(2); 
                      tft.println("* = Go Home"); 
                      onesPlace = 0; 
                      twosPlace = 0; 
                      threesPlace = 0; 
                      foursPlace = 0; 
                      fivesPlace = 0; 
                      sixthsPlace = 0; 
                      seventhsPlace = 0; 
                      eighthsPlace = 0; 
                      BruteMenuSelector = 3; 
                      menuSelector = 10;
                      possibleCombinations = pow(librarySize, 8.00); 
                      passwordsGuessed = 0; 
                      // guess the password as long as 'stopguess' is false. 
                      while (stopGuess == false) {
                        // increase counter by 1
                        onesPlace+=1; 
                        checkPassword(); 
                        passwordsGuessed ++; 
                        // keep track of the number of calculations
                        numCalculations+=1; 
                        // Show how close till done
                        //percentComplete =  (numCalculations / possibleCombinations)*10;
                        if(onesPlace > librarySize) {
                          twosPlace+=1; 
                          onesPlace = 0; 
                          twosGuessed = true;// bool set to true which allows "checkPassword()" to append it to the guessed password.
                          checkPassword(); 
                        }

                        if(twosPlace > librarySize) {  
                          twosPlace = 0; 
                          threesPlace += 1; 
                          threesGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          checkPassword(); 
                        }

                        if(threesPlace > librarySize) {
                          threesPlace = 0; 
                          foursPlace +=1; 
                          foursGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          checkPassword(); 
                        }

                        if (foursPlace > librarySize) {
                          fivesGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          foursPlace = 0; 
                          fivesPlace +=1; 
                          checkPassword(); 
                        }

                        if(fivesPlace > librarySize) {
                          sixthsGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          fivesPlace = 0; 
                          sixthsPlace +=1; 
                          checkPassword(); 
                        }

                        if(sixthsPlace > librarySize) {
                          seventhsGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          sixthsPlace = 0; 
                          seventhsPlace += 1; 
                          checkPassword(); 
                        }

                        if (seventhsPlace > librarySize) {
                          eighthsGuessed = true; // bool set to true which allows "checkPassword()" to append it to the guessed password. 
                          seventhsPlace = 0; 
                          eighthsPlace +=1; 
                          checkPassword(); 
                        }

                        if(eighthsPlace > librarySize) {
                          stopGuess = true;
                          Serial.println("Stopping."); 
                        } 
                        checkPassword(); 
                      }
            break;

            case 'e': // Guess my password
                      tft.init(); 
                      tft.setCursor(0,0); 
                      tft.fillScreen(TFT_BLACK); 
                      tft.setTextSize(2);  
                      tft.setCursor(0,0); 
                      tft.setTextSize(2); 
                      tft.println("* = Go Home"); 
                      BruteMenuSelector = 4;
                      menuSelector = 10;
            break;

            // user wants to return to main menu
            case 'f':
                    menuSelector = 0; 
                    firstBootup = true; 
            break;

            // user wants to change library size
            case 'g':
                    
                      tft.init(); 
                      tft.setCursor(0,0); 
                      tft.fillScreen(TFT_BLACK); 
                      tft.setTextSize(2);  
                      tft.setCursor(0,0); 
                      tft.setTextSize(2); 
                      tft.println("* = Go Home"); 
                      tft.setTextSize(1); 
                      tft.println("Enter a number into the Serial Monitor to change the library size"); 
                      BruteMenuSelector = 5; 
                      menuSelector = 10; 
            break;
        }
  break;

  // Where the user goes from the Brute Force Menu, using BruteMenuSelector. At this point the calculations should be done already and the user just can choose to go home from here. 
  // BUT this is usually where we loop to get info as well. 
  case 10: 
        switch (BruteMenuSelector) {
            // User comes here from 'Set Password to Guess' 
            case 0: 
                  Serial.flush();
                  if(Serial.available()) {
                    // read the first character
                    incomingByte = Serial.read(); 
                    // check if the first character is '*', indicating a request to go home
                    if(incomingByte == 42) {
                        menuSelector = 9;
                        showOptions = true; 
                    } else {
                      // include the first character in the password 
                      passwordToGuess = String(incomingByte);
                      // read the rest of the characters in the serial buffer
                      while(Serial.available()) {
                          incomingByte = Serial.read();
                          passwordToGuess += String(incomingByte); // append each character to the string
                      } 
                      // trim newline characters and whitespace from the password:
                      passwordToGuess.trim(); 
                      // display the entered password
                      tft.println("Password to Crack: "); 
                      tft.println(passwordToGuess);
                      tft.println("Length: "); 
                      tft.println(String(passwordToGuess.length()));
                    }
                }
            break;

            // user comes here from 'print library'
            case 1:
                  // user can return to Brute Home from here.
                  if(Serial.available()) {
                  incomingByte = Serial.read(); // go home using asterisk
                  if(incomingByte == 42) {  
                    menuSelector = 9;
                    showOptions = true; 
                  }
          }
            break;
            
            // user comes here from 'calculate # of possible combinations'
            case 2:
                  // user can return to Brute Home from here.

                  if(Serial.available()) {
                  incomingByte = Serial.read(); // go home using asterisk
                  if(incomingByte == 42) {
                    menuSelector = 9;
                    showOptions = true;   
                  }
          }
            break;

            // user comes here from 'show possible combinations'
            case 3:
                  // user can return to Brute Home from here.

                  if(Serial.available()) {
                  incomingByte = Serial.read(); // go home using asterisk
                  if(incomingByte == 42) {
                    menuSelector = 9;
                    showOptions = true; 
                    stopGuess = false; 
                  }
          }
            break;

            // user comes here from 'guess my password'
            case 4:
                  // user can return to Brute Home from here.
                  if(Serial.available()) {
                    incomingByte = Serial.read(); // go home using asterisk
                    if(incomingByte == 42) {
                      menuSelector = 9;
                      showOptions = true;  
                    }
                  }
            break;
            
            // user comes here from "change library size"
            case 5:
                  // user can return to Brute home form here and change the library size. 
                  if(Serial.available()) {
                    incomingByte = Serial.read(); // go home using asterisk
                    if(incomingByte == 42) {
                      menuSelector = 9;
                      showOptions = true;  
                    }
                  // user can change library size:
                  if(incomingByte == 'a' && librarySize < 94) {
                    librarySize += 1; 
                    tft.print("Library Size Changed: "); 
                    tft.print(librarySize); 
                  }

                  if(incomingByte == 'b' && librarySize > 1) {
                    librarySize -=1; 
                    tft.print("Library Size Changed: "); 
                    tft.print(librarySize); 
                  }
                  }
            break;
        }
  break;
}
}

void checkPassword() {
  guessedPassword="";                 
  // only add the letters to the guessed password if they haven't been changed yet. 
  guessedPassword+=possibleCharacters[onesPlace];
  if(twosGuessed == true) { guessedPassword+=possibleCharacters[twosPlace];}
  if(threesGuessed == true) {guessedPassword+=possibleCharacters[threesPlace];}
  if(foursGuessed == true) {guessedPassword+=possibleCharacters[foursPlace];}
  if(fivesGuessed == true) {guessedPassword+=possibleCharacters[fivesPlace];}
  if(sixthsGuessed == true) {guessedPassword+=possibleCharacters[sixthsPlace];}
  if(seventhsGuessed == true) {guessedPassword+=possibleCharacters[seventhsPlace];}
  if(eighthsGuessed == true) {guessedPassword+=possibleCharacters[eighthsPlace];} 
  // update the user on the number of guesses
  if(passwordsGuessed > 1000000) {
    passwordsGuessed = 0; 
    Serial.print("Guessed ");
    Serial.print(numCalculations);
    Serial.print(" times: Current Password: "); 
    Serial.print(guessedPassword); 
    Serial.println(); 
  }
  if(guessedPassword.equals(passwordToGuess)) {
    stopGuess = true; 
    Serial.println("Is your password "); 
    Serial.println(guessedPassword); 
  }
}