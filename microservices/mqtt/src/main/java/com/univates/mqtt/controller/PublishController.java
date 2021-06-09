package com.univates.mqtt.controller;

import org.springframework.web.bind.annotation.RestController;

import com.univates.mqtt.Client;

import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;

@RestController
@RequestMapping(value = "/publish")
public class PublishController {

    @PostMapping("temp")
    public void setControllerTemp(@RequestBody String data) {
        Client.getIntance().publish("1.1.1.2/controller", "hello");
    }
}
