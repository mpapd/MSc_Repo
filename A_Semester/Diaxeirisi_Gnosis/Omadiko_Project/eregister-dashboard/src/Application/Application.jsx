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
        schoolType : ''
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
        this.setState({ [input]: e.target.value });
      };

      handleEnglish = (field, value) => {
        this.setState({ [field]: value  });
      };
    
      render() {
        const { step } = this.state;
        const { firstname,lastname,fathername,mothername,birthdate,town,townEng,district,districtEng,street,foreignLanguage1,foreignLanguage2,optionalClass1,optionalClass2,school_id,comments, schoolType } = this.state;
        const values = { firstname,lastname,fathername,mothername,birthdate,town,townEng,district,districtEng,street,foreignLanguage1,foreignLanguage2,optionalClass1,optionalClass2,school_id,comments, schoolType };
    
        switch (step) {
          case 1:
            return (
              <FormUserDetails
                nextStep={this.nextStep}
                handleChange={this.handleChange}
                handleEnglish={this.handleEnglish}
                values={values}
              />
            );
          case 2:
            return (
              <FormPersonalDetails
                nextStep={this.nextStep}
                prevStep={this.prevStep}
                handleChange={this.handleChange}
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