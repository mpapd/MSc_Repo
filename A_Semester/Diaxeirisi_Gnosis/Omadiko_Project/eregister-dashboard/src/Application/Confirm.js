import React, { Component } from 'react';
import Dialog from '@material-ui/core/Dialog';
import AppBar from '@material-ui/core/AppBar';
import { ThemeProvider as MuiThemeProvider } from '@material-ui/core/styles'
import { List, ListItem, ListItemText } from '@material-ui/core/';
import Button from '@material-ui/core/Button';
import createMuiTheme from '@material-ui/core/styles/createMuiTheme';
import { userService } from '../_services';
import { ButtonToolbar  } from 'reactstrap';

const theme = createMuiTheme();

export class Confirm extends Component {
  continue = e => {
    e.preventDefault();
    // PROCESS FORM //
    //TODO fetch post
    userService.saveApplication(this.props.values.firstname, this.props.values.lastname, this.props.values.fathername, this.props.values.mothername, 
      this.props.values.birthdate, this.props.values.town, this.props.values.townEng, this.props.values.district, this.props.values.districtEng, 
      this.props.values.street,this.props.values.foreignLanguage1,this.props.values.foreignLanguage2,this.props.values.optionalClass1,
      this.props.values.optionalClass2,this.props.values.school_id,this.props.values.comments).then(
      response=> this.props.nextStep()     
    );

    
  };

  back = e => {
    e.preventDefault();
    this.props.prevStep();
  };

  render() {
    const {
      values: { firstname,lastname,fathername,mothername,birthdate,town,townEng,district,districtEng,street,foreignLanguage1,foreignLanguage2,optionalClass1,optionalClass2,school_id,comments, schoolType, schoolObject  }
    } = this.props;
    return (
      <MuiThemeProvider theme={theme}>
        <React.Fragment>
          {/* <Dialog
            open={true}
            fullWidth={true}
            maxWidth='sm'
          > */}
          <div><h3>Σύνοψη Στοιχείων Αιτούμενου</h3></div>
            <br />
          <List>
            <ListItem>
              <ListItemText primary="Όνομα" secondary={firstname} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Επώνυμο" secondary={lastname} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Ημερομηνία Γέννησης" secondary={birthdate} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Όνομα Πατρός" secondary={fathername} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Όνομα Μητρός" secondary={mothername} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Κατοικία" secondary={street +', '+ district + ', ' + town} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Επιλεγμένο Σχολείο" secondary={schoolObject.name} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Ξένη Γλώσσα Επιλογής 1" secondary={foreignLanguage1} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Ξένη Γλώσσα Επιλογής 2" secondary={foreignLanguage2} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Μάθημα Επιλογής 1" secondary={optionalClass1} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Μάθημα Επιλογής 2" secondary={optionalClass2} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Σχόλια" secondary={comments} /> 
            </ListItem>
            
          </List>
          <br />
        
          <ButtonToolbar>
              <Button
                  color="secondary"
                  variant="contained"
                  onClick={this.back}
                  size="lg"
              >ΠΙΣΩ</Button>
              
              <Button
                variant="link"
                disabled
              ></Button>
              <Button
                color="primary"
                variant="contained"
                onClick={this.continue}
                size="lg"
              >Επομενο</Button>             
            </ButtonToolbar>
          {/* </Dialog> */}
        </React.Fragment>
      </MuiThemeProvider>
    );
  }
}

export default Confirm;
