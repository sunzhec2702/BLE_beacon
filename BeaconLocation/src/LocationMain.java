import java.util.ArrayList;
import java.util.List;

import org.apache.commons.math3.linear.RealMatrix;

public class LocationMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.print("Hello World\n");
		testData(5);
	}
	
	public static List<RssiInfo> createRssiInfos(double rssi) {
		List<RssiInfo> rssiInfos = new ArrayList<RssiInfo>();
		for (int i = 0; i < 30; i++) {
			RssiInfo info = new RssiInfo(2 * i, Math.round(rssi));
			rssiInfos.add(info);
		}
		return rssiInfos;
	}
	
	public static void testData(int stationNumber) {
		double beacon_x = (Math.random()) * 20 ; // -50 ~ 50
		double beacon_y = (Math.random()) * 20; // -50 ~ 50
		BeaconStation tmp = new BeaconStation(0,0,0);
		LocationElement tmpElement = new LocationElement(tmp, null);
		System.out.println("Real Data");
		System.out.println(beacon_x + ", " + beacon_y);
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
		for (int i = 0; i < 9; i++) {
			double x = stationPosition[i][0];
			double y = stationPosition[i][1];
			double distance = Math.sqrt(Math.pow(x - beacon_x, 2) + Math.pow(y - beacon_y, 2));
			BeaconStation station = new BeaconStation(x, y, 0);
			LocationElement element = new LocationElement(station, LocationMain.createRssiInfos(tmpElement.DistanceToRssi(distance)));
			elements.add(element);
		}

		LocationCalculator cal = new LocationCalculator(elements);
		RealMatrix result = cal.locationCalculate();
		if (result == null) {
			System.out.println("NULL result");
			return;
		}
		double[][] x = new double[2][1];
		x = result.getData();
		System.out.println("Calculated Data");
		System.out.println(x[0][0] + ", " +  x[1][0]);
		System.out.println("Distance diff");
		double diff_x = beacon_x - x[0][0];
		double diff_y = beacon_y - x[1][0];
		double diff = Math.sqrt(Math.pow(diff_x, 2) + Math.pow(diff_y, 2));
		System.out.println(diff);
	}
}
