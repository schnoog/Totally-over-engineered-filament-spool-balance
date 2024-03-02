
const char PAGE_MAIN[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<title>ESPBalance - Filament weight and more</title>

  <style>
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .tabledata {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #000000;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #00AA00;
    }
    .tabledataneg {
      font-size: 24px;
      position: relative;
      padding-left: 5px;
      padding-top: 5px;
      height:   25px;
      border-radius: 5px;
      color: #000000;
      line-height: 20px;
      transition: all 200ms ease-in-out;
      background-color: #db3e22;
    }
    .tabledatabig {
      font-size: 72px;
      position: relative;
      padding-left: 5px;
      padding-top: 25px;
      height:   80px;
      border-radius: 5px;
      color: #000000;
      line-height: 50px;
      transition: all 200ms ease-in-out;
      background-color: #befeaa;
    }    
    .fanrpmslider {
      width: 30%;
      height: 55px;
      outline: none;
      height: 25px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #000000;
    }
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }
  
    .btn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
    }
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
    
  </style>

    <body style="background-color: #efefef" onload="process()">
    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">ESPBalance - Filament weight and more</div>
            <a href="/update">OTA-UPDATER</a>
                    </div>
            <button type="button" class="btn" onclick="fetchDataAndUpdateHTML();">Update</button>
      </div>
    </header>
  
    <main class="container" style="margin-top:70px">
      <div style="border-radius: 10px !important;">
        <table style="width:95%">
            <colgroup>
              <col span="1" style="background-color:rgb(230,230,230); width: 30%; color:#000000 ;">
              <col span="1" style="background-color:rgb(200,200,200); width: 30%; color:#000000 ;">
              <col span="1" style="background-color:rgb(200,200,200); width: 10%; color:#000000 ;">
              <col span="1" style="background-color:rgb(200,200,200); width: 20%; color:#000000 ;">
            </colgroup>
            <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
            <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
            <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
            <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
            <tr>
              <th colspan="1"><div class="heading">Sensor</div></th>
              <th colspan="1"><div class="heading">Data</div></th>
              <th colspan="1"><div class="heading">Pumps</div></th>
              <th colspan="1"><div class="heading">Humidity Control</div></th>
            </tr>
            <tr>
              <td><div class="bodytext">Temperature</div></td>
              <td><div class="tabledata" id="temp">12.2°C</div></td>
              <td><div class="bodytext">Pumps</div>
            
                <div class="tabledata" id="autoindi" onclick="switchpumpmode(this);">Auto</div>            
            
            </td>
              <td>Lower Limit: <table><td><div class="tabledata" id="minhum" onclick="newminhum(this);">58.5</div></td><td>%</td></table></td>
            </tr>
            <tr>
              <td><div class="bodytext">Humidity</div></td>
              <td><div class="tabledata" id="hum">57.8%</div></td>
              <td><div class="tabledata" id="pumpstate" onclick="togglepumps(this)">ON</div></td>
              <td>Upper Limit: <table><td><div class="tabledata" id="maxhum" onclick="newmaxhum(this);">61.1</div></td><td>%</td></tr></table></td>
            </tr>
            </table>  

      </div>

      <div style="border-radius: 10px !important;">
      <table style="width:95%">
      <colgroup>
        <col span="1" style="background-color:rgb(230,230,230); width: 50%; color:#000000 ;">
        <col span="1" style="background-color:rgb(200,200,200); width: 50%; color:#000000 ;">
      </colgroup>
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
      <tr>
        <th colspan="1"><div class="heading">Spool 1</div></th>
        <th colspan="1"><div class="heading">Spool 2</div></th>
      </tr>
      <tr>
        <td>
            <div class="tabledatabig" id="weightsp1">111g</div>
            <div class="tabledata" id="spoolsp1">245g</div>
            <button type="button" class = "btn" id = "tare1" onclick="tare(1,this);">Tare</button>
            <button type="button" class = "btn" id = "cali1" onclick="calibrate(1,this);">Calibrate</button>            
            <button type="button" class = "btn" id = "m4p1" onclick="spool(1,'m4p750g',this);">Material 4 Print 0.75kg</button>
            <button type="button" class = "btn" id = "over1" onclick="spool(1,'overture1000g',this);">Overture 1kg</button>
            <button type="button" class = "btn" id = "none1" onclick="spool(1,'none',this);">No spool</button>
        </td>
        <td>
            <div class="tabledatabig" id="weightsp2">222g</div>
            <div class="tabledata" id="spoolsp2">245g</div>
            <button type="button" class = "btn" id = "tare2" onclick="tare(2,this);">Tare</button>
            <button type="button" class = "btn" id = "cali2" onclick="calibrate(2,this);">Calibrate</button>            
            <button type="button" class = "btn" id = "m4p2" onclick="spool(2,'m4p750g',this);">Material 4 Print 0.75kg</button>
            <button type="button" class = "btn" id = "over2" onclick="spool(2,'overture1000g',this);">Overture 1kg</button>
            <button type="button" class = "btn" id = "none2" onclick="spool(2,'none',this);">No spool</button>

        </td>
      </tr>
      <tr>
        <th colspan="1"><div class="heading">Spool 3</div></th>
        <th colspan="1"><div class="heading">Spool 4</div></th>
      </tr>
      <tr>
        <td>
            <div class="tabledatabig" id="weightsp3">333g</div>
            <div class="tabledata" id="spoolsp3">245g</div>
            <button type="button" class = "btn" id = "tare3" onclick="tare(3,this);">Tare</button>
            <button type="button" class = "btn" id = "cali3" onclick="calibrate(3,this);">Calibrate</button>            
            <button type="button" class = "btn" id = "m4p3" onclick="spool(3,'m4p750g',this);">Material 4 Print 0.75kg</button>
            <button type="button" class = "btn" id = "over3" onclick="spool(3,'overture1000g',this);">Overture 1kg</button>
            <button type="button" class = "btn" id = "none3" onclick="spool(3,'none',this);">No spool</button>

        </td>
        <td>
            <div class="tabledatabig" id="weightsp4">444g</div>
            <div class="tabledata" id="spoolsp4">245g</div>
            <button type="button" class = "btn" id = "tare4" onclick="tare(4,this);">Tare</button>
            <button type="button" class = "btn" id = "cali4" onclick="calibrate(4,this);">Calibrate</button>            
            <button type="button" class = "btn" id = "m4p4" onclick="spool(4,'m4p750g',this);">Material 4 Print 0.75kg</button>
            <button type="button" class = "btn" id = "over4" onclick="spool(4,'overture1000g',this);">Overture 1kg</button>
            <button type="button" class = "btn" id = "none4" onclick="spool(4,'none',this);">No spool</button>

        </td>
      </tr>
      </table>
    </div>
    <br>

  </main>

  <footer div class="foot" id = "temp" >ESP32 Filament Balance</div></footer>
  
  </body>

<script>
    var BASEURL = "api"
    function togglepumps(ele){
        console.log("Togglepumps");
        var state = ele.innerHTML;
        if(state.trim().toUpperCase() === "ON"){

            url = BASEURL + "/pumps/0";
        }else{
            url = BASEURL + "/pumps/1";
        }
        callurl(url);

    }

    function switchpumpmode(ele){
        var state = ele.innerHTML;
        if(state.trim().toUpperCase() === "AUTO"){

            url = BASEURL + "/mancontrol"
        }else{
            url = BASEURL + "/autocontrol"
        }
        callurl(url);
    }

    function tare(BalanceNo,ele){
    var confirmation = confirm("Please ensure that the balance " + BalanceNo + " has no wight on it");
      if (confirmation) {
          url = BASEURL + "/tare/" + BalanceNo;
          callurl(url);
      }
    }

    function calibrate(BalanceNo, ele) {
        var confirmation = confirm("Please ensure that the balance " + BalanceNo + " is tared and place a 1000g weight on it");

        if (confirmation) {
            var url = BASEURL + "/calibrate/" + BalanceNo;
            callurl(url);
        }
    }

    function newminhum(ele){
        var tmp = "";
        ele.id.innerHTML
        let newhum = window.prompt("New Minimum Humidity",ele.innerHTML);
        if(!isNaN(newhum)){
            ele.innerHTML = newhum;
            url = BASEURL + "/minhum/" + newhum;
            callurl(url);
        }

    }
    function newmaxhum(ele){
        var tmp = "";
        ele.id.innerHTML
        let newhum = window.prompt("New Maximum Humidity",ele.innerHTML);
        if(!isNaN(newhum)){
            ele.innerHTML = newhum;
            url = BASEURL + "/maxhum/" + newhum;
            callurl(url);
        }
    }

    function spool(spoolno,stype,ele){
        var spooltara = document.getElementById("spoolsp" + spoolno).innerHTML;
        if(stype == "m4p750g") spooltara = 245;
        if(stype == "overture1000g") spooltara = 176;
        if(stype == "none") spooltara = 0;
        document.getElementById("spoolsp" + spoolno).innerHTML = spooltara + "g";
        url = BASEURL + "/emptyspool/" + spoolno + "/" + spooltara;
        callurl(url);
    }






    function callurl(url){
        console.log("Calling URL: " + url);
    makePlainTextRequest(url)
        .then(data => {
    // Do something with the received data
    })
    .catch(error => {
        alert('Request failed:', error);
    });
    }

    async function makePlainTextRequest(url) {
    try {
        const response = await fetch(url);
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        const data = await response.text();
        return data;
    } catch (error) {
        console.error('Error:', error);
        return null;
    }
    }



    async function makeRequest(url) {
    try {
        const response = await fetch(url);
        if (!response.ok) {
        throw new Error('Network response was not ok');
        }
        const data = await response.json();
        return data;
    } catch (error) {
        console.error('Error:', error);
        return null;
    }
    }

    function DebugFetch(){
        var mystring = '{"LoadCells":[{"Weight":-0.530525684,"WeightInG":-1,"TaraOffSet":0,"ConvFactor":0,"EmptySpool":220},{"Weight":0.007858722,"WeightInG":0,"TaraOffSet":0,"ConvFactor":0,"EmptySpool":0},{"Weight":482.4055176,"WeightInG":482,"TaraOffSet":0,"ConvFactor":0,"EmptySpool":0},{"Weight":-0.730652511,"WeightInG":-1,"TaraOffSet":0,"ConvFactor":0,"EmptySpool":0}],"Humidity":61.00683594,"Temperature":9.609999657,"MinHum":59.09999847,"MaxHum":60,"AutoControl":0,"PumpState":0}';
        fetchDataAndUpdateHTML(mystring);
    }


    function fetchDataAndUpdateHTML(responseString = null) {
    if (responseString) {
        updateHTMLWithResponse(responseString);
    } else {
        fetch('/api/data')
        .then(response => response.json())
        .then(data => {
            const jsonString = JSON.stringify(data);
            updateHTMLWithResponse(jsonString);
        })
        .catch(error => {
            console.error('Error fetching data:', error);
        });
    }
    }

    function updateHTMLWithResponse(responseString) {
    const data = JSON.parse(responseString);

    // Update WeightInG values
    for (let i = 0; i < data.LoadCells.length; i++) {
        const emptyspool = data.LoadCells[i].EmptySpool;
        const spid = "spoolsp" + (i+1);
        document.getElementById(spid).innerHTML = emptyspool + "g";

        var weightInG = data.LoadCells[i].WeightInG;
        const weightSpId = 'weightsp' + (i + 1);
        if(emptyspool > 0 ){
            var calcSpoolWeight = weightInG - emptyspool;
            document.getElementById(weightSpId).innerHTML = calcSpoolWeight + "g (Tared)";

            
        }else{
            document.getElementById(weightSpId).innerHTML = weightInG + "g";
        }

    }

    // Update Humidity and Temperature values
    const humidity = data.Humidity.toFixed(1);
    const temperature = data.Temperature.toFixed(1);
    var PumpState = parseInt(data.PumpState);
    var minhum = data.MinHum.toFixed(1);
    var maxhum = data.MaxHum.toFixed(1);
    var AI = parseInt(data.AutoControl);
    var lbl = "";
    var minhele = document.getElementById("minhum");
    minhele.innerHTML = minhum;

    var maxhele = document.getElementById("maxhum");
    maxhele.innerHTML = maxhum;

    var humele = document.getElementById('hum');
    var mclass = "tabledata";
    if(humidity > maxhum) mclass = "tabledataneg";
    humele.classList.remove("tabledata");
    humele.classList.remove("tabledataneg");
    humele.classList.add(mclass);

    var pumpStateElement = document.getElementById("pumpstate");
    document.getElementById('hum').innerHTML = humidity + "% RH";
    document.getElementById('temp').innerHTML = temperature + "°C";
    console.log("PumpState:", "++" + PumpState + "++"); // Add this line for debugging
    if(PumpState === 1){
        lbl = "ON";
        pumpStateElement.classList.remove("tabledataneg");
        pumpStateElement.classList.add("tabledata");

    }else{
        lbl = "OFF";
        pumpStateElement.classList.remove("tabledata");
        pumpStateElement.classList.add("tabledataneg");

    }
    document.getElementById("pumpstate").innerHTML = lbl;
    var autoindi = document.getElementById("autoindi");
    if(AI === 1){
        autoindi.innerHTML = "AUTO";
    }else{
        autoindi.innerHTML = "MANUAL";
    }


    }



    function process(){
        fetchDataAndUpdateHTML();
        setTimeout("process()",1000);
    }



</script>


</html>



)=====";