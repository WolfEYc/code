import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Empty Queue Tests")
public class EmptyCircularArrayQueue {

	private CircularArrayQueue<String> TARGET = init();
	private CircularArrayQueue<String> T = init();

	public CircularArrayQueue<String> init() {

		return new CircularArrayQueue<String>(3);
	
	}

	@org.junit.Test(timeout=12000)
	@jug.TestName("size() and isEmpty()")
	public void Test1() throws Throwable {
		
		org.junit.Assert.assertEquals("size() and isEmpty()", (Object)(true), (Object)((T.size() == 0 && T.isEmpty())));
	}

	@org.junit.Test()
	@jug.TestName("first() is null")
	public void Test2() throws Throwable {
		
		org.junit.Assert.assertEquals("first() is null", (Object)(null), (Object)(T.first()));
	}

	@org.junit.Test()
	@jug.TestName("enqueue(\"A\") and dequeue()")
	public void Test3() throws Throwable {
		T.enqueue("A");
		
		org.junit.Assert.assertEquals("enqueue(\"A\") and dequeue()", (Object)("A"), (Object)(T.dequeue()));
	}

	@org.junit.Test()
	@jug.TestName("enqueue(\"A\") and dequeue()")
	public void Test4() throws Throwable {
		T.enqueue("A");
		
		org.junit.Assert.assertEquals("enqueue(\"A\") and dequeue()", (Object)(1), (Object)(T.size()));
	}

}
