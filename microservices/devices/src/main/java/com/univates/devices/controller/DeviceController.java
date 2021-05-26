package com.univates.devices.controller;

import java.util.List;

import com.univates.core.model.Device;
import com.univates.devices.service.DeviceService;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import lombok.extern.slf4j.Slf4j;

@RestController
@RequestMapping( path = "/devices")
@Slf4j
public class DeviceController {
    private DeviceService deviceService;

    public DeviceController(DeviceService deviceService) {
        this.deviceService = deviceService;
    }

    @GetMapping( "getAll" )
    public List<Device> getAll(){
        return deviceService.getAll();
    }
}
