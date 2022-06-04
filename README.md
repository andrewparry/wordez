## wordez
Clone of a popular word game written in C++. 5 Turns to guess a 5 letter randomly selected word. Each guess is evaluated, if the word is spelt correctly, the result is given by color coded the guess's letters. Green, if the letter is in the word and in the right place, Yellow, if the letter is in the word but not in the correct location and grey, when the letter is not in the word. The keyboard letters are also updated with the color coding to help aid follow on guesses. Incorrectly spelt words will shake for a second. 

The game ends when either the word is correctly guessed, all letters are green, or all the turns are used up. At the end of the game. 

## Setup & Build
# Dependencies (Same as Membot)
* cmake >= 3.11
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* wxWidgets >= 3.0
  * Linux: `sudo apt-get install libwxgtk3.0-gtk3-dev libwxgtk3.0-gtk3-0v5`. Refer to the [official page](https://wiki.codelite.org/pmwiki.php/Main/WxWidgets30Binaries#toc2) for installing the unmet dependencies.
  * Mac: There is a [homebrew installation available](https://formulae.brew.sh/formula/wxmac).
  * Installation instructions can be found [here](https://wiki.wxwidgets.org/Install). Some version numbers may need to be changed in instructions to install v3.0 or greater.

## Word list word.txt
Linux contains a collections of words that are derived from scowl http://wordlist.aspell.net/scowl-readme/ The license within the readme allows use and redistribution. A subset of these collections is generated from linux using the instructions at https://leancrew.com/all-this/2022/01/wordle-letters/
For an american wordlist of 5 characters use:
$ perl -nle 'print if /^[a-z]{5}$/' /usr/share/dict/american-english > words.txt
The word list is used to randomly select a target word and also to evaluate guesses for spelling.
Additional words may be manually added or removed from the list.

## Keyboard file kb.txt
A file containing a list of ascii characters grouped by the row they should appear on the keyboard. Enter is character 10 and Backspace is character 8. The game uses Capital letters only.

## Basic Build Instructions
1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Ensure word.txt and kb.txt are in the top level directory
5. Run it: `./wordez`.

## Project Structure
* The project utlizes wxWidgets for the GUI capabilities. This is suitable for this type of game which is driven by key presses and button click events.
* Multiple classes make up the structure of the application, each class is extensively documented. In Summary:
  * Wordezapp     The main wxwidgets class
  * WordezFrame   Inherited from wxFrame, the top-level frame for the UI and initializes the core Game object. At the end of game, the the Game object can be deleted and recreated via a function callback.
  * Game          The Game class controlling the game logic:
    * Creates a Dictionary Object to manage the word functions
    * Creates a wxPanel to display the game Turns, Buttons and Keyboard.
    * Creates a vector of Turn objects. A game is made up of 6 Turns. The Game class also tracks the current game Turn, evaluating completed guesses.
    * Creates 2 hidden buttons for the End Game options - Copy the clipboard of the game result and Restart the game by calling back to the parent WordezFrame object
    * Creates a Keyboard of buttons and events, connecting those events to the the keyboard callback function.
    * Keyboard callback function. If the key is an alpha, the current letter is updated and the next letter becomes active until in the last letter of the turn. Backspace will correctly clear the relevant value and change the active letter. When When a turn has 5 letters and the enter key is pressed, the word made of letters will be evaluated, result displayed and game logic progresses.
  * Turns         A Turn is made up of a Vector of Letter Objects, 5 Letters make up a word. The current Turn will also track the current Letter for the next input. Each Turn object tracks the result of its guess for the clipboard summary at the end of the game.
  * Letter        The Letter class holds the current letter value and is updated from the latest key press. This class also draws each letter tile that makes up a turn and updates the background color based on the result of the guess.
  * Keyboard     Inherited from wxPanel, this class, loads a vector of keys from the kb.txt file, creating wxButtons onto this panel, and the relevant on click events, with key press events as well. Those events will callback the main game object. 
  * Dictionary    Class of word functions. Load a vector of words from the word.txt file, select the target word, evaluate guesses.

## Additional files
- icon.png - Application icon

## Addressing the Rubic
  * README.md - Completed the 6 criteria for the readme.
  * Compiling and Testing - Utilizes cmake and make, succesfully tested compiling and running according to the build instructions on Linux, Mac and Windows
  * The project demonstrates an understanding of C++ functions and control structures.

## Future work
- Use command line arguments e.g. for word and kb file
- Just took the words from the linux dictionary, can include difficult words, maybe subset the word list into difficulty levels
- Responsive gui that auto resizes the game board and keyboard
- Animate the keys as they are pressed.
- Try different language and character set, may need a shift key.
- TODO's in the code

# 
- Memory leak check 
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=w%p.log ./wordez

