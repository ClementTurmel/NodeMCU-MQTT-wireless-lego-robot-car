console.log("file imported !");

  var previousPressedKey;

  $('html').keydown(function(e){
       //console.log(e.which);
       
       keyPressed = e.which;

       if(keyPressed != previousPressedKey){

       		previousPressedKey = keyPressed;

       		switch(keyPressed){
       		case 38:
        		console.log("up");
            lightUpButton("up");
            move("up");
        		break;
    			case 40:
        		console.log("down");
            lightUpButton("down");
            move("down");
        		break;
    		 	case 37:
        		console.log("left");
            lightUpButton("left");
            move("left");
        		break;	
    		 	case 39:
        		console.log("right");
            lightUpButton("right");
            move("right");
        		break;
          case 32:
            console.log("space (fire)");
            lightUpButton("space");
            move("fire");
            //lightUpButton("space");
            break;  	                 
          default:
          	console.log("not a arrow or spacebar");
       	  }
       }else{
       		console.log("same key !");
       }
       
       
       
  });

  $('html').keyup(function(e){
    $('.myButton:not(.unused)').css("background-color", "transparent");  
    previousPressedKey = "";
    console.log("stop");
    move("stop");     
  });
  
  function lightUpButton(button){
    $('#'+button).css("background-color", "chartreuse");
  }

  function move(direction){
  	var ip = $('#ip').val();
    var url = "http://" + ip + "/"+ direction;
    console.log(url);
    $.ajax({url: url, success: function(result){
       //$("#div1").html(result);
    }});
  }
  
