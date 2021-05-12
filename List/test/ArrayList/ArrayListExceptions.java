import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Test Exceptions {\"two\", \"items\"}")
public class ArrayListExceptions {

	private ArrayList<String> TARGET = init();
	private ArrayList<String> T = init();

	public ArrayList<String> init() {

		return new ArrayList<String>();
	
	}

	@Before
	public void setup() throws Throwable {
		T.add(0,"items");
			T.add(0,"two");
	}

	@org.junit.Test(timeout=12000)
	@jug.TestName("add(3, \"X\") throws IndexOutOfBoundsException")
	public void Test1() throws Throwable {
		
		{ boolean thrown = false;
			try {
				T.add(4, "X");
			} catch (Throwable t) {
				thrown = true;
				org.junit.Assert.assertThat("add(3, \"X\") throws IndexOutOfBoundsException", t, org.hamcrest.CoreMatchers.instanceOf(IndexOutOfBoundsException.class));
			}
			if(!thrown){
				org.junit.Assert.fail("add(3, \"X\") throws IndexOutOfBoundsException: Expected Throwable IndexOutOfBoundsException");
			}
		}
	}

	@org.junit.Test()
	@jug.TestName("get(-1) throws IndexOutOfBoundsException")
	public void Test2() throws Throwable {
		
		{ boolean thrown = false;
			try {
				T.get(-1);
			} catch (Throwable t) {
				thrown = true;
				org.junit.Assert.assertThat("get(-1) throws IndexOutOfBoundsException", t, org.hamcrest.CoreMatchers.instanceOf(IndexOutOfBoundsException.class));
			}
			if(!thrown){
				org.junit.Assert.fail("get(-1) throws IndexOutOfBoundsException: Expected Throwable IndexOutOfBoundsException");
			}
		}
	}

	@org.junit.Test()
	@jug.TestName("remove(2) throws IndexOutOfBoundsException")
	public void Test3() throws Throwable {
		
		{ boolean thrown = false;
			try {
				T.remove(2);
			} catch (Throwable t) {
				thrown = true;
				org.junit.Assert.assertThat("remove(2) throws IndexOutOfBoundsException", t, org.hamcrest.CoreMatchers.instanceOf(IndexOutOfBoundsException.class));
			}
			if(!thrown){
				org.junit.Assert.fail("remove(2) throws IndexOutOfBoundsException: Expected Throwable IndexOutOfBoundsException");
			}
		}
	}

	@org.junit.Test()
	@jug.TestName("set(3, \"X\") throws IndexOutOfBoundsException")
	public void Test4() throws Throwable {
		
		{ boolean thrown = false;
			try {
				T.set(3, "X");
			} catch (Throwable t) {
				thrown = true;
				org.junit.Assert.assertThat("set(3, \"X\") throws IndexOutOfBoundsException", t, org.hamcrest.CoreMatchers.instanceOf(IndexOutOfBoundsException.class));
			}
			if(!thrown){
				org.junit.Assert.fail("set(3, \"X\") throws IndexOutOfBoundsException: Expected Throwable IndexOutOfBoundsException");
			}
		}
	}

}
