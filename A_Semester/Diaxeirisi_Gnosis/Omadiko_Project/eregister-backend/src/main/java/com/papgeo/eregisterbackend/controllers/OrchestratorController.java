package com.papgeo.eregisterbackend.controllers;

import com.papgeo.eregisterbackend.components.ApplicationComponent;
import com.papgeo.eregisterbackend.components.SchoolComponent;
import com.papgeo.eregisterbackend.config.jwt.security.UserDetailsServiceImpl;
import com.papgeo.eregisterbackend.entities.ApplicantEntity;
import com.papgeo.eregisterbackend.entities.SchoolEntity;
import com.papgeo.eregisterbackend.entities.dao.ApplicationDAO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.web.bind.annotation.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.List;


@CrossOrigin
@RestController
@RequestMapping("/orchestrator")
public class OrchestratorController {
    private final Logger logger = LoggerFactory.getLogger(this.getClass());

    @Autowired
    private SchoolComponent schoolComponent;

    @Autowired
    private ApplicationComponent applicationComponent;

    @Autowired
    private UserDetailsServiceImpl userDetailsService;


    private ResponseEntity<?> response;

    @GetMapping("/schools/{town}/{district}")
    public ResponseEntity<?> getSchools(@PathVariable String town, @PathVariable String district, @RequestParam Integer category){

        try{
            List<SchoolEntity> schoolEntityList = schoolComponent.getSchoolsByCategoryAndDistrict(town,district,category);
            response = new ResponseEntity<>(schoolEntityList,HttpStatus.OK);
        }catch (Exception e){
            logger.error(e.getMessage(), e);
            response = new ResponseEntity<>(e.getMessage(),HttpStatus.INTERNAL_SERVER_ERROR);
        }

        return response;
    }

    @GetMapping("/schools/{town}")
    public ResponseEntity<?> getSpecialSchoolsByTown(@PathVariable String town, @RequestParam Integer type){
        try{

            List<SchoolEntity> schoolEntityList = schoolComponent.getSpecialSchoolsByTown(type,town);
            response = new ResponseEntity<>(schoolEntityList,HttpStatus.OK);
        }catch (Exception e){
            logger.error(e.getMessage(), e);
            response = new ResponseEntity<>(e.getMessage(),HttpStatus.INTERNAL_SERVER_ERROR);
        }

        return response;
    }

    @PostMapping("/application")
    public ResponseEntity<?> saveApplication(@RequestBody ApplicationDAO application){
        try{

            int userId = userDetailsService.findUserID(SecurityContextHolder.getContext().getAuthentication());
            applicationComponent.saveApplication(application,userId);
            response = new ResponseEntity<>(HttpStatus.OK);

        }catch (Exception e){
            logger.error(e.getMessage(), e);
            response = new ResponseEntity<>(e.getMessage(),HttpStatus.INTERNAL_SERVER_ERROR);
        }

        return response;
    }

    @GetMapping("/applications")
    public ResponseEntity<?> getApplications(){
        try{

            int userId = userDetailsService.findUserID(SecurityContextHolder.getContext().getAuthentication());

            response = new ResponseEntity<>(applicationComponent.getApplications(userId),HttpStatus.OK);

        }catch (Exception e){
            logger.error(e.getMessage(), e);
            response = new ResponseEntity<>(e.getMessage(),HttpStatus.INTERNAL_SERVER_ERROR);
        }

        return response;

    }

}
