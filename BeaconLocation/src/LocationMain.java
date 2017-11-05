import java.util.ArrayList;
import java.util.List;

import org.apache.commons.math3.linear.RealMatrix;

public class LocationMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.print("Hello World\n");
		BeaconStation A = new BeaconStation(-1, 0, 0);
		BeaconStation B = new BeaconStation(0, 1, 0);
		BeaconStation C = new BeaconStation(1, 0, 0);
		LocationElement A1 = new LocationElement(A, 0, -51);
		LocationElement A2 = new LocationElement(B, 0, -51);
		LocationElement A3 = new LocationElement(C, 0, -51);
		System.out.println("A1 distance " + A1.distanceToStation);
		System.out.println("A2 distance " + A2.distanceToStation);
		System.out.println("A3 distance " + A3.distanceToStation);
		List<LocationElement> elements = new ArrayList<LocationElement>();
		elements.add(A1);
		elements.add(A2);
		elements.add(A3);
		LocationCalculator cal = new LocationCalculator(elements);
		RealMatrix result = cal.locationCalculate();
		double[][] x = new double[2][1];
		x = result.getData();
		System.out.println(x[0][0]);
		System.out.println(x[1][0]);
	}
}
