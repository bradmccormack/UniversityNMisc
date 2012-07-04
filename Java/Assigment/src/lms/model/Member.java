package lms.model;

/**
 * This is the Member interface
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see AbstractMember
 */
public interface Member extends Borrower {

   /**
    * Returns the amount of credit available to the Member
    * 
    * @return the amount of credit
    */
   public int calculateRemaingCredit();

   /**
    * Returns the Borrowing History records
    * 
    * @return an Array of History records
    */
   public HistoryRecord[] getBorrowingHistory();

   /**
    * Gets a specific History record for a holdingID
    * 
    * @return the History record found for the holdingID.
    */
   public HistoryRecord getHistoryRecord(int holdingId);

   /**
    * Gets the Members current holdings.
    * 
    * @return an Array of Holding records
    */
   public Holding[] getCurrentHoldings();

   /**
    * Gets the Members full name
    * 
    * @return the Members full name
    */
   public String getFullName();

   /**
    * Gets the Members maximum credit
    * 
    * @return the maximum credit
    */
   public int getMaxCredit();

   /**
    * Gets the Members Id
    * 
    * @return the Members Id
    */
   public String getMemberid();

   /**
    * Resets the Members credit to their maximum value
    */
   public void resetCredit();

   /**
    * This assigns the library that a member belongs to
    * 
    * @param library
    *           The library the member belongs to
    */
   public void setMembersLibrary(Library library);

   /**
    * Calculates the total amount of late fees for the member
    * 
    * @return the total amount of late fees
    */
   public int calculateTotalLateFees();

}
