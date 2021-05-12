import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Test iterator Methods {\"Five\", \"Four\", \"Three\", \"Two\", \"One\"}")
public class ArrayListIterators {

	private ArrayList<String> TARGET = init();
	private ArrayList<String> T = init();

	public ArrayList<String> init() {

		return new ArrayList<String>();
	
	}

	@Before
	public void setup() throws Throwable {
		T.add(0,"One");
			T.add(0,"Two");
			T.add(0,"Three");
			T.add(0,"Four");
			T.add(0,"Five");
	}

	@org.junit.Test(timeout=12000)
	@jug.TestName("for(String s: iterator){...}")
	public void Test1() throws Throwable {
		String[] goal = {"Five", "Four", "Three", "Two", "One"}
		;
		java.util.ArrayList<String> list = new java.util.ArrayList<String>(5);
		for(String s: T){
				list.add(s);
			}
		
		org.junit.Assert.assertArrayEquals("for(String s: iterator){...}", goal, list.toArray(new String[5]));
	}

}
