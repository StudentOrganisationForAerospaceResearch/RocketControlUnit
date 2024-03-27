# FILE: LoadCell.py
# BRIEF: This file contains functions that handle
#        loadcell calibration.

# General imports =================================================================================
from enum import Enum
import matplotlib.pyplot as plt
import json


# Class Definitions ===============================================================================
class CalLoadCell():
    class State(Enum):
        COLLECT_MASS = 0
        STORE_POINT = 1
        RETURN_WEIGHT = 2

    def __init__(self, name="DefaultLoadCell") -> None:
        self.name = name
        self.tare = 0
        self.slope = 1
        self.voltage_offset = 0
        self.calibration_points = []
        self.current_mass = 0
        self.is_calibrated = False
        self.current_state = self.State.COLLECT_MASS

    def reset(self):
        """
        Reset the state of the object to the default state.
        """
        self.current_state = self.State.COLLECT_MASS

    def _collect_point(self, voltage:float, mass:float):
        """
        Collect a calibration point with the given voltage and mass.

        Parameters:
        - voltage (float): The voltage reading for the calibration point.
        - mass (float): The corresponding mass for the calibration point.
        """
        self.current_state = self.State.COLLECT_MASS
        if not self.calibration_points:
            self.voltage_offset = voltage
        self.calibration_points.append((mass, voltage))

    def _discard_cal(self, num=1):
        """
        Discard the specified number of calibration points.

        Parameters:
        - num (int): The number of calibration points to discard. Default is 1.
        """
        for i in range(num):
            self.calibration_points.popitem()

    def display(self):
        """
        Display a scatter plot of calibration points and, if available, the linear regression line.
        """
        masses = [x[0] for x in self.calibration_points]
        voltages = [x[1] for x in self.calibration_points]
        plt.scatter(voltages, masses, label='Calibration Points')
        plt.xlabel('Voltage')
        plt.ylabel('Mass')
        plt.title('Calibration Points and Linear Regression')
        if self.is_calibrated:
            x_values = [min(voltages), max(voltages)]
            y_values = [self._calibrated_weight(x) for x in x_values]
            plt.plot(x_values, y_values, color='red', label='Linear Regression')
        plt.legend()
        plt.show()

    def store(self):
        """
        Store calibration parameters and increment a value in a text file.
        """
        jsonValues = {
            f"{self.name}": {
                "Tare": self.tare,
                "Slope": self.slope,
                "Offset": self.voltage_offset
            }
        }
        json_data = json.dumps(jsonValues, indent=1)
        with open("data.json", "a") as writer:
            writer.write(json_data)

    def load(self):           
        """
        Load calibration parameters from a JSON file.
        """
        with open("data.json", 'r') as reader:
            data = json.load(reader)
            self.name = data["LoadCell"]
            self.tare = data["tare"]
            self.slope = data["Slope"]
            self.voltage_offset = data["Offset"]
        self.current_state = self.State.RETURN_WEIGHT

    def finalize(self):
        """
        Perform final calculations for calibration and update the object state.
        """
        masses = [x[0] for x in self.calibration_points]
        voltages = [x[1] for x in self.calibration_points]
        mass_mean = sum(masses) / len(masses)
        voltage_mean = sum(voltages) / len(voltages)
        numerator = sum((mass - mass_mean) * ((voltage) - voltage_mean) for mass, voltage in zip(masses, voltages))
        denominator = sum((mass - mass_mean) ** 2 for mass in masses)
        slope = numerator/ denominator
        self.slope = slope
        self.is_calibrated = True
        self.current_state = self.State.RETURN_WEIGHT

    def _calibrated_weight(self, voltage:float):
        """
        Calculate the calibrated weight based on the provided voltage reading.

        Parameters:
        - voltage (float): The voltage reading to be calibrated.

        Returns:
        - float: The calibrated weight corresponding to the voltage reading.
        """
        return (voltage - self.voltage_offset) * self.slope

    def calculate_weight(self, raw_reading:float):
        """
        Calculate the weight based on the raw reading.

        Parameters:
        - raw_reading (float): The raw reading obtained from the sensor.
        """
        if self.current_state == self.State.COLLECT_MASS:
            self.current_mass = raw_reading
            self.current_state = self.State.STORE_POINT
        elif self.current_state == self.State.STORE_POINT:
            self._collect_point(raw_reading, self.current_mass)
        elif self.current_state == self.State.RETURN_WEIGHT:
            print(self._calibrated_weight(raw_reading))



if __name__ == "__main__":
    # Instantiate a calibration load cell
    load_cell = CalLoadCell(name="MyLoadCell")

    # Test collecting calibration points
    load_cell.calculate_weight(0)  # Assuming a raw reading of 0
    load_cell.calculate_weight(0.1)  # Assuming a raw reading of 0
    load_cell.calculate_weight(0.5)  # Assuming a raw reading of 0.5
    load_cell.calculate_weight(0.4678)  # Assuming a raw reading of 0.5
    load_cell.calculate_weight(1.0)  # Assuming a raw reading of 1.0
    load_cell.calculate_weight(1.253)  # Assuming a raw reading of 1.0
    load_cell.calculate_weight(1.5)  # Assuming a raw reading of 1.5
    load_cell.calculate_weight(1.67)  # Assuming a raw reading of 1.5

    print(load_cell.calibration_points)
    print(load_cell.voltage_offset)

    # Finalize calibration
    load_cell.finalize()

    # test point for post calibration
    (load_cell.calculate_weight(2.23))

    # Display calibration points
    load_cell.display()