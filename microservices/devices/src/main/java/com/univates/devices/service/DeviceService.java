package com.univates.devices.service;

import java.util.List;

import com.univates.devices.model.Device;
import com.univates.devices.repository.DeviceRepository;

import org.springframework.stereotype.Service;

@Service
public class DeviceService {
    private final DeviceRepository deviceRepository;

    public DeviceService(DeviceRepository deviceRepository) {
        this.deviceRepository = deviceRepository;
    }

    public List<Device> getAll() {
        return deviceRepository.findAll();
    }

    public Device getById(long id) {
        return deviceRepository.findById(id).get();
    }

    public void save(Device a) {
        deviceRepository.save(a);
    }
}
