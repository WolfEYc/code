import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Empty List Tests")
public class EmptyList {

	private DoublyLinkedList<String> TARGET = init();
	private DoublyLinkedList<String> T = init();

	public DoublyLinkedList<String> init() {

		return new DoublyLinkedList<String>();
	
	}

	@org.junit.Test(timeout=15000)
	@jug.TestName("size() and isEmpty()")
	public void Test1() throws Throwable {
		
		org.junit.Assert.assertEquals("size() and isEmpty()", (Object)(true), (Object)((T.size() == 0 && T.isEmpty())));
	}

	@org.junit.Test()
	@jug.TestName("addFirst(\"0\") and first().getElement()")
	public void Test2() throws Throwable {
		T.addFirst("0");
		
		org.junit.Assert.assertEquals("addFirst(\"0\") and first().getElement()", (Object)("0"), (Object)(T.first().getElement()));
	}

	@org.junit.Test()
	@jug.TestName("addLast(\"0\") and last().getElement()")
	public void Test3() throws Throwable {
		T.addLast("0");
		
		org.junit.Assert.assertEquals("addLast(\"0\") and last().getElement()", (Object)("0"), (Object)(T.last().getElement()));
	}

	@org.junit.Test()
	@jug.TestName("addLast(\"0\") and size() / isEmpty()")
	public void Test4() throws Throwable {
		T.addLast("0");
		
		org.junit.Assert.assertEquals("addLast(\"0\") and size() / isEmpty()", (Object)(true), (Object)(T.size() == 1 && !T.isEmpty()));
	}

	@org.junit.Test()
	@jug.TestName("first()")
	public void Test5() throws Throwable {
		
		org.junit.Assert.assertEquals("first()", (Object)(null), (Object)(T.first()));
	}

	@org.junit.Test()
	@jug.TestName("last()")
	public void Test6() throws Throwable {
		
		org.junit.Assert.assertEquals("last()", (Object)(null), (Object)(T.last()));
	}

}
