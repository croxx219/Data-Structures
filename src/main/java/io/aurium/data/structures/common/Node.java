package io.aurium.data.structures.common;

import java.util.Objects;

public class Node<T> {
	public T data;
	public Node<T> next;

	public Node(T data) {
		this.next = null;
		this.data = data;
	}

	public Node() {
		this.next = null;
		this.data = null;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (!(o instanceof Node)) return false;
		Node<?> biNode = (Node<?>) o;
		return Objects.equals(data, biNode.data) &&
			Objects.equals(next, biNode.next);
	}

	@Override
	public int hashCode() {
		return Objects.hash(data, next);
	}

	@Override
	public String toString() {
		return "Node{" +
			"data=" + data +
			", next=" + next +
			'}';
	}
}
