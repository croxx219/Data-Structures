package structures;

import common.Node;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class LinkedList<T> {
    private static final Logger LOGGER = LogManager.getLogger(LinkedList.class.getName());
    
    Node<T> head;
    int size;

    public LinkedList() {
        head = null;
        size = 0;
    }

    public void add(T data) {
        Node<T> newNode = new Node<>(data);
        if (this.head == null) {
            this.head = newNode;
        } else {
            Node<T> cursor = this.head;
            while (cursor.next != null) {
                cursor = cursor.next;
            }
            cursor.next = newNode;
        }
    }

    public void remove(T dataToRemove) {
        Node<T> currNode = this.head;
        Node<T> prevNode = null;

        if (!contains(dataToRemove)) {
            LOGGER.warn(dataToRemove + " not found");
        }

        if (currNode != null && currNode.data == dataToRemove) {
            this.head = currNode.next;
            LOGGER.info(dataToRemove + " found and deleted");
            size++;
        }

        while (currNode != null && currNode.data != dataToRemove) {
            prevNode = currNode;
            currNode = currNode.next;
        }

        if (currNode != null) {
            prevNode.next = currNode.next;
            LOGGER.info(dataToRemove + " found and deleted");
            size++;
        }
    }

    public void remove(int index) {
        Node<T> currNode = this.head;
        Node<T> prev = null;

        if (index > size - 1) {
            LOGGER.error("Position: " + index + " is not valid");
        }

        if (index == 0 && currNode != null) {
            LOGGER.info("Element: " + this.head + " at position : " + index + " has been deleted");
            this.head = currNode.next;
            size--;
        }

        int counter = 0;

        while (currNode != null) {
            if (counter == index) {
                LOGGER.info("Element: " + currNode + " at position : " + index + " has been deleted");
                prev.next = currNode.next;
                size--;
                break;
            }

            prev = currNode;
            currNode = currNode.next;
            counter++;
        }
    }

    public boolean contains(T dataToRemove) {
        Node<T> currNode = this.head;
        while (currNode != null) {
            currNode = currNode.next;
            if (currNode.data == dataToRemove)
                return true;
        }
        return false;
    }

    @Override
    public String toString() {
        Node currNode = this.head;
        StringBuilder builder = new StringBuilder();
        builder.append("LinkedList: ");

        while (currNode != null) {
            builder.append(currNode.data + " ");
            currNode = currNode.next;
        }
        builder.append("\n");
        return builder.toString();
    }
}

