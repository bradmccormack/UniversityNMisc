package lms.model;

import java.util.Hashtable;
import java.lang.StringBuilder;

/**
 * This is the Library Collection class
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see Library
 * 
 */

public class LibraryCollection {
   private String _code;
   private String _name;
   private Hashtable<String, Holding> _holdings;

   /**
    * @param code
    *           the code for the collection
    * @param Name
    *           the name for the collection
    */
   public LibraryCollection(String code, String Name) {
      this._code = code;
      this._name = Name;
      this._holdings = new Hashtable<String, Holding>();

   }

   /**
    * gets the code of the collection
    * 
    * @return the code of the collection
    */
   public String getCode() {
      return _code;
   }

   /**
    * gets the name of the collection
    * 
    * @return the name of the collection
    */
   public String getName() {
      return _name;
   }

   /**
    * adds a holding to the collection
    * 
    * @param holding
    *           to add to the collection
    * @return true if holding was added ok or false if it wasn't
    */
   public boolean addHolding(Holding holding) {
      try {
         // if the holding exists then exit otherwise add it
         int holdingid = holding.getCode();
         if (_holdings.containsKey(Integer.toString(holdingid)))
            return false;
         _holdings.put(Integer.toString(holdingid), holding);
         return true;
      }

      catch (Exception e) {
         System.out.printf("Error ", e.getMessage());
         return false;
      }

   }

   /**
    * gets a holding
    * 
    * @param code
    *           the holding to get
    * @return the holding for the code
    */
   public Holding getHolding(int code) {
      return _holdings.get(Integer.toString(code));
   }

   /**
    * getAllHoldings will return the list of Holdings as an array.
    * 
    * @return Array of Holdings or null if there are no Holdings in the
    *         collection
    */
   public Holding[] getAllHoldings() {
      if (_holdings.size() == 0)
         return null;
      return (Holding[]) _holdings.values().toArray(
            new Holding[_holdings.size()]);
   }

   /**
    * removes a holding
    * 
    * @param code
    *           the holding code to remove
    * @return true if it was removed or false if it wasn't
    */
   public boolean removeHolding(int code) {
      if (getHolding(code) == null)
         return false;

      try {
         // if the holding is not on loan then remove it from the collection
         Holding toremove = _holdings.get(Integer.toString(code));
         if (!toremove.isOnLoan()) {
            _holdings.remove(Integer.toString(code));
            return true;
         }
         // the holding is on loan so you cannot remove it from the collection
         else
            return false;
      }

      catch (Exception e) {
         System.out.printf("Error ", e.getMessage());
         return false;
      }

   }

   /**
    * returns formatted string representing the LibraryCollection information
    * 
    * @return formatted string representing the LibraryCollection information
    */
   @Override
   public String toString() {
      StringBuilder sb = new StringBuilder();
      sb.append(getCode());
      sb.append(":");
      sb.append(getName());
      sb.append(":");

      for (int i = 0; i < _holdings.size(); i++) {
         Holding holding = _holdings.elements().nextElement();
         sb.append(":");
         sb.append(holding.getCode());
      }
      return sb.toString();
   }

}
