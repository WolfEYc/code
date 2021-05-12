//package csc311;

import net.datastructures.Position;

public class TestNode<E> implements Position<E>{
private E element;
								
	public TestNode(E e) {
		element = e;
	}
	@Override
	public E getElement() throws IllegalStateException {
		return element;
	}
} // End of Node class
