<!DOCTYPE html>
<html>

<head>
    <meta charset='utf-8'>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <title>Remote Temperature</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <link rel='stylesheet' type='text/css' media='screen' href='/css/main.css'>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
</head>
<script>
    _selectedRow = null;

    refreshData = function (row) {
        http = new XMLHttpRequest();

        http.open("GET", "/data/getLatest?deviceId=" + row.value.id);
        http.setRequestHeader("Content-Type", "application/json");

        http.send();

        http.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {

                temperatureValue = document.getElementById("temperatureValue");
                humidityValue = document.getElementById("humidityValue");

                if (http.responseText) {
                    data = JSON.parse(http.responseText);

                    temperatureValue.innerHTML = data.temperature ? data.temperature : "n/d";
                    humidityValue.innerHTML = data.humidity ? data.humidity : "n/d";
                }

                else {
                    temperatureValue.innerHTML = "n/d";
                    humidityValue.innerHTML = "n/d";
                }
            }
        }

        http2 = new XMLHttpRequest();

        http2.open("GET", "data/getAll?deviceId=" + row.value.id);
        http2.setRequestHeader("Content-Type", "application/json");

        http2.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {

                chartData = JSON.parse(http2.responseText);

                var data = new google.visualization.DataTable();
                data.addColumn('datetime', 'Data');
                data.addColumn('number', 'Temperature');
                data.addColumn('number', 'Humidade');

                var options = {
                    'title': 'Dados',
                    'height': '100%',
                    'width': '100%',
                    'hAxis': {
                        'format': 'dd/MM/yy'
                    }
                };

                for (i = 0; i < chartData.length; i++) {
                    data.addRow([new Date(chartData[i].date), chartData[i].temperature, chartData[i].humidity]);
                }

                chart = new google.visualization.AreaChart(document.getElementById('graph'));
                chart.draw(data, options);
            }
        }

        http2.send();
    }

    refresh = function () {
        http = new XMLHttpRequest();
        http.open("GET", '/devices/getAll');

        http.setRequestHeader("Content-Type", "application/json");

        http.send();

        http.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                devices = JSON.parse(http.responseText);

                table = document.getElementById('dataTable').getElementsByTagName('tbody')[0];

                table.innerHTML = "";

                for (i = 0; i < devices.length; i++) {
                    row = table.insertRow(i);

                    row.innerHTML = "<td>" + devices[i].id + "</td>" +
                        "<td>" + devices[i].name + "</td>" +
                        "<td>" + devices[i].ip + "</td>";

                    row.value = devices[i];

                    row.onclick = function () {
                        idField = document.getElementById("idField");
                        nameField = document.getElementById("nameField");
                        ipField = document.getElementById("ipField");

                        temperatureInput = document.getElementById("temperatureInput");
                        statusInput = document.getElementById("statusInput");

                        idField.value = this.value.id;
                        nameField.value = this.value.name;
                        ipField.value = this.value.ip;

                        temperatureInput.value = this.value.temperature ? this.value.temperature : 0;
                        statusInput.innerHTML = (!this.value.temperature || this.value.temperature == 55 || this.value.temperature == 0) ? "Desligado" : "Ligado";

                        if (_selectedRow != null) {
                            _selectedRow.setAttribute("class", null);
                        }

                        this.setAttribute("class", "selected");

                        _selectedRow = this;

                        refreshData( this );
                    }

                    if (_selectedRow && _selectedRow.value.id == devices[i].id) {
                        row.onclick();
                    }
                }
            }
        }
    }

    clearFields = function () {
        idField = document.getElementById("idField");
        nameField = document.getElementById("nameField");
        ipField = document.getElementById("ipField");

        idField.value = null;
        nameField.value = null;
        ipField.value = null;

        _selectedRow = null;
    }

    send = function () {
        http = new XMLHttpRequest();

        http.open("POST", "/devices/update");

        http.setRequestHeader("Content-Type", "application/json");

        idField = document.getElementById("idField");
        nameField = document.getElementById("nameField");
        ipField = document.getElementById("ipField");
        temperatureInput = document.getElementById("temperatureInput");

        value = {};

        value.id = idField.value;
        value.name = nameField.value;
        value.ip = ipField.value;
        value.temperature = temperatureInput.value;

        http.onreadystatechange = function () {
            if (this.readyState == 4) {
                if (this.status == 200) {
                    refresh();
                }

                else if (this.status == 500) {
                    alert(JSON.parse(this.responseText).message);
                }
            }
        }

        http.send(JSON.stringify(value));
    }

    window.onload = function () {
        google.charts.load('current', { 'packages': ['corechart'] });

        refresh();

        document.getElementById("temperatureInput").oninput = function () {
            if (!this.value || this.value < 17 || this.value > 30) {
                this.style.backgroundColor = "red";
            }

            else {
                this.style.backgroundColor = "";
                http.open("POST", "/mqtt/publish");

                http.setRequestHeader("Content-Type", "application/json");

                value = {};

                value.ip = _selectedRow.value.ip;
                value.temperature = this.value;

                http.onreadystatechange = function () {
                    if (this.readyState == 4) {
                        if (this.status == 500) {
                            alert(JSON.parse(this.responseText).message);
                        }
                    }
                }

                http.send(JSON.stringify(value));

                send();
            }
        }

        document.getElementById("shutdownButton").onclick = function () {
            http.open("POST", "/mqtt/publish");

            http.setRequestHeader("Content-Type", "application/json");

            value = {};

            value.ip = _selectedRow.value.ip;
            value.temperature = 55;

            document.getElementById("temperatureInput").value = 0;

            http.onreadystatechange = function () {
                if (this.readyState == 4) {
                    if (this.status == 500) {
                        alert(JSON.parse(this.responseText).message);
                    }
                }
            }

            http.send(JSON.stringify(value));

            send();
        }

        window.setInterval(function () {
            if (_selectedRow) {
                refreshData( _selectedRow );
            }
        }, 5000);
    }
</script>

<body>
    <div id="left">
        <div id="form">
            <p>ID:</p><input id="idField" type="text" disabled="true">
            <p>Nome:</p><input id="nameField" type="text">
            <p>IP:</p><input id="ipField" type="text">
            <input value="Salvar" onclick="send()" type="button">
            <input value="Limpar" onclick="clearFields()" type="button">
        </div>
        <div>
            <table id="dataTable">
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Nome</th>
                        <th>IP</th>
                    </tr>
                </thead>
                <tbody>

                </tbody>
            </table>
        </div>
    </div>
    <div id="right">
        <div id="graph"></div>
        <div>
            <p>Sesores:</p>
            <div>
                <p>Temperatura:<span id="temperatureValue"></span></p>
                <p>Humidade:<span id="humidityValue"></span></p>
            </div>
        </div>
        <div>
            <p>Controles:</p>
            <p>Status:<span id="statusInput"></span></p>
            <p>Temperatura:<input id="temperatureInput" type="text" /></p>
            <input id="shutdownButton" type="button" value="Desilgar" />
        </div>
    </div>
</body>

</html>