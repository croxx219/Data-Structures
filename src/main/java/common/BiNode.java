package common;

import java.util.Objects;

public class BiNode<T> extends Node<T> {
	public Node<T> prev;

	public BiNode(T data) {
		super(data);
		this.prev = null;
	}

	public BiNode() {
		super(null);
		this.prev = null;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (!(o instanceof BiNode)) return false;
		if (!super.equals(o)) return false;
		BiNode<?> biNode = (BiNode<?>) o;
		return Objects.equals(prev, biNode.prev);
	}

	@Override
	public int hashCode() {
		return Objects.hash(super.hashCode(), prev);
	}

	@Override
	public String toString() {
		return "BiNode{" +
			"prev=" + prev +
			", data=" + data +
			", next=" + next +
			'}';
	}
}
