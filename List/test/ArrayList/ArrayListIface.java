import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Test ArrayList Interface {\"1\",..., \"50\"}")
public class ArrayListIface {

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

	@org.junit.Test(timeout=12000)
	@jug.TestName("size() is 50")
	public void Test1() throws Throwable {
		
		org.junit.Assert.assertEquals("size() is 50", (Object)(true), (Object)(T.size() == 50 && !T.isEmpty()));
	}

	@org.junit.Test()
	@jug.TestName("get(0) equals \"1\"")
	public void Test2() throws Throwable {
		
		org.junit.Assert.assertEquals("get(0) equals \"1\"", (Object)("1"), (Object)(T.get(0)));
	}

	@org.junit.Test()
	@jug.TestName("get(7) equals \"8\"")
	public void Test3() throws Throwable {
		
		org.junit.Assert.assertEquals("get(7) equals \"8\"", (Object)("8"), (Object)(T.get(7)));
	}

	@org.junit.Test()
	@jug.TestName("get(25) equals \"26\"")
	public void Test4() throws Throwable {
		
		org.junit.Assert.assertEquals("get(25) equals \"26\"", (Object)("26"), (Object)(T.get(25)));
	}

	@org.junit.Test()
	@jug.TestName("get(49) equals \"50\"")
	public void Test5() throws Throwable {
		
		org.junit.Assert.assertEquals("get(49) equals \"50\"", (Object)("50"), (Object)(T.get(49)));
	}

	@org.junit.Test()
	@jug.TestName("set(0, \"X\") returns 1")
	public void Test6() throws Throwable {
		
		org.junit.Assert.assertEquals("set(0, \"X\") returns 1", (Object)("1"), (Object)(T.set(0,"X")));
	}

	@org.junit.Test()
	@jug.TestName("set(0, \"X\") ( get(0) )")
	public void Test7() throws Throwable {
		T.set(0,"X");
		
		org.junit.Assert.assertEquals("set(0, \"X\") ( get(0) )", (Object)("X"), (Object)(T.get(0)));
	}

	@org.junit.Test()
	@jug.TestName("set(0, \"X\") ( get(1) )")
	public void Test8() throws Throwable {
		T.set(0,"X");
		
		org.junit.Assert.assertEquals("set(0, \"X\") ( get(1) )", (Object)("2"), (Object)(T.get(1)));
	}

	@org.junit.Test()
	@jug.TestName("set(49, \"X\")")
	public void Test9() throws Throwable {
		
		org.junit.Assert.assertEquals("set(49, \"X\")", (Object)("50"), (Object)(T.set(49,"X")));
	}

	@org.junit.Test()
	@jug.TestName("set(49, \"X\") ( get(49) )")
	public void Test10() throws Throwable {
		T.set(49,"X");
		
		org.junit.Assert.assertEquals("set(49, \"X\") ( get(49) )", (Object)("X"), (Object)(T.get(49)));
	}

	@org.junit.Test()
	@jug.TestName("set(49, \"X\") ( get(48) )")
	public void Test11() throws Throwable {
		T.set(49,"X");
		
		org.junit.Assert.assertEquals("set(49, \"X\") ( get(48) )", (Object)("49"), (Object)(T.get(48)));
	}

	@org.junit.Test()
	@jug.TestName("set(24, \"X\")")
	public void Test12() throws Throwable {
		
		org.junit.Assert.assertEquals("set(24, \"X\")", (Object)("26"), (Object)(T.set(25,"X")));
	}

	@org.junit.Test()
	@jug.TestName("set(24, \"X\") ( get(24) )")
	public void Test13() throws Throwable {
		T.set(24,"X");
		
		org.junit.Assert.assertEquals("set(24, \"X\") ( get(24) )", (Object)("X"), (Object)(T.get(24)));
	}

	@org.junit.Test()
	@jug.TestName("set(24, \"X\") ( get(23) )")
	public void Test14() throws Throwable {
		T.set(24,"X");
		
		org.junit.Assert.assertEquals("set(24, \"X\") ( get(23) )", (Object)("24"), (Object)(T.get(23)));
	}

	@org.junit.Test()
	@jug.TestName("set(24, \"X\") ( get(25) )")
	public void Test15() throws Throwable {
		T.set(24,"X");
		
		org.junit.Assert.assertEquals("set(24, \"X\") ( get(25) )", (Object)("26"), (Object)(T.get(25)));
	}

	@org.junit.Test()
	@jug.TestName("add(0, \"X\") (size())")
	public void Test16() throws Throwable {
		T.add(0,"X");
		
		org.junit.Assert.assertEquals("add(0, \"X\") (size())", (Object)(51), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("add(0, \"X\") (get(0))")
	public void Test17() throws Throwable {
		T.add(0,"X");
		
		org.junit.Assert.assertEquals("add(0, \"X\") (get(0))", (Object)("X"), (Object)(T.get(0)));
	}

	@org.junit.Test()
	@jug.TestName("add(0, \"X\") (get(1))")
	public void Test18() throws Throwable {
		T.add(0,"X");
		
		org.junit.Assert.assertEquals("add(0, \"X\") (get(1))", (Object)("1"), (Object)(T.get(1)));
	}

	@org.junit.Test()
	@jug.TestName("add(50, \"X\") (size())")
	public void Test19() throws Throwable {
		T.add(50,"X");
		
		org.junit.Assert.assertEquals("add(50, \"X\") (size())", (Object)(51), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("add(50, \"X\") (get(50))")
	public void Test20() throws Throwable {
		T.add(50,"X");
		
		org.junit.Assert.assertEquals("add(50, \"X\") (get(50))", (Object)("X"), (Object)(T.get(50)));
	}

	@org.junit.Test()
	@jug.TestName("add(50, \"X\") (get(49))")
	public void Test21() throws Throwable {
		T.add(50,"X");
		
		org.junit.Assert.assertEquals("add(50, \"X\") (get(49))", (Object)("50"), (Object)(T.get(49)));
	}

	@org.junit.Test()
	@jug.TestName("add(30, \"X\") (size())")
	public void Test22() throws Throwable {
		T.add(30,"X");
		
		org.junit.Assert.assertEquals("add(30, \"X\") (size())", (Object)(51), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("add(30, \"X\") (get(30))")
	public void Test23() throws Throwable {
		T.add(30,"X");
		
		org.junit.Assert.assertEquals("add(30, \"X\") (get(30))", (Object)("X"), (Object)(T.get(30)));
	}

	@org.junit.Test()
	@jug.TestName("add(30, \"X\") (get(29))")
	public void Test24() throws Throwable {
		T.add(30,"X");
		
		org.junit.Assert.assertEquals("add(30, \"X\") (get(29))", (Object)("30"), (Object)(T.get(29)));
	}

	@org.junit.Test()
	@jug.TestName("add(30, \"X\") (get(31))")
	public void Test25() throws Throwable {
		T.add(30,"X");
		
		org.junit.Assert.assertEquals("add(30, \"X\") (get(31))", (Object)("31"), (Object)(T.get(31)));
	}

	@org.junit.Test()
	@jug.TestName("remove(0)")
	public void Test26() throws Throwable {
		
		org.junit.Assert.assertEquals("remove(0)", (Object)("1"), (Object)(T.remove(0)));
	}

	@org.junit.Test()
	@jug.TestName("remove(0) (size())")
	public void Test27() throws Throwable {
		T.remove(0);
		
		org.junit.Assert.assertEquals("remove(0) (size())", (Object)(49), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("remove(0) (get(0))")
	public void Test28() throws Throwable {
		T.remove(0);
		
		org.junit.Assert.assertEquals("remove(0) (get(0))", (Object)("2"), (Object)(T.get(0)));
	}

	@org.junit.Test()
	@jug.TestName("remove(0) (get(48))")
	public void Test29() throws Throwable {
		T.remove(0);
		
		org.junit.Assert.assertEquals("remove(0) (get(48))", (Object)("50"), (Object)(T.get(48)));
	}

	@org.junit.Test()
	@jug.TestName("remove(20)")
	public void Test30() throws Throwable {
		
		org.junit.Assert.assertEquals("remove(20)", (Object)("21"), (Object)(T.remove(20)));
	}

	@org.junit.Test()
	@jug.TestName("remove(20) (size())")
	public void Test31() throws Throwable {
		T.remove(20);
		
		org.junit.Assert.assertEquals("remove(20) (size())", (Object)(49), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("remove(20) (get(20))")
	public void Test32() throws Throwable {
		T.remove(20);
		
		org.junit.Assert.assertEquals("remove(20) (get(20))", (Object)("22"), (Object)(T.get(20)));
	}

	@org.junit.Test()
	@jug.TestName("remove(20) (get(19))")
	public void Test33() throws Throwable {
		T.remove(20);
		
		org.junit.Assert.assertEquals("remove(20) (get(19))", (Object)("20"), (Object)(T.get(19)));
	}

	@org.junit.Test()
	@jug.TestName("remove(20) (get(48))")
	public void Test34() throws Throwable {
		T.remove(20);
		
		org.junit.Assert.assertEquals("remove(20) (get(48))", (Object)("50"), (Object)(T.get(48)));
	}

	@org.junit.Test()
	@jug.TestName("remove(49)")
	public void Test35() throws Throwable {
		
		org.junit.Assert.assertEquals("remove(49)", (Object)("50"), (Object)(T.remove(49)));
	}

	@org.junit.Test()
	@jug.TestName("remove(49) (get(0))")
	public void Test36() throws Throwable {
		T.remove(49);
		
		org.junit.Assert.assertEquals("remove(49) (get(0))", (Object)("1"), (Object)(T.get(0)));
	}

	@org.junit.Test()
	@jug.TestName("remove(49) (get(48))")
	public void Test37() throws Throwable {
		T.remove(49);
		
		org.junit.Assert.assertEquals("remove(49) (get(48))", (Object)("49"), (Object)(T.get(48)));
	}

}
