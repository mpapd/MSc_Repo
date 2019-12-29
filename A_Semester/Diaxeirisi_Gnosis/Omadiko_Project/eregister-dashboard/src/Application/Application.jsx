import 'bootstrap/dist/css/bootstrap.min.css';
import React, { Component } from 'react';
import FormUserDetails from './FormUserDetails';
import FormPersonalDetails from './FormPersonalDetails';
import Confirm from './Confirm';
import Success from './Success';


class Application extends React.Component {
    state = {
        step: 1,
        firstname: '',
        lastname: '',
        fathername : '',
        mothername : '',
        birthdate : '',
        town : '',
        townEng : '',
        district : '',
        districtEng : '',
        street : '',
        foreignLanguage1 : '',
        foreignLanguage2 : '',
        optionalClass1 : '',
        optionalClass2 : '',
        school_id : 0,
        comments : '',
        schoolType : '',
        schoolObject : null
      };
    
      // Proceed to next step
      nextStep = () => {
        const { step } = this.state;
        this.setState({
          step: step + 1
        });
      };
    
      // Go back to prev step
      prevStep = () => {
        const { step } = this.state;
        this.setState({
          step: step - 1
        });
      };
    
      // Handle fields change
      handleChange = input => e => {
        if(input === 'foreignLanguage' && e !==null ){         
          var languageSplitted = e.target.outerHTML.split(" ");
          var furtherSplitted = languageSplitted[8].split(">")[1];
          if(typeof  furtherSplitted !== 'undefined'){
            var finalSplit = furtherSplitted.split("<")[0];
            if(this.state.foreignLanguage1 === ''){
              this.setState(({foreignLanguage1: finalSplit, foreignLanguage2: ''}));
            }
            else if(this.state.foreignLanguage2 === ''){
              if(finalSplit !== this.state.foreignLanguage1){
                this.setState(({foreignLanguage2: finalSplit}));
              }
              
            }
          }
          else{
            //Check type of undefined
            this.setState(({foreignLanguage1: '', foreignLanguage2: ''}));
          }

          console.log('foreignLanguage1 = ' + this.state.foreignLanguage1 +'\t'+'foreignLanguage2 = ' + this.state.foreignLanguage2);
          


        }
        else if(input === 'optionalClass' && e !==null ){
          var initialSplit = e.target.outerHTML.split(">");
          var finalSplit = initialSplit[1].split("<")[0];

          if(finalSplit !== ''){
            if(this.state.optionalClass1 === ''){
              this.setState(({optionalClass1: finalSplit, optionalClass2: ''}));
            }
            else if(this.state.optionalClass2 === ''){
              if(finalSplit !== this.state.optionalClass1){
                this.setState(({optionalClass2: finalSplit}));
              }
              
            }
          }
          else{
            //Check type of undefined
            this.setState(({optionalClass1: '', optionalClass2: ''}));
            
          }

          console.log('optionalClass1 = ' + this.state.optionalClass1 +'\t'+'optionalClass2 = ' + this.state.optionalClass2);
        }
        else{
          this.setState({ [input]: e.target.value });
        }
        
      };

      handler = (field, value) => {
        this.setState({ [field] : value  });
      };

      handleSchoolId = (field, value) => {
        this.setState({school_id : value.schoolId, schoolObject: value})
      };


    
      render() {
        const { step } = this.state;
        const { firstname,lastname,fathername,mothername,birthdate,town,townEng,district,districtEng,street,foreignLanguage1,foreignLanguage2,optionalClass1,optionalClass2,school_id,comments, schoolType, schoolObject } = this.state;
        const values = { firstname,lastname,fathername,mothername,birthdate,town,townEng,district,districtEng,street,foreignLanguage1,foreignLanguage2,optionalClass1,optionalClass2,school_id,comments, schoolType, schoolObject };
    
        switch (step) {
          case 1:
            return (
              <FormUserDetails
                nextStep={this.nextStep}
                handleChange={this.handleChange}
                handler={this.handler}
                values={values}
              />
            );
          case 2:
            return (
              <FormPersonalDetails
                nextStep={this.nextStep}
                prevStep={this.prevStep}
                handleChange={this.handleChange}
                handleSchoolId={this.handleSchoolId}
                values={values}
              />
            );
          case 3:
            return (
              <Confirm
                nextStep={this.nextStep}
                prevStep={this.prevStep}
                values={values}
              />
            );
          case 4:
            return <Success />;
        }
      }

}

export { Application };