package lms.model;

/**
 * This is the interface for a Holding
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see AbstractHolding
 * @see Book
 * @see Movie
 * @see AbstractHolding
 */

public interface Holding {

   /**
    * Calculates the late fee for the Holding based on specification rules
    * 
    * @return the late fee
    */
   public int calculateLateFee(int daysOnLoan);

   /**
    * Gets the date that the holding was borrowed
    * 
    * @return String the date that the holding was borrowed
    */
   public String getBorrowDate();

   /**
    * Gets the code of the holding
    * 
    * @return the code of the holding
    */
   public int getCode();

   /**
    * Gets the default loan fee for the holding
    * 
    * @return the default loan fee
    */
   public int getDefaultLoanFee();

   /**
    * Gets the max loan period for the holding
    * 
    * @return the maximum loan period
    */
   public int getMaxLoanPeriod();

   /**
    * Gets the title of the holding
    * 
    * @return the title of the holding
    */
   public String getTitle();

   /**
    * Gets if the holding is on loan or not
    * 
    * @return true if the item is on loan or false if it isn't
    */
   public boolean isOnLoan();

   /**
    * Sets the date the holding was borrowed and if it is on loan
    */
   public void setBorrowDate(String Date);

   /**
    * Gets the overdue fee that was paid for this holding
    * 
    * @return the over due fee that was paid for this holding
    * 
    */
   public int getFeePaid();
}
