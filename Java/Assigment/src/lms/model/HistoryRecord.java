package lms.model;

/**
 * This class represents a History record
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see BorrowingHistory
 */

public class HistoryRecord {
   private Holding _holding;

   /**
    * @param holding
    *           the holding to associated with the history record
    */
   public HistoryRecord(Holding holding) {
      this._holding = holding;

   }

   /**
    * Gets the fee paid for the holding
    * 
    * @return the fee paid
    */
   public int getFeePayed() {
      return _holding.getFeePaid();
   }

   /**
    * Gets the associated holding for the history record
    * 
    * @return the associated holding for this history record.
    */
   public Holding getHolding() {
      return _holding;
   }

   /**
    * This returns a formatted string representing the History Record
    * information
    * 
    * @return the formatted string for the History Record
    */
   @Override
   public String toString() {
      return _holding.getCode() + ":" + _holding.getDefaultLoanFee();
   }

}
