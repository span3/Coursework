// Author: Steven Pan (span3@ucsc.edu)
// $Id: jfmt.java,v 1.1 2011-04-10 17:33:48-08 - - $
//
// Starter code for the jfmt utility.  This program is similar
// to the example code jcat.java, which iterates over all of its
// input files, except that this program shows how to use
// String.split to extract non-whitespace sequences of characters
// from each line.
//

import java.io.*;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import static java.lang.System.*;

class jfmt {

   //Prints out everything stored in the list.
   static void printparagraph (List<String> words) {
      for (String word: words) {
         out.printf ("%s ", word);
      }
      out.printf ("%n");
   }

   //Formats the letters being put in, ensures that words
   //are in the proper format.
   static void format (Scanner infile, int charLimit) {
      String temp = " ";
      List<String> words = new LinkedList<String> ();
      int limit = 0;
      int space = 0;
      for (int linenr = 1; infile.hasNextLine (); ++linenr) {
         String line = infile.nextLine ();
         line = line.trim  ();
         if (space == 0) {
            line = line.replaceAll ("\t", "");
         }
         for (String word: line.split ("\\s+")) {
	    //End of paragraph, print and make a new line.
            if (word.length() == 0) {
               if (!(word.equals (temp))) {
                  space = 0 ;
                  printparagraph (words);
                  out.printf ("%n");
               }
               words.clear();
               limit = 0;
	    //Line limit reached, print out what is stored.
            } else if (limit + word.length() > charLimit) {
               space = 0;
               printparagraph (words);
               words.clear();
               limit = 0;
               words.add (word);
            }
	    //Proceed to add the current word to the list.
            else {
               words.add (word);
            }
	    //Keeps track of character limit.
            limit += word.length () + 1;
            temp = word;
         }
         space++;
      }
      //Print out what is left after the entier file is read.
      printparagraph (words);
   }

   public static void main (String[] args) {
      int charLimit = 65;
      //Allows user to input text to be formatted.
      if (args.length < 1) {
         format (new Scanner (in), charLimit);
      }else {
         for (int argix = 0; argix < args.length; ++argix) {
            String filename = args[argix];
            if (args[argix].matches ("-\\d+")) {
	       //Sets the character limit to a specified number.
               if (args.length > 0) {
                  charLimit =
                  Integer.parseInt(args[argix].substring(1));
               }
               if (args.length == 1) {
                  format (new Scanner (in), charLimit);
               } else if (filename.equals ("-")) {
                  format (new Scanner (in), charLimit);
               }
	    //The user has specified a file to be formatted.
            } else {
               try {
                  Scanner infile = new Scanner (new File (filename));
		  //Prints out name of file then proceeds to format.
                  out.printf ("FILE: %s%n", filename);
                  format (infile, charLimit);
                  infile.close ();
               } catch (IOException error) {
                  auxlib.warn (error.getMessage ());
               }
            }
         }
      }
   }
}

