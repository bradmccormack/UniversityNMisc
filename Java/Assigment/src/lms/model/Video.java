package lms.model;

/**
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see Holding,AbstractHolding,Book This class a specialized Holding to
 *      represent a Video
 */

public class Video extends AbstractHolding {
   static int _loanfee = 4;
   final static int _loanperiod = 7;
   final static String type = "VIDEO";

   /**
    * 
    * @param code
    *           the code of the Video
    * @param title
    *           the title of the Video
    */
   public Video(int code, String title, int fee) {
      super(code, title, fee, _loanperiod);

   }

   /**
    * Calculates the late fee for the Video based on specification rules
    * 
    * @return the late fee
    */
   @Override
   public int calculateLateFee(int daysOnLoan) {
      // if they brought back on time no late fee
      if (daysOnLoan <= _loanperiod)
         return 0;
      // late fee = number of late days x 50% of the standard loan fee
      super._fee_paid = (daysOnLoan - _loanperiod)
            * (int) (0.5 * super.getDefaultLoanFee());
      return super._fee_paid;
   }

   /**
    * Outputs the Video information as a string
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
