// $Id: queue.java,v 1.1 2011-05-09 21:44:29-07 - - $

import java.util.Iterator;
import java.util.NoSuchElementException;

class queue <item_t> implements Iterable <item_t> {

   private class node {
      item_t item;
      node link;
   }
   private node head = null;
   private node tail = null;

   public boolean isempty () {
      return head == null;
   }

   public void insert (item_t newitem) {
      node n1 = new node();
      n1.item = newitem;
      if (isempty()) {
         head = n1;
         tail = head;
      }
      else {
         tail.link = n1;
         tail = n1;
      }
   }

   public Iterator <item_t> iterator () {
      return new itor ();
   }

   class itor implements Iterator <item_t> {
      node next = head;
      public boolean hasNext () {
         return next != null;
      }
      public item_t next () {
         if (! hasNext ()) throw new NoSuchElementException ();
         item_t result = next.item;
         next = next.link;
         return result;
      }
      public void remove () {
         throw new UnsupportedOperationException ();
      }
   }

}

