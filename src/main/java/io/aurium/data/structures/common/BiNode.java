package io.aurium.data.structures.common;

import java.util.Objects;

public class BiNode<T> {
	public T data;
	public BiNode<T> prev;
	public BiNode<T> next;

	public BiNode(T data) {
		this.prev = null;
		this.next = null;
		this.data = data;
	}

	public BiNode() {
		this.prev = null;
		this.next = null;
		this.data = null;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (!(o instanceof BiNode)) return false;
		BiNode<?> biNode = (BiNode<?>) o;
		return Objects.equals(data, biNode.data) &&
			Objects.equals(prev, biNode.prev) &&
			Objects.equals(next, biNode.next);
	}

	@Override
	public int hashCode() {
		return Objects.hash(data, prev, next);
	}

	@Override
	public String toString() {
		return "BiNode{" +
			"data=" + data +
			", prev=" + prev +
			", next=" + next +
			'}';
	}
}
