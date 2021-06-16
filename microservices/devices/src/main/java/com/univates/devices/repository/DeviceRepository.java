package com.univates.devices.repository;

import com.univates.devices.model.Device;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface DeviceRepository extends JpaRepository<Device, Long>{
    
}
