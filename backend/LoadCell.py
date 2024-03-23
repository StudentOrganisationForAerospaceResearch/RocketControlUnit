from enum import Enum
import matplotlib.pyplot as plt
import json
import numpy as np

class CalLoadCell():
    class State(Enum):
        NORMAL = 0
        STORE = 1
        WAIT = 2

    def __init__(self, name="DefaultLoadCell") -> None:
        self.name = name
        self.load_cell = 0
        self.tare = 0
        self.slope = 1
        self.vol_offset = 0
        self.cal = False
        self.cal_points = {}
        self.mass = 0
        self.volts = 0
        self.txtval = 0
        self.current_state = self.State.NORMAL

    def reset(self):
        self.current_state = self.State.NORMAL

    def _collect_point(self, voltage, mass):
        self.current_state: self.State.NORMAL
        if not self.cal_points:
            self.cal_points = {0: voltage}
            self.vol_offset = voltage
        else:
            self.cal_points[mass] = voltage

    def _discard_cal(self, num=1):
        for i in range(num):
            self.cal_points.popitem()

    def _display(self):
        masses = list(self.cal_points.keys())
        voltages = list(self.cal_points.values())
        plt.scatter(voltages, masses, label='Calibration Points')
        plt.xlabel('Voltage')
        plt.ylabel('Mass')
        plt.title('Calibration Points and Linear Regression')
        if self.cal:
            x_values = [min(voltages), max(voltages)]
            y_values = [self.calc_weight(x) for x in x_values]
            plt.plot(x_values, y_values, color='red', label='Linear Regression')
        plt.legend()
        plt.show()

    def _store(self):
        with open("val.txt", 'w') as r:
            self.txtval = int(r.read()) + 1
            r.write(self.txtval)
        jsonValues = {
            "LoadCell": "f{self.name}+{self.txtval}",
            "Tare": self.tare,
            "Slope": self.slope,
            "Offset": self.vol_offset,}
        json_data = json.dumps(jsonValues, indent=1)
        with open("data.json", "w") as writer:
            writer.write(json_data)

    def _load(self):           
        with open("data.json" 'r') as reader:
            data = json.load(reader)
            self.name = data["LoadCell"]
            self.tare = data["tare"]
            self.slope = data["Slope"]
            self.vol_offset = data["Offset"]

    def cal_fin(self):
        masses = list(self.cal_points.keys())
        voltages = list(self.cal_points.values())
        mass_mean = sum(masses) / len(masses)
        voltage_mean = sum(voltages) / len(voltages)
        numerator = sum((mass - mass_mean) * (voltage - voltage_mean) for mass, voltage in zip(masses, voltages))
        denominator = sum((mass - mass_mean) ** 2 for mass in masses)
        slope = numerator / denominator
        self.slope = slope
        self.cal = True
        self.current_state = self.State.WAIT

    def _calc_weight(self, voltage):
        return (voltage - self.vol_offset) / self.slope
    
    def _cal_mass(self, mass):
        self.mass = mass
        self.current_state = self.State.STORE

    def cal_weight(self, input):
        if self.State == self.State.NORMAL:
            self._cal_mass(input)
        elif self.State == self.State.STORE:
            self._collect_point(input, self.mass)
        elif self.State == self.State.WAIT:
            self._calc_weight(input)
        



