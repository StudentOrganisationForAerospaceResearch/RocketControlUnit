from enum import Enum
import matplotlib.pyplot as plt
import json
import numpy as np

class CalLoadCell():
    class State(Enum):
        NORMAL = 0
        STORE = 1
        RUN = 2

    def __init__(self, name="DefaultLoadCell") -> None:
        self.name = name
        self.load_cell = 0
        self.tare = 0
        self.slope = 1
        self.vol_offset = 0
        self.cal = False
        self.cal_points = {}
        self.volts = 0
        self.txtval = 0
        self.current_state = self.State.NORMAL

    def reset(self):
        self.current_state = self.State.NORMAL

    def collect_zero(self, voltage):
        self.current_state: self.State.STORE
        self.vol_offset = voltage
        self.cal_points = {0: voltage}

    def collect_point(self, voltage, mass):
        self.current_state = self.State.STORE
        self.cal_points[mass] = voltage

    def discard_cal(self, num=1):
        for i in range(num):
            self.cal_points.popitem()

    def display(self):
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

    def store(self):
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

    def load(self):           
        with open("data.json" 'r') as reader:
            data = json.load(reader)
            self.name = data["LoadCell"]
            self.tare = data["tare"]
            self.slope = data["Slope"]
            self.vol_offset = data["Offset"]

    def remove_outliers(self):
        # This is a test
        masses = list(self.cal_points.keys())
        voltages = list(self.cal_points.values())
        data = np.array(list(zip(masses, voltages)))
        z_scores = (data - np.mean(data, axis=0)) / np.std(data, axis=0)
        threshold = 1.0
        outliers = np.where(np.abs(z_scores) > threshold)[0]
        for idx in outliers:
            mass, voltage = data[idx]
            del self.cal_points[mass]
        self.calibrate()

    def calibrate(self):
        masses = list(self.cal_points.keys())
        voltages = list(self.cal_points.values())
        mass_mean = sum(masses) / len(masses)
        voltage_mean = sum(voltages) / len(voltages)
        numerator = sum((mass - mass_mean) * (voltage - voltage_mean) for mass, voltage in zip(masses, voltages))
        denominator = sum((mass - mass_mean) ** 2 for mass in masses)
        slope = numerator / denominator
        self.slope = slope
        self.cal = True
        self.current_state = self.State.RUN

    def calc_weight(self, voltage):
        return (voltage - self.vol_offset) / self.slope

    def run(self, voltage=None, mass=None, display=False):
        if voltage is None and mass is None and not self.cal:
            self.calibrate()
        else:
            if self.current_state == self.State.COLLECT_ZERO:
                self.collect_zero(voltage)
                print("Offset has been captured, awaiting further points")
            elif self.current_state == self.State.COLLECT_POINT:
                self.collect_point(voltage, mass)
                print("Point has been collected, awaiting next point.")
                self.current_state = self.State.COLLECT_POINT
            elif self.current_state == self.State.RETURN and self.cal and voltage is not None:
                return self.calc_weight(voltage)  # Change this to return elsewhere later as required
        if display:
            self.display()


