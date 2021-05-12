import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Test Exceptions {\"two\", \"items\"}")
public class ListExceptions {

	private DoublyLinkedList<String> TARGET = init();
	private DoublyLinkedList<String> T = init();

	public DoublyLinkedList<String> init() {

		return new DoublyLinkedList<String>();
	
	}

	@Before
	public void setup() throws Throwable {
		T.addFirst("items");
			T.addFirst("two");
	}

	@org.junit.Test(timeout=15000)
	@jug.TestName("T.before(p) throws exception")
	public void Test1() throws Throwable {
		Position<String> p = new TestNode<String>("Hi");
		
		{ boolean thrown = false;
			try {
				T.before(p);
			} catch (Throwable t) {
				thrown = true;
				org.junit.Assert.assertThat("T.before(p) throws exception", t, org.hamcrest.CoreMatchers.instanceOf(IllegalArgumentException.class));
			}
			if(!thrown){
				org.junit.Assert.fail("T.before(p) throws exception: Expected Throwable IllegalArgumentException");
			}
		}
	}

	@org.junit.Test()
	@jug.TestName("T.after(p) throws exception")
	public void Test2() throws Throwable {
		Position<String> p = new TestNode<String>("Hi");
		
		{ boolean thrown = false;
			try {
				T.after(p);
			} catch (Throwable t) {
				thrown = true;
				org.junit.Assert.assertThat("T.after(p) throws exception", t, org.hamcrest.CoreMatchers.instanceOf(IllegalArgumentException.class));
			}
			if(!thrown){
				org.junit.Assert.fail("T.after(p) throws exception: Expected Throwable IllegalArgumentException");
			}
		}
	}

	@org.junit.Test()
	@jug.TestName("T.addBefore(p,\"hi\")) throws exception")
	public void Test3() throws Throwable {
		Position<String> p = new TestNode<String>("Hi");
		
		{ boolean thrown = false;
			try {
				T.addBefore(p, "hi");
			} catch (Throwable t) {
				thrown = true;
				org.junit.Assert.assertThat("T.addBefore(p,\"hi\")) throws exception", t, org.hamcrest.CoreMatchers.instanceOf(IllegalArgumentException.class));
			}
			if(!thrown){
				org.junit.Assert.fail("T.addBefore(p,\"hi\")) throws exception: Expected Throwable IllegalArgumentException");
			}
		}
	}

	@org.junit.Test()
	@jug.TestName("T.addAfter(p,\"hi\")) throws exception")
	public void Test4() throws Throwable {
		Position<String> p = new TestNode<String>("Hi");
		
		{ boolean thrown = false;
			try {
				T.addAfter(p, "hi");
			} catch (Throwable t) {
				thrown = true;
				org.junit.Assert.assertThat("T.addAfter(p,\"hi\")) throws exception", t, org.hamcrest.CoreMatchers.instanceOf(IllegalArgumentException.class));
			}
			if(!thrown){
				org.junit.Assert.fail("T.addAfter(p,\"hi\")) throws exception: Expected Throwable IllegalArgumentException");
			}
		}
	}

	@org.junit.Test()
	@jug.TestName("T.set(p,\"hi you\")) throws exception")
	public void Test5() throws Throwable {
		Position<String> p = new TestNode<String>("Hi");
		
		{ boolean thrown = false;
			try {
				T.set(p, "hi you");
			} catch (Throwable t) {
				thrown = true;
				org.junit.Assert.assertThat("T.set(p,\"hi you\")) throws exception", t, org.hamcrest.CoreMatchers.instanceOf(IllegalArgumentException.class));
			}
			if(!thrown){
				org.junit.Assert.fail("T.set(p,\"hi you\")) throws exception: Expected Throwable IllegalArgumentException");
			}
		}
	}

	@org.junit.Test()
	@jug.TestName("T.remove(p)) throws exception")
	public void Test6() throws Throwable {
		Position<String> p = new TestNode<String>("Hi");
		
		{ boolean thrown = false;
			try {
				T.remove(p);
			} catch (Throwable t) {
				thrown = true;
				org.junit.Assert.assertThat("T.remove(p)) throws exception", t, org.hamcrest.CoreMatchers.instanceOf(IllegalArgumentException.class));
			}
			if(!thrown){
				org.junit.Assert.fail("T.remove(p)) throws exception: Expected Throwable IllegalArgumentException");
			}
		}
	}

}
