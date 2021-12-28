

void LinkedListVec(){
	cout << "\n//LinkedList with vector<int>\n\n";
	LinkedList<int,vector<int> > con1;
	Queue<int,vector<int> > * colptr1 = &con1;
	Iterator<int,vector<int> > it;
	for (int i = 0; i < 100; ++i){
		colptr1->add(i);
	}
	LinkedList<int,vector<int> > con2;
	Queue<int,vector<int> > * colptr2 = &con2;
	for (int i = 50; i < 100; ++i){
		colptr2->add(i);
	}
	cout << "Before retaining the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->retainAll(*colptr2);
	cout << "After retaining:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		auto a = it.next();
		if (a >= 70 && a <80)
			it.remove();
	}
	cout << "After removing the elements between 70 and 80:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr1->addAll(*colptr2);
	cout << "After adding the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr2->clear();
	for (int i = 0; i < 100; ++i){
		colptr2->add(i);
	}
	cout << "Before removing the elements of other class:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr2->removeAll(*colptr1);
	cout << "After removing:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	int ifExist = 15;
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	ifExist = 60;
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	colptr1->clear();
	for (int i = 20; i < 40; ++i)
		colptr1->add(i);
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	for (int i = 40; i < 60; ++i)
		colptr1->add(i);
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	for (int i = 40; i < 60; ++i)
		colptr1->add(i);
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	cout << "Size of the container is " << colptr1->size() << ".\n\n";
	cout << "Elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->offer(61);
	colptr1->offer(62);
	colptr1->offer(63);
	colptr1->offer(64);
	colptr1->offer(65);
	cout << "After insertion, elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	cout << "The first element of the container is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->element() << ".\n\n";
}

void LinkedListVecStr(){
	cout << "\n//LinkedList with vector<string>\n\n";
	LinkedList<string,vector<string> > con1;
	Queue<string,vector<string> > * colptr1 = &con1;
	Iterator<string,vector<string> > it;
	colptr1->add("A");
	colptr1->add("B");
	colptr1->add("C");
	colptr1->add("D");
	colptr1->add("E");
	colptr1->add("F");
	colptr1->add("G");
	colptr1->add("H");
	colptr1->add("I");
	colptr1->add("J");
	LinkedList<string,vector<string> > con2;
	Queue<string,vector<string> > * colptr2 = &con2;
	colptr2->add("F");
	colptr2->add("G");
	colptr2->add("H");
	colptr2->add("I");
	colptr2->add("J");
	cout << "Before retaining the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->retainAll(*colptr2);
	cout << "After retaining:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		auto a = it.next();
		if (a == "H" || a == "I")
			it.remove();
	}
	cout << "After removing the elements H and I:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr1->addAll(*colptr2);
	cout << "After adding the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr2->clear();
	colptr2->add("A");
	colptr2->add("B");
	colptr2->add("C");
	colptr2->add("D");
	colptr2->add("E");
	colptr2->add("F");
	colptr2->add("G");
	colptr2->add("H");
	colptr2->add("I");
	colptr2->add("J");
	cout << "Before removing the elements of other class:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr2->removeAll(*colptr1);
	cout << "After removing:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	string ifExist = "D";
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	ifExist = "G";
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	colptr1->clear();
	colptr1->add("C");
	colptr1->add("D");
	colptr1->add("E");
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	colptr1->add("G");
	colptr1->add("H");
	colptr1->add("I");
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	colptr1->add("A");
	colptr1->add("B");
	colptr1->add("C");
	colptr1->add("D");
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	cout << "Size of the container is " << colptr1->size() << ".\n\n";
	cout << "Elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->offer("E");
	colptr1->offer("F");
	colptr1->offer("G");
	cout << "After insertion, elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	cout << "The first element of the container is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->element() << ".\n\n";
}


void LinkedListList(){
	cout << "\n//LinkedList with list<int>\n\n";
	LinkedList<int,list<int> > con1;
	Queue<int,list<int> > * colptr1 = &con1;
	Iterator<int,list<int> > it;
	for (int i = 0; i < 100; ++i){
		colptr1->add(i);
	}
	LinkedList<int,list<int> > con2;
	Queue<int,list<int> > * colptr2 = &con2;
	for (int i = 50; i < 100; ++i){
		colptr2->add(i);
	}
	cout << "Before retaining the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->retainAll(*colptr2);
	cout << "After retaining:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		auto a = it.next();
		if (a >= 70 && a <80)
			it.remove();
	}
	cout << "After removing the elements between 70 and 80:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr1->addAll(*colptr2);
	cout << "After adding the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr2->clear();
	for (int i = 0; i < 100; ++i){
		colptr2->add(i);
	}
	cout << "Before removing the elements of other class:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr2->removeAll(*colptr1);
	cout << "After removing:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	int ifExist = 15;
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	ifExist = 60;
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	colptr1->clear();
	for (int i = 20; i < 40; ++i)
		colptr1->add(i);
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	for (int i = 40; i < 60; ++i)
		colptr1->add(i);
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	for (int i = 40; i < 60; ++i)
		colptr1->add(i);
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	cout << "Size of the container is " << colptr1->size() << ".\n\n";
	cout << "Elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->offer(61);
	colptr1->offer(62);
	colptr1->offer(63);
	colptr1->offer(64);
	colptr1->offer(65);
	cout << "After insertion, elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	cout << "The first element of the container is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->element() << ".\n\n";
}

void LinkedListListStr(){
	cout << "\n//LinkedList with list<string>\n\n";
	LinkedList<string,list<string> > con1;
	Queue<string,list<string> > * colptr1 = &con1;
	Iterator<string,list<string> > it;
	colptr1->add("A");
	colptr1->add("B");
	colptr1->add("C");
	colptr1->add("D");
	colptr1->add("E");
	colptr1->add("F");
	colptr1->add("G");
	colptr1->add("H");
	colptr1->add("I");
	colptr1->add("J");
	LinkedList<string,list<string> > con2;
	Queue<string,list<string> > * colptr2 = &con2;
	colptr2->add("F");
	colptr2->add("G");
	colptr2->add("H");
	colptr2->add("I");
	colptr2->add("J");
	cout << "Before retaining the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->retainAll(*colptr2);
	cout << "After retaining:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		auto a = it.next();
		if (a == "H" || a == "I")
			it.remove();
	}
	cout << "After removing the elements H and I:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr1->addAll(*colptr2);
	cout << "After adding the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr2->clear();
	colptr2->add("A");
	colptr2->add("B");
	colptr2->add("C");
	colptr2->add("D");
	colptr2->add("E");
	colptr2->add("F");
	colptr2->add("G");
	colptr2->add("H");
	colptr2->add("I");
	colptr2->add("J");
	cout << "Before removing the elements of other class:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr2->removeAll(*colptr1);
	cout << "After removing:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	string ifExist = "D";
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	ifExist = "G";
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	colptr1->clear();
	colptr1->add("C");
	colptr1->add("D");
	colptr1->add("E");
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	colptr1->add("G");
	colptr1->add("H");
	colptr1->add("I");
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	colptr1->add("A");
	colptr1->add("B");
	colptr1->add("C");
	colptr1->add("D");
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	cout << "Size of the container is " << colptr1->size() << ".\n\n";
	cout << "Elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->offer("E");
	colptr1->offer("F");
	colptr1->offer("G");
	cout << "After insertion, elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	cout << "The first element of the container is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->element() << ".\n\n";
}


void LinkedListSet(){
	cout << "\n//LinkedList with set<int>\n\n";
	LinkedList<int,set<int> > con1;
	Queue<int,set<int> > * colptr1 = &con1;
	Iterator<int,set<int> > it;
	for (int i = 0; i < 100; ++i){
		colptr1->add(i);
	}
	LinkedList<int,set<int> > con2;
	Queue<int,set<int> > * colptr2 = &con2;
	for (int i = 50; i < 100; ++i){
		colptr2->add(i);
	}
	cout << "Before retaining the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->retainAll(*colptr2);
	cout << "After retaining:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		auto a = it.next();
		if (a >= 70 && a <80)
			it.remove();
	}
	cout << "After removing the elements between 70 and 80:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr1->addAll(*colptr2);
	cout << "After adding the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr2->clear();
	for (int i = 0; i < 100; ++i){
		colptr2->add(i);
	}
	cout << "Before removing the elements of other class:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr2->removeAll(*colptr1);
	cout << "After removing:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	int ifExist = 15;
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	ifExist = 60;
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	colptr1->clear();
	for (int i = 20; i < 40; ++i)
		colptr1->add(i);
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	for (int i = 40; i < 60; ++i)
		colptr1->add(i);
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	for (int i = 40; i < 60; ++i)
		colptr1->add(i);
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	cout << "Size of the container is " << colptr1->size() << ".\n\n";
	cout << "Elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->offer(61);
	colptr1->offer(62);
	colptr1->offer(63);
	colptr1->offer(64);
	colptr1->offer(65);
	cout << "After insertion, elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	cout << "The first element of the container is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->element() << ".\n\n";
}

void LinkedListSetStr(){
	cout << "\n//LinkedList with set<string>\n\n";
	LinkedList<string,set<string> > con1;
	Queue<string,set<string> > * colptr1 = &con1;
	Iterator<string,set<string> > it;
	colptr1->add("A");
	colptr1->add("B");
	colptr1->add("C");
	colptr1->add("D");
	colptr1->add("E");
	colptr1->add("F");
	colptr1->add("G");
	colptr1->add("H");
	colptr1->add("I");
	colptr1->add("J");
	LinkedList<string,set<string> > con2;
	Queue<string,set<string> > * colptr2 = &con2;
	colptr2->add("F");
	colptr2->add("G");
	colptr2->add("H");
	colptr2->add("I");
	colptr2->add("J");
	cout << "Before retaining the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->retainAll(*colptr2);
	cout << "After retaining:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		auto a = it.next();
		if (a == "H" || a == "I")
			it.remove();
	}
	cout << "After removing the elements H and I:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr1->addAll(*colptr2);
	cout << "After adding the elements of other class:\n";
	it = colptr1->iterator();
	while (it.hasNext())
		cout << it.next() << " ";
	cout << "\n\n";
	colptr2->clear();
	colptr2->add("A");
	colptr2->add("B");
	colptr2->add("C");
	colptr2->add("D");
	colptr2->add("E");
	colptr2->add("F");
	colptr2->add("G");
	colptr2->add("H");
	colptr2->add("I");
	colptr2->add("J");
	cout << "Before removing the elements of other class:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr2->removeAll(*colptr1);
	cout << "After removing:\n";
	it = colptr2->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	string ifExist = "D";
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	ifExist = "G";
	if (colptr2->contains(ifExist))
		cout << "This collection contains the element " << ifExist << ".\n\n";
	else
		cout << "This collection does not contain the element " << ifExist << ".\n\n";
	colptr1->clear();
	colptr1->add("C");
	colptr1->add("D");
	colptr1->add("E");
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	colptr1->add("G");
	colptr1->add("H");
	colptr1->add("I");
	if (colptr2->containsAll(*colptr1))
		cout << "This collection contains all the elements of other collection.\n\n";
	else
		cout << "This collection does not contain all the elements of other collection.\n\n";
	colptr1->clear();
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	colptr1->add("A");
	colptr1->add("B");
	colptr1->add("C");
	colptr1->add("D");
	if (colptr1->isEmpty())
		cout << "This collection is empty.\n\n";
	else
		cout << "This collection is not empty.\n\n";
	cout << "Size of the container is " << colptr1->size() << ".\n\n";
	cout << "Elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	colptr1->offer("E");
	colptr1->offer("F");
	colptr1->offer("G");
	cout << "After insertion, elements of the container are:\n";
	it = colptr1->iterator();
	while (it.hasNext()){
		cout << it.next() << " ";
	}
	cout << "\n\n";
	cout << "The first element of the container is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->poll() << ".\n\n";
	cout << "After removing the head, the first element is " << colptr1->element() << ".\n\n";
}