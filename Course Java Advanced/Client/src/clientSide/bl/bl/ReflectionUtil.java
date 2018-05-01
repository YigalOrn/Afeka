package clientSide.bl.bl;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashMap;
import java.util.concurrent.locks.ReentrantLock;

public class ReflectionUtil {

	private static final HashMap<String, Object> vals = new HashMap<>(3);
	private static ReentrantLock lock = new ReentrantLock(true);

	public static void activateByMethodName(String classNameStr,
			String methodNameStr) throws ClassNotFoundException {
		lock.lock();
		try {

			Class<?> contextClass = Class.forName(classNameStr);
			try {
				Object obj = contextClass.newInstance();
				Method method = contextClass.getMethod(methodNameStr,
						new Class[] {});
				Object returnVal = method.invoke(obj);

				if (returnVal != null) {
					vals.put(methodNameStr, (String) returnVal);
				}// if

			} catch (IllegalAccessException | InstantiationException
					| NoSuchMethodException | SecurityException
					| IllegalArgumentException | InvocationTargetException e) {
				e.printStackTrace();
			}

		} finally {
			lock.unlock();
		}

	}//

	public static Object getReturnValByMethodName(String methodNameStr) {
		lock.lock();
		Object temp = null;
		try {
			temp = vals.get(methodNameStr);
		} finally {
			lock.unlock();
		}
		return temp;
	}//
}//
