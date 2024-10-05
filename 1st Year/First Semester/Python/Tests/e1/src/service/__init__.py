import random
import math

class Service:
    _over : bool
    _year : int
    _starved : int
    _arrived : int
    _population : int
    _acres : int
    _harvest : int
    _eaten : int
    _price : int
    _stocks : int

    def __init__(self):
        """
            Create a game starting with the default values.
        """
        self._over = False
        self._year = 1
        self._starved = 0
        self._arrived = 0
        self._population = 100
        self._acres = 1000
        self._harvest = 3
        self._eaten = 200
        self._price = 20
        self._stocks = 2800

        random.seed()

    def checkBuyable(self, acres : int):
        # if buying
        if acres >= 0:
            if acres * self._price >= self._stocks:
                raise ValueError("You can not afford that many acres!")
        # if selling
        else:
            if -acres > self._acres:
                raise ValueError("You don't have that many acres to sell.")

    def checkFeedable(self, units : int):
        if units > self._stocks:
            raise ValueError("You don't have that much stocks to feed the people with.")

    def checkPlantable(self, acres : int):
        if acres > self._acres:
            raise ValueError("You can't plant acres that you do not possess.")
        if acres > self._stocks:
            raise ValueError("You can't plant grains that you do not possess.")

    def simulateYear(self, acresToBuy, unitsToFeed, acresToPlant):
        """
            Given the required parameters, try to advance the year.

            Eventual errors:
                - ValueError - Some of the input values can't be used in this context as they are not valid.
        """
        newState = Service()
        newState._year = self._year + 1
        
        # Step 1
        self.checkBuyable(acresToBuy)
        newState._acres = self._acres + acresToBuy
        newState._stocks = self._stocks - acresToBuy * self._price
        newState._price = random.randint(15, 25)

        # Step 2
        self.checkFeedable(unitsToFeed)
        newState._starved = self._population - unitsToFeed // 20
        if newState._starved <= 0:
            newState._arrived = random.randint(0, 10)
            newState._starved = 0
        newState._stocks -= (self._population - newState._starved) * 20
        newState._population = self._population - newState._starved + newState._arrived
        if newState._population <= self._population / 2:
            newState._over = True

        # Step 3
        newState.checkPlantable(acresToPlant)
        newState._harvest = random.randint(1, 6)
        newState._stocks += (newState._harvest - 1) * min(newState._population * 10, acresToPlant)
        
        # Step 4
        if random.random() <= 0.2:     # pragma: nocover
            newState._eaten = math.floor(random.random() * newState._stocks / 10)
        else:
            newState._eaten = 0
        newState._stocks -= newState._eaten

        # Pass everything on.
        self._over = newState._over
        self._year = newState._year
        self._starved = newState._starved
        self._arrived = newState._arrived
        self._population = newState._population
        self._acres = newState._acres
        self._harvest = newState._harvest
        self._eaten = newState._eaten
        self._price = newState._price
        self._stocks = newState._stocks

    @property
    def IsOver(self) -> bool:
        return self._over

    def checkWin(self) -> bool:
        if self._population < 100 or self._acres < 1000 or self._over:
            return False
        return True

    def __str__(self) -> str:   # pragma: nocover
        starvedString = f"In year { self._year }, { self._starved } people starved."
        arrivedString = f"{ self._arrived } people came to the city."
        populationString = f"City population is { self._population }."
        acresString = f"City owns { self._acres } acres of land."
        harvestString = f"Harvest was { self._harvest } units per acre."
        ratsString = f"Rats ate { self._eaten } units."
        landString = f"Land Price is { self._price } units per acre."
        stocksString = f"Grain stocks are { self._stocks } units."
        return f"{ starvedString }\n{ arrivedString }\n{ populationString }\n{ acresString }\n{ harvestString }\n{ ratsString }\n{ landString }\n{ stocksString }"