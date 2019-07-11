package io.aurium.data.structures.common;

import org.hamcrest.CoreMatchers;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.hamcrest.CoreMatchers.is;
import static org.junit.Assert.*;

public class BiNodeTest {
	private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
	private final ByteArrayOutputStream errContent = new ByteArrayOutputStream();
	private final PrintStream originalOut = System.out;
	private final PrintStream originalErr = System.err;

	@Before
	public void setUpStreams() {
		System.setOut(new PrintStream(outContent));
		System.setErr(new PrintStream(errContent));
	}

	@After
	public void restoreStreams() {
		System.setOut(originalOut);
		System.setErr(originalErr);
	}

	@Test
	public void hasNextAndDataGivenAnyBiNode() {
		BiNode<Integer> intBiNode = new BiNode<>(10);
		intBiNode.next = new BiNode<>(20);
		intBiNode.prev = new BiNode<>(30);
		assertNotNull(intBiNode.next);
		assertNotNull(intBiNode.data);
		BiNode<String> stringBiNode = new BiNode<>();
		assertNull(stringBiNode.next);
		assertNull(stringBiNode.data);
	}

	@Test
	public void equalsAndHashCodeExistsAndExecutesAsExpected() throws NoSuchMethodException {
		assertNotNull(BiNode.class.getMethod("equals", Object.class));
		assertNotNull(BiNode.class.getMethod("hashCode"));
		BiNode<Integer> BiNode1 = new BiNode<>(10);
		BiNode<Integer> BiNode2 = new BiNode<>(10);
		BiNode<Integer> BiNode3 = new BiNode<>(11);
		assertEquals(BiNode1, BiNode2);
		assertNotEquals(BiNode1, BiNode3);
		BiNode<String> BiNode4 = new BiNode<>("Hello");
		BiNode<String> BiNode5 = new BiNode<>("Hello");
		BiNode<String> BiNode6 = new BiNode<>("Hi");
		assertEquals(BiNode1, BiNode2);
		assertNotEquals(BiNode1, BiNode3);
		assertThat(BiNode1.hashCode(), is(CoreMatchers.<Integer>instanceOf(Integer.class)));
	}

	@Test
	public void toStringExists() throws NoSuchMethodException {
		assertNotNull(BiNode.class.getMethod("toString"));
		BiNode<Integer> BiNode = new BiNode<>(10999);
		System.out.print(BiNode);
		assertEquals(outContent.toString(), BiNode.toString());
	}
}