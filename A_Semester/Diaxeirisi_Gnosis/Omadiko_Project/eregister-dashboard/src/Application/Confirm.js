import React, { Component } from 'react';
import Dialog from '@material-ui/core/Dialog';
import AppBar from '@material-ui/core/AppBar';
import { ThemeProvider as MuiThemeProvider } from '@material-ui/core/styles'
import { List, ListItem, ListItemText } from '@material-ui/core/';
import Button from '@material-ui/core/Button';
import createMuiTheme from '@material-ui/core/styles/createMuiTheme';
const theme = createMuiTheme();

export class Confirm extends Component {
  continue = e => {
    e.preventDefault();
    // PROCESS FORM //
    //TODO fetch post
    console.log("TEST\t" + this.props.values.firstName)
    this.props.nextStep();
  };

  back = e => {
    e.preventDefault();
    this.props.prevStep();
  };

  render() {
    const {
      values: { firstName, lastName, email, occupation, city, bio }
    } = this.props;
    return (
      <MuiThemeProvider theme={theme}>
        <React.Fragment>
          <Dialog
            open={true}
            fullWidth={true}
            maxWidth='sm'
          >
          <AppBar title="Confirm User Data" />
          <List>
            <ListItem>
              <ListItemText primary="First Name" secondary={firstName} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Last Name" secondary={lastName} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Email" secondary={email} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Occupation" secondary={occupation} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="City" secondary={city} /> 
            </ListItem>
            <ListItem>
              <ListItemText primary="Bio" secondary={bio} /> 
            </ListItem>
          </List>
          <br />
        
          <Button
            color="secondary"
            variant="contained"
            onClick={this.back}
          >Back</Button>

          <Button
            color="primary"
            variant="contained"
            onClick={this.continue}
          >Confirm & Continue</Button>
          </Dialog>
        </React.Fragment>
      </MuiThemeProvider>
    );
  }
}

export default Confirm;
