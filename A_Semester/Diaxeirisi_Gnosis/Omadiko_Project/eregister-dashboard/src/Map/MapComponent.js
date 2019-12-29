import React, { Component } from 'react';
import { Map, GoogleApiWrapper, Marker } from 'google-maps-react';
import { googleapi } from '../_keys/googleapi';

export class MapComponent extends Component {
    render() {
        const { values, handleChange } = this.props;
        return (
            <Map
                google={this.props.google}
                zoom={16}
                style={mapStyles}
                initialCenter={{ lat: 47.444, lng: -122.176}}
                >
                <Marker position={{ lat: 47.444, lng: -122.176}} />
            </Map>
        );

    }
}
export default GoogleApiWrapper({
    apiKey: googleapi.getgetApiKey()
  })(MapComponent);
const mapStyles = {
    width: '100%',
    height: '50%',
  }