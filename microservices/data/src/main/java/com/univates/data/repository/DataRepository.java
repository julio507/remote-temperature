package com.univates.data.repository;

import org.springframework.stereotype.Repository;

import java.util.List;

import com.univates.data.model.Data;
import com.univates.data.model.Device;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

@Repository
public interface DataRepository extends JpaRepository<Data, Long> {

    @Query("select d from Data d where d.device = ?1 and d.date = ( "
            + " select max( d.date ) from Data d where d.device = ?1 ) ")
    Data getLatest(Device device);

    @Query( "select d from Data d where d.device = ?1" )
    List<Data> getAll( Device device );
}
