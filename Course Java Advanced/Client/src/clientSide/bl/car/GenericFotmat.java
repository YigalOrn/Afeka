package clientSide.bl.car;

import java.util.Date;
import java.util.logging.Formatter;
import java.util.logging.LogRecord;

public class GenericFotmat extends Formatter {
	@SuppressWarnings("deprecation")
	@Override
	public String format(LogRecord record) {
		
		return new Date().toLocaleString() + "-->"+ record.getLevel()+ ":" + record.getMessage() + ":)\r\n";
	}

}
