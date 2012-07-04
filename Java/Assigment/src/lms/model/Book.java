package lms.model;

/**
 * This class a specialized Holding to represent a Book
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see Holding
 * @see AbstractHolding
 * @see Video
 */

public class Book extends AbstractHolding {

   final static int _loanfee = 10;
   final static int _loanperiod = 28;
   final static String type = "BOOK";

   /**
    * 
    * @param code
    *           the code of the Book
    * @param title
    *           the title of the Book
    */
   public Book(int code, String title) {
      super(code, title, _loanfee, _loanperiod);

   }

   /**
    * Calculates the late fee for the Book based on specification rules
    * 
    * @return the late fee
    */
   @Override
   public int calculateLateFee(int daysOnLoan) {
      // if they brought back on time no late fee
      if (daysOnLoan <= _loanperiod)
         return 0;
      // late fee=number of late days x fixed daily rate of $2
      super._fee_paid = (daysOnLoan - _loanperiod) * 2;
      return super._fee_paid;
   }

   /**
    * Outputs the Book information as a string
    * 
    * @return the information expressed as a string
    */
   @Override
   public String toString() {
      return super.getCode() + ":" + super.getTitle() + ":"
            + super.getDefaultLoanFee() + ":" + super.getMaxLoanPeriod() + ":"
            + type;
   }

}
