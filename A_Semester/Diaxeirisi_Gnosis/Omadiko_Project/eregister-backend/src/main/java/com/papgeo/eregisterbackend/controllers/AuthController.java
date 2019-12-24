package com.papgeo.eregisterbackend.controllers;


import com.papgeo.eregisterbackend.config.jwt.JwtProvider;
import com.papgeo.eregisterbackend.entities.JwtResponse;
import com.papgeo.eregisterbackend.entities.UserEntity;
import com.papgeo.eregisterbackend.entities.dao.UserDAO;
import com.papgeo.eregisterbackend.repositories.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;

@CrossOrigin
@RestController
@RequestMapping("/api/auth")
public class AuthController {
    @Autowired
    AuthenticationManager authenticationManager;

    @Autowired
    UserRepository userRepository;

    @Autowired
    PasswordEncoder encoder;

    @Autowired
    JwtProvider jwtProvider;

    @PostMapping("/login")
    public ResponseEntity<?> authenticateUser(@Valid @RequestBody UserDAO loginRequest) {

        try{
            UserEntity user = userRepository.findByUsernameAuth(loginRequest.getUsername());
            if(user==null){
                user = userRepository.findByEmail(loginRequest.getEmail());
            }

            Authentication authentication = authenticationManager.authenticate(
                    new UsernamePasswordAuthenticationToken(
                            user.getUsername(),
                            loginRequest.getPassword()
                    ));

            SecurityContextHolder.getContext().setAuthentication(authentication);

            String jwt = jwtProvider.generateJwtToken(authentication);
            return ResponseEntity.ok(new JwtResponse(jwt));

        }catch(Exception e){
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }


    }

}
