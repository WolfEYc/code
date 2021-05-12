import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Empty List Tests")
public class EmptyArrayList {

	private ArrayList<String> TARGET = init();
	private ArrayList<String> T = init();

	public ArrayList<String> init() {

		return new ArrayList<String>();
	
	}

	@org.junit.Test(timeout=12000)
	@jug.TestName("size() and isEmpty()")
	public void Test1() throws Throwable {
		
		org.junit.Assert.assertEquals("size() and isEmpty()", (Object)(true), (Object)((T.size() == 0 && T.isEmpty())));
	}

	@org.junit.Test()
	@jug.TestName("add(0,\"A\") and get(0)")
	public void Test2() throws Throwable {
		T.add(0,"A");
		
		org.junit.Assert.assertEquals("add(0,\"A\") and get(0)", (Object)("A"), (Object)(T.get(0)));
	}

	@org.junit.Test()
	@jug.TestName("add(0,\"A\") and get(0)")
	public void Test3() throws Throwable {
		T.add(0,"A");
		
		org.junit.Assert.assertEquals("add(0,\"A\") and get(0)", (Object)(1 ), (Object)(T.size()));
	}

}
