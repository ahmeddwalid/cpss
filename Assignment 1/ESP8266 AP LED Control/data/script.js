// ESP8266 LED Control JavaScript
// Handles dynamic UI updates and API communication

// Update LED status display
function updateStatus(led, status) {
    const statusElement = document.getElementById(`led${led}-status`);
    if (status) {
        statusElement.textContent = 'ON ✓';
        statusElement.className = 'on';
    } else {
        statusElement.textContent = 'OFF ✗';
        statusElement.className = 'off';
    }
}

// Control individual LED
function controlLED(ledNum, action) {
    fetch(`/led${ledNum}/${action}`)
        .then(response => response.json())
        .then(data => {
            updateStatus(1, data.led1);
            updateStatus(2, data.led2);
        })
        .catch(error => console.error('Error:', error));
}

// Control both LEDs
function controlBoth(action) {
    fetch(`/both/${action}`)
        .then(response => response.json())
        .then(data => {
            updateStatus(1, data.led1);
            updateStatus(2, data.led2);
        })
        .catch(error => console.error('Error:', error));
}

// Load initial status when page loads
function loadStatus() {
    fetch('/status')
        .then(response => response.json())
        .then(data => {
            updateStatus(1, data.led1);
            updateStatus(2, data.led2);
        })
        .catch(error => console.error('Error:', error));
}

// Load status when page is ready
document.addEventListener('DOMContentLoaded', loadStatus);