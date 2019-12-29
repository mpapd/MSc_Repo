import React, { Component } from 'react';
import Dialog from '@material-ui/core/Dialog';
import AppBar from '@material-ui/core/AppBar';
import { ThemeProvider as MuiThemeProvider } from '@material-ui/core/styles'
import TextField from '@material-ui/core/TextField';
import Button from '@material-ui/core/Button';
import createMuiTheme from '@material-ui/core/styles/createMuiTheme';
import Autocomplete from '@material-ui/lab/Autocomplete';

const theme = createMuiTheme();
function searchDistrictEng(nameKey, myArray){
  for (var i=0; i < myArray.length; i++) {
      if (myArray[i].district === nameKey) {
          return myArray[i];
      }
  }
}

export class FormUserDetails extends Component {

  continue = e => {
    e.preventDefault();
    if(this.props.values.firstname == '' ||
    this.props.values.lastname == '' ||
    this.props.values.birthdate == '' ||
    this.props.values.fathername == '' ||
    this.props.values.mothername == '' ||
    this.props.values.district == '' || 
    this.props.values.schoolType == '' 
    ){
        //TODO bgale kokkina    
    }
    else{
      //Setting english names
      var resultObject = searchDistrictEng(this.props.values.district, towns);
      this.props.handleEnglish('townEng', resultObject.townEng);
      this.props.handleEnglish('districtEng', resultObject.districtEng);
      this.props.nextStep();
    }
    
  };
  

  render() {
    const { values, handleChange } = this.props;
    return (
      <MuiThemeProvider theme={theme} >
        <React.Fragment>
          <Dialog 
            open={true}
            fullWidth={true}
            maxWidth='sm'
          >
            <div><h3>Εισαγωγή Στοιχείων Αιτούμενου</h3></div>
            <br />
            
            <TextField
              placeholder="Εισάγετε το όνομα"
              label="Όνομα"
              onChange={handleChange('firstname')}
              defaultValue={values.firstname}
              margin="normal"
							fullWidth={true}
            />
            <br />
            <TextField
              placeholder="Εισάγετε το επώνυμο"
              label="Επώνυμο"
              onChange={handleChange('lastname')}
              defaultValue={values.lastname}
              margin="normal"
							fullWidth={true}
            />
            <br />
            <TextField
              label="Ημερομηνία Γέννησης"
              type="date"
              defaultValue="2005-01-01"
              onChange={handleChange('birthdate')}
              defaultValue={values.birthdate}
              margin="normal"
              fullWidth={true}
              InputLabelProps={{
                shrink: true,
              }}
            />
            <br />
            <TextField
              placeholder="Εισάγετε όνομα πατρός"
              label="Όνομα πατρός"
              onChange={handleChange('fathername')}
              defaultValue={values.fathername}
              margin="normal"
							fullWidth={true}
            />
            <br />
            <TextField
              placeholder="Εισάγετε όνομα μητρός"
              label="Όνομα μητρός"
              onChange={handleChange('mothername')}
              defaultValue={values.mothername}
              margin="normal"
							fullWidth={true}
            />
            <br />
            <br />
            <Autocomplete
              id="combo-district"
              groupBy={option => option.town}
              options={towns}
              getOptionLabel={option => option.district}
              style={{ width: 300 }}
              renderInput={params => (
              <TextField {...params} 
                label="Πόλη" 
                variant="outlined" 
                fullWidth={true}
                onSelect={handleChange('district')}               
              />
              )}
            />
          
            <br />
            <br />
            <Autocomplete
              id="combo-schooltype"
              options={schoolType}
              getOptionLabel={option => option.type}
              style={{ width: 300 }}
              renderInput={params => (
              <TextField {...params} 
                label="Τύπος Σχολείου" 
                variant="outlined" 
                fullWidth={true}
                onSelect={handleChange('schoolType')}               
              />
              )}
            />
          
            <br />
            <br />
            <TextField
              placeholder="Εισάγετε σχόλια"
              label="Σχόλια"
              onChange={handleChange('comments')}
              defaultValue={values.comments}
              margin="normal"
              fullWidth={true}
              multiline={true}
              rows={2}
              rowsMax={4}
            />
            <br />
            <Button
              color="primary"
              variant="contained"
              onClick={this.continue}
            >Επομενο</Button>
          </Dialog>
        </React.Fragment>
      </MuiThemeProvider>
    );
  }
}

export default FormUserDetails;
const towns = [
  { district : 'Νεα Φιλαδέλφεια', districtEng: 'Nea Filadelfia', town: 'Αθήνα', townEng: 'Athens'},
  { district : 'Νεα Ιωνία', districtEng: 'Nea Ionia', town: 'Αθήνα', townEng: 'Athens'},
  { district : 'Άγιοι Ανάργυροι', districtEng: 'Agioi Anarguroi', town: 'Αθήνα', townEng: 'Athens'},
  { district : 'Καλαμαριά', districtEng: 'Kalamaria', town: 'Θεσσαλονίκη', townEng: 'Thessaloniki'},
  { district : 'Πυλαία', districtEng: 'Pulaia', town: 'Θεσσαλονίκη', townEng: 'Thessaloniki'},
  { district : 'Χαριλάου', districtEng: 'Harilaou', town: 'Θεσσαλονίκη', townEng: 'Thessaloniki'},
  { district : 'Νέο Φάληρο', districtEng: 'Neo Faliro', town: 'Πειραιάς', townEng: 'Piraeus'}
  
];

const schoolType = [
  { type: 'Γενικό Λύκειο', schoolTypeId : 1},
  { type: 'Μουσικό Λύκειο', schoolTypeId : 2},
  { type: 'Αθλητικό Λύκειο', schoolTypeId : 3},
  
];