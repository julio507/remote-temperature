package com.univates.data.service;

import java.util.List;

import com.univates.data.model.Data;
import com.univates.data.model.Device;
import com.univates.data.repository.DataRepository;

import org.springframework.stereotype.Service;

@Service
public class DataService {
    private final DataRepository dataRepository;

    public DataService(DataRepository dataRepository) {
        this.dataRepository = dataRepository;
    }

    public void save( Data d ){
        dataRepository.save( d );
    }

    public Data getLatest( Device device ){
        return dataRepository.getLatest( device );
    }

    public List<Data> getAll( Device device ){
        return dataRepository.getAll( device );
    }
}
