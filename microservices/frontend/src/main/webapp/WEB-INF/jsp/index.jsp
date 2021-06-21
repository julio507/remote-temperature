<!DOCTYPE html>
<html>

<head>
    <meta charset='utf-8'>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <title>Remote Temperature</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <link rel='stylesheet' type='text/css' media='screen' href='/css/main.css'>
</head>
<script>
    _selectedRow = null;

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

                        idField.value = this.value.id;
                        nameField.value = this.value.name;
                        ipField.value = this.value.ip;

                        if (_selectedRow != null) {
                            _selectedRow.setAttribute("class", null);
                        }

                        this.setAttribute("class", "selected");

                        _selectedRow = this;

                        http = new XMLHttpRequest();

                        http.open("GET", "/data/getLatest?deviceId=" + this.value.id);
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

                                else
                                {
                                    temperatureValue.innerHTML = "n/d";
                                    humidityValue.innerHTML = "n/d";
                                }
                            }
                        }
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

        value = {};

        value.id = idField.value;
        value.name = nameField.value;
        value.ip = ipField.value;

        http.onreadystatechange = function () {
            if (this.readyState == 4) {
                if (this.status == 200) {
                    clear();
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
        refresh();
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
        <div>
            <p>Sesores:</p>
            <div>
                <p>Temperatura:<span id="temperatureValue"></span></p>
                <p>Humidade:<span id="humidityValue"></span></p>
            </div>
        </div>
        <div>
            <p>Controles:</p>
        </div>
    </div>
</body>

</html>