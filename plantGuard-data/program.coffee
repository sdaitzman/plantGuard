SerialPort = require('serialport').SerialPort

serialPort = new SerialPort('/dev/tty.usbmodem1411', baudrate: 9600)

serialPort.on 'open', ->
	console.log 'serial connection established'
	serialPort.on 'data', (data) ->
		console.log 'data received from serial: ' + data
		return
	serialPort.write 'ls\n', (err, results) ->
		console.log 'err ' + err
		console.log 'results ' + results
		return
	return

console.log "hello world"
