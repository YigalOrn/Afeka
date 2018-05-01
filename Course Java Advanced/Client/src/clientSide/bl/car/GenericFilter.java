package clientSide.bl.car;

import java.util.logging.Filter;
import java.util.logging.LogRecord;

public class GenericFilter implements Filter {
	Object target;
	public GenericFilter(Object target){
	this.target = target;
	}
	
	@Override
	public boolean isLoggable(LogRecord record) {
		if (record.getParameters() != null) {
			Object temp = record.getParameters()[0];
			return target == temp;
		}
		else
			return false;
	}

}
