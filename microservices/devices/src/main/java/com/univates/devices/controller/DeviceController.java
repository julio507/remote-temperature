package com.univates.devices.controller;

import java.util.List;
import java.util.Map;

import com.univates.core.model.Device;
import com.univates.devices.service.DeviceService;

import org.springframework.boot.json.BasicJsonParser;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;

@RestController
@RequestMapping(path = "/devices")
public class DeviceController {
    private DeviceService deviceService;

    public DeviceController(DeviceService deviceService) {
        this.deviceService = deviceService;
    }

    @GetMapping("getAll")
    public List<Device> getAll() {
        return deviceService.getAll();
    }

    @PostMapping("update")
    public void update(@RequestBody String data) throws Exception {
        Map<String, Object> json = new BasicJsonParser().parseMap(data);

        Device d = new Device();

        if (json.get("name") == null || json.get("name").toString().isEmpty()) {
            throw new Exception("Campo Nome vazio");
        }

        if (json.get("ip") == null || json.get("ip").toString().isEmpty()) {
            throw new Exception("Campo IP vazio");
        }

        if (json.get("id") == null || json.get("id").toString().isEmpty()) {
            d.setId(0l);
        }

        else {
            d = deviceService.getById(Long.parseLong(json.get("id").toString()));
        }

        d.setName( json.get("name").toString() );
        d.setIp( json.get( "ip" ).toString() );

        deviceService.save(d);
    }
}
