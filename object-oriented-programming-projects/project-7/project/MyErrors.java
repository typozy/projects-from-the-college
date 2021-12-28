
class MyErrors extends Exception{
	
	private int errType;
	
	MyErrors(){}
	MyErrors(int myErr){
		errType = myErr;
	}
	
	public void what(){
		switch (errType){
			case -1:
				System.err.println("The index you confirmed is out of range!\n");
				break;
			case -2:
				System.err.println("You cannot have a position with negative value!\n");
				break;
			case -3:
				System.err.println("You cannot construct a rectangle with a width length of less than 1!\n");
				break;
			case -4:
				System.err.println("You cannot construct a rectangle with a height length of less than 1!\n");
				break;
			case -5:
				System.err.println("You cannot construct a circle with a radius length of less than 1!\n");
				break;
			case -6:
				System.err.println("You cannot construct a triangle with an edge length of less than 1!\n");
				break;
			case -7:
				System.err.println("Increment and decrement methods does not work for any ComposedShape object!\n");
				break;
		}		
	}
}