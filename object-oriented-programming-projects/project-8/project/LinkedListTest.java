
public class LinkedListTest {
	public static void Integer(){
		try{
			System.out.println("\n//LinkedList with Integer\n\n");
			LinkedList<Integer> con1 = new LinkedList<Integer>();
			Queue<Integer> colptr1 = con1;
			Iterator<Integer> it;
			for (int i = 0; i < 100; ++i)
				colptr1.add(i);
			LinkedList<Integer> con2 = new LinkedList<Integer>();
			Queue<Integer> colptr2 = con2;
			for (int i = 50; i < 100; ++i)
				colptr2.add(i);
			System.out.println("Before retaining the elements of other class:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%d ", it.next());
			System.out.println("\n\n");
			colptr1.retainAll(colptr2);
			System.out.println("After retaining:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%d ", it.next());
			System.out.println("\n\n");
			it = colptr1.iterator();
			while (it.hasNext()){
				int a = it.next();
				if (a >= 70 && a <80)
					it.remove();
			}
			System.out.println("After removing the elements between 70 and 79:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%d ", it.next());
			System.out.println("\n\n");
			colptr1.addAll(colptr2);
			System.out.println("After adding the elements of other class:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%d ", it.next());
			System.out.println("\n\n");
			colptr2.clear();
			for (int i = 0; i < 100; ++i)
				colptr2.add(i);
			System.out.println("Before removing the elements of other class:\n");
			it = colptr2.iterator();
			while (it.hasNext())
				System.out.printf("%d ", it.next());
			System.out.println("\n\n");
			colptr2.removeAll(colptr1);
			System.out.println("After removing:\n");
			it = colptr2.iterator();
			while (it.hasNext())
				System.out.printf("%d ", it.next());
			System.out.println("\n\n");
			int ifExist = 15;
			if (colptr2.contains(ifExist))
				System.out.printf("This collection contains the element %d.\n\n\n", ifExist);
			else
				System.out.printf("This collection does not contain the element %d.\n\n\n", ifExist);
			ifExist = 60;
			if (colptr2.contains(ifExist))
				System.out.printf("This collection contains the element %d.\n\n\n", ifExist);
			else
				System.out.printf("This collection does not contain the element %d.\n\n\n", ifExist);
			colptr1.clear();
			for (int i = 20; i < 40; ++i)
				colptr1.add(i);
			if (colptr2.containsAll(colptr1))
				System.out.println("This collection contains all the elements of other collection.\n\n");
			else
				System.out.println("This collection does not contain the elements of other collection.\n\n");
			colptr1.clear();
			for (int i = 40; i < 60; ++i)
				colptr1.add(i);
			if (colptr2.containsAll(colptr1))
				System.out.println("This collection contains all the elements of other collection.\n\n");
			else
				System.out.println("This collection does not contain the elements of other collection.\n\n");
			colptr1.clear();
			if (colptr1.isEmpty())
				System.out.println("This collection is empty.\n\n");
			else
				System.out.println("This collection is not empty.\n\n");
			for (int i = 40; i < 60; ++i)
				colptr1.add(i);
			if (colptr1.isEmpty())
				System.out.println("This collection is empty.\n\n");
			else
				System.out.println("This collection is not empty.\n\n");
			System.out.printf("Size of the container is %d.\n\n\n", colptr1.size());
			System.out.println("Elements of the container are:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%d ", it.next());
			System.out.println("\n\n");
			colptr1.offer(60);
			colptr1.offer(61);
			colptr1.offer(62);
			colptr1.offer(63);
			colptr1.offer(64);
			colptr1.offer(65);
			System.out.println("After insertion, elements of the container are:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%d ", it.next());
			System.out.println("\n\n");
			System.out.printf("The first element of the container is %d.\n\n\n", colptr1.poll());
			System.out.printf("After removing the head, the first element is %d.\n\n\n", colptr1.poll());
			System.out.printf("After removing the head, the first element is %d.\n\n\n", colptr1.poll());
			System.out.printf("After removing the head, the first element is %d.\n\n\n", colptr1.poll());
			System.out.printf("After removing the head, the first element is %d.\n\n", colptr1.element());
		}
		catch(MyErrors me){
			me.what();
		}
	}
	public static void String(){
		try{
			System.out.println("\n//LinkedList with String\n\n");
			LinkedList<String> con1 = new LinkedList<String>();
			Queue<String>  colptr1 = con1;
			Iterator<String> it;
			colptr1.add("A");
			colptr1.add("B");
			colptr1.add("C");
			colptr1.add("D");
			colptr1.add("E");
			colptr1.add("F");
			colptr1.add("G");
			colptr1.add("H");
			colptr1.add("I");
			colptr1.add("J");
			LinkedList<String> con2 = new LinkedList<String>();
			Queue<String>  colptr2 = con2;
			colptr2.add("F");
			colptr2.add("G");
			colptr2.add("H");
			colptr2.add("I");
			colptr2.add("J");
			System.out.println("Before retaining the elements of other class:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%s ", it.next());
			System.out.println("\n\n");
			colptr1.retainAll(colptr2);
			System.out.println("After retaining:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%s ", it.next());
			System.out.println("\n\n");
			it = colptr1.iterator();
			while (it.hasNext()){
				String a = it.next();
				if (a.equals("H") || a.equals("I"))
					it.remove();
			}
			System.out.println("After removing the elements H and I:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%s ", it.next());
			System.out.println("\n\n");
			colptr1.addAll(colptr2);
			System.out.println("After adding the elements of other class:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%s ", it.next());
			System.out.println("\n\n");
			colptr2.clear();
			colptr2.add("A");
			colptr2.add("B");
			colptr2.add("C");
			colptr2.add("D");
			colptr2.add("E");
			colptr2.add("F");
			colptr2.add("G");
			colptr2.add("H");
			colptr2.add("I");
			colptr2.add("J");
			System.out.println("Before removing the elements of other class:\n");
			it = colptr2.iterator();
			while (it.hasNext())
				System.out.printf("%s ", it.next());
			System.out.println("\n\n");
			colptr2.removeAll(colptr1);
			System.out.println("After removing:\n");
			it = colptr2.iterator();
			while (it.hasNext())
				System.out.printf("%s ", it.next());
			System.out.println("\n\n");
			String ifExist = "D";
			if (colptr2.contains(ifExist))
				System.out.printf("This collection contains the element %s.\n\n\n", ifExist);
			else
				System.out.printf("This collection does not contain the element %s.\n\n\n", ifExist);
			ifExist = "G";
			if (colptr2.contains(ifExist))
				System.out.printf("This collection contains the element %s.\n\n\n", ifExist);
			else
				System.out.printf("This collection does not contain the element %s.\n\n\n", ifExist);
			colptr1.clear();
			colptr1.add("C");
			colptr1.add("D");
			colptr1.add("E");
			if (colptr2.containsAll(colptr1))
				System.out.println("This collection contains all the elements of other collection.\n\n");
			else
				System.out.println("This collection does not contain all the elements of other collection.\n\n");
			colptr1.clear();
			colptr1.add("G");
			colptr1.add("H");
			colptr1.add("I");
			if (colptr2.containsAll(colptr1))
				System.out.println("This collection contains all the elements of other collection.\n\n");
			else
				System.out.println("This collection does not contain all the elements of other collection.\n\n");
			colptr1.clear();
			if (colptr1.isEmpty())
				System.out.println("This collection is empty.\n\n");
			else
				System.out.println("This collection is not empty.\n\n");
			colptr1.add("A");
			colptr1.add("B");
			colptr1.add("C");
			colptr1.add("D");
			if (colptr1.isEmpty())
				System.out.println("This collection is empty.\n\n");
			else
				System.out.println("This collection is not empty.\n\n");
			System.out.printf("Size of the container is %s.\n\n\n", colptr1.size());
			System.out.println("Elements of the container are:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%s ", it.next());
			System.out.println("\n\n");
			colptr1.offer("E");
			colptr1.offer("F");
			colptr1.offer("G");
			System.out.println("After insertion, elements of the container are:\n");
			it = colptr1.iterator();
			while (it.hasNext())
				System.out.printf("%s ", it.next());
			System.out.println("\n\n");
			System.out.printf("The first element of the container is %s.\n\n\n", colptr1.poll());
			System.out.printf("After removing the head, the first element is %s.\n\n\n", colptr1.poll());
			System.out.printf("After removing the head, the first element is %s.\n\n", colptr1.element());
		}
		catch(MyErrors me){
			me.what();
		}
	}

}
