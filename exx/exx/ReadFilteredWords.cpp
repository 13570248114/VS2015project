/**
 * ReadFilteredWords class, the extend class for CE221 Assignment 2 (Exercise 2)
 * original version written by Dave Lyons
 * modified by sands
 */

#include "ReadFilteredWords.h"
#include <cstdlib>
#include <cctype>

/**
 * Constructor. Opens the file with the given filename.
 * Program exits with an error message if the file does not exist.
 * @param - filename, a C string naming the file to read.
 * After a successful open, the constructor reads the first of the strings,
 * and initialises the eoffound flag.
 */

void ReadFilteredWords::close()
{   ReadWords::close();
}

/**
 * Returns true if there is a further word in the file, false if we have reached the
 * end of file.
 * @return - bool - !eof
 * eoffound will have been set by getNextWord
 */
bool ReadFilteredWords::isNextWord()
{   return ReadWords::isNextWord();
}


bool ReadFilteredWords::filter(string word){
	return false;
}


/**
 * Returns a string, being the next word in the file.
 * @return - string, fixed nextword.
 */
// note that this function could return an empty string
// if the "word" is a sequence of non-alphanumeric characters the fix function will remove everything!

string ReadFilteredWords::getNextWord()
{
     return  ReadWords::getNextWord();
}

