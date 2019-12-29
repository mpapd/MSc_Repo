import React, { Component } from 'react';
import Dialog from '@material-ui/core/Dialog';
import { ThemeProvider as MuiThemeProvider } from '@material-ui/core/styles'
import TextField from '@material-ui/core/TextField';
import Button from '@material-ui/core/Button';
import createMuiTheme from '@material-ui/core/styles/createMuiTheme';
import { userService } from '../_services';
import Autocomplete from '@material-ui/lab/Autocomplete';
import MapComponent from '../Map/MapComponent';
const theme = createMuiTheme();

function searchSchool(nameKey, myArray){
  for (var i=0; i < myArray.length; i++) {
      if (myArray[i].name === nameKey) {
          return myArray[i];
      }
  }
  return null;
}

export class FormPersonalDetails extends Component {
  
constructor(props) {
  super(props);

      this.state = {
        schools: null,
        schoolInfo: ''
    };
}

  componentDidMount() {
    //Get schools based on selected schoolType
    if(this.props.values.schoolType === "Γενικό Λύκειο"){
      userService.getSchools(this.props.values.townEng, this.props.values.districtEng).then(
        schoolsResponse => this.setState(({schools: schoolsResponse}))            
        );
    }
    else if(this.props.values.schoolType === "Μουσικό Λύκειο"){
      userService.getMusicSchools(this.props.values.townEng).then(
        schoolsResponse => this.setState(({schools: schoolsResponse}))            
        );
    }
    else if(this.props.values.schoolType === "Αθλητικό Λύκειο"){
      userService.getAthleticSchools(this.props.values.townEng).then(
        schoolsResponse => this.setState(({schools: schoolsResponse}))            
        );
    }
      

      
}

  continue = e => {
    e.preventDefault();
    this.props.nextStep();
  };

  back = e => {
    e.preventDefault();
    this.props.prevStep();
  };

  showSchoolInfo  = (event, values) => {
    if(event.target.value !== ''){
      var resultObject = searchSchool(event.target.value, this.state.schools);
      if(resultObject === null){
        this.setState({schoolInfo: ''});  
      }else{ 
        this.setState({schoolInfo: resultObject});
        this.props.handleSchoolId('schoolId', resultObject);
      }
      
    }
    
    
  };

  render() {
    const { values, handleChange } = this.props;
    return (
      <MuiThemeProvider theme={theme}>
        <React.Fragment>
        
        {(this.state.schools !== null)?(
              <div>
        <Dialog 
            open={true}
            fullWidth={true}
            maxWidth='sm'
          >
            
            <div><h4>Επιλέξτε {this.props.values.schoolType}</h4></div>
            <br />
            <Autocomplete
                id="combo-school"
                options={this.state.schools}
                getOptionLabel={option => option.name}
                style={{ width: 500 }}
                disableClearable
                onSelect={this.showSchoolInfo}     
                renderInput={params => (
                <TextField {...params} 
                  label="Λύκεια" 
                  variant="outlined" 
                  fullWidth={true}
                  onSelect={this.showSchoolInfo}    
                  
                />
                )}
              />


                <div>
                {(this.state.schoolInfo !== '')?(
                <div>    
                            <div className="card card-body bg-light"> 
                            
                                        
                                    <table className="table table-hover table-fixed">

                                    <thead>
                                    <tr>
                                        <th></th>
                                        <th>Πληροφορίες</th>
                                        
                                    </tr>
                                    </thead>

                                    <tbody>
                                    <tr>
                                        <th scope="row">Όνομα Σχολείου</th>
                                        <td>{this.state.schoolInfo.name}</td>
                                        
                                    </tr>
                                    <tr>
                                        <th scope="row">Περιοχή</th>
                                        <td>{this.state.schoolInfo.district}, {this.state.schoolInfo.town} </td>
                                        
                                    </tr>
                                    <tr>
                                        <th scope="row">Οδός</th>
                                        <td>{this.state.schoolInfo.street} </td>
                                        
                                    </tr>
                                    <tr>
                                        <th scope="row">Τηλέφωνο</th>
                                        <td>{this.state.schoolInfo.phone} </td>
                                        
                                    </tr>
                                    
                                    
                                    </tbody>

                                    </table>
                                        
                            </div> 
                            <div>
                              <MapComponent 
                                district={this.state.schoolInfo.district}
                                town={this.state.schoolInfo.town}
                                street={this.state.schoolInfo.street}
                              />
                            </div>
                            <br />   <br /> <br /> <br />  <br /><br /> <br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br />
                            
                        </div>
                        ): ''} 

                </div>
                  
                <br />                
                <br />
                <Button
                  color="primary"
                  variant="contained"
                  onClick={this.continue}
                  
                >ΕΠΟΜΕΝΟ</Button>
                <Button
                  color="secondary"
                  variant="contained"
                  onClick={this.back}
                >ΠΙΣΩ</Button>

                
            
          </Dialog>
          </div>
          ): ''}  
        </React.Fragment>
      </MuiThemeProvider>
    );
  }
}

export default FormPersonalDetails;
