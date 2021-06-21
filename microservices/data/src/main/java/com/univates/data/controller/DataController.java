package com.univates.data.controller;

import java.util.Date;
import java.util.LinkedHashMap;
import java.util.List;

import com.univates.data.model.Data;
import com.univates.data.model.Device;
import com.univates.data.service.DataService;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(value = "data")
public class DataController {

    private DataService dataService;

    public DataController(DataService dataService) {
        this.dataService = dataService;
    }

    @PostMapping("save")
    public void save(@RequestBody LinkedHashMap<String, Object> d) {
        Data data = new Data();

        data.setDate(new Date(Long.parseLong(String.valueOf(d.get("date")))));
        data.setTemperature(Double.parseDouble(String.valueOf(d.get("temperature"))));
        data.setHumidity(Double.parseDouble(String.valueOf(d.get("humidity"))));

        Device device = new Device();
        device.setId(Long.parseLong(String.valueOf(((LinkedHashMap<String, Object>) d.get("device")).get("id"))));

        data.setDevice(device);

        dataService.save(data);
    }

    @GetMapping("getLatest")
    public Data getLatest(@RequestParam long deviceId ){
        Device device = new Device();
        
        device.setId( deviceId );

        return dataService.getLatest( device );
    }

    @GetMapping("getAll")
    public List<Data> getAll(@RequestParam long deviceId ){
        Device device = new Device();
        
        device.setId( deviceId );

        return dataService.getAll( device );
    }
}
