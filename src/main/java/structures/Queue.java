package structures;

import common.BiNode;
import common.Node;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.NoSuchElementException;

public class Queue<T> {
	private static final Logger LOGGER = LogManager.getLogger(LinkedList.class.getName());

	public int size;
	BiNode<T> front;
	BiNode<T> rear;

	public Queue() {
		this.size = 0;
		front = new BiNode<>();
		rear = new BiNode<>();
		front.prev = rear;
		front = rear;
	}

	public boolean isEmpty(Queue queue) {
		return (queue.size == 0);
	}

	public void enqueue(T item) {
		BiNode<T> temp = new BiNode<>(item);
		temp.next = rear;
		rear.prev = temp;
		rear = temp;
		this.size = this.size + 1;
		if (size == 1) front = rear;
		LOGGER.info("{} enqueued to queue", item);
	}


	public T dequeue() {
		if (isEmpty(this))
			throw new NoSuchElementException("Queue is empty");

		T item = front.data;
		BiNode<T> newFront = new BiNode<>(front.prev.data);
		newFront.next = front;
		front.prev = newFront;
		front = newFront;
		this.size = this.size - 1;
		return item;
	}

	public T peek() {
		if (isEmpty(this))
			throw new NoSuchElementException("Queue is empty");

		return front.data;
	}

	@Override
	public String toString() {
		Node<T> currNode = this.rear;
		StringBuilder builder = new StringBuilder();
		builder.append("Queue: ");

		while (currNode.next != null) {
			builder.append(currNode.data + ", ");
			currNode = currNode.next;
		}
		builder.append("\n");
		return builder.toString();
	}
}
