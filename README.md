## wordez
Clone of a popular word game written in C++. Take 5 Turns to guess a 5 letter randomly selected word. Each guess is evaluated, if the word is spelt correctly, the result is given by color coding the guess's letters. Green, if the letter is in the word and in the right place, Yellow, if the letter is in the word but not in the correct location and grey, when the letter is not in the word. The keyboard letters are also updated with the color coding to help aid follow on guesses. Incorrectly spelt words will shake for a second. 

The game ends when either the word is correctly guessed and all letters are green, or all the turns are used up. 

At the end of the game there is an option to copy the game result to the clipboard, and a second option to restart the game.

## Setup & Build
The game was developed, built and tested in an Ubuntu Linux environment. While build instructions are provided for the Mac and Windows, the project was not bulit or tested on those platforms and happy to receive feedback from those platform developers.
# Dependencies
* cmake >= 3.11
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](https://sourceforge.net/projects/mingw/)
* wxWidgets >= 3.0
  * Linux: `sudo apt-get install libwxgtk3.0-gtk3-dev libwxgtk3.0-gtk3-0v5`. Refer to the [official page](https://wiki.codelite.org/pmwiki.php/Main/WxWidgets30Binaries#toc2) for installing the unmet dependencies.
  * Mac: Using homebrew to install `brew install wxwidgets` https://formulae.brew.sh/formula/wxwidgets
  * Installation instructions can be found [here](https://wiki.wxwidgets.org/Install). Recommend [wxPack](https://github.com/rjpcomputing/wxpack/wiki) which includes gcc and wxwidgets.

## Word list word.txt
Linux contains a collections of words that are derived from scowl http://wordlist.aspell.net/scowl-readme/ The license within the readme allows use and redistribution and is included in the repository. A subset of these collections is generated from linux using the instructions at https://leancrew.com/all-this/2022/01/wordle-letters/
For an american wordlist of 5 characters use:
`perl -nle 'print if /^[a-z]{5}$/' /usr/share/dict/american-english > words.txt`
The word list is used to randomly select a target word and also to evaluate the guesses for spelling.
Additional words may be manually added or removed from the list.

## Keyboard file kb.txt
A file containing a list of ascii characters grouped by the row they should appear on the keyboard. Enter is character 10 and Backspace is character 8. The game uses Capital letters only.

## Build Instructions
1. Clone this repo. `git clone https://github.com/andrewparry/wordez.git`
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Ensure word.txt and kb.txt are in the top level directory
5. Run it: `./wordez`.

## Project Structure
* The project utlizes wxWidgets for the GUI capabilities. This is suitable for this type of game which is driven by key press and button click events.
* Multiple classes make up the structure of the application, each class is extensively documented. In Summary:
  * Wordezapp     The main wxwidgets class for the app.
  * WordezFrame   Inherited from the wxwidgets wxFrame class, the top-level frame for the game UI objects and events. This class creates a raw Game object for a new game.
  * Game          The Game class controlling the game logic.
    * Creates smart pointer to a Dictionary Object to manage the word functions.
    * Creates a wxPanel to display the game Turns, Buttons and Keyboard.
    * Creates a vector of Turn objects. A game is made up of 6 Turns. The Game class also tracks the current game Turn, evaluating completed guesses.
    * Creates 2 hidden wxButtons for the End Game options - Copy the clipboard of the game result and Restart the game by calling back to the parent WordezFrame object
    * Creates a Keyboard object of buttons and events, 
  * Turns         A Turn is made up of a Vector of Letter Objects, 5 Letters make up a word. The current Turn will also track the current Letter for the next input. Each Turn object tracks the result of its guess for the clipboard summary at the end of the game.
  * Letter        The Letter class holds the current letter value and is updated from the latest key press. This class also draws each letter tile that makes up a turn and updates the background color based on the result of a guess.
  * Keyboard     Inherited from wxPanel, this class, loads a vector of keys from the kb.txt file, creates a grid of wxButtons, and the enables the relevant on click and key press events. Those events will callback the main Game object. 
  * Dictionary    Class of word functions. Loads a vector of words from the word.txt file, selects the target word, and evaluates guesses, generating a result vector.

  The game is driven by keyboard and mouse events. The Keyboard class calls the character of a key/mouse event to the Game object through a callback function. If the key is an alpha, the current letter is updated with a key, and the next letter in the turn becomes active waiting for a key. Backspace will correctly clear the relevant value and change the active letter. When a turn is complete and the enter key is pressed, the word will be evaluated for correct spelling, and then the result is updated and game logic progresses to the next turn, until the end of game.

## Additional files
- icon.png - Application icon

## Addressing the Rubic
  * **README.md** - Completed the 6 criteria for the readme.
  * **Compiling and Testing** - Utilizes cmake and make, developed, built and tested succesfully on a Linux Ubuntu environment.
  * **1. The project demonstrates an understanding of C++ functions and control structures.** Please review game.cpp file as an example of a class utilizing various control structures and broken down by functions.
  * **2. The project reads data from a file and process the data, or the program writes data to a file.** Please review dictionary.cpp class file, line 24, Dictionary::ReadWordFile, this function reads a file into a vector of words. Also the keyboard.cpp, line 94, Keyboard::ReadKeyboardFile function also reads in the keyboard layout and additinally uses istream to split lines into a vector of struct Keys (See keyboard.h, line 12 for the struct definition).
  * **3 The project uses Object Oriented Programming techniques.** The project is built upon classes as described in the project structure above.
  * **4 Class constructors utilize member initialization lists.** Argument values are initialized through member initialization lists. (See game.cpp line 14)
  * **5 Classes use appropriate access specifiers for class members.** Class definitions are approprietly specified public or private. (See keyboard.h line 24+ )
  * **6 Classes follow an appropriate inheritance hierarchy.** The project inherits wxWidget objects approprietly (see keyboard.cpp line 16)
  * **7 The project makes use of references in function declarations.** At least two variables are defined as references, or two functions use pass-by-reference in the project code. (See turn.h lines 16 and 18).
  * **8 The project uses destructors appropriately.** The Game class is purposely constructed and destructed using unmanaged dynamic memory. (See wordezapp.cpp line 38 for the Game object delete call and  game.cpp line 27 for the destructors. wxWidget objects are deleted using their Destroy() method.

## Future work
- Use command line arguments e.g. for word and kb file paths or show the answer on the command line (the default)
- Build and Test on Mac and Windows platforms
- Convert the Game object back to a smart pointer for safer memory management
- Just took the words from the linux dictionary, can include difficult words, maybe subset the word list into difficulty levels
- Responsive gui that auto resizes the game board and keyboard
- Animate the keys as they are pressed
- Try different language and character set, may need a shift key
- TODO's in the code

## Other  
- Memory leak check 
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=w%p.log ./wordez

