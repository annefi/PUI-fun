from ace_pha import ace_pha

class aceswx_event(object):
    def __init__(self,d):
        self.d = d

    def set_std_mask(self):
        self.d.set_mask("H+","mq",0.8,1.3,reset=True)
        self.d.set_mask("sec_0","sec",0,0,reset=True)
        self.d.set_mask("sec_1","sec",1,1,reset=True)
        self.d.set_mask("sec_2","sec",2,2,reset=True)
        self.d.set_mask("sec_3","sec",3,3,reset=True)
        self.d.set_mask("sec_4","sec",4,4,reset=True)
        self.d.set_mask("sec_5","sec",5,5,reset=True)
        self.d.set_mask("sec_6","sec",6,6,reset=True)
        self.d.set_mask("sec_7","sec",7,7,reset=True)
        self.d.set_mask("sec_0","H+",applied=True)
        self.d.set_mask("sec_1","H+",applied=True)
        self.d.set_mask("sec_2","H+",applied=True)
        self.d.set_mask("sec_3","H+",applied=True)
        self.d.set_mask("sec_4","H+",applied=True)
        self.d.set_mask("sec_5","H+",applied=True)
        self.d.set_mask("sec_6","H+",applied=True)
        self.d.set_mask("sec_7","H+",applied=True)        

        self.d.set_mask("He2+","mq",1.8,2.3,reset=True)
        self.d.set_mask("He2+sec_0","sec",0,0,reset=True)
        self.d.set_mask("He2+sec_1","sec",1,1,reset=True)
        self.d.set_mask("He2+sec_2","sec",2,2,reset=True)
        self.d.set_mask("He2+sec_3","sec",3,3,reset=True)
        self.d.set_mask("He2+sec_4","sec",4,4,reset=True)
        self.d.set_mask("He2+sec_5","sec",5,5,reset=True)
        self.d.set_mask("He2+sec_6","sec",6,6,reset=True)
        self.d.set_mask("He2+sec_7","sec",7,7,reset=True)
        self.d.set_mask("He2+sec_0","He2+",applied=True)
        self.d.set_mask("He2+sec_1","He2+",applied=True)
        self.d.set_mask("He2+sec_2","He2+",applied=True)
        self.d.set_mask("He2+sec_3","He2+",applied=True)
        self.d.set_mask("He2+sec_4","He2+",applied=True)
        self.d.set_mask("He2+sec_5","He2+",applied=True)
        self.d.set_mask("He2+sec_6","He2+",applied=True)
        self.d.set_mask("He2+sec_7","He2+",applied=True)        
