package com.univates.mqtt.controller;

import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

import com.univates.mqtt.Client;

import org.springframework.boot.json.BasicJsonParser;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
@RequestMapping(value = "/publish")
public class PublishController {

    @PostMapping("controller")
    public void setControllerTemp(@RequestBody String data) {
        Map<String, Object> json = new BasicJsonParser().parseMap(data);

        Client.getIntance().publish( json.get( "ip" ) + "/controller", json.get( "temperature" ).toString() );
    }
}
