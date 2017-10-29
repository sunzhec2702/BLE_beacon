
class BEACON_LOCATION(object):
    station_info = None
    '''
    station info should be [[x,y,z],[x,y,z],[x,y,z]...]
    '''
    def __init__(self, station_info):
        self.station_info = station_info


    def look_up_helper(self, addr_str, timestamp, adv_index):
        distances = None

        return distances


    def calculate_beacon(self, addr_str, timestamp, adv_index):
        distances = self.look_up_helper(timestamp, adv_index)
