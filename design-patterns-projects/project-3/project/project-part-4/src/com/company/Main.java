package com.company;
import java.io.IOException;
public class Main {

    public static void main(String[] args) throws IOException {
		Transform ft = new FourierTransform();
		Transform ct = new CosineTransform();
		ft.solve(args[0]);
		ct.solve(args[0]);
	}
}
