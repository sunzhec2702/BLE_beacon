import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collector;

public class LocationElement {
	BeaconStation station;
	double distanceToStation;
	double distanceToStationWithoutIIR;
	double finalRssi;
	
	final static int TX_POWER = -51;
	final static double IIR_INTERVAL = 30;
	
	LocationElement(BeaconStation station, List<RssiInfo> rssiList) {
		this.station = station;
		ComparatorRssi comparator = new ComparatorRssi();
		if (rssiList != null) {
			Collections.sort(rssiList, comparator);
			this.finalRssi = this.applyIIRFilter(rssiList);
			this.distanceToStation = this.rssiToDistance(this.finalRssi);
			this.distanceToStationWithoutIIR = this.rssiToDistance(rssiList.get(rssiList.size() - 1).rssi);
		}
	}
	
	void notUseIIR() {
		this.distanceToStation = this.distanceToStationWithoutIIR;
	}
	
	double applyIIRFilter(List<RssiInfo> rssiList) {
		if (rssiList == null) {
			return 0;
		}
		double lastRssi = rssiList.get(0).rssi;
		double lastTimeStamp = rssiList.get(0).timeStamp;
        for (int index = 1; index < rssiList.size(); index++) {
        	double currentTimeStamp = rssiList.get(index).timeStamp;
        	double currentRssi = rssiList.get(index).rssi;
        	double constValue = Math.exp(-1 * (currentTimeStamp - lastTimeStamp) / IIR_INTERVAL);
        	lastRssi = constValue * lastRssi + (1 - constValue) * currentRssi;
        	lastTimeStamp = currentTimeStamp;
        }
		return lastRssi;
	}
	
	public double rssiToDistance(double rssi) {
		double distance = Math.pow(10, ((TX_POWER - rssi) / 20));
		distance = Math.sqrt((Math.pow(distance, 2)) - Math.pow(this.station.z, 2));
		return distance;
	}
	
	public double DistanceToRssi(double distance) {
		double realDistance = Math.sqrt(Math.pow(distance, 2) + Math.pow(this.station.z, 2));
		return (TX_POWER - 20 * Math.log10(realDistance));
	}

	public class ComparatorRssi implements Comparator<RssiInfo>{
		@Override
		public int compare(RssiInfo arg0, RssiInfo arg1) {
			// TODO Auto-generated method stub
			if (arg0.timeStamp < arg1.timeStamp)
				return -1;
			if (arg0.timeStamp > arg1.timeStamp)
				return 1;
			else
				return 0;
		}
	}
}
