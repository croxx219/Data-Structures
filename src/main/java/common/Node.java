package common;

import java.util.Objects;

public class Node<T> {
    public T data;
    public Node<T> next;

	public Node() {
		this.data = null;
		this.next = null;
	}

    public Node(T data) {
        this.data = data;
        this.next = null;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Node)) return false;
        Node<?> node = (Node<?>) o;
        return Objects.equals(data, node.data) &&
                Objects.equals(next, node.next);
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
