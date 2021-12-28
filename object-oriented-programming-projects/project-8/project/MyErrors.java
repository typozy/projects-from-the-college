
public class MyErrors extends Exception{
	private int errType;
	public MyErrors(){}
	public MyErrors(int theErr){
		errType = theErr;
	}
	public void what(){
		switch (errType){
			case -1:
				System.err.println("You are out of range!\n");
				break;
			case -2:
				System.err.println("The collection is empty!\n");
				break;
		}
	}
}
