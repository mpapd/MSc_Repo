package com.papgeo.eregisterbackend.repositories;

import com.papgeo.eregisterbackend.entities.ApplicationEntity;
import com.papgeo.eregisterbackend.entities.UserEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface ApplicationRepository extends JpaRepository<ApplicationEntity, Integer> {
    List<ApplicationEntity> findByUsersByUserId(UserEntity userEntity);

}
