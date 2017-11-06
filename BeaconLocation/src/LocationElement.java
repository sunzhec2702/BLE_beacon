
public class LocationElement {
	BeaconStation station;
	double distanceToStation;
	double lastRssi;
	double nowRssi;
	double finalRssi;
	
	final static int TX_POWER = -51;
	
	LocationElement(BeaconStation station, double lastRssi, double rssi) {
		this.station = station;
		this.lastRssi = lastRssi;
		this.nowRssi = rssi;
		this.finalRssi = this.applyIIRFilter(this.nowRssi, this.lastRssi);
		this.distanceToStation = this.rssiToDistance(this.finalRssi);
	}
	
	double applyIIRFilter(double nowRssi, double lastRssi) {
		// TODO: Apply a IIR filter later.
		return nowRssi;
	}
	
	public static double rssiToDistance(double rssi) {
		double distance = Math.pow(10, ((TX_POWER - rssi) / 20));
		//distance = Math.sqrt((Math.pow(distance, 2)) - Math.pow(this.station.z, 2));
		return distance;
	}
	
	public static double DistanceToRssi(double distance) {
		double rssi = TX_POWER - 20 * Math.log10(distance);
		return rssi;
	}
}
