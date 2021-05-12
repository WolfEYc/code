import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("ArrayList Stack/Queue Tests")
public class ArrayListStackQueue {

	private ArrayList TARGET = init();
	private ArrayList T = init();

	public ArrayList init() {

		return new ArrayList<String>();
	
	}

	@Before
	public void setup() throws Throwable {
		/* insert 1,2, to 50 to the list*/
			for(int i = 1; i <= 50; i++){
				T.add(T.size(),String.valueOf(i));
			}
	}

	@org.junit.Test(timeout=60000)
	@jug.TestName("addFirst() Test")
	public void Test1() throws Throwable {
		T.addFirst("A");
		
		org.junit.Assert.assertEquals("addFirst() Test", (Object)("A"), (Object)(T.get(0)));
	}

	@org.junit.Test()
	@jug.TestName("removeFirst() Test")
	public void Test2() throws Throwable {
		T.add(0, "A");
		
		org.junit.Assert.assertEquals("removeFirst() Test", (Object)("A"), (Object)(T.removeFirst()));
	}

	@org.junit.Test()
	@jug.TestName("addLast() Test")
	public void Test3() throws Throwable {
		T.addLast("A");
		
		org.junit.Assert.assertEquals("addLast() Test", (Object)("A"), (Object)(T.get(T.size()-1)));
	}

	@org.junit.Test()
	@jug.TestName("removeLast() Test")
	public void Test4() throws Throwable {
		T.add(T.size(), "A");
		
		org.junit.Assert.assertEquals("removeLast() Test", (Object)("A"), (Object)(T.removeLast()));
	}

}
