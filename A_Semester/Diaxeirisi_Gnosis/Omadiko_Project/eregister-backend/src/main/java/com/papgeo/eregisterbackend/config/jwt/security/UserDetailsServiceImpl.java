package com.papgeo.eregisterbackend.config.jwt.security;

import com.papgeo.eregisterbackend.entities.UserEntity;
import com.papgeo.eregisterbackend.repositories.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;

@Service
public class UserDetailsServiceImpl implements UserDetailsService {

    @Autowired
    UserRepository userRepository;

    @Override
    @Transactional
    public UserDetails loadUserByUsername(String username)
            throws UsernameNotFoundException {

        UserEntity user = userRepository.findByUsername(username)
                .orElseThrow(() ->
                        new UsernameNotFoundException("User Not Found with -> username or email : " + username)
                );


        UserPrinciple userPrinciple  = UserPrinciple.build(user);
        return userPrinciple;
    }

    public int findUserID(Authentication authentication) {

        UserPrinciple user = (UserPrinciple) authentication.getPrincipal();

        int userID = 0;

        if (user != null) {
            userID = user.getId().intValue();
        }

        return userID;

    }


}