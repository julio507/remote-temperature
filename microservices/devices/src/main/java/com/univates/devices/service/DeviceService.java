package com.univates.devices.service;

import java.util.List;

import com.univates.core.model.Device;
import com.univates.core.repository.DeviceRepository;

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
}
