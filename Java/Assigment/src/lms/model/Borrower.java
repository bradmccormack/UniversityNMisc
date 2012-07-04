package lms.model;

import lms.model.exception.InsufficientCreditException;
import lms.model.exception.MultipleBorrowingException;
import lms.model.exception.OverdrawnCreditException;

/**
 * This is the Borrow interface which Member extends
 * 
 * @author brad
 * @version 1.0
 * @since 18th July 2010
 * @see Member
 */

public interface Borrower {
   /**
    * Borrow the holding
    * 
    * @param the
    *           holding requested to borrow
    * @return true if the borrow request was ok or false if it wasn't
    * @throws InsufficientCreditException
    * @throws MultipleBorrowingException
    */
   public boolean borrowHolding(int holding)
         throws InsufficientCreditException, MultipleBorrowingException;

   /**
    * Return the holding
    * 
    * @param the
    *           holding requested to return
    * @return true if the return was ok or false if it wasn't
    * @throws OverdrawnCreditException
    */
   public boolean returnHolding(int holding) throws OverdrawnCreditException;
}
