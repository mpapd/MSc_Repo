import React, { Component } from 'react';
import Dialog from '@material-ui/core/Dialog';
import AppBar from '@material-ui/core/AppBar';
import { ThemeProvider as MuiThemeProvider } from '@material-ui/core/styles'
import Button from '@material-ui/core/Button';
import createMuiTheme from '@material-ui/core/styles/createMuiTheme';
import { history } from '../_helpers';
const theme = createMuiTheme();

export class Success extends Component {
  continue = e => {
    e.preventDefault();
    // PROCESS FORM //

    history.push('/');
  };

  back = e => {
    e.preventDefault();
    this.props.prevStep();
  };

  render() {
    return (
      <MuiThemeProvider theme={theme}> 
        <React.Fragment>
        <Dialog 
            open={true}
            fullWidth={true}
            maxWidth='sm'
          >
            <AppBar title="Success" />
            <h1>Επιτυχία Δημιουργία αίτησης</h1>
            <p>Θα ενημερωθείτε για την πρόοδο της αίτησης σας</p>
            <Button
            color="primary"
            variant="contained"
            onClick={this.continue}
          >ΣΥΝΕΧΕΙΑ</Button>
          </Dialog>
        </React.Fragment>
      </MuiThemeProvider>
    );
  }
}

export default Success;
