package lms.model;

import lms.model.util.DateUtil;

/**
 * This is the PremiumMember class Specialized version of AbastractMember
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see AbstractMember
 * @see Member
 * @see StandardMember
 */

public class PremiumMember extends AbstractMember {

   private static final int _maxcredit = 45;
   private static final String _type = "PREMIUM";

   /**
    * 
    * @param Id
    *           of the Member
    * @param fullname
    *           of the member
    */
   public PremiumMember(String memberId, String memberName) {
      super(memberId, memberName, _maxcredit);
   }

   /**
    * returns a holding
    * 
    * @return true if holding was returned OK false if not
    */
   @Override
   public boolean returnHolding(int holdingId) {

      // Get the members library
      Library memberslib = super.getLibrary();

      // fetch the holding information
      Holding holding = memberslib.getHolding(holdingId);

      // determine if the holdingId exists in the members current holdings
      boolean found = false;
      for (Holding searchholding : super.getCurrentHoldings()) {
         if (holding.equals(searchholding)) {
            found = true;
            break;
         }
      }
      // if the Member does not have this holding return false
      if (!found)
         return false;

      // get the amount of days this holding has been borrowed
      DateUtil dute = DateUtil.getInstance();
      int daysborrowed = dute.getElapsedDays(holding.getBorrowDate());
      int fee = holding.calculateLateFee(daysborrowed);

      if (fee > 0) {
         int currentcredit = super.calculateRemaingCredit();
         // adjust their credit by the fee
         super.setRemainingCredit(currentcredit - fee);
      }

      // make a history record
      _history.addHistoryRecord(holding);

      // remove the holding from the list of holdings the member has
      super.removeHolding(holdingId);
      return true;

   }

   /**
    * returns formatted string representing PremiumMember info
    * 
    * @return formatted string representing PremiumMember info
    */
   @Override
   public String toString() {
      return super.getMemberid() + ":" + super.getFullName() + ":"
            + super.getMaxCredit() + ":" + _type;
   }

}
