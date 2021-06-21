package com.univates.devices.model;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;

import org.dom4j.tree.AbstractEntity;

@Entity
public class Data extends AbstractEntity{
    @Id
    @GeneratedValue( strategy = GenerationType.IDENTITY )
    private Long id;
    private Date date;
    private Double temperature;
    private Double humidity;

    @ManyToOne
    @JoinColumn( name = "deviceId" )
    private Device device;

    public void setId(Long id) {
        this.id = id;
    }

    public Double getTemperature() {
        return temperature;
    }

    public void setTemperature(Double temperature) {
        this.temperature = temperature;
    }

    public Double getHumidity() {
        return humidity;
    }

    public void setHumidity(Double humidity) {
        this.humidity = humidity;
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }
}
