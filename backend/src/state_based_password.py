from flask import Flask, jsonify
from flask_cors import CORS


app = Flask(__name__)
cors = CORS(app, methods=['GET'])
import os
import platform
system = platform.uname()

#this acquires the name of the usb we are looking for
def get_name_macos():

    os.chdir('/Volumes')
    # then do some listing
    List = os.listdir()
    i = 0
    while i < len(List):
        if (List[i] == 'Macintosh HD'):
            del List[i:i+1]
            continue
        else:
            if List[i] == "MASTER" or List[i] == "TESTER":
                return List[i]
            else:
                i = i +1
        return None

#using the name the first function returns we are able to locate the files in the usb by inputing our usb file path
#this gives us our path to the file so we can now read it
def list_files_in_usb_macos(usb_path):
    try:
        # Check if the provided path exists
        if not os.path.exists(usb_path):
            print(f"The path '{usb_path}' does not exist.")
            return

        # List all files and directories in the specified USB path
        for root, dirs, files in os.walk(usb_path):
            for file in files:
                if file == "test.txt":
                    return file
                else:
                    continue
            else:
                print("file not found")

    except Exception as e:
        print(f"An error occurred: {e}")
   
#This function reads the file at the directory path we gave
def read_file_from_usb(usb_file_path):
    try:
        with open(usb_file_path, 'r') as file:
            content = file.read()
            return content
    except FileNotFoundError:
        print(f"File not found: {usb_file_path}")
    except Exception as e:
        print(f"An error occurred: {e}")

def encrypt(text, shift):
    encrypted_text = ""
    for char in text:
        if char.isalpha():
            shift_base = ord('A') if char.isupper() else ord('a')
            encrypted_char = chr((ord(char) - shift_base + shift) % 26 + shift_base)
            encrypted_text += encrypted_char
        else:
            encrypted_text += char
    return encrypted_text

def find_specific_usb(volume_label):
    os_type = platform.system()
    
    if os_type == 'Windows':
        # Get all drives
        drives = [f"{chr(d)}:" for d in range(68, 91)]  # D-Z
        print(drives)
        for drive in drives:
            if os.path.exists(drive):
                # Check the volume label
                try:
                    import subprocess
                    label = subprocess.check_output(f'wmic logicaldisk where "DeviceID=\'{drive}\'" get VolumeName', shell=True).decode().strip().split("\n")[1]
                    if label.strip() == volume_label:
                        return drive
                except Exception as e:
                    print(f"Error getting volume label: {e}")
        else:
            print(f'{volume_label} is not found')

    return None
def read_files_from_usb(usb_path):
    try:
        for root, dirs, files in os.walk(usb_path):
            for file in files:
                file_path = os.path.join(root, file)
                if file_path.lower().endswith('.txt'):  # Check for text files
                    print(f"\nReading file: {file_path}")
                    with open(file_path, 'r', encoding='utf-8') as f:
                        content = f.read()
                        return content
                       
    except Exception as e:
        print(f"Error reading files: {e}")




@app.route('/message', methods=['GET']) 
def send():
    #This checks which os is being used by the user and calls the appropriate function
    if system[0] == "Darwin":
        usb_name = get_name_macos()
        #calls the files listing function
        try:
            if __name__ == "__main__":
                usb_drive_path ='/Volumes/'+usb_name
                list_files_in_usb_macos(usb_drive_path)
            #calls the read file method
            if __name__ == "__main__":

                usb_file_path = '/Volumes/'+ usb_name +'/' +  list_files_in_usb_macos(usb_drive_path) # Linux/macOS example
                password = read_file_from_usb(usb_file_path)
                key = encrypt(password, 3)
                return jsonify({'message': key})
                
        except TypeError:
            return jsonify({'message' : "usb drive not found"})

    elif system[0] == "WINDOWS":  
        if __name__ == "__main__":
            volume_label = "MASTER"
            usb_drive = find_specific_usb(volume_label)
    
            if usb_drive:
                print(f"USB Drive with label '{volume_label}' found at: {usb_drive}")
                password = read_files_from_usb(usb_drive)
                key = encrypt(password, 3)
                return jsonify({'message': key})
            else:
                print(f"No USB drive with label '{volume_label}' detected.")
app.run()
