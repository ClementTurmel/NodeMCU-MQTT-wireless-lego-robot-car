//console.log("file controller.js imported !");

//for reverse controlling
var isReversed=false;


function connect(){
  console.log( "connecting..." );
  var ip = $('#broker-ip').val();
  var port = $('#broker-port').val();
  var login = $('#broker-login').val();
  var pwd = $('#broker-password').val();
  
  //console.log(ip + "|" + port + "|" + login + "|" + pwd);
  connectToMqttBroker(ip, port, login, pwd);
}

  var previousPressedKey;

  $('html').keydown(function(e){
       //console.log(e.which);
       
       keyPressed = e.which;

       if(keyPressed != previousPressedKey){

       		previousPressedKey = keyPressed;

       		var strKeyPressed;

          switch(keyPressed){
       		case 38:
            	strKeyPressed = "up";
        		break;
    			case 40:
            strKeyPressed = "down";
        		break;
    		case 37:
            	strKeyPressed = "left";
        		break;	
    		case 39:
            	strKeyPressed = "right";
        		break;
          	case 32:
            	strKeyPressed = "space";
            	break;  	                 
          default:
          	console.log("not a arrow or spacebar");
       	  }

          //callAction(strKeyPressed); // normal mode
          callAction(strKeyPressed); // reverse mode
          lightUpButton(strKeyPressed);

       }else{
       		console.log("same key !");
       }

  });

  $('html').keyup(function(e){
    //$('.myButton:not(.unused)').css("background-color", "transparent");
    $('.myButton:not(.unused)').removeClass("myButtonDarkBlue"); 
    previousPressedKey = "";
    callAction("stop");     
  });
  
  $(document).ready(function() {
    // REVERSE MODE
    $('input[type=radio][name=options]').change(function() {
          if (this.id == 'normal') {
            isReversed=false;
          }
          else if (this.id == 'reverse') {
            isReversed=true;
          }
      });

    //UPDATE SPEED
    $('input[type=range]').on('input', function () {
      $(this).trigger('change');
      var robotSpeed = $(this).val();
      //console.log("range : " + robotSpeed);
      sendThroughMqtt("robot-lego-car-speed", robotSpeed, 0);

    });

  });

  function lightUpButton(button){
    //$('#'+button).css("background-color", "chartreuse");
    $('#'+button).addClass("myButtonDarkBlue");
  }

  function callAction(key){
  	console.log(key);
  	if("up" == key & isReversed){
  		key = "down";
  	}else if("down" == key & isReversed){
      key = "up";
    }

    sendThroughMqtt("robot-lego-car", key, 0);
  }

  function mouseClick(param){
    hold_trigger = $('#' + param);

    hold_trigger.mousedown(function(){
      //console.log("okkkkk !" + param);
      //lightUpButton(param);
      callAction(param);
    }).bind('mouseup', function() {
      //console.log("enddddd !" + param);
      callAction("stop");
    });

  }

  function displayConnectionState(state){
    if(state){ 
      //broker parameters
      $('#connection-state').text("connected !");
      $('#connection-state').removeClass("badge-secondary");
      $('#connection-state').addClass("badge-success");
      $('#broker-form').collapse('hide'); // hide connection to broker controls
      
      //Robot controls
      $('#controls-state').text("operational !");
      $('#controls-state').removeClass("badge-secondary");
      $('#controls-state').addClass("badge-success");
      $('#controls-form').collapse('show'); // show robot control form

    }else{
      //broker parameters
      $('#connection-state').text("not connected.");
      $('#connection-state').removeClass("badge-success");
      $('#connection-state').addClass("badge-secondary");
      $('#broker-form').collapse('show');
      
      //Robot controls
      $('#controls-state').text("connection needed");
      $('#controls-state').removeClass("badge-success");
      $('#controls-state').addClass("badge-secondary");
      $('#controls-form').collapse('hide');
    }
  }

  
  
