import org.junit.*;

import csc311.*;
import jug.*;
import net.datastructures.*;

@jug.SuiteName("Test PositionList Interface {\"A\", \"b\", \"C\", \"d\", \"E\", \"f\", \"G\", \"h\", \"I\", \"j\"}")
public class PositionIface {

	private DoublyLinkedList<String> TARGET = init();
	private DoublyLinkedList<String> T = init();

	public DoublyLinkedList<String> init() {

		return new DoublyLinkedList<String>();
	
	}

	@Before
	public void setup() throws Throwable {
		T.addLast("A");
			T.addLast("b");
			T.addLast("C");
			T.addLast("d");
			T.addLast("E");
			T.addLast("f");
			T.addLast("G");
			T.addLast("h");
			T.addLast("I");
			T.addLast("j");
	}

	@org.junit.Test(timeout=15000)
	@jug.TestName("size()/isEmpty()")
	public void Test1() throws Throwable {
		
		org.junit.Assert.assertEquals("size()/isEmpty()", (Object)(true), (Object)(T.size() == 10 && !T.isEmpty()));
	}

	@org.junit.Test()
	@jug.TestName("first() is Position")
	public void Test2() throws Throwable {
		
		org.junit.Assert.assertThat("first() is Position", T.first(), org.hamcrest.CoreMatchers.instanceOf(Position.class));
	}

	@org.junit.Test()
	@jug.TestName("first().getElement() equals \"A\"")
	public void Test3() throws Throwable {
		
		org.junit.Assert.assertEquals("first().getElement() equals \"A\"", (Object)("A"), (Object)(T.first().getElement()));
	}

	@org.junit.Test()
	@jug.TestName("last() is Position")
	public void Test4() throws Throwable {
		
		org.junit.Assert.assertThat("last() is Position", T.last(), org.hamcrest.CoreMatchers.instanceOf(Position.class));
	}

	@org.junit.Test()
	@jug.TestName("last().getElement() equals \"j\"")
	public void Test5() throws Throwable {
		
		org.junit.Assert.assertEquals("last().getElement() equals \"j\"", (Object)("j"), (Object)(T.last().getElement()));
	}

	@org.junit.Test()
	@jug.TestName("after(first()) is Position")
	public void Test6() throws Throwable {
		
		org.junit.Assert.assertThat("after(first()) is Position", T.after(T.first()), org.hamcrest.CoreMatchers.instanceOf(Position.class));
	}

	@org.junit.Test()
	@jug.TestName("after(first()).getElement() equals \"b\"")
	public void Test7() throws Throwable {
		
		org.junit.Assert.assertEquals("after(first()).getElement() equals \"b\"", (Object)("b"), (Object)(T.after(T.first()).getElement()));
	}

	@org.junit.Test()
	@jug.TestName("after(after((first()))).getElement() equals \"C\"")
	public void Test8() throws Throwable {
		
		org.junit.Assert.assertEquals("after(after((first()))).getElement() equals \"C\"", (Object)("C"), (Object)(T.after(T.after(T.first())).getElement()));
	}

	@org.junit.Test()
	@jug.TestName("before(first()) equals null")
	public void Test9() throws Throwable {
		
		org.junit.Assert.assertEquals("before(first()) equals null", (Object)(null), (Object)(T.before(T.first())));
	}

	@org.junit.Test()
	@jug.TestName("before(last()) is Position")
	public void Test10() throws Throwable {
		
		org.junit.Assert.assertThat("before(last()) is Position", T.before(T.last()), org.hamcrest.CoreMatchers.instanceOf(Position.class));
	}

	@org.junit.Test()
	@jug.TestName("before(last()) equals \"I\"")
	public void Test11() throws Throwable {
		
		org.junit.Assert.assertEquals("before(last()) equals \"I\"", (Object)("I"), (Object)(T.before(T.last()).getElement()));
	}

	@org.junit.Test()
	@jug.TestName("before(before(last())) equals \"h\"")
	public void Test12() throws Throwable {
		
		org.junit.Assert.assertEquals("before(before(last())) equals \"h\"", (Object)("h"), (Object)(T.before(T.before(T.last())).getElement()));
	}

	@org.junit.Test()
	@jug.TestName("after(before(last())) == last()")
	public void Test13() throws Throwable {
		
		org.junit.Assert.assertEquals("after(before(last())) == last()", true, T.after(T.before(T.last())) == T.last());
	}

	@org.junit.Test()
	@jug.TestName("after(last()) equals null")
	public void Test14() throws Throwable {
		
		org.junit.Assert.assertEquals("after(last()) equals null", (Object)(null), (Object)(T.after(T.last())));
	}

	@org.junit.Test()
	@jug.TestName("before(before(before(before(last())))) == after(after(after(after(after(first())))))")
	public void Test15() throws Throwable {
		
		org.junit.Assert.assertEquals("before(before(before(before(last())))) == after(after(after(after(after(first())))))", true, T.before(T.before(T.before(T.before(T.last())))) == T.after(T.after(T.after(T.after(T.after(T.first()))))));
	}

	@org.junit.Test()
	@jug.TestName("set(first(), \"X\")")
	public void Test16() throws Throwable {
		
		org.junit.Assert.assertEquals("set(first(), \"X\")", (Object)("A"), (Object)(T.set(T.first(),"X")));
	}

	@org.junit.Test()
	@jug.TestName("set(first(), \"X\") (size())")
	public void Test17() throws Throwable {
		T.set(T.first(), "X");
		
		org.junit.Assert.assertEquals("set(first(), \"X\") (size())", (Object)(10), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("addAfter(after(first())), \"X\") (size)")
	public void Test18() throws Throwable {
		T.addAfter(T.after(T.first()), "X");
		
		org.junit.Assert.assertEquals("addAfter(after(first())), \"X\") (size)", (Object)(11), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("addAfter(after(first())), \"X\") (first four elements))")
	public void Test19() throws Throwable {
		T.addAfter(T.after(T.first()), "X");
		String[] test = {T.first().getElement(), T.after(T.first()).getElement(), T.after(T.after(T.first())).getElement(), T.after(T.after(T.after(T.first()))).getElement() }
		;
		String[] ans = {"A","b","X", "C"}
		;
		
		org.junit.Assert.assertArrayEquals("addAfter(after(first())), \"X\") (first four elements))", ans, test);
	}

	@org.junit.Test()
	@jug.TestName("addBefore(before(last()), \"X\") (size)")
	public void Test20() throws Throwable {
		T.addBefore(T.before(T.last()), "X");
		
		org.junit.Assert.assertEquals("addBefore(before(last()), \"X\") (size)", (Object)(11), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("addBefore(before(last()), \"X\") (last four elements)")
	public void Test21() throws Throwable {
		T.addBefore(T.before(T.last()), "X");
		String[] test = {T.before(T.before(T.before(T.last()))).getElement(), T.before(T.before(T.last())).getElement(), T.before(T.last()).getElement(), T.last().getElement() }
		;
		String[] ans = {"h","X","I", "j"}
		;
		
		org.junit.Assert.assertArrayEquals("addBefore(before(last()), \"X\") (last four elements)", ans, test);
	}

	@org.junit.Test()
	@jug.TestName("remove(after(after(first())))")
	public void Test22() throws Throwable {
		
		org.junit.Assert.assertEquals("remove(after(after(first())))", (Object)("C"), (Object)(T.remove(T.after(T.after(T.first())))));
	}

	@org.junit.Test()
	@jug.TestName("remove(after(after(first()))) (size())")
	public void Test23() throws Throwable {
		T.remove(T.after(T.after(T.first())));
		
		org.junit.Assert.assertEquals("remove(after(after(first()))) (size())", (Object)(9), (Object)(T.size()));
	}

	@org.junit.Test()
	@jug.TestName("remove(after(after(first()))) (first four elements)")
	public void Test24() throws Throwable {
		T.remove(T.after(T.after(T.first())));
		String[] test = {T.first().getElement(), T.after(T.first()).getElement(), T.after(T.after(T.first())).getElement(), T.after(T.after(T.after(T.first()))).getElement() }
		;
		String[] ans = {"A","b","d", "E"}
		;
		
		org.junit.Assert.assertArrayEquals("remove(after(after(first()))) (first four elements)", ans, test);
	}

}
