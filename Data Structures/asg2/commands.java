// $Id: commands.java,v 1.1 2011-04-26 03:47:01-07 - - $

import java.util.HashMap;
import static java.lang.System.*;

class commands {
   static String changed = ".";
   static int indent = 10,offset = 0,margin = 3,
              blanklines = 0,length = 65;

   public static String getChanged() {
      return changed;
   }
   public static int lineLength() {
      return length;
   }
   public static int getIndent() {
      return indent;
   }
   public static int getOffset() {
      return offset;
   }
   public static int getMargin() {
      return margin;
   }
   public static int getLines() {
      return blanklines;
   }
   static void STUB_message (Object obj, String[] opnds) {
      out.printf ("%s: STUB: %s.exec ",
                  auxlib.PROGNAME, obj.getClass().getName());
      for (String opnd: opnds) out.printf ("[%s]", opnd);
      out.printf ("%n");
   }

   static interface cmd {
      public void exec (String[] opnds);
   }

   static class cmd_00 implements cmd {
      public void exec (String[] opnds) {}
   }

   static class cmd_bp implements cmd {
      public void exec (String[] opnds) {
         STUB_message (this, opnds);
      }
   }

   static class cmd_br implements cmd {
      public void exec (String[] opnds) {}
   }

   static class cmd_cc implements cmd {
      public void exec (String[] opnds) {
         changed = opnds[1];
      }
   }

   static class cmd_in implements cmd {
      public void exec (String[] opnds) {
         offset = Integer.parseInt(opnds[1]);
      }
   }

   static class cmd_ll implements cmd {
      public void exec (String[] opnds) {
         if (Integer.parseInt(opnds[1]) > 0) {
            length = Integer.parseInt(opnds[1]);
         }
      }
   }

   static class cmd_mt implements cmd {
      public void exec (String[] opnds) {
         margin = Integer.parseInt(opnds[1]);
      }
   }

   static class cmd_tl implements cmd {
      public void exec (String[] opnds) {
         
      }
   }

   static class cmd_pl implements cmd {
      public void exec (String[] opnds) {
         STUB_message (this, opnds);
      }
   }

   static class cmd_po implements cmd {
      public void exec (String[] opnds) {
         indent = Integer.parseInt(opnds[1]);
      }
   }

   static class cmd_sp implements cmd {
      public void exec (String[] opnds) {
         if (opnds.length == 1) {
            blanklines = 0;
         }
         else {
            blanklines = Integer.parseInt(opnds[1]);
         }
      }
   }

   static HashMap<String, cmd> cmd_map = new HashMap<String, cmd>();
   static {
      cmd_map.put (".\\\"", new cmd_00 ());
      cmd_map.put (".bp"  , new cmd_bp ());
      cmd_map.put (".br"  , new cmd_br ());
      cmd_map.put (".cc"  , new cmd_cc ());
      cmd_map.put (".in"  , new cmd_in ());
      cmd_map.put (".ll"  , new cmd_ll ());
      cmd_map.put (".mt"  , new cmd_mt ());
      cmd_map.put (".tl"  , new cmd_tl ());
      cmd_map.put (".pl"  , new cmd_pl ());
      cmd_map.put (".po"  , new cmd_po ());
      cmd_map.put (".sp"  , new cmd_sp ());
   }

}

