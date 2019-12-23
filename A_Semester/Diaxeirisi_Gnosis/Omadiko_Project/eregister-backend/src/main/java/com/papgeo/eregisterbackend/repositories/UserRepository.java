package com.papgeo.eregisterbackend.repositories;

import com.papgeo.eregisterbackend.entities.UserEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface UserRepository extends JpaRepository<UserEntity,Integer> {
    Optional<UserEntity> findByUsername(String username);
    UserEntity findByEmail(String email);
    UserEntity findByUserId(Integer userId);

    @Query("SELECT user FROM UserEntity user WHERE user.username=:username")
    public UserEntity findByUsernameAuth(@Param("username") String username);
}
