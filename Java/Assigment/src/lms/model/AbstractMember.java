package lms.model;

import java.util.Hashtable;
import lms.model.exception.InsufficientCreditException;
import lms.model.exception.MultipleBorrowingException;

/**
 * This class is the base class for Library members. It is the basis for
 * specialized members
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see Member
 * @see PremiumMember
 * @see StandardMember
 */

public abstract class AbstractMember implements Member {

   private String _memberID;
   private String _fullName;
   private int _maxcredit;
   private int _credit;

   Hashtable<String, Holding> _holdings;
   protected BorrowingHistory _history;

   /*
    * This stores a reference to the members library I feel that i have to add
    * this due to restrictions such as the holding passed to borrowHolding is by
    * int i need to get the holding info just from the int
    */
   private Library _membersLibrary;

   /**
    * 
    * @param memberId
    *           the id of the Member
    * @param memberName
    *           the fullname of the Member
    * @param maxcredit
    *           the maximum credit for the Member
    */
   public AbstractMember(String memberId, String memberName, int maxcredit) {
      this._memberID = memberId;
      this._fullName = memberName;
      this._maxcredit = maxcredit;
      this._credit = _maxcredit;
      this._history = new BorrowingHistory();
      _holdings = new Hashtable<String, Holding>();

   }

   /**
    * This assigns the library that a member belongs to
    * 
    * @param library
    *           The library the member belongs to
    */
   @Override
   public void setMembersLibrary(Library library) {
      if (library != null)
         this._membersLibrary = library;
   }

   /**
    * Attempts to borrow the holding requested
    * 
    * @param holdingID
    *           the id of the holding to borrow
    * @return if borrowing the Holding was successful
    * @throws InsufficientCreditException
    * @throws MultipleBorrowingException
    */
   @Override
   public boolean borrowHolding(int holdingId)
         throws InsufficientCreditException, MultipleBorrowingException {
      // Get the holding info from the id that was passed in
      Holding holding = _membersLibrary.getHolding(holdingId);

      // If they are trying to borrow something they have already borrowed
      // then throw MultipleBorrowingException

      if (_history.getHistoryRecord(holdingId) != null)
         throw new MultipleBorrowingException();

      // evaluate the credit and if not enough throw insufficient credit
      // exception
      if (_credit < holding.getDefaultLoanFee())
         throw new InsufficientCreditException();

      // add to the list of holding the member has
      _holdings.put(Integer.toString(holdingId), holding);

      // subtract the fee from the credit
      this._credit -= holding.getDefaultLoanFee();
      return true;

   }

   /**
    * Returns the amount of credit available to the Member
    * 
    * @return the amount of credit
    */
   @Override
   public int calculateRemaingCredit() {
      return this._credit;
   }

   /**
    * Calculates the total amount of late fees for the member
    * 
    * @return the total amount of late fees
    */
   @Override
   public int calculateTotalLateFees() {
      return _history.calculateTotalLateFees();
   }

   /**
    * Sets the members available credit.
    * 
    * @param the
    *           amount to set available credit to
    */
   public void setRemainingCredit(int value) {
      this._credit = value;
   }

   /**
    * Returns the Borrowing History records
    * 
    * @return an Array of History records
    */
   @Override
   public HistoryRecord[] getBorrowingHistory() {
      return _history.getAllHistoryRecords();
   }

   /**
    * Gets a specific History record for a holdingID
    * 
    * @return the History record found for the holdingID.
    */
   @Override
   public HistoryRecord getHistoryRecord(int holdingID) {
      return _history.getHistoryRecord(holdingID);
   }

   /**
    * Gets the Members current holdings.
    * 
    * @return an Array of Holding records
    */
   @Override
   public Holding[] getCurrentHoldings() {
      return (Holding[]) _holdings.values().toArray(
            new Holding[_holdings.size()]);

   }

   /**
    * Gets the Members full name
    * 
    * @return the Members full name
    */
   @Override
   public String getFullName() {
      return this._fullName;
   }

   /**
    * Gets the Members maximum credit
    * 
    * @return the maximum credit
    */
   @Override
   public int getMaxCredit() {
      return this._maxcredit;
   }

   /**
    * Gets the Members Id
    * 
    * @return the Members Id
    */
   @Override
   public String getMemberid() {
      return this._memberID;
   }

   /**
    * Resets the Members credit to their maximum value
    */
   @Override
   public void resetCredit() {
      this._credit = this._maxcredit;
   }

   /**
    * This method returns the members associated Library
    * 
    * @return the Library that the member is associated with
    */
   public Library getLibrary() {
      return _membersLibrary;

   }

   /**
    * This removes a holding from a list of the holdings the member has out
    * 
    * @param holding
    *           the holding code to remove
    */
   public void removeHolding(int holding) {
      _holdings.remove(Integer.toString(holding));

   }
   @Override
   public abstract String toString();

}
