import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Test Iterator method {\"Five\", \"Four\", \"Three\", \"Two\", \"One\"}")
public class DoublyLinkedListIterator {

	private DoublyLinkedList<String> TARGET = init();
	private DoublyLinkedList<String> T = init();

	public DoublyLinkedList<String> init() {

		return new DoublyLinkedList<String>();
	
	}

	@Before
	public void setup() throws Throwable {
		T.addFirst("One");
			T.addFirst("Two");
			T.addFirst("Three");
			T.addFirst("Four");
			T.addFirst("Five");
	}

	@org.junit.Test(timeout=15000)
	@jug.TestName("for (string S: iterator){...}")
	public void Test1() throws Throwable {
		String[] goal = {"Five", "Four", "Three", "Two", "One"}
		;
		java.util.ArrayList<String> list = new java.util.ArrayList<String>(5);
		for(String s: T){ 
				list.add(s);
			}
		
		org.junit.Assert.assertArrayEquals("for (string S: iterator){...}", goal, list.toArray(new String[5]));
	}

	@org.junit.Test()
	@jug.TestName("for (Position<String> P: iterator){...}")
	public void Test2() throws Throwable {
		String[] goal = {"Five", "Four", "Three", "Two", "One"}
		;
		java.util.ArrayList<String> list = new java.util.ArrayList<String>(5);
		for(Position<String> p: T.positions()){ 
				list.add(p.getElement());
			}
		
		org.junit.Assert.assertArrayEquals("for (Position<String> P: iterator){...}", goal, list.toArray(new String[5]));
	}

}
