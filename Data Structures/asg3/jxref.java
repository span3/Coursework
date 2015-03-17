// Steven Pan span3@ucsc.edu
// $Id: jxref.java,v 1.5 2011-05-11 02:33:52-07 - - $
import java.io.*;
import java.util.Scanner;
import static java.lang.System.*;

class jxref {
   static final String STDIN_NAME = "-";

   static class printer implements visitor <String, queue <Integer>> {
      public void visit (String key, queue <Integer> value) {
         out.printf ("%s %s", key, value);
         for (int linenr: value) out.printf (" %d", linenr);
         out.printf ("%n");
      }
   }

   static void xref_file (String filename, Scanner scan, 
      boolean lowercase, boolean debug) {
      queue<Integer> queue = new queue<Integer> ();
      treemap <String, queue <Integer>> map =
            new treemap <String, queue <Integer>> ();
      out.printf("\n");
      for (int i = 0; i < 64; i++) {
         out.printf(":");
      }
      out.printf("\n%s\n", filename);
      for (int i = 0; i < 64; i++) {
         out.printf(":");
      }
      out.printf("\n\n");
      for (int linenr = 1; scan.hasNextLine (); ++linenr) {
         for (String word: scan.nextLine().split ("\\W+")) {
            if (lowercase) {
               word.toLowerCase();
            }
            if (word.matches ("^\\d*$")) continue;
            out.printf("%s", map.put(word, queue));
         }
      }
      visitor <String, queue <Integer>> print_fn = new printer ();
      map.debug_dump();
   }

   public static void main (String[] args) {
      boolean debug = false;
      boolean lowercase = false;
      if (args.length == 0) {
         xref_file (STDIN_NAME, new Scanner (in),lowercase, debug);
      }else {
         int argi = 0;
         if (args[0].charAt(0) == '-') {
            for (int i = 1; i < args[0].length(); i++) {
               if (args[0].charAt(i) == 'd') debug = true;
               else if (args[0].charAt(i) == 'f') lowercase = true;
               else out.printf("ERROR: Invalid option %s\n",
                   args[0].charAt(i));
            }
            argi = 1;
         }
         for (argi = argi; argi < args.length; ++argi) {
            String filename = args[argi];
            if (filename.equals (STDIN_NAME)) {
               xref_file (STDIN_NAME, new Scanner (in),lowercase,debug);
            }else {
               try {
                  Scanner scan = new Scanner (new File (filename));
                  xref_file (filename, scan,lowercase,debug);
                  scan.close ();
               }catch (IOException error) {
                  auxlib.warn (error.getMessage ());
               }
            }
         }
      }
      auxlib.exit ();
   }

}


