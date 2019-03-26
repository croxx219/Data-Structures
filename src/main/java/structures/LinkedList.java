package structures;

import common.Node;

public class LinkedList<T> {
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
            System.out.println(dataToRemove + " not found");
        }

        if (currNode != null && currNode.data == dataToRemove) {
            this.head = currNode.next;
            System.out.println(dataToRemove + " found and deleted");
            size++;
        }

        while (currNode != null && currNode.data != dataToRemove) {
            prevNode = currNode;
            currNode = currNode.next;
        }

        if (currNode != null) {
            prevNode.next = currNode.next;
            System.out.println(dataToRemove + " found and deleted");
            size++;
        }
    }

    public void remove(int index) {
        Node<T> currNode = this.head;
        Node<T> prev = null;

        if (index > size - 1) {
            System.out.println("Position: " + index + " is not valid");
        }

        if (index == 0 && currNode != null) {
            System.out.println("Element: " + this.head + " at position : " + index + " has been deleted");
            this.head = currNode.next;
            size--;
        }

        int counter = 0;

        while (currNode != null) {
            if (counter == index) {
                System.out.println("Element: " + currNode + " at position : " + index + " has been deleted");
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

