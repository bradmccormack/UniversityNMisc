package lms.model;

/**
 * This class represents a generic type Holding It is the basis for specialized
 * types of Holdings
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see Holding
 * @see Book
 * @see Video
 */

public abstract class AbstractHolding implements Holding {

   private int _code;
   private String _title;
   private int _loan_fee;
   private int _max_loan_period;
   private boolean _isOnLoan;
   private String _loandate;
   protected int _fee_paid;

   /**
    * 
    * @param code
    *           the code for the new holding
    * @param title
    *           the title for the new holding
    * @param loanfee
    *           the loan fee for the new holding
    * @param loanperiod
    *           the loan period for the new holding
    */
   public AbstractHolding(int code, String title, int loanfee, int loanperiod) {
      this._code = code;
      this._title = title;
      this._loan_fee = loanfee;
      this._max_loan_period = loanperiod;
      this._loandate = null;
      this._fee_paid = 0;
   }

   /**
    * Gets the overdue fee that was paid for this holding
    * 
    * @return the over due fee that was paid for this holding
    * 
    */
   @Override
   public int getFeePaid() {
      return _fee_paid;
   }

   /**
    * Gets the date that the holding was borrowed
    * 
    * @return String the date that the holding was borrowed
    */
   @Override
   public String getBorrowDate() {
      return _loandate;
   }

   /**
    * Gets the code of the holding
    * 
    * @return the code of the holding
    */
   @Override
   public int getCode() {
      return _code;
   }

   /**
    * Gets the default loan fee for the holding
    * 
    * @return the default loan fee
    */
   @Override
   public int getDefaultLoanFee() {
      return _loan_fee;
   }

   /**
    * Gets the max loan period for the holding
    * 
    * @return the maximum loan period
    */
   @Override
   public int getMaxLoanPeriod() {
      return _max_loan_period;
   }

   /**
    * Gets the title of the holding
    * 
    * @return the title of the holding
    */
   @Override
   public String getTitle() {
      return _title;
   }

   /**
    * Gets if the holding is on loan or not
    * 
    * @return true if the item is on loan or false if it isn't
    */
   @Override
   public boolean isOnLoan() {
      return _isOnLoan;
   }

   /**
    * Sets the date the holding was borrowed and if it is on loan
    */
   @Override
   public void setBorrowDate(String date) {

      // they are returning the book so clear the loan date and set isOnLoan to
      // false
      if (date == null) {
         this._isOnLoan = false;
         this._loandate = null;
      }
      // they are borrowing the book so mark as onLoan and set the loan date
      else {
         _isOnLoan = true;
         this._loandate = date;
      }

   }
   @Override
   public abstract String toString();

}
