package com.univates.mqtt.controller;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.client.RestTemplate;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import com.univates.mqtt.Client;
import com.univates.mqtt.model.Device;

import org.springframework.boot.json.BasicJsonParser;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
@RequestMapping(value = "/mqtt")
public class MqttController {

    @PostMapping("publish")
    public void setControllerTemp(@RequestBody String data) {
        Map<String, Object> json = new BasicJsonParser().parseMap(data);

        Client.getIntance().publish( json.get( "ip" ) + "/controller", json.get( "temperature" ).toString() );
    }

    @GetMapping("refresh")
    public void refresh(){
		Client.getIntance().refresh();
    }
}
