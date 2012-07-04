package lms.model.util;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 * @author Mikhail Perepletchikov 24/06/2010
 */

public class DateUtil {

	private static DateUtil dateUtil;
	private String date = null;

	/** the following code fragment shows an example of using a Singleton design pattern **/
	/** ------------------------------ **/
	// private constructor prevents instantiation from other classes
	private DateUtil() {}
	// make sure that only one instance of DateUtil can be created
	public static DateUtil getInstance() {
		if (dateUtil == null)
			dateUtil = new DateUtil();
		return dateUtil;
	}
	/** ------------------------------ **/

	
	public String getDate() {
		return date;
	}

	public void setDate(String currentDate) {
		this.date = currentDate;
	}

	/*
	 * calculates the difference (in number of days) between the provided borrow
	 * date and current date. make sure that the provided borrow date is kept in
	 * its original format (dd-MM-yyyy e.g. "29-03-2010")
	 */
	public int getElapsedDays(String borrowDate) {
		// creates two calendars instances
		Calendar cal1 = Calendar.getInstance();
		Calendar cal2 = Calendar.getInstance();

		/** sets the dates for both calendar instances **/
		// first date is the holding borrow date
		cal1.setTime(createDate(borrowDate));
		// second date is the return (i.e. current) date
		cal2.setTime(createDate(date));

		// calculates difference in milliseconds
		long diff = cal2.getTimeInMillis() - cal1.getTimeInMillis();
		// calculates difference in days
		long diffDays = diff / (24 * 60 * 60 * 1000);	
		return (int) diffDays;
	}

	private Date createDate(String dateString) {
		DateFormat formatter;
		try {
			formatter = new SimpleDateFormat("dd-MM-yyyy");
			return (Date) formatter.parse(dateString);
		} catch (ParseException e) {
			e.getStackTrace();
		}
		return null;
	}
}
