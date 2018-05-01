package utility.myexecuter;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class MyExecutor {

	private final ExecutorService executorService;

	public MyExecutor() {
		executorService = Executors.newCachedThreadPool();
	}

	public void submitTask(Runnable newTask) {
		executorService.execute(newTask);
	}

	public void closeExecutorsService() {
		try {
			executorService.awaitTermination(5, TimeUnit.SECONDS);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		executorService.shutdownNow();
	}
}
