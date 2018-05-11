/**
 * ReadFilteredWords abstract class, for CE221 Assignment 2 (Exercise 2)
 * adapted from original version written by Dave Lyons
 * modified by sands
 */

#ifndef _READFWORDS_H
#define _READFWORDS_H

using namespace std;
#include <string>
#include "ReadWords.h"

class ReadFilteredWords: public ReadWords
{   public:

        /**
         * Constructor. Opens the file with the given filename.
         * Program exits with an error message if the file does not exist.
         * @param fname - a C string naming the file to read.
         */
        ReadFilteredWords(char *fname): ReadWords(fname){}
        //pure virtual function for filter
        bool filter(string word);

        /**
         * Returns a string, being the next word in the file that satisfies the filter.
         * @return - string - next word that satisfies the filter
         * returns empty string if there's no such word
         */
        string getNextFilteredWord();

/**
         * Closes the file.
         */
        void close();

        /**
         * Returns a string, being the next word in the file.
         * @return - string - next word.
         */
        string getNextWord();

        /**
         * Returns true if there is a further word in the file, false if we have reached the
         * end of file.
         * @return - bool - !eof
         */
        
    //protected:
        bool isNextWord();

    
 };

 #endif
