package lms.model;

import java.util.ArrayList;

import lms.model.exception.InsufficientCreditException;
import lms.model.exception.MultipleBorrowingException;
import lms.model.exception.OverdrawnCreditException;
import lms.model.util.DateUtil;

/**
 * This is the Library class
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see LMSFacade
 * @see LMSModel
 * 
 */

public class Library {

   private LibraryCollection _librarycollection;
   private Member _member;

   /**
    * Gets the Member associated with the Library
    * 
    * @return the Member in the library
    */
   public Member getMember() {
      return _member;
   }

   /**
    * Gets the collection associated with the library
    * 
    * @return the associated library collection
    */
   public LibraryCollection getCollection() {
      return _librarycollection;
   }

   /**
    * Adds a Member to the Library
    * 
    * @param the
    *           member to add
    */
   public void addMember(Member member) {
      _member = member;
      // Set the members library so that the member can lookup
      // info on a holding by its code later
      _member.setMembersLibrary(this);

   }

   /**
    * Adds a collection to the Library
    * 
    * @param c
    *           the Library collection to add
    */
   public void addCollection(LibraryCollection c) {
      _librarycollection = c;

   }

   public boolean addHolding(Holding holding) {
      return _librarycollection.addHolding(holding);

   }

   /**
    * removes a holding from the library collection
    * 
    * @param holdingId
    *           the holding to remove
    * @return true if remove successful or false if it wasn't
    */
   public boolean removeHolding(int holdingId) {
      return _librarycollection.removeHolding(holdingId);
   }

   /**
    * gets a holding by its Id
    * 
    * @param holdingId
    *           the Id to retrieve the full Holding for
    * @return the holding that matches the id
    */
   public Holding getHolding(int holdingId) {
      return _librarycollection.getHolding(holdingId);
   }

   /**
    * Gets all holdings in the library collection
    * 
    * @return array of Holdings
    */
   public Holding[] getAllHoldings() {
      return _librarycollection.getAllHoldings();
   }

   /**
    * Attempts to borrow a Holding
    * 
    * @param holdingId
    *           the holding requested to borrow
    * @throws InsufficientCreditException
    * @throws MultipleBorrowingException
    */
   public void borrowHolding(int holdingId) throws InsufficientCreditException,
         MultipleBorrowingException {

      Holding holding = _librarycollection.getHolding(holdingId);

      // There is no Holding by this id so just return
      if (holding == null)
         return;

      // member try to borrow the holding
      if (_member.borrowHolding(holdingId)) {
         // member borrowed the holding ok so mark it as onloan
         DateUtil dute = DateUtil.getInstance();
         holding.setBorrowDate(dute.getDate());
      }
   }

   /**
    * Attempts to return a holding
    * 
    * @param holdingId
    *           the holding to return
    * @throws OverdrawnCreditException
    */
   public void returnHolding(int holdingId) throws OverdrawnCreditException {

      // if member failed to return holding then just exit
      if (!_member.returnHolding(holdingId))
         return;

      // set the holding to not on loan anymore
      _librarycollection.getHolding(holdingId).setBorrowDate(null);

   }

   /**
    * Gets the complete borrowing history
    * 
    * @return array of History Records
    */
   public HistoryRecord[] getBorrowingHistory() {
      return _member.getBorrowingHistory();
   }

   /**
    * Gets a specific history record for a holding.
    * 
    * @param holdingId
    *           the id to get the history record for
    * @return a history record for the holding id requested
    */
   public HistoryRecord getHistoryRecord(int holdingId) {
      // TODO Auto-generated method stub
      return _member.getHistoryRecord(holdingId);
   }

   /**
    * Gets borrowed holdings
    * 
    * @return an array of Holdings
    */
   public Holding[] getBorrowedHoldings() {

      // fetch all of the holdings in the library collection
      Holding[] holdings = _librarycollection.getAllHoldings();
      // loop through them all and build a list of borrowed holdings
      ArrayList<Holding> borrowedHoldings = new ArrayList<Holding>();
      for (Holding holding : holdings) {
         if (holding.isOnLoan())
            borrowedHoldings.add(holding);
      }
      // return the borrowed holdings as array as it expects
      if (borrowedHoldings.size() == 0)
         return null;

      // return the borrowed holdings as a Holding array
      return borrowedHoldings.toArray(new Holding[borrowedHoldings.size()]);

   }

   /**
    * Resets a Members credit to the maximum for their type
    */
   public void resetMemberCredit() {
      _member.resetCredit();

   }

   /**
    * Calculates the amount of remaining credit for the member
    * 
    * @return the amount of remaining credit
    */
   public int calculateRemainingCredit() {
      return _member.calculateRemaingCredit();
   }

   /**
    * Calculates the amount of total late fees.
    * 
    * @return
    */
   public int calculateTotalLateFees() {
      return _member.calculateTotalLateFees();
   }
}
