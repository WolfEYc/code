import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Test Deque Interface {\"1\", \"2\"}")
public class DequeIface {

	private DoublyLinkedList<String> TARGET = init();
	private DoublyLinkedList<String> T = init();

	public DoublyLinkedList<String> init() {

		return new DoublyLinkedList<String>();
	
	}

	@Before
	public void setup() throws Throwable {
		T.addLast("1");
			T.addLast("2");
	}

	@org.junit.Test(timeout=15000)
	@jug.TestName("size()/isEmpty()")
	public void Test1() throws Throwable {
		
		org.junit.Assert.assertEquals("size()/isEmpty()", (Object)(true), (Object)(T.size() == 2 && !T.isEmpty()));
	}

	@org.junit.Test()
	@jug.TestName("first().getElement()")
	public void Test2() throws Throwable {
		
		org.junit.Assert.assertEquals("first().getElement()", (Object)("1"), (Object)(T.first().getElement()));
	}

	@org.junit.Test()
	@jug.TestName("last()")
	public void Test3() throws Throwable {
		
		org.junit.Assert.assertEquals("last()", (Object)("2"), (Object)(T.last().getElement()));
	}

	@org.junit.Test()
	@jug.TestName("addFirst(\"0\") (getFirst)")
	public void Test4() throws Throwable {
		T.addFirst("0");
		
		org.junit.Assert.assertEquals("addFirst(\"0\") (getFirst)", (Object)("0"), (Object)(T.first().getElement()));
	}

	@org.junit.Test()
	@jug.TestName("addFirst(\"0\") (size)")
	public void Test5() throws Throwable {
		T.addFirst("0");
		
		org.junit.Assert.assertEquals("addFirst(\"0\") (size)", (Object)(3), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("addLast(\"3\") (getLast)")
	public void Test6() throws Throwable {
		T.addLast("3");
		
		org.junit.Assert.assertEquals("addLast(\"3\") (getLast)", (Object)("3"), (Object)(T.last().getElement()));
	}

	@org.junit.Test()
	@jug.TestName("addLast(\"3\") (size)")
	public void Test7() throws Throwable {
		T.addLast("3");
		
		org.junit.Assert.assertEquals("addLast(\"3\") (size)", (Object)(3), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("remove() (check size)")
	public void Test8() throws Throwable {
		T.remove(T.first());
		
		org.junit.Assert.assertEquals("remove() (check size)", (Object)(1), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("remove() (check remaining)")
	public void Test9() throws Throwable {
		T.remove(T.first());
		
		org.junit.Assert.assertEquals("remove() (check remaining)", (Object)("2"), (Object)(T.first().getElement()));
	}

	@org.junit.Test()
	@jug.TestName("removeFirst(), removeFirst()")
	public void Test10() throws Throwable {
		T.remove(T.first());
		
		org.junit.Assert.assertEquals("removeFirst(), removeFirst()", (Object)("2"), (Object)(T.removeFirst()));
	}

	@org.junit.Test()
	@jug.TestName("removeLast(), removeLast()")
	public void Test11() throws Throwable {
		T.remove(T.last());
		
		org.junit.Assert.assertEquals("removeLast(), removeLast()", (Object)("1"), (Object)(T.removeLast()));
	}

	@org.junit.Test()
	@jug.TestName("remove() (check size)")
	public void Test12() throws Throwable {
		T.remove(T.last());
		
		org.junit.Assert.assertEquals("remove() (check size)", (Object)(1), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("remove() (check remaining)")
	public void Test13() throws Throwable {
		T.remove(T.last());
		
		org.junit.Assert.assertEquals("remove() (check remaining)", (Object)("1"), (Object)(T.last().getElement()));
	}

}
