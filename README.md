## wordez - A C++ clone of a popular word game.
Take 5 Turns to guess a 5 letter, randomly selected, word. If the guess is a word in the dictionary, a color coded result is given on each of the guess's letters. Green, if the letter is in the target word and in the right place, Yellow, if the letter is in the word but not in the correct location and grey, when the letter is not in the word. The keyboard letters are also updated with the color coding to help aid follow on guesses. Incorrectly spelt words will shake for a second. 

The game ends when either the word is correctly guessed and all letters are green, or all the turns are used up. 

At the end of the game there is an option to copy the game result to the clipboard, and a second option to restart the game.

## Setup & Build
The game was developed, built and tested in an Ubuntu Linux environment. While build instructions are provided for the Mac and Windows, the project was not built or tested on those platforms. I am happy to receive any feedback for improvement to enable cross platform builds.
# Dependencies
* cmake >= 3.11
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](https://sourceforge.net/projects/mingw/)
* wxWidgets >= 3.0
  * Linux: `sudo apt-get install libwxgtk3.0-gtk3-dev libwxgtk3.0-gtk3-0v5`. Refer to the [official page](https://wiki.codelite.org/pmwiki.php/Main/WxWidgets30Binaries#toc2) for installing the unmet dependencies.
  * Mac: Using homebrew to install `brew install wxwidgets` https://formulae.brew.sh/formula/wxwidgets
  * Installation instructions can be found [here](https://wiki.wxwidgets.org/Install). Recommend [wxPack](https://github.com/rjpcomputing/wxpack/wiki) which includes gcc and wxwidgets.

## Build Instructions
1. Clone this repo. `git clone https://github.com/andrewparry/wordez.git`
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Ensure word.txt, kb.txt, and icon.png are in the top level directory
5. Run it: `./wordez`

## Project Structure
* The project utlizes the wxWidget library for all the GUI capabilities. This is suitable for this type of game which is driven by key press and button click events.
* Multiple classes make up the structure of the application, each class is extensively documented. In Summary:
  * Wordezapp     The 'main' wxwidgets class for the app.
  * WordezFrame   Inherited from the wxWidgets wxFrame class, the top-level frame for the game UI objects and events. This class creates a Game object for a new game.
  * Game          The Game class controlling the game logic:
    * Creates smart pointer to a Dictionary Object to manage the word functions.
    * Creates a wxPanel to layout the game Turns, Buttons and Keyboard.
    * Creates a vector of Turn objects. A game is made up of 6 Turns. The Game class also tracks the current game Turn, evaluating completed guesses.
    * Creates 2 hidden wxButtons for the End Game options - Copy the clipboard of the game result and Restart the game by calling back to the parent WordezFrame object
    * Creates a Keyboard object of buttons and events. 
  * Turns         A Turn is made up of a Vector of Letter Objects, 5 Letters make up a word. The current Turn will also track the current Letter for the next character input. Each completed Turn object keeps the result of its guess for the clipboard summary at the end of the game.
  * Letter        The Letter class holds the current letter character from a key press. This class also draws each letter tile that makes up a turn and updates the background color based on the result of a guess.
  * Keyboard     Inherited from wxPanel for the UI layout, this class loads a vector of keys from the kb.txt file, creates a grid of wxButtons, and sets up the on-click and on-key press events. Those events will callback the main Game object. 
  * Dictionary    Class of word functions. Loads a vector of words from the word.txt file, selects the target word, and evaluates guesses returning a result in a vector of ints.

  The game is driven by keyboard and mouse events. The Keyboard class processes key/mouse events to return a character, this is referenced to a call back function in the the Game object. If the charater is an alpha, the current letter is updated with the character, and the next letter in the turn becomes active waiting for input. Backspace will correctly clear the relevant value and change the active letter. When a turn is complete and the enter key is pressed, the word will be evaluated for correct spelling, and then the result is updated and game logic progresses to the next turn, until the end of game.

## Word list file word.txt
Linux contains collections of words that are derived from scowl http://wordlist.aspell.net/scowl-readme/ The license within the readme allows use and redistribution and is included in the repository. A subset of these collections is generated from linux using the instructions at https://leancrew.com/all-this/2022/01/wordle-letters/
For an american wordlist of 5 characters use:
`perl -nle 'print if /^[a-z]{5}$/' /usr/share/dict/american-english > words.txt`
This word list is used to randomly select a target word and also to evaluate the guesses for spelling.
Additional words may be manually added or removed from the list.

## Keyboard file kb.txt
A file containing a list of ascii characters grouped by the row they should appear on the keyboard. Enter is character 10 and Backspace is character 8. The game uses Capital letters only.

## Icon file icon.png
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
  * **8 The project uses destructors appropriately.** The Game class is constructed and destructed using managed dynamic memory. (See wordezapp.cpp line 38 for the Game object reset(delete) call and  game.cpp line 27 for the destructors. wxWidget objects are deleted using their Destroy() method. Raw pointers are not used in the non-wxwidget objects.

## Future work
- Use command line arguments e.g. for word and kb file paths or show the answer on the command line (the default)
- Build and Test on Mac and Windows platforms
- Just took the words from the linux dictionary, can include difficult words, maybe subset the word list into difficulty levels
- Responsive gui that auto resizes the game board and keyboard
- Animate the keys as they are pressed
- Try different language and character set, may need a shift key
- Added concurrency, I was thinking the loading of the word file and target word selection could be run in parallel and only needs to complete in time 
for the first guess to be submitted.
- Any remaining TODO's in the code

## Other  
- Project was lots of fun, explored many avenues developing the game, and using what was learnt in the course.
- Memory leak check 
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=w%p.log ./wordez

