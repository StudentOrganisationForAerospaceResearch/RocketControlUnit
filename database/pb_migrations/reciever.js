const { spawn } = require('child_process');
const path = require('path');

const pythonScriptPath = path.join(__dirname, '../../backend/src/state_based_password.py');
const pythonProcess = spawn('python', [pythonScriptPath]);
let recievedData ='';
let validation = '';

pythonProcess.stdout.on('data', (data) => {
    // Convert the Buffer data to a string
    const messageString = data.toString().trim();
    let decryptedText = "";
    let shift =3;
    for (let char of messageString) {
        if (/[a-zA-Z]/.test(char)) {
            const shiftBase = char === char.toUpperCase() ? 'A'.charCodeAt(0) : 'a'.charCodeAt(0);
            const decryptedChar = String.fromCharCode(((char.charCodeAt(0) - shiftBase - shift + 26) % 26) + shiftBase);
            decryptedText += decryptedChar;
        } else {
            decryptedText += char;
        }
    
    }
    recievedData = decryptedText;
   	

    console.log(`Received from Python: ${messageString}`);});

pythonProcess.stderr.on('data', (data) => {
    console.error(`Error from Python: ${data}`);
});

pythonProcess.on('close', (code) => {
    console.log(`Python process exited with code ${code}`);
});
function validate(password){	
	if(password == "MasterKey"){
		return "Master"
	}
	else if(password == "TesterKey"){
		return "Tester"
	}
	else{
		return "Denied"
	}
}
setTimeout(() => {
    validation = validate(recievedData);
    console.log(validation);	
}, 35);

