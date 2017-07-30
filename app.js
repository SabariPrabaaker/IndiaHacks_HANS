/*eslint-env node*/

//------------------------------------------------------------------------------
// node.js starter application for Bluemix
//------------------------------------------------------------------------------

// This application uses express as its web server
// for more info, see: http://expressjs.com
var express = require('express');

// cfenv provides access to your Cloud Foundry environment
// for more info, see: https://www.npmjs.com/package/cfenv
var cfenv = require('cfenv');

// create a new express server
var app = express();

// serve the files out of ./public as our main files
app.use(express.static('public'));

// get the app environment from Cloud Foundry


var serialPort = require("serialport");
serialPort.list(function (err, ports) {
  ports.forEach(function(port) {
    console.log(port.comName);
    console.log(port.pnpId);
    console.log(port.manufacturer);
  });
}); 

var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort('COM8', {baudrate: 9600}, false);
    

var collection = "list"






app.get('/', function (req, res) {
   var datathings = db[collection].find();
   res.send('Hello World'+ datathings);
})

serialPort.open(function (error) {
  if ( !error ) {
  console.log('open');
    serialPort.on('data', function(data) {
      console.log("data: "+data);
    });  
  } else {
    console.log('failed to open: '+error);
    
  }
}); 
app.get('/api', function (req, res){
   var direction = req.query.direction;
   //console.log('Received:"' + direction+'"');
   console.log(direction)
   serialPort.write(direction);
   
   //db[collection].insert({'pass':pass})
   res.send('Hello fam');
})

var server = app.listen(8081, function () {
  var host = server.address().address
  var port = server.address().port
  console.log("Example app listening at http://%s:%s", host, port)
})
