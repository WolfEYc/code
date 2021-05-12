import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Capacity Function Tests")
public class ArrayListCapacity {

	private ArrayList TARGET = init();
	private ArrayList T = init();

	public ArrayList init() {

		return new ArrayList<String>();
	
	}

	@org.junit.Test(timeout=60000)
	@jug.TestName("capacity() when instantiation")
	public void Test1() throws Throwable {
		
		org.junit.Assert.assertEquals("capacity() when instantiation", (Object)(16), (Object)(T.capacity()));
	}

	@org.junit.Test()
	@jug.TestName("capacity() when expanding")
	public void Test2() throws Throwable {
		for (int i=0; i < 17; i++){
				T.addLast(String.valueOf(i));
			}
		
		org.junit.Assert.assertEquals("capacity() when expanding", (Object)(32), (Object)(T.capacity()));
	}

}
