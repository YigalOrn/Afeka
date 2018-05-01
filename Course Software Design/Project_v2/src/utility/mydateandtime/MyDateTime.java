package utility.mydateandtime;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.concurrent.TimeUnit;

final public class MyDateTime {

	public static String getCurrentTime() {
		SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
		Calendar cal = Calendar.getInstance();
		return sdf.format(cal.getTime());
	}

	public static String getCurrentdate() {
		SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
		Calendar cal = Calendar.getInstance();
		return sdf.format(cal.getTime());
	}

	public static String getCurrentDateTime() {
		SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");
		Calendar cal = Calendar.getInstance();
		return sdf.format(cal.getTime());
	}

	public static long calcDateYearDiff(String date1, String date2) {
		Calendar cal1 = Calendar.getInstance();
		Calendar cal2 = Calendar.getInstance();
		Date d1 = null, d2 = null;
		SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy HH:mm:ss");

		try {
			d1 = sdf.parse(date1);
			d2 = sdf.parse(date2);
		} catch (ParseException e) {
			e.printStackTrace();
		}

		cal1.setTime(d1);
		cal1.setTime(d2);

		long diff = cal1.getTime().getTime() - cal2.getTime().getTime();
		long res = TimeUnit.DAYS.convert(diff, TimeUnit.MILLISECONDS);
		res /= 365;

		return res;
	}

	public static void checkDateByFormat(String date, String format) throws ParseException {
		SimpleDateFormat sdf = new SimpleDateFormat(format);
		sdf.parse(date);
	}

	public static String getNextYearFromNow() {
		return null;
		
	}
}
