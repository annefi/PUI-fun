
class swdata:
    from libacepy.swicsiondata import swicsiondata
    from libacepy.swepamdata import swepamdata
    from libacepy.mag import magdata

    def __init__(self,ionlist,swicsres,swepamres,magres,year,timeframe,path):
        self.ionlist=ionlist
        self.swicsres=swicsres
        self.magres=magres
        self.swepamres=swepamres
        self.year=year
        self.timeframe=timeframe
        self.path=path

    
