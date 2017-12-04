import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class NetworkDataProcessor {
	List<Integer> rssiList = new ArrayList<Integer>();
	List<RssiInfo> rssiInfos = new ArrayList<RssiInfo>();
	List<List<RssiInfo>> stationRssiInfos = new ArrayList<List<RssiInfo>>();
	Map<String, Map<Double, Integer>> stationTimeRssi = new HashMap<String, Map<Double, Integer>>();
	Map<String, Map<Double, Double>> stationTimeDistance = new HashMap<String, Map<Double, Double>>();

    public NetworkDataProcessor() {
    	StringBuffer stringBuffer = new StringBuffer();
    	String line = null ;
    	try {
    		BufferedReader br = new BufferedReader(new FileReader(new File("data/11-2/time.txt")));
	    	while( (line = br.readLine())!= null ){
	    		stringBuffer.append(line);
	    	} 
    	} catch (FileNotFoundException e) {
    	       e.printStackTrace();
    	} catch (IOException e) {
    		e.printStackTrace();
    	}
    	//将Json文件数据形成JSONObject对象
		try {
			JSONObject jsonObject = new JSONObject(stringBuffer.toString());
			JSONObject dataObject = jsonObject.getJSONObject("data");
			Iterator dataIt = dataObject.keys();
			while (dataIt.hasNext()) {
				String beaconMac = (String) dataIt.next();
				JSONObject beacons = dataObject.getJSONObject(beaconMac);
				Iterator beaconIt = beacons.keys();

				while (beaconIt.hasNext()) {
					double rssi_average = 0;
					String stationMac = (String) beaconIt.next();
					System.out.println(stationMac + stationMac + stationMac + stationMac);
					System.out.println(stationMac + stationMac + stationMac + stationMac);
					System.out.println(stationMac + stationMac + stationMac + stationMac);
					System.out.println(stationMac + stationMac + stationMac + stationMac);
					System.out.println(stationMac + stationMac + stationMac + stationMac);
					System.out.println(stationMac + stationMac + stationMac + stationMac);
					System.out.println(stationMac + stationMac + stationMac + stationMac);
					System.out.println(stationMac + stationMac + stationMac + stationMac);
					JSONArray stationData = beacons.getJSONArray(stationMac);
					Map timeRssi = new HashMap<Double, Integer>();
					Map timeDistance = new HashMap<Double, Integer>();
					for(int i=0;i<stationData.length();i++){
	                    JSONObject jsonobject = stationData.getJSONObject(i);  
	                    String rssi_now = (String) jsonobject.get("rssi");
	                    double time = jsonobject.getDouble("time");
	                    int b = Integer.parseInt(rssi_now, 16) + 0xFFFFFF00;
	                    RssiInfo info = new RssiInfo(time, b);
	                    this.rssiInfos.add(info);
	            		BeaconStation tmp = new BeaconStation(0,0,0);
	            		LocationElement tmpElement = new LocationElement(tmp, null);
	            		timeRssi.put(time, b);
	            		timeDistance.put(time, tmpElement.rssiToDistance(b));
	            		System.out.println(time + " " + tmpElement.rssiToDistance(b) + " " + b);
	                }

//					System.out.println(timeDistance);
//					System.out.println(timeRssi);
	                this.stationTimeRssi.put(stationMac, timeRssi);
	                this.stationTimeDistance.put(stationMac, timeDistance);
				}
			}
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
    }
}
