package io.aurium.data.structures.structures;

import io.aurium.data.structures.common.BiNode;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class Stack<T> {
	private static final Logger LOGGER = LogManager.getLogger(LinkedList.class.getName());
	private static final int MAX_SIZE = 100;
	public BiNode<T> top;
	private int size;

	public Stack() {
		size = 0;
		top = null;
	}

	boolean isEmpty() {
		return (top != null);
	}

	public void push(T newElement) {
		if (size + 1 > MAX_SIZE) {
			throw new StackOverflowError("Stack Overflow");
		} else {
			BiNode<T> newAdd = new BiNode<>(newElement);
			if (size > 0) {
				top.next = newAdd;
				newAdd.prev = top;
			}
			top = newAdd;
			size++;
			LOGGER.info("{} pushed into stack", newElement);
		}
	}

	public T pop() {
		if (size - 1 < 0) {
			throw new StackOverflowError("Stack Underflow");
		} else {
			T toReturn = top.data;
			top = top.prev;
			top.next = null;
			size--;
			return toReturn;
		}
	}

	@Override
	public String toString() {
		BiNode<T> currNode = this.top;
		StringBuilder builder = new StringBuilder();
		builder.append("Stack: ");

		while (currNode != null) {
			builder.append(currNode.data + ", ");
			currNode = currNode.prev;
		}
		builder.append("\n");
		return builder.toString();
	}
}
