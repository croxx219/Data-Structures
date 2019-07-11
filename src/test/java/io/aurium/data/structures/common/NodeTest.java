package io.aurium.data.structures.common;

import org.hamcrest.CoreMatchers;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.hamcrest.CoreMatchers.is;
import static org.junit.Assert.*;

public class NodeTest {
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
	public void hasNextAndDataGivenAnyNode() {
		Node<Integer> intNode = new Node<>(10);
		intNode.next = new Node<>(20);
		assertNotNull(intNode.next);
		assertNotNull(intNode.data);
		Node<String> stringNode = new Node<>();
		assertNull(stringNode.next);
		assertNull(stringNode.data);
	}

	@Test
	public void equalsAndHashCodeExistsAndExecutesAsExpected() throws NoSuchMethodException {
		assertNotNull(Node.class.getMethod("equals", Object.class));
		assertNotNull(Node.class.getMethod("hashCode"));
		Node<Integer> node1 = new Node<>(10);
		Node<Integer> node2 = new Node<>(10);
		Node<Integer> node3 = new Node<>(11);
		assertEquals(node1, node2);
		assertNotEquals(node1, node3);
		Node<String> node4 = new Node<>("Hello");
		Node<String> node5 = new Node<>("Hello");
		Node<String> node6 = new Node<>("Hi");
		assertEquals(node1, node2);
		assertNotEquals(node1, node3);
		assertThat(node1.hashCode(), is(CoreMatchers.<Integer>instanceOf(Integer.class)));
	}

	@Test
	public void toStringExists() throws NoSuchMethodException {
		assertNotNull(Node.class.getMethod("toString"));
		Node<Integer> node = new Node<>(10999);
		System.out.print(node);
		assertEquals(outContent.toString(), node.toString());
	}
}
