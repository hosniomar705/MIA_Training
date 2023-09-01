
#first we create character_stats (health,energy,shield)
class character_stats():
    #user should enter health,energy,shield for each character for more customization by default health=100,energy=500,shield=0)
    #we make them private so cant be accessed by the user
    def __init__(self,health=100,energy=500,shield=0):
        self._health = health
        self._energy = energy
        self._shield = shield
    #this fun we pass the damge to it so it will reduce the health of the character
    #but if the character has a shield we reduce damage dealed to the character
    def damage_taken(self,damage):
        self._health -= damage*(1-self._shield/100) 
    #here we can pass shield as a percentage ex(50) so when character take damage it will be reduce
    def set_shield(self,shield):
        self._shield = shield
    #when character choose to attack or defend we pass consumed_energy after each round ,reduce energy of this character
    def reduce_energy(self,consumed_energy):
        self._energy -= consumed_energy
    #this fun return character stats so we can know when character run out of energy or die (healt = 0)
    def return_stats(self):
        return [self._health,self._energy,self._shield]
    

#this is the first character gru
#i made 2 character with the same construction the only difference between them is the dictionaries 
class gru(character_stats):
    #first we pass health, energy and shield so we can controll it for each character like make one character tanky(with more health) and another one has more energy
    def __init__(self,health=100,energy=500,shield=0):
        super().__init__(health,energy,shield)
        self.__player_name = "gru"

        #this dictionaries define character weapons properties  
        self.__weapon_energy = {"Freeze Gun":50,"Electric Prod":88,"Mega Magnet":92,"Kalman Missile":120}
        self.__weapon_damage = {"Freeze Gun":11,"Electric Prod":18,"Mega Magnet":10,"Kalman Missile":20}
        self.__weapon_resources = {"Freeze Gun":1000,"Electric Prod":5,"Mega Magnet":3,"Kalman Missile":1}
        #this dictionaries define character shields properties
        self.__shield_energy = {"Energy-Projected BarrierGun":15,"Selective Permeability":40}
        self.__shield_saves = {"Energy-Projected BarrierGun":32,"Selective Permeability":80}
        self.__shield_resources = {"Energy-Projected BarrierGun":1000,"Selective Permeability":3}

    #pass weapon_type then it returns damage of this weapon if we dont have enough energy will return error message "not enough energy" and 
    #if we dont have enough resources will return error message "not enough resources"
    def weapons(self,weapon_type):

        if super().return_stats()[1] >= self.__weapon_energy[weapon_type]:
            if self.__weapon_resources[weapon_type] > 0:
                self.__weapon_resources[weapon_type] -= 1
                super().reduce_energy(self.__weapon_energy[weapon_type])
                return self.__weapon_damage[weapon_type]
            else:
                return "not enough resources"
        else:
            return "not enough energy"
    #pass shield_type then it returns sheild percentage of this shield if we dont have enough energy will return error message "not enough energy" and 
    #if we dont have enough resources will return error message "not enough resources"
    def shields(self,shield_type):
    
        if super().return_stats()[1] >= self.__shield_energy[shield_type]:
            if self.__shield_resources[shield_type] > 0:
                self.__shield_resources[shield_type] -= 1
                super().reduce_energy(self.__shield_energy[shield_type])
                return self.__shield_saves[shield_type]
            else:
                return "not enough resources"
        else:
            return "not enough energy"
    #return villain name
    def name(self):
        return self.__player_name
    #return available_weapons names
    def available_weapons(self):
        return self.__weapon_energy.keys()
    #return available_shields names
    def available_shields(self):
        return self.__shield_energy.keys()
    #return minimum energy this character needs to make a play
    def min_energy_to_play(self):
        x = min(list(self.__shield_energy.values())+ list(self.__weapon_energy.values()))
        return x


            
class vector(character_stats):
    #first we pass health, energy and shield so we can controll it for each character like make one character tanky(with more health) and another one has more energy
    def __init__(self,health,energy,shield=0):
        super().__init__(health,energy,shield)
        self.__player_name = "vector"

        #this dictionaries define character weapons properties 
        self.__weapon_energy = {"Laser Blasters":40,"Plasma Grenades":56,"Sonic Resonance Cannon":100}
        self.__weapon_damage = {"Laser Blasters":8,"Plasma Grenades":13,"Sonic Resonance Cannon":22}
        self.__weapon_resources = {"Laser Blasters":1000,"Plasma Grenades":8,"Sonic Resonance Cannon":3}
        #this dictionaries define character shields properties
        self.__shield_energy = {"Energy Net Trap":15,"Quantum Deflector":40}
        self.__shield_saves = {"Energy Net Trap":32,"Quantum Deflector":80}
        self.__shield_resources = {"Energy Net Trap":1000,"Quantum Deflector":3}

    #pass weapon_type then it returns damage of this weapon if we dont have enough energy will return error message "not enough energy" and 
    #if we dont have enough resources will return error message "not enough resources"
    def weapons(self,weapon_type):
          
        if super().return_stats()[1] >= self.__weapon_energy[weapon_type]:
            if self.__weapon_resources[weapon_type] > 0:
                self.__weapon_resources[weapon_type] -= 1
                super().reduce_energy(self.__weapon_energy[weapon_type])
                return self.__weapon_damage[weapon_type]
            else:
                return "not enough resources"
        else:
            return "not enough energy"
    #pass shield_type then it returns sheild percentage of this shield if we dont have enough energy will return error message "not enough energy" and 
    #if we dont have enough resources will return error message "not enough resources"
    def shields(self,shield_type):
    
        if super().return_stats()[1] >= self.__shield_energy[shield_type]:
            if self.__shield_resources[shield_type] > 0:
                self.__shield_resources[shield_type] -= 1
                super().reduce_energy(self.__shield_energy[shield_type])
                return self.__shield_saves[shield_type]
            else:
                return "not enough resources"
        else:
            return "not enough energy"
    #return villain name    
    def name(self):
        return self.__player_name
    #return available_weapons names
    def available_weapons(self):
        return self.__weapon_energy.keys()
    #return available_shields names
    def available_shields(self):
        return self.__shield_energy.keys()
    #return minimum energy this character needs to make a play
    def min_energy_to_play(self):
        x = min(list(self.__shield_energy.values())+ list(self.__weapon_energy.values()))
        return x

