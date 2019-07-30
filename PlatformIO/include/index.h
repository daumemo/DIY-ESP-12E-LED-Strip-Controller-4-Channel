const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
.device-card{
    width: 300px;
    height: auto;
    display: inline-block;
    left: 50%;
    top: 50%;
    position: absolute;
    transform: translate(-50%, -50%);
    margin-bottom: 5px;
}
@media (max-width:500px) {
	
	.control-main-icon-circle:focus, .control-main-icon-circle:active{
    	background: whitesmoke;
	}
	
	.control-main-button:focus, .control-main-button:active{
    	background: whitesmoke;
	}
}
@media (min-width:501px) {
	
	.control-main-icon-circle:hover{
    	background: whitesmoke;
	}
	
	.control-main-button:hover{
    	background: whitesmoke;
	}
	
    .device-control-extra.lock:hover {
        background: whitesmoke;
    }
}
.device-control-main{
    width: 100%;
    height: 204px;
    display: inline-block;
    position: relative;
    border-radius: 8px;
    box-shadow: 0 1px 3px 0 rgba(0, 0, 0, 0.4);
    background-color: white;
}
.device-control-extra{
    width: 80%;
    height: 48px;
    display: inline-block;
    position: relative;
    border-radius: 8px;
    box-shadow: 0 1px 3px 0 rgba(0, 0, 0, 0.4);
    text-align: center;
    background-color: white;
}
.device-control-extra.full {
    width: 100%;
}
.device-control-extra.lock {
    width: 19%;
    float: right;
    cursor: pointer;
}
.device-control-extra.lock.active {
    width: 19%;
    float: right;
    cursor: pointer;
    color:  rgb(255, 187, 61);
}
.control-slider{
    -webkit-appearance: none;
    width: 90%;
    height: 2px;
    background: linear-gradient(to right, rgb(40, 20, 0) , rgb(210, 150, 0) , rgb(255, 230, 0));
    opacity: 1;
    outline: none;
    position: absolute;
    top: 45%;
    left: 50%;
    transform: translate(-50%, -50%);
    
}
.control-slider::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 24px;
    height: 24px;
    border-radius: 12px;
    background-color: white;
    cursor: pointer;
    box-shadow: 0 0px 3px 0 rgba(0, 0, 0, 0.6);
}
.control-slider::-moz-range-thumb {
    width: 24px;
    height: 24px;
    border-radius: 12px;
    background-color: white;
    cursor: pointer;
    box-shadow: 0 0px 3px 0 rgba(0, 0, 0, 0.6);
}
.control-main-icon-circle{
    width: 120px;
    height: 120px;
    position: absolute;
    background: white;
    border-radius: 60px;
    cursor: pointer;
    box-shadow: 0 0px 3px 0 rgba(0, 0, 0, 0.6);
    left: 50%;
    top: 50%;
    transform: translate(-50%, -50%);
	-webkit-tap-highlight-color: transparent;
}
.control-main-button{
    width: 50%;
    height: 50%;
    position: absolute;
    overflow: hidden;
    cursor: pointer;
	-webkit-tap-highlight-color: transparent;
}
.button-shadow{
    position: absolute;
    margin: -60px;
    padding: 60px;
    border-radius: 50%;
}
.button1{
    left: 0;
    top: 0;
    border-right: solid 1px #ddd;
    border-bottom: solid 1px #ddd;
}
.button1-sh {
    right: 0px;
    bottom: 0px;
}
.button2{
    right: 0;
    top: 0;
    border-bottom: solid 1px #ddd;
}
.button2-sh {
    left: 0px;
    bottom: 0px;
}

.button3{
    left: 0;
    bottom: 0;
    border-right: solid 1px #ddd;
}
.button3-sh {
    right: 0px;
    top: 0px;
}

.button4{
    right: 0;
    bottom: 0;
}
.button4-sh {
    left: 0px;
    top: 0px;
}

.active-shadow {
    box-shadow: 0 0 30px  rgb(255, 187, 61);
}
.button-number{
    position: absolute;
    top:50%;
    transform: translate(-50%, -50%);
    font-family: Roboto, sans-serif;
    font-size: 26px;
    font-weight:normal ;
    color: lightgray;
    -webkit-user-select: none; /* Safari */        
    -moz-user-select: none; /* Firefox */
    -ms-user-select: none; /* IE10+/Edge */
    user-select: none;
}

.name{
    position: absolute;
    top:50%;
    left:50%;
    transform: translate(-50%, -50%);
    font-family: Roboto, sans-serif;
    font-size: 20px;
    font-weight:normal;
    color: lightgray;
    -webkit-user-select: none; /* Safari */        
    -moz-user-select: none; /* Firefox */
    -ms-user-select: none; /* IE10+/Edge */
    user-select: none;
}
.lock-name{
    position: absolute;
    top:50%;
    left:50%;
    transform: translate(-50%, -50%);
    font-family: Roboto, sans-serif;
    font-size: 20px;
    font-weight:normal;
    color: lightgray;
    -webkit-user-select: none; /* Safari */        
    -moz-user-select: none; /* Firefox */
    -ms-user-select: none; /* IE10+/Edge */
    user-select: none;
}
.lock-name.active{
    color: rgb(255, 210, 126);
}
.button-number.active{
    color: rgb(255, 210, 126);
}

.button-number.left{
    left:35%;
}

.button-number.right{
    left:63%;
}

body{
    background-color: whitesmoke;
}

.hidden{
    display:none;
}

</style>
</head>
<body>

<div class="device-card">
    <div class="device-control-extra full">
        <div class="name">LED Strip</div>
    </div>
    <div class="device-control-main">
        <div class="control-main-button button1" onclick="invertLampVal(0)">
            <div class="button-number left active">OFF</div>
            <div id="shadowLamp1" class="button-shadow button1-sh active-shadow"></div>
        </div>
        <div class="control-main-button button2" onclick="invertLampVal(1)">
            <div class="button-number right">OFF</div>
            <div id="shadowLamp2" class="button-shadow button2-sh active-shadow"></div>
        </div>
        <div class="control-main-button button3" onclick="invertLampVal(2)">
            <div class="button-number left">OFF</div>
            <div id="shadowLamp3" class="button-shadow button3-sh active-shadow"></div>
        </div>
        <div class="control-main-button button4" onclick="invertLampVal(3)">
            <div class="button-number right">OFF</div>
            <div id="shadowLamp4" class="button-shadow button4-sh active-shadow"></div>
        </div>
        <div class="control-main-icon-circle" onclick="invertGroupVal()"></div>
    </div>
    <div class="device-control-extra">
        <input class="control-slider" type="range" min="0" max="100" value="1">
    </div>
    <div class="device-control-extra lock" onclick="toggleLock(0)">
        <div class="lock-name">M</div>
    </div>
    <div class="device-control-extra">
        <input class="control-slider" type="range" min="0" max="100" value="1">
    </div>
    <div class="device-control-extra lock" onclick="toggleLock(1)">
        <div class="lock-name">M</div>
    </div>
    <div class="device-control-extra">
        <input class="control-slider" type="range" min="0" max="100" value="1">
    </div>
    <div class="device-control-extra lock" onclick="toggleLock(2)">
        <div class="lock-name">M</div>
    </div>
    <div class="device-control-extra">
        <input class="control-slider" type="range" min="0" max="100" value="1">
    </div>
    <div class="device-control-extra lock" onclick="toggleLock(3)">
        <div class="lock-name">M</div>
    </div>
</div>


<script>
    var lamps = [0,0,0,0];
    var lampsLastVal = [100,100,100,100];
    var groupLastVal = [100,100,100,100];
    var locks = [0,0,0,0];
    var slider1 = document.getElementsByClassName("control-slider")[0];
    var slider2 = document.getElementsByClassName("control-slider")[1];
    var slider3 = document.getElementsByClassName("control-slider")[2];
    var slider4 = document.getElementsByClassName("control-slider")[3];
    var output = document.getElementById("demo");
    var periodicCheck;
    
    function getDataFromServer()
    {
        var xmlhttp = new XMLHttpRequest();
        xmlhttp.onreadystatechange = function() {
            if (this.readyState == 4 && this.status == 200) {
            var myObj = JSON.parse(this.responseText);
            lamps[0] = parseInt(myObj.ch1);
            lamps[1] = parseInt(myObj.ch2);
            lamps[2] = parseInt(myObj.ch3);
            lamps[3] = parseInt(myObj.ch4);
            rewriteLockDataFromString(myObj.locks);
            updateView();
            }
    };
    
    xmlhttp.open("GET", "/channels");
    xmlhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xmlhttp.send();
    }

    function doStuff(){
        var xhr = new XMLHttpRequest();
        xhr.open('post', '/channels');
        xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
        xhr.send('ch1=' + lamps[0] + '&ch2=' + lamps[1] + '&ch3=' + lamps[2] + '&ch4=' + lamps[3] + '&locks=' + generateLockData());
    }

    function changeLockedSliders(toValue){
        for(var i = 0; i<locks.length; i++){
            if(locks[i]==1){
                lamps[i]=toValue;
            }
        }
    }

    function generateLockData(){
        var data = 0;
        for(var i=0; i<locks.length; i++){
            data+= locks[i]*Math.pow(2, i);
        }
        return data;
    }

    function rewriteLockDataFromString(dataString){
        var dataInteger = parseInt(dataString);
        for(var i = 0; i<locks.length; i++)
        {
            if ((dataInteger & (1<<i)) != 0)
            locks[i] = 1;
            else locks[i] = 0;
        }
    }

    slider1.oninput = function() {
        stopDataChecks()
        if(locks[0]==1){
            changeLockedSliders(this.value);
        }
        else lamps[0] = this.value;
        doStuff();
        updateView();
        startDataChecks();
    }

    slider2.oninput = function() {
        stopDataChecks();
        if(locks[1]==1){
            changeLockedSliders(this.value);
        }
        else lamps[1] = this.value;
        doStuff();
        updateView();
        startDataChecks();
    }

    slider3.oninput = function() {
        stopDataChecks();
        if(locks[2]==1){
            changeLockedSliders(this.value);
        }
        else lamps[2] = this.value;
        doStuff();
        updateView();
        startDataChecks();
    }

    slider4.oninput = function() {
        stopDataChecks();
        if(locks[3]==1){
            changeLockedSliders(this.value);
        }
        else lamps[3] = this.value;
        doStuff();
        updateView();
        startDataChecks();
    }

    function updateView(){
        for(var i = 0; i<lamps.length; i++)
        {
            if(lamps[i] > 0)
            {
                document.getElementsByClassName("button-shadow")[i].classList.add("active-shadow");
                document.getElementsByClassName("button-number")[i].classList.add("active");
                document.getElementsByClassName("button-number")[i].innerHTML = lamps[i] +"%";
            }
            else {
                document.getElementsByClassName("button-shadow")[i].classList.remove("active-shadow");
                document.getElementsByClassName("button-number")[i].classList.remove("active");
                document.getElementsByClassName("button-number")[i].innerHTML = "OFF";
            }

            document.getElementsByClassName("control-slider")[i].value = lamps[i];
        }

        for(var i = 0; i<locks.length; i++)
        {
            if(locks[i] == 0) document.getElementsByClassName("lock-name")[i].classList.remove("active");
            else document.getElementsByClassName("lock-name")[i].classList.add("active");
        }
    }
    function toggleLock(lockNo){
        if(locks[lockNo] == 0) locks[lockNo] = 1;
        else locks[lockNo] = 0;
        doStuff();
        updateView();
    }
    function invertLampVal(lamp){
        lamps[lamp] = -1;
        doStuff();
        getDataFromServer();
        updateView();
    }

    function invertGroupVal(){
        for (var i=0; i<lamps.length; i++){
            lamps[i] = -1;
        }
        doStuff();
        getDataFromServer();
        updateView();
    }

    function startDataChecks(){
        periodicCheck = setInterval(getDataFromServer, 2500);
    }

    function stopDataChecks(){
        clearInterval(periodicCheck);
    }

    getDataFromServer();
    startDataChecks();
</script>
</body>
</html>
)=====";