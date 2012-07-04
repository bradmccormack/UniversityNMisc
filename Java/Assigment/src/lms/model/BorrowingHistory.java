package lms.model;

import java.util.Hashtable;

/**
 * This is the Borrowing History class that manages History Records
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see HistoryRecord
 */

public class BorrowingHistory {
   private Hashtable<String, HistoryRecord> _historyRecords;

   public BorrowingHistory() {
      _historyRecords = new Hashtable<String, HistoryRecord>();
   }

   /**
    * 
    * @param holding
    *           The holding code to make a record of
    * @return boolean. True if adding the record was ok. False if it failed.
    */
   public boolean addHistoryRecord(Holding holding) {
      try {
         HistoryRecord record = new HistoryRecord(holding);
         _historyRecords.put(Integer.toString(holding.getCode()), record);
         return true;
      } catch (Exception e) {
         System.out.printf("Error ", e.getMessage());
         return false;
      }
   }

   /**
    * Calculates the total late fees
    * 
    * @return total late fees
    */
   public int calculateTotalLateFees() {
      // loop through all History records and sum the total late fee
      int total = 0;

      HistoryRecord[] history = getAllHistoryRecords();
      for (HistoryRecord record : history) {
         total += record.getFeePayed();
      }
      return total;
   }

   /**
    * Gets all history records
    * 
    * @return array of all History records
    */
   public HistoryRecord[] getAllHistoryRecords() {
      if (_historyRecords.size() == 0)
         return null;
      return (HistoryRecord[]) _historyRecords.values().toArray(
            new HistoryRecord[_historyRecords.size()]);

   }

   /**
    * 
    * @param holdingID
    *           the holdingid that you want a History record for
    * @return a History record for the specified holding Id
    */
   public HistoryRecord getHistoryRecord(int holdingID) {
      return _historyRecords.get(Integer.toString(holdingID));

   }

}
