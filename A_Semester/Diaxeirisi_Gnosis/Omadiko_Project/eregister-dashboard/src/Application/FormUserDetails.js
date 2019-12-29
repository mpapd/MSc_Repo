import React, { Component } from 'react';
import Dialog from '@material-ui/core/Dialog';
import AppBar from '@material-ui/core/AppBar';
import { ThemeProvider as MuiThemeProvider } from '@material-ui/core/styles'
import TextField from '@material-ui/core/TextField';
import Button from '@material-ui/core/Button';
import createMuiTheme from '@material-ui/core/styles/createMuiTheme';
import Autocomplete from '@material-ui/lab/Autocomplete';
import Checkbox from '@material-ui/core/Checkbox';
import CheckBoxOutlineBlankIcon from '@material-ui/icons/CheckBoxOutlineBlank';
import CheckBoxIcon from '@material-ui/icons/CheckBox';

const theme = createMuiTheme();
function searchDistrictEng(nameKey, myArray){
  for (var i=0; i < myArray.length; i++) {
      if (myArray[i].district === nameKey) {
          return myArray[i];
      }
  }
}
const icon = <CheckBoxOutlineBlankIcon fontSize="small" />;
const checkedIcon = <CheckBoxIcon fontSize="small" />;

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
      this.props.handler('townEng', resultObject.townEng);
      this.props.handler('town', resultObject.town);
      this.props.handler('districtEng', resultObject.districtEng);
      this.props.handler('district', resultObject.district);
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

            <TextField
              placeholder="Εισάγετε όνομα πατρός"
              label="Όνομα πατρός"
              onChange={handleChange('fathername')}
              defaultValue={values.fathername}
              margin="normal"
							fullWidth={true}
            />

            <TextField
              placeholder="Εισάγετε όνομα μητρός"
              label="Όνομα μητρός"
              onChange={handleChange('mothername')}
              defaultValue={values.mothername}
              margin="normal"
							fullWidth={true}
            />

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
            <TextField
              placeholder="Εισάγετε οδό"
              label="Οδός"
              onChange={handleChange('street')}
              defaultValue={values.street}
              margin="normal"
							fullWidth={true}
            />
        
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
          <Autocomplete
            multiple
            id="tags-foreignLanguages"
            options={foreignLanguages}
            getOptionLabel={option => option.language}
            filterSelectedOptions
            onChange={handleChange('foreignLanguage')}    
            renderInput={params => (
              <TextField
                {...params}
                variant="outlined"
                label="Ξένες Γλώσσες"
                placeholder="Επιλέξτε ξένες γλώσσες"
                fullWidth={true} 
              />
            )}
          />
          <br />
          <Autocomplete
            multiple
            id="tags-optionalClasses"
            options={optionalClasses}
            getOptionLabel={option => option.optionalClass}
            filterSelectedOptions
            onChange={handleChange('optionalClass')}    
            renderInput={params => (
              <TextField
                {...params}
                variant="outlined"
                label="Μαθήματα Επιλογής"
                placeholder="Επιλέξτε μαθήματα επιλογής"
                fullWidth={true} 
              />
            )}
          />
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

const foreignLanguages = [
  { language: 'Γερμανικά'},
  { language: 'Γαλλικά'},
];

const optionalClasses = [
  { optionalClass: 'Εικαστικά'},
  { optionalClass: 'Εφαρμογές Πληροφορικής'},
  { optionalClass: 'Γεωολογία και Διαχείριση Φυσικών Πόρων'},
  { optionalClass: 'Στοιχεία Θεατρολογίας'},
];