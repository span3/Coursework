// $Id: linkedqueue.java,v 1.1 2011-04-26 03:47:01-07 - - $

import java.util.NoSuchElementException;

class linkedqueue <item_t> {

   private class node{
      item_t item;
      node link;
   }

   //
   // INVARIANT:  front == null && rear == null
   //          || front != null && rear != null
   // In the latter case, following links from the node pointed 
   // at by front will lead to the node pointed at by rear.
   //
   private node front = null;
   private node rear = null;

   public boolean empty (){
      return front == null;
   }

   public void insert (item_t any) {
      node n1 = new node();
      n1.item = any;
      if (empty()) {
         front = n1;
         rear = front;
      }
      else {
         rear.link = n1;
         rear = n1;
      }
   }

   public item_t remove (){
      if (empty()) throw new NoSuchElementException();
      item_t val = front.item;
      front = front.link;
      return val;
   }

}
