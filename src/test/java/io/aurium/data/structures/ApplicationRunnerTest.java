package io.aurium.data.structures;

import mockit.Tested;
import org.junit.Test;

public class ApplicationRunnerTest {
	@Tested
	private ApplicationRunner tested;

	@Test
	public void canStart() {
		ApplicationRunner.main(null);
	}
}