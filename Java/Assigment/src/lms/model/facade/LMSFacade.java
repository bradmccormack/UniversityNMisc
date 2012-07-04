package lms.model.facade;

import lms.model.Library;
import lms.model.Member;
import lms.model.LibraryCollection;
import lms.model.Holding;
import lms.model.exception.MultipleBorrowingException;
import lms.model.exception.InsufficientCreditException;
import lms.model.exception.OverdrawnCreditException;
import lms.model.util.DateUtil;
import lms.model.HistoryRecord;

/**
 * @author Mikhail Perepletchikov 24/06/2010
 */
public class LMSFacade implements LMSModel {
	private Library _library;

	
	public LMSFacade()
	{
		_library=new Library();
	}
	
	
	/* you need to implement all LMSModel methods here */
	

      // this shows an example of using the provided DateUtil class to set the current date
	public void setDate(String currentDate) {
		DateUtil.getInstance().setDate(currentDate);		
	}

	@Override
	public Member getMember() {
		// TODO Auto-generated method stub
		return _library.getMember();
	}

	
	@Override
	public LibraryCollection getCollection() {
		// TODO Auto-generated method stub
		return _library.getCollection();
	}

	@Override
	public void addMember(Member member) {
		_library.addMember(member);
		
	}

	@Override
	public void addCollection(LibraryCollection c) {
		_library.addCollection(c);
	}

	@Override
	public boolean addHolding(Holding holding) {
		// TODO Auto-generated method stub
		return _library.addHolding(holding);
	}

	@Override
	public boolean removeHolding(int holdingId) {
		return _library.removeHolding(holdingId);
	}

	@Override
	public Holding getHolding(int holdingId) {
		// TODO Auto-generated method stub
		return _library.getHolding(holdingId);
	}

	@Override
	public Holding[] getAllHoldings() {
		// TODO Auto-generated method stub
		return _library.getAllHoldings();
	}

	@Override
	public void borrowHolding(int holdingId)
			throws InsufficientCreditException, MultipleBorrowingException 
	{
		//the member should try to borrow the holding
		_library.borrowHolding(holdingId);
		
	}

	@Override
	public void returnHolding(int holdingId) throws OverdrawnCreditException {
		_library.returnHolding(holdingId);
		
	}

	@Override
	public HistoryRecord[] getBorrowingHistory() {
		return _library.getBorrowingHistory();
	}

	@Override
	public HistoryRecord getHistoryRecord(int holdingId) {
		// TODO Auto-generated method stub
		return _library.getHistoryRecord(holdingId);
	}

	@Override
	public Holding[] getBorrowedHoldings() {
		// TODO Auto-generated method stub
		return _library.getBorrowedHoldings();
	}

	@Override
	public void resetMemberCredit() {
		// TODO Auto-generated method stub
		_library.resetMemberCredit();
	}

	@Override
	public int calculateRemainingCredit() {
		// TODO Auto-generated method stub
		return _library.calculateRemainingCredit();
	}

	@Override
	public int calculateTotalLateFees() {
		// TODO Auto-generated method stub
		return _library.calculateTotalLateFees();
	}	
}