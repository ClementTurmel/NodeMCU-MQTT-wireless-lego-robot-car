console.log("file mqttService.js imported !");

$( document ).ready(function() {
    //console.log( "ready!" );
    displayConnectionState(false);
});

function connectToMqttBroker(brokerIp, brokerPort, brokerLogin, brokerPwd){

  client = new Messaging.Client(brokerIp, parseInt(brokerPort), "myclientid_" + parseInt(Math.random() * 100, 10));

  // set callback handlers
  client.onConnectionLost = function (responseObject) {
      console.log("Connection Lost: "+responseObject.errorMessage);
      displayConnectionState(false);
  }
   
  client.onMessageArrived = function (message) {
    console.log("Message Arrived: "+message.payloadString);
  }
   
  // Called when the connection is made
  function onConnect(){
      console.log("Connected!");
      displayConnectionState(true);
  }
   
  // Connect the client, providing an onConnect callback
  client.connect({
      onSuccess: onConnect, 
      userName : brokerLogin,
      password : brokerPwd
  });
}
  
function sendThroughMqtt(topic, payload, qos){

  var message = new Messaging.Message(payload);
  message.destinationName = topic;
  message.qos = qos;
  client.send(message);
}