
    export async function getDecryption(messageString: string){
        let decryptedText = "";
        let shift =3;
        if(messageString == "usb drive not found"){
            return messageString;
        }
        for (let char of messageString) {
            if (/[a-zA-Z]/.test(char)) {
                const shiftBase = char === char.toUpperCase() ? 'A'.charCodeAt(0) : 'a'.charCodeAt(0);
                const decryptedChar = String.fromCharCode(((char.charCodeAt(0) - shiftBase - shift + 26) % 26) + shiftBase);
                decryptedText += decryptedChar;
            } else {
                decryptedText += char;
            }
        }
        return decryptedText;
    }
    export async function fetchPermission() {
        try {
            const response = await fetch('http://127.0.0.1:5000/message');
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            const data = await response.json();
            const serverResponse = data.permission; // Store the message
            return serverResponse; // Return the message
        } catch (error) {
            console.error('Error:', error);
        }
     }
     export async function fetchEmail() {
        try {
            const response = await fetch('http://127.0.0.1:5000/message');
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            const data = await response.json();
            const serverResponse = data.email; // Store the message
            return serverResponse; // Return the message
        } catch (error) {
            console.error('Error:', error);
        }
     }
     export async function fetchPassword() {
        try {
            const response = await fetch('http://127.0.0.1:5000/message');
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            const data = await response.json();
            const serverResponse = data.password; // Store the message
            return serverResponse; // Return the message
        } catch (error) {
            console.error('Error:', error);
        }
     }
        
       
   