// $Id: treemap.java,v 1.1 2011-05-09 21:44:29-07 - - $

import static java.lang.System.*;

class treemap <key_t extends Comparable <key_t>, value_t> {

   private class node {
      key_t key;
      value_t value;
      node left;
      node right;
   }
   private node root;

   private void debug_dump_rec (node tree, int depth) {
      out.printf("%s", (String)(tree.value));
      if (tree.left != null) debug_dump_rec(tree.left,depth+1);
      if (tree.right != null) debug_dump_rec(tree.right,depth+1);
   }

   private void do_visit_rec (visitor <key_t, value_t> visit_fn,
                              node tree) {
      throw new UnsupportedOperationException ();
   }

   public value_t get (key_t key) {
      node next = root;
      while (next != null) {
         if (key.compareTo(next.key) == 0) return next.value;
         else if (key.compareTo(next.key) < 0) next = next.left;
         else next = next.right;
      }
      return null;
   }

   public value_t put (key_t key, value_t value) {
      node next = root;
      while (next != null) {
         if (key.compareTo(next.key) == 0) {
            value_t temp = next.value;
            next.value = value;
            return temp;
         }
         else if (key.compareTo(next.key) < 0) {
            next = next.left; 
         }
         else {
            next = next.right;
         }
      }
      node add = new node();
      add.key = key;
      add.value = value;
      next = add;
      return null;
   }

   public void debug_dump () {
      debug_dump_rec (root, 0);
   }

   public void do_visit (visitor <key_t, value_t> visit_fn) {
      do_visit_rec (visit_fn, root);
   }

}

