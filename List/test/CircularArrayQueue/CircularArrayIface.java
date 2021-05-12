import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Test CircularArrayQueue Interface {\"A\",\"B\",\"C\"}")
public class CircularArrayIface {

	private CircularArrayQueue TARGET = init();
	private CircularArrayQueue T = init();

	public CircularArrayQueue init() {

		return new CircularArrayQueue<String>(3);
	
	}

	@Before
	public void setup() throws Throwable {
		/* insert "A", "B", "C" */
			T.enqueue("A");
			T.enqueue("B");
			T.enqueue("C");
	}

	@org.junit.Test(timeout=12000)
	@jug.TestName("size() is 3")
	public void Test1() throws Throwable {
		
		org.junit.Assert.assertEquals("size() is 3", (Object)(3), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("first() is \"A\"")
	public void Test2() throws Throwable {
		
		org.junit.Assert.assertEquals("first() is \"A\"", (Object)("A"), (Object)(T.first()));
	}

	@org.junit.Test()
	@jug.TestName("dequeue() is \"A\"")
	public void Test3() throws Throwable {
		
		org.junit.Assert.assertEquals("dequeue() is \"A\"", (Object)("A"), (Object)(T.dequeue()));
	}

	@org.junit.Test()
	@jug.TestName("dequeue() and size()")
	public void Test4() throws Throwable {
		T.dequeue();
		
		org.junit.Assert.assertEquals("dequeue() and size()", (Object)(2), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("dequeue(); dequeue() is \"B\"")
	public void Test5() throws Throwable {
		T.dequeue();
		
		org.junit.Assert.assertEquals("dequeue(); dequeue() is \"B\"", (Object)("B"), (Object)(T.dequeue()));
	}

	@org.junit.Test()
	@jug.TestName("dequeue(); dequeue() and size()")
	public void Test6() throws Throwable {
		T.dequeue();
		T.dequeue();
		
		org.junit.Assert.assertEquals("dequeue(); dequeue() and size()", (Object)(1), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("dequeue(); dequeue(); dequeue() is \"C\"")
	public void Test7() throws Throwable {
		T.dequeue();
		T.dequeue();
		
		org.junit.Assert.assertEquals("dequeue(); dequeue(); dequeue() is \"C\"", (Object)("C"), (Object)(T.dequeue()));
	}

	@org.junit.Test()
	@jug.TestName("dequeue(); dequeue(); dequeue() and size()")
	public void Test8() throws Throwable {
		T.dequeue();
		T.dequeue();
		T.dequeue();
		
		org.junit.Assert.assertEquals("dequeue(); dequeue(); dequeue() and size()", (Object)(0), (Object)(T.size()));
	}

}
