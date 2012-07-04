package lms.model.facade;

import lms.model.Member;
import lms.model.LibraryCollection;
import lms.model.Holding;
import lms.model.exception.MultipleBorrowingException;
import lms.model.exception.OverdrawnCreditException;
import lms.model.HistoryRecord;
import lms.model.exception.InsufficientCreditException;

/**
 * @author Mikhail Perepletchikov 24/06/2010
 */

public interface LMSModel {

	/**
	 * returns the (current) member
	 */
	public Member getMember();

	/**
	 * returns the (current) library collection
	 */
	public LibraryCollection getCollection();

	/**
	 * adds new member to library
	 */
	public void addMember(Member member);

	/**
	 * adds new collection to library
	 */
	public void addCollection(LibraryCollection c);

	/**
	 * adds new holding to library collection. returns false if the holding
	 * already exists (i.e. only one copy of a given holding can be added to the
	 * collection).
	 */
	public boolean addHolding(Holding holding);

	/**
	 * removes a holding from library collection. returns false if the holding
	 * is currently on loan and therefore cannot be removed.
	 */
	public boolean removeHolding(int holdingId);

	/**
	 * returns a holding according to the provided holdingId
	 */
	public Holding getHolding(int holdingId);

	/**
	 * returns all holdings held in the library collection
	 */
	public Holding[] getAllHoldings();

	/**
	 * allows a member to borrow a given holding. deducts a loan fee from
	 * member's borrowing credit. throws exceptions when the borrowing
	 * eligibility is violated (refer to the assignment specs for further
	 * details).
	 */
	public void borrowHolding(int holdingId)
			throws InsufficientCreditException, MultipleBorrowingException;

	/**
	 * allows a member to return a given holding. deducts a late fee, if
	 * applicable, from member's borrowing credit. throws exception if the
	 * (Standard) member's borrowing credit gets overdrawn (refer to the
	 * assignment specs for further details).
	 */
	public void returnHolding(int holdingId) throws OverdrawnCreditException;

	/**
	 * returns a borrowing history (collection of all history records) of a
	 * member
	 */
	public HistoryRecord[] getBorrowingHistory();

	/**
	 * returns a specific history record from the borrowing history
	 */
	public HistoryRecord getHistoryRecord(int holdingId);

	/**
	 * returns a collection of all currently borrowed holdings
	 */
	public Holding[] getBorrowedHoldings();

	/**
	 * resets member's credit to the original MAX credit value
	 */
	public void resetMemberCredit();

	/**
	 * returns the remaining credit ($ value) for the member
	 */
	public int calculateRemainingCredit();

	/**
	 * returns the total late fees ($ value) accumulated by the member as
	 * captured in the borrowing history
	 */
	public int calculateTotalLateFees();

	/**
	 * this method sets the "system date", and is included for the testing
	 * purposes only!!!
	 */
	public void setDate(String currentDate);
}