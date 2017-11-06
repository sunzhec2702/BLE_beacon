import java.util.ArrayList;
import java.util.List;

import org.apache.commons.math3.linear.RealMatrix;

public class LocationMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.print("Hello World\n");
		testData(3);
	}
	
	public static void testData(int stationNumber) {
		double beacon_x = (Math.random()) * 20 ; // -50 ~ 50
		double beacon_y = (Math.random()) * 20; // -50 ~ 50
		System.out.println("Real Data");
		System.out.println(beacon_x);
		System.out.println(beacon_y);
		// 20 * 20, 400 squar meters
		double stationPosition[][] = { 
			{0, 0},
			{10, 0},
			{20, 0},
			{0, 10},
			{10, 10},
			{20, 10},
			{0, 20},
			{10, 20},
			{20, 20},
		};

		List<LocationElement> elements = new ArrayList<LocationElement>();
		List<LocationElement> elementsInUse = new ArrayList<LocationElement>();
		for (int i = 0; i < 9; i++) {
			double x = stationPosition[i][0];
			double y = stationPosition[i][1];
			double distance = Math.sqrt(Math.pow(x - beacon_x, 2) + Math.pow(y - beacon_y, 2));
			BeaconStation station = new BeaconStation(x, y, 0);
			double rssi = Math.round(LocationElement.DistanceToRssi(distance) + (Math.random() - 0.7) * 10);
			System.out.println("before " + distance + " after " + LocationElement.rssiToDistance(rssi));
			LocationElement element = new LocationElement(station, 0 , rssi);
			if (LocationElement.rssiToDistance(rssi) < 15)
				elements.add(element);
			else
				System.out.println("Skip " + i);
		}
		
		for (int i1 = 0; i1 < elements.size(); i1++) {
			for (int j1 = i1 + 1; j1 < elements.size(); j1++) {
				for (int q1 = j1 + 1; q1 < elements.size(); q1++) {
					for (int p1 = q1 + 1; p1 < elements.size(); p1++) {
								elementsInUse.clear();
								elementsInUse.add(elements.get(i1));
								elementsInUse.add(elements.get(j1));
								elementsInUse.add(elements.get(q1));
								elementsInUse.add(elements.get(p1));
								LocationCalculator cal = new LocationCalculator(elementsInUse);
								RealMatrix result = cal.locationCalculate();
								if (result == null) {
									System.out.println("NULL result");
									continue;
								}
								double[][] x = new double[2][1];
								x = result.getData();
								/*
								System.out.println("Calculated Data");
								System.out.println(x[0][0]);
								System.out.println(x[1][0]);
								*/
								System.out.println("Distance diff");
								double diff_x = beacon_x - x[0][0];
								double diff_y = beacon_y - x[1][0];
								double diff = Math.sqrt(Math.pow(diff_x, 2) + Math.pow(diff_y, 2));
								System.out.println(diff);

					}
				}
			}
		}
		

		LocationCalculator cal = new LocationCalculator(elements);
		RealMatrix result = cal.locationCalculate();
		if (result == null) {
			System.out.println("NULL result");
			return;
		}
		double[][] x = new double[2][1];
		x = result.getData();
		/*
		System.out.println("Calculated Data ALL");
		System.out.println(x[0][0]);
		System.out.println(x[1][0]);
		*/
		System.out.println("Distance diff ALL");
		double diff_x = beacon_x - x[0][0];
		double diff_y = beacon_y - x[1][0];
		double diff = Math.sqrt(Math.pow(diff_x, 2) + Math.pow(diff_y, 2));
		System.out.println(diff);

	}
}
