package lms.model.exception;

/**
 * @author Mikhail Perepletchikov 24/06/2010
 */
@SuppressWarnings("serial")
public abstract class LMSException extends Exception {

   public LMSException() {
      super("DEFAULT LMS Exception");
   }

   // NOTE: it is advisable to use this constructor when creating new exceptions
   public LMSException(String message) {
      super(message);
   }
}